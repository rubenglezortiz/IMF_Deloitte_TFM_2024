#pragma once

#include <memory>

class GameStateMachine;
class Manager;
// when you are not using the methods of a class, just
// say that it exists, that saves time when parsing files

class GameState { //hereda de GameState
public:
	GameState(GameStateMachine* gsm);
	virtual ~GameState();
	virtual void init();
	virtual void update();
	
protected:
	std::unique_ptr<Manager> mngr_;  	//unique pointer se hace delete a si mismo al terminar la ejecucion
	GameStateMachine* gameStateMachine;
};
