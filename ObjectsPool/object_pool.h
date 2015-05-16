#ifndef OBJECT_POOL_H
#define OBJECT_POOL_H

#pragma warning (disable:4290) // ignore warning function is not __declspec(nothrow)

#include <queue>
#include <vector>
#include <stdexcept>
#include <memory>

using std::queue;
using std::vector;


template<class T>
class ObjectPool
{
public:

	ObjectPool(int chunkSize = kDefaultChunkSize) throw(std::invalid_argument);

	~ObjectPool();

	T& acquireObject();

	void releaseObject(T& obj);

protected:

	queue<T*> mFreeList;
	vector<T*> mAllObjects;

	int mChunkSize;
	static const int kDefaultChunkSize = 10;


	void allocateChunk();
	static void arrayDeleteObject(T* obj);

private:

	ObjectPool(const ObjectPool<T>& src);
	ObjectPool<T>& operator=(const ObjectPool<T>& rhs);
};


template<class T>
const int ObjectPool<T>::kDefaultChunkSize;

template<class T>
ObjectPool<T>::ObjectPool(int chunkSize) throw(std::invalid_argument) 
	: mChunkSize(chunkSize)
{
	if (mChunkSize <= 0)
	{
		throw std::invalid_argument("chunk size must be positive");
	}

	allocateChunk();
}

template<class T>
void ObjectPool<T>::allocateChunk()
{
	T* newObject = new T[mChunkSize];
	mAllObjects.push_back(newObject);
	for (int i = 0; i < mChunkSize; ++i)
	{
		mFreeList.push(&newObject[i]);
	}//end for
}

template<class T>
void ObjectPool<T>::arrayDeleteObject(T* obj)
{
	delete[] obj;
}

template<class T>
ObjectPool<T>::~ObjectPool()
{
	for_each(mAllObjects.begin(), mAllObjects.end(), arrayDeleteObject);
}

template<class T>
T& ObjectPool<T>::acquireObject()
{
	if (mFreeList.empty()){
		allocateChunk();
	}
	T* obj = mFreeList.front();
	mFreeList.pop();
	return (*obj);
}

template<class T>
void  ObjectPool<T>::releaseObject(T& obj)
{
	mFreeList.push(&obj);
}

#endif