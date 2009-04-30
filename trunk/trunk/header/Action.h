#ifndef ACTION_H
#define ACTION_H

#include "Threads.h"

class Action
{
protected:
	int id;
public:
	// Le constructeur
	Action()
	{
		static int ID=0;
		this->id = ID;
		ID++;
	}
	// Le getter
	int getID()
	{
		return this->id;
	}
	//methode a implementer: executer l'action
	virtual void execute()=0;
};

void * actionThread ( void* p_data );


#endif