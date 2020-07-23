#include <iostream>
#include <vector>
#include <map>

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
private:
	// Created pool per Object Description, just in case they are of different sizes.  This would help prevent memory fragmentation.
	std::map <const ObjectDescription, vector<Object*> > pools_;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~
// ObjectPool class methods

void ObjectPool::PreWarmObject(const ObjectDescription& description, const unsigned int amount)
{
	// TODO: Add MAX_POOL_LIMIT and check amount does not exceed
	if (pools_.find(description) != pools_.end())
	{
		// TODO: Handle overwritting existing pools
		std::cerr << "Pool already exists with ObjectDescription ID: (" << description.m_ID << ") " << description.m_Name << " Suggestion: Check for duplicate ObjectDescriptions" << '\n';
	}

	std::vector<Object*> objects(amount, CreateObjectFromDescription(description));
	pools_[description] = objects;

}

unsigned int ObjectPool::GetPoolObjectCount(const ObjectDescription& description)
{
	// Check to see if pool exists first
	if (pools_.find(description) == pools_.end())
		return 0;

	try {
		return static_cast<int>(pools_.at(description).size());
	}
	catch (const std::out_of_range& oor) {
		// TODO: Remove out_of_range catch not that we are using map.find before map.at
		//std::cerr << "Out of Range error: " << oor.what() << '\n';
	}
	return 0;
}

Object* ObjectPool::GetObject(const ObjectDescription& description)
{
	if (pools_.find(description) == pools_.end())
		throw "Called GetObject on an unknown ObjectDescription pool.  Suggestion: Call PreWarmObject first!";
	if (pools_.at(description).empty())
		return nullptr;
	Object* pObject = pools_.at(description).back();
	pools_.at(description).pop_back();
	pObject->m_isActive = true;
	return pObject;
}

void ObjectPool::ReturnObject(Object* obj)
{
	// TODO: Check if at capacity first
	if (obj == nullptr)
	{
		//throw "Attempted to return a null object";
		std::cerr << "Attempted to add null object to pool.  Suggestion: Increase amount pram on PreWarmObject" << '\n';
		return;
	}
	obj->m_isActive = false;
	pools_.at(ObjectDescription(obj->m_ID, obj->m_Name)).push_back(obj);
}

// Some sample Descriptions and data
const int MaxDescrtiptions = 3;
// TODO: Should we consider no duplicates, if so then we could used ID as key in map
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