#ifndef COMPOSANT_H
#define COMPOSANT_H

class Composant
{
	// Attributs
protected:
	int id;
	btDynamicsWorld* World;

	// Les methodes
public:
	int getID()
	{
		return this->id;
	}

	btDynamicsWorld* getWorld()
	{
		return this->World;
	}
	void setWorld(btDynamicsWorld* newWorld)
	{
		this->World = newWorld;
	}

	btRigidBody* localCreateRigidBody (btScalar mass, const btTransform& startTransform, btCollisionShape* shape,Ogre::SceneNode* nodeOgre)
	{
		bool isDynamic = (mass != 0.f);
		btVector3 localInertia(0,0,0);
		if (isDynamic)
			shape->calculateLocalInertia(mass,localInertia);

		btMotionState* myMotionState = new TetraMotionState(startTransform,nodeOgre);
			
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,shape,localInertia);
		btRigidBody* body = new btRigidBody(rbInfo);

		World->addRigidBody(body);
		return body;
	}
};

#endif
