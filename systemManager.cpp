
#include "systemManager.h"
#include "stateMachine.h"
#include "keyboard.h"
#include "myFunctions.h"

int n, m;
StateMachine * myStateMachine;
Keyboard * myKeyboard;

SystemManager :: SystemManager() {
	// Initialize table for all diagrams, event time in ms (POSIX)
	// The maximum size of the table is defined in stateTable.h:
	// MAXDIA = 9, MAXLINES = 66
	// Should these be exceeded, please correct!

	tab[0][0] = new TableEntry ("ChainModeIdle","ChainModeIdle","Timer0",2000,myAction00,myCondition00);
	tab[0][1] = new TableEntry ("ChainModeIdle","LocalModeIdle","Timer0",2000,myAction01,myCondition01);
	tab[0][2] = new TableEntry ("ChainModeIdle","TransferFromLeft","Trigg0",0,myAction02,myCondition02);
	tab[0][3] = new TableEntry ("TransferFromLeft","MotorProfile","Trigg0",0,myAction02,myCondition02);
	tab[0][4] = new TableEntry ("MotorProfile","MotorProfile","ProfileTimer",50,myAction02,myCondition02);
	tab[0][5] = new TableEntry ("MotorProfile","WaitForIt","ProfileTimer",50,myAction02,myCondition02);
	tab[0][6] = new TableEntry ("WaitForIt","TransferToRight","Trigg0",0,myAction02,myCondition02);
	tab[0][7] = new TableEntry ("TransferToRight","TransferFromLeft","Trigg0",0,myAction02,myCondition02);
	tab[0][8] = new TableEntry ("TransferToRight","ChainModeIdle","Trigg0",0,myAction02,myCondition02);

	
	tab[1][0] = new TableEntry ("LocalModeIdle","LocalModeIdle","Trigg1",0,myAction10,myCondition10);
	tab[1][1] = new TableEntry ("LocalModeIdle","MotorProfile","Timer1",4000,myAction11,myCondition11);
	tab[1][2] = new TableEntry ("LocalModeIdle","ChainModeIdle","Timer1",4000,myAction11,myCondition11);
	tab[1][3] = new TableEntry ("MotorProfile","MotorProfile","ProfileTimer",50,myAction12,myCondition12);
	tab[1][4] = new TableEntry ("MotorProfile","LocalModeIdle","ProfileTimer",50,myAction13,myCondition13);

	tab[2][0] = new TableEntry ("KeyboardIdle","KeyboardIdle","KeyboardTimer",50,myAction20,myCondition20);
	tab[2][0] = new TableEntry ("KeyboardIdle","KeyboardIdle","KeyboardTimer",50,myAction20,myCondition20);

	// Initialize timer names for all diagrams
	// Timer names are always Timer followed by the diagram number
	timerNames[0] = "Timer0";
	timerNames[1] = "Timer1";
	timerNames[2] = "KeyboardTimer";

	// Initialize line numbers for all diagrams
	lines[0] = 3;
	lines[1] = 4;
	lines[2] = 1;

	// Initialize first state for all diagrams
	actualState[0] = "StateA";
	actualState[1] = "StateC";
	actualState[2] = "StateK";
	
	// Set the actual number of diagrams
	diagrams = 3;
	
	// Create instance of my Keyboard
	myKeyboard = new Keyboard;

	// Create instance of state machine
	myStateMachine = new StateMachine;

	// Start timer for each diagram which needs one in the first state!
	// In my case these are diagram 0 and 2
	myStateMachine->diaTimerTable[0]->startTimer(tab[0][0]->eventTime);
	myStateMachine->diaTimerTable[2]->startTimer(tab[2][0]->eventTime);

	// Initial actions can be done here, if needed!
	n = 0;
	m = 0;

	return;
}

SystemManager :: ~SystemManager() {
	return;
}

void SystemManager :: action00(){
	printf(" StateA -> Transition00 -> StateA\n\r"); 
	n++;
	return;
}

void SystemManager :: action01(){
	printf(" StateA -> Transition01 -> StateB\n\r"); 
	myStateMachine->sendEvent("Trigg1");
	return;
}

void SystemManager :: action02(){
	printf(" StateB -> Transition02 -> StateA\n\r"); 
	n = 0;
	return;
}

void SystemManager :: action10(){
	printf(" StateC -> Transition10 -> StateD\n\r"); 
	m = 0;
	return;
}

void SystemManager ::action11(){
	printf(" StateD -> Transition11 -> StateD\n\r"); 
	m++;
	return;
}

void SystemManager :: action12(){
	printf(" StateD -> Transition12 -> StateE\n\r"); 
	return;
}

void SystemManager :: action13(){
	printf(" StateE -> Transition13 -> StateC\n\r"); 
	myStateMachine->sendEvent("Trigg0");
	return;
}

void SystemManager :: action20(){
	myKeyboard->getPressedKey();
	return;
}

bool SystemManager :: conditionTrue(){
	return TRUE;
}

bool SystemManager :: condition00(){
	if (n < 5) {
		return TRUE;
	}
	else return FALSE;
}

bool SystemManager :: condition01(){
	if (n >= 5) return TRUE;
	else return FALSE;
}

bool SystemManager :: condition11(){
	if (m < 4) return TRUE;
	else return FALSE;
}

bool SystemManager :: condition12(){
	if (m >= 4) return TRUE;
	else return FALSE;
}
