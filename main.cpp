
#include <taskLib.h>
#include <stdio.h>
#include <intLib.h>
#include <sysLib.h>
#include <stdLib.h>
#include "ifLib.h"
#include "systemManager.h"
#include "stateMachine.h"

SystemManager * mySystemManager;
StateMachine * myStateMachine;

void setLocalIp();

int main (void) {
	

	// Set tick to 5 ms. This is the time resolution!
	sysClkRateSet(200);
	
	// Set local IP address according to MAC table
	setLocalIp();

	// Create instance of top class
	mySystemManager = new SystemManager;

	// Start the state machine. This method blocks, so no while(1) is needed.
	myStateMachine->runToCompletion();
	
}

//actions:

void noAction(){
	mySystemManager->myNoAction();
	return;
}

void setLocalModeTrue(){
	mySystemManager->mySetLocalModeTrue();
	return;
}


void startTransfer(){
	mySystemManager->myStartTransfer();
	return;
}

void evaluateKeyboard(){
	mySystemManager->myEvaluateKeyboard();
	return;
}



void myAction02(){
	mySystemManager->action02();
	return;
}


void myAction10(){
	mySystemManager->action10();
	return;
}

void myAction11(){
	mySystemManager->action11();
	return;
}

void myAction12(){
	mySystemManager->action12();
	return;
}

void myAction13(){
	mySystemManager->action13();
	return;
}

void myAction20(){
	mySystemManager->action20();
	return;
}


//conditions:

bool keyB(){
	return mySystemManager->myKeyB();
}

bool noRelevantKey(){
	return mySystemManager->myNoRelevantKey();
}

bool keyA(){
	return mySystemManager->myKeyA();
}

bool conditionTrue(){
	return mySystemManager->myConditionTrue();
}




bool myCondition02(){
	return mySystemManager->oldConditionTrue();
}

bool myCondition10(){
	return mySystemManager->oldConditionTrue();
}

bool myCondition11(){
	return mySystemManager->condition11();
}

bool myCondition12(){
	return mySystemManager->condition12();
}

bool myCondition13(){
	return mySystemManager->oldConditionTrue();
}

bool myCondition20(){
	return mySystemManager->oldConditionTrue();
}
