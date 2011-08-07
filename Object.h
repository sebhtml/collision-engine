
#ifndef _Object_H
#define _Object_H

#include "Screen.h"

class Object{

public:
	virtual void update() = 0;
	virtual void display(Screen*screen) = 0;
};

#endif
