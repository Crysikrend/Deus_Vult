#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "..\Core\ResourceManagers\EntityList.h"
#include "EntityExtra.h"

#include "..\Core\ResourceManagers\InputManager.h"

class InputManager;

class Controller {
public:
	Controller(EntityList* list) : _list(list) {}

	void initialise(InputManager* const);

private:
	EntityList* _list;
	Entity* _player;
};

#endif