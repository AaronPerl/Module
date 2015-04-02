#ifndef __MODULE__DYNAMIC_data_HPP__
#define __MODULE__DYNAMIC_data_HPP__

#include <cstring>
#include <cstddef>
#include <iostream>

namespace Module
{
// DynamicArrays are an in-house replacement for stl's vector,
// allowing for implementations across platforms to use it.
template <class T>
class DynamicArray 
{
	public:
		// TYPEDEFS
		typedef unsigned int size_type;		// The usedSize type for DynamicArrays
		static const size_type INIT_SIZE = 32;
		
		// CONSTRUCTORS
		DynamicArray();						// The default constructor for a DynamicArray
		DynamicArray(size_type initSize);	// A constructor for DynamicArray given a size
		
		// GETTERS
		T& operator[] (size_type index)				{ return data[index];	}		// The bracket [] operator
		const T& operator[] (size_type index) const	{ return data[index];	}		// The const bracket [] operator
		T& get(size_type index)						{ return data[index];	}		// The get() function
		const T& get(size_type index) const			{ return data[index];	}		// The const get() function
		
		T& front()									{ return data[0];			}	// The first element in the data
		const T& front() const						{ return data[0];			}	// The first element in the data
		T& back()									{ return data[usedSize-1];	}	// The last element in the data
		const T& back()	const						{ return data[usedSize-1];	}	// The last element in the data
		
		size_type size() const						{ return usedSize;		}		// Gets the size of the DynamicArray
		size_type capacity() const					{ return allocSize;		}		// Gets the allocated space of the DynamicArray
		
		// MEMBER FUNCTIONS
		void add(const T& newVal);									// Adds an element to the end of a DynamicArray
		void resize(size_type newSize);								// Resizes the DynamicArray
		void insert(const T& newVal, size_type index);				// Inserts an element into the DynamicArray
		void append(T* appendedData, size_type appendedSize);		// Appends an data to this DynamicArray
		void append(const Module::DynamicArray<T>& other);			// Appends a DynamicArray to this DynamicArray
		bool remove(size_type index);								// Removes an element from the DynamicArray (returns success)
		bool removeFromEnd(size_type numRemoved);					// Removes the last element from the DynamicArray (returns success)

	private:
		// REPRESENTATION
		T* data;				// The underlying representation of a DynamicArray
		size_type usedSize;		// The number of elements in the DynamicArray
		size_type allocSize;	// The size allocated for this DynamicArray
};
template <class T>
DynamicArray<T>::DynamicArray() : usedSize(0)
{
	allocSize = INIT_SIZE;
	data = new T[INIT_SIZE];
}
template <class T>
DynamicArray<T>::DynamicArray(size_type initSize) : usedSize(0)
{
	allocSize = initSize;
	data = new T[initSize];
}

template <class T>
void DynamicArray<T>::add(const T& newVal)
{
	if (usedSize == allocSize)
	{
		if (usedSize != 0)
			resize(allocSize * 2);
		else
			resize(INIT_SIZE);
	}
	data[usedSize] = newVal;
	usedSize++;
}
template <class T>
void DynamicArray<T>:: resize(size_type newSize)
{
	if (newSize > allocSize) // If we're expanding the data
	{
		T* newdata = new T[newSize];
		for (size_type i = 0; i < usedSize; i++)
		{
			newdata[i] = data[i];
		}
		delete[] data;
		data = newdata;
		allocSize = newSize;
	}
	else if (newSize < allocSize)
	{
		T* newdata = new T[newSize];
		for (size_type i = newSize; i < usedSize; i++)
		{
			data[i].~T();
		}
		for (size_type i = 0; i < usedSize; i++)
		{
			newdata[i] = data[i];
		}
		delete[] data;
		data = newdata;
		allocSize = newSize;
	}
}
template <class T>
void DynamicArray<T>::append(T* appendedData, size_type appendedSize)
{
	if (usedSize + appendedSize < allocSize)
	{
		size_type newSize = allocSize;
		while (newSize < usedSize + appendedSize) newSize *=2;
		resize(newSize);
	}
	for (size_type i = 0; i < appendedSize; i++)
	{
		data[usedSize + i] = appendedData[i];
	}
}
template <class T>
void DynamicArray<T>::append(const Module::DynamicArray<T>& other)
{
	append(other.data, other.usedSize);
}

}

#endif
