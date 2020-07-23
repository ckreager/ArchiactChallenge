#pragma once

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Welcome to the Archiact challenge!
//
// Problem: We have objects that take a long time to create. To prevent hitching we need to set up a pool to manage these objects
// An Object pools function is to store disabled versions of the object until it is needed, when it is called upon the object will give you an object that had 
// previously been created.
//
// In this file are some foundational objects and functions. In Answer.cpp is the main function and an ObjectPool Class. You will mainly need to fill in the empty 
// functions of ObjectPool with the goal of completing the tasks in main(), you can add new functions as well.
//
// Bonus: Implement a pool for another type, for example ParticleEmitter.
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include <string>
#include <vector>
#include <map>
#include <stack>

using namespace std;

// A description of how to create an object, like a prototype
struct ObjectDescription
{
	ObjectDescription(int id, string name) :
		m_ID(id),
		m_Name(name)
	{

	}

	bool operator==(const ObjectDescription& objDes) const 
	{
		return m_ID == objDes.m_ID && m_Name == objDes.m_Name;
	}

	bool operator<(const ObjectDescription& objDes) const 
	{
		return m_ID < objDes.m_ID;
	}

	// Unique id for an object type
	const int m_ID;
	const string m_Name;
};

// Base class for all game objects
class Object
{
public:
	Object(int id) : m_ID(id)
	{

	};

	const int m_ID;
	string m_Name;

	// Is the object currently in use from the pool
	bool m_isActive;
};

// Instantiate a new object from a description and initialize correctly. Don't need to instantiate objects manually
static Object* CreateObjectFromDescription(const ObjectDescription& description)
{
	Object* ret = new Object(description.m_ID);
	ret->m_Name = description.m_Name;
	ret->m_isActive = false;
	return ret;
}

static void DestroyObject(Object* object)
{
	delete object;
}

// Interface for object pools
template<typename PoolType, typename Description>
class IPool
{
public:
	// Fill the pool with a number of inactive objects of the given type
	virtual void PreWarmObject(const Description& description, const unsigned int amount) = 0;
	
	// The number of objects currently in the pool
	virtual unsigned int GetPoolObjectCount(const Description& description) = 0;
	
	// Retrieve a single object from the pool, activates it
	virtual PoolType* GetObject(const Description& description) = 0;

	// Returns an in use object to the pool, deactivates it
	virtual void ReturnObject(PoolType* Object) = 0;
};