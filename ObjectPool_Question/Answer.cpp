#include <iostream>

#include "Question.h"

using namespace std;

// A skeleton class definition which implements the IPool interface
class ObjectPool : public IPool<Object, ObjectDescription>
{
public:
	virtual void PreWarmObject(const ObjectDescription& description, const unsigned int amount);
	virtual unsigned int GetPoolObjectCount(const ObjectDescription& description);
	virtual Object* GetObject(const ObjectDescription& description);
	virtual void ReturnObject(Object* Object);
protected:
};

// ~~~~~~~~~~~~~~~~~~~~~~~~
// ObjectPool class methods

void ObjectPool::PreWarmObject(const ObjectDescription& description, const unsigned int amount)
{
	// TODO:
}

unsigned int ObjectPool::GetPoolObjectCount(const ObjectDescription& description)
{
	// TODO:
	return 0;
}

Object* ObjectPool::GetObject(const ObjectDescription& description)
{
	// TODO:
	return nullptr;
}

void ObjectPool::ReturnObject(Object* obj)
{
	// TODO:
}

// Some sample Descriptions and data
const int MaxDescrtiptions = 3;
const ObjectDescription ObjDescriptions[] =
{
	ObjectDescription(0, "\"Exceptionally Green Diode\""),
	ObjectDescription(1, "\"Dragon's pet 24-cell\""),
	ObjectDescription(2, "\"Event Horizon of Slime\"")
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Main function. Your implementation should complete all of the tests performed in this function
int main()
{
	ObjectPool pool;
	//Prewarm the pools
	cout << "We will now Prewarm the pools \n\n";
	for (int i = 0; i < MaxDescrtiptions; ++i)
	{
		ObjectDescription objDesc = ObjDescriptions[i];
		cout << "ID: (" << objDesc.m_ID << ") " << objDesc.m_Name << "\n";
		cout << "The size is: " << pool.GetPoolObjectCount(objDesc) << "\n";
		cout << "We will now prewarm the pool with 10 objects\n";
		pool.PreWarmObject(objDesc, 10);
		cout << "The size is: " << pool.GetPoolObjectCount(objDesc) << "\n";
		cout << "\n";
	}
	//Access object from each pool and return it

	cout << "\nWe will now access an object and return it to the pool\n\n";
	for (int i = 0; i < MaxDescrtiptions; ++i)
	{
		ObjectDescription objDesc = ObjDescriptions[i];

		cout << "ID: (" << objDesc.m_ID << ") " << objDesc.m_Name << "\n";
		cout << "The size is: " << pool.GetPoolObjectCount(objDesc) << "\n";
		Object* obj = pool.GetObject(objDesc);
		if (obj != nullptr)
		{
			cout << "We have retrieved from the pool an object with\nname: " << obj->m_Name << "\nID: " << obj->m_ID << "\n";
		}
		else
		{
			cout << "Object retrieval failed!";
		}
		
		cout << "The size is: " << pool.GetPoolObjectCount(objDesc) << "\n";

		cout << "Returning Object to pool\n";
		pool.ReturnObject(obj);
		obj = nullptr;
		cout << "The size is: " << pool.GetPoolObjectCount(objDesc) << "\n";
		cout << "\n";
	}

	// Handle the scenario where more objects have been pulled from the pool than have been put in

	cout << "\nWe will now access more object than the pool contains and return them all\n\n";
	for (int i = 0; i < MaxDescrtiptions; ++i)
	{
		const unsigned int ObjCount = 12;
		Object* objects[ObjCount];
		ObjectDescription objDesc = ObjDescriptions[i];

		cout << "ID: (" << objDesc.m_ID << ") " << objDesc.m_Name << "\n";


		cout << "We will now retreive " << ObjCount << " objects from the pool\n";
		cout << "The size is: " << pool.GetPoolObjectCount(objDesc) << "\n";
		for (int i = 0; i < ObjCount; ++i)
		{
			objects[i] = pool.GetObject(objDesc);
		}
		cout << "The size is: " << pool.GetPoolObjectCount(objDesc) << "\n";

		cout << "Returning Objects to pool\n";

		for (int i = 0; i < ObjCount; ++i)
		{
			pool.ReturnObject(objects[i]);
		}
		cout << "The size is: " << pool.GetPoolObjectCount(objDesc) << "\n";
		cout << "\n";
	}
	//We made it!
	cout << "Excellent!!! We made it and we didn't crash or nothin'!!! Thats great!!! GOOD JOB";
}