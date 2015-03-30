#ifndef __MODULE__DYNAMIC_ARRAY_HPP__
#define __MODULE__DYNAMIC_ARRAY_HPP__

#include <cstddef>

namespace Module {

template <class T>
class DynamicArray {
	
public:
	typedef unsigned int size_type;
	static const size_type INIT_SIZE = 32;
	
	DynamicArray() : size(0)
	{
		allocatedSpace = INIT_SIZE;
		myArray = new T[INIT_SIZE];
	}
	DynamicArray(size_type initSize) : size(0)
	{
		allocatedSpace = initSize;
		myArray = new T[initSize];
	}
	
	size_type getSize() const { return size; }
	size_type getAllocatedSpace() const { return allocatedSpace; }
	
	void expand(size_type newSize)
	{
		if (newSize > allocatedSpace) // do not contract the array
		{
			T* newArray = new T[newSize];
			
			for (size_type i = 0; i < size; i++)
			{
				newArray[i] = myArray[i];
			}
			
			delete[] myArray;
			myArray = newArray;
			allocatedSpace = newSize;
		}
	}
	
	T& operator[] (size_type index) { return myArray[index]; }
	const T& operator[] (size_type index) const { return myArray[index]; }
	
	T& get(size_type index) { return myArray[index]; }
	const T& get(size_type index) const { return myArray[index]; }
	
	void add(const T& newVal)
	{
		if (size == allocatedSpace)
		{
			if (size)
				expand(allocatedSpace * 2);
			else
				expand(INIT_SIZE);
		}
		myArray[size] = newVal;
		size++;
	}
	
	void insert(const T& newVal, size_type index);
	bool remove(size_type index);
	bool removeFromEnd(size_type numRemoved);
	
	void append(T* appendedArray, size_type appendedSize)
	{
		if (size + appendedSize < allocatedSpace)
		{
			size_type newSize = allocatedSpace;
			while (newSize < size + appendedSize) newSize *=2;
			expand(newSize);
		}
		for (size_type i = 0; i < appendedSize; i++)
		{
			myArray[size + i] = appendedArray[i];
		}
	}
	
	void append(const Module::DynamicArray<T>& other)
	{
		append(other.myArray, other.size);
	}

private:
	T* myArray;
	size_type size;
	size_type allocatedSpace;
};

}

#endif