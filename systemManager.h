
#ifndef SYSTEMMANAGER_H_
#define SYSTEMMANAGER_H_

/*
#include <queue>
#include <semLib.h>

#include "diaTimer.h"
#include "stateTable.h"
*/

class SystemManager {
public:
	SystemManager();
	~SystemManager();
	//actions:
	void myNoAction();
	void mySetLocalModeTrue();
	void myKeyPressed();
	void myStartTransfer();
	void myEvaluateKeyboard();
	
	void action02();
	void action10();
	void action11();
	void action12();
	void action13();
	void action20();
	
	//conditions:
	bool myConditionTrue();
	bool myKeyB();
	bool myKeyA();
	bool myNoRelevantKey();
	
	bool oldConditionTrue();
	bool condition11();
	bool condition12();

private:
	void myStoreKeyValue();
};

#endif // SYSTEMMANAGER_H_
