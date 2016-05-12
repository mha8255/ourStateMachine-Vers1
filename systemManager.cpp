
#include "systemManager.h"
#include "stateMachine.h"
#include "keyboard.h"
#include "myFunctions.h"
#include <sysLib.h>
#include <ioLib.h>

extern "C" {
#include "hw_functions/hwFunc.h"
}

int n, m;
bool localMode;
char keyVal;
char newKeyVal;
StateMachine * myStateMachine;
Keyboard * myKeyboard;

SystemManager :: SystemManager() {
	// Initialize table for all diagrams, event time in ms (POSIX)
	// The maximum size of the table is defined in stateTable.h:
	// MAXDIA = 9, MAXLINES = 66
	// Should these be exceeded, please correct!

	initHardware (0);

	tab[0][0] = new TableEntry ("ChainModeIdle","ChainModeIdle","keyPressed",0,noAction,noRelevantKey);
	tab[0][1] = new TableEntry ("ChainModeIdle","LocalModeIdle","keyPressed",0,setLocalModeTrue,keyB);
	tab[0][2] = new TableEntry ("ChainModeIdle","TransferFromLeft","keyPressed",0,startTransfer,keyA);
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

	tab[2][0] = new TableEntry ("KeyboardIdle","KeyboardIdle","KeyboardTimer",50,evaluateKeyboard,conditionTrue);
	tab[2][1] = new TableEntry ("KeyboardIdle","KeyboardIdle","KeyboardTimer",50,noAction,myCondition20);

	// Initialize timer names for all diagrams
	// Timer names are always Timer followed by the diagram number
	timerNames[0] = "ProfileTimer";
	timerNames[1] = "Timer1";
	timerNames[2] = "KeyboardTimer";

	// Initialize line numbers for all diagrams
	lines[0] = 9;
	lines[1] = 5;
	lines[2] = 2;

	// Initialize first state for all diagrams
	actualState[0] = "ChainModeIdle";
	actualState[1] = "LocalModeIdle";
	actualState[2] = "KeyboardIdle";
	
	// Set the actual number of diagrams
	diagrams = 3;
	
	// Create instance of my Keyboard
	myKeyboard = new Keyboard;

	// Create instance of state machine
	myStateMachine = new StateMachine;

	// Start timer for each diagram which needs one in the first state!
	// In my case these are diagram 0 and 2
	//myStateMachine->diaTimerTable[0]->startTimer(tab[0][4]->eventTime);
	//myStateMachine->diaTimerTable[1]->startTimer(tab[1][1]->eventTime);
	myStateMachine->diaTimerTable[2]->startTimer(tab[2][0]->eventTime);

	// Initial actions can be done here, if needed!
	n = 0;
	m = 0;

	return;
}

SystemManager :: ~SystemManager() {
	return;
}

//actions:

void SystemManager :: myEvaluateKeyboard(){
	// read Keyboard; if Keyboard value is other than before make the following bzw generell gedrückt:
	char newKeyVal = getKey();
	if (newKeyVal == 0x0) {
		//do nuttin
	}
	else{
		keyVal = newKeyVal;
		printf(" A key has been pressed: %c \n\r", keyVal);
		myStateMachine->sendEvent("keyPressed");
	}
	return;

}

void SystemManager :: myNoAction(){
	printf("ich bin faul\n\r"); 
	//myStateMachine->sendEvent("Trigg1");
	return;
}

void SystemManager :: mySetLocalModeTrue(){
	printf(" Transition to local Mode because of Key B pressed\n\r"); 
	localMode = true;
	return;
}

void SystemManager :: myStartTransfer(){
	printf(" Transition to TransferfromLeft because of Key A pressed\n\r"); 
	//start motor; sendReady
	return;
}


void SystemManager :: action02(){
	printf(" StateC -> Transition10 -> StateD\n\r"); 
	m = 0;
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

//conditions:

bool SystemManager :: myConditionTrue(){
	return TRUE;
}

bool SystemManager :: myNoRelevantKey(){
	
	if ( keyVal == ('B' || 'A') ) {
		printf("relevantKeyPressed\n\r");
		return FALSE;
	}
	else return TRUE;
}

bool SystemManager :: myKeyB(){
	if (keyVal =='B') { 
		return TRUE;
	}
	else return FALSE;
}

bool SystemManager :: myKeyA(){
	if (keyVal == 'A') { 
		return TRUE;
	}
	else return FALSE;
}




bool SystemManager :: condition12(){
	if (m >= 4) return TRUE;
	else return FALSE;
}
