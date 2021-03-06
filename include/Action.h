//  @ Project : Tetrabot
//  @ File Name : Action.h
//  @ Date : 01/06/2009
//  @ Author : Frozen Brains

#ifndef ACTION_H
#define ACTION_H

#include "Threads.h"
class Action
{
protected:
	int id;

public:

	Action();

	//virtual ~Action();

	int getID();

	virtual void execute() = 0;
};

void * actionThread (void* p_data );


#endif /* ACTION_H */
