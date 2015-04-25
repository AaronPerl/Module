#ifndef __MODULE_BOOK_HPP__
#define __MODULE_BOOK_HPP__

#include <iostream>
#include <vector>

namespace Module
{
	// The Book class is a data structure that consists of a growing vector
	// of fixed-size "pages" of memory resembling an unrolled linked list.
	// These pages are static and will not change address, allowing for
	// pointers to objects in this data structure to remain valid as long as the
	// book itself still exists. Books should NOT be used to store objects that are frequently removed.
	// They should be used for data that persists for a long time, such as vertices and sound data.
	template <class T>
	class Book
	{
		public:		
			typedef typename std::vector<T*>::size_type page_size_type;	// The size type for the page vector and pages
			typedef unsigned long size_type;							// The size type for the Book itself
			static const page_size_type maxPageSize = 4 * 1024; // 4 kilobyte pages
				
			Book();
			~Book();
				
			T& operator[] (size_type index) 						{ return get(index); }
			const T& operator[](size_type index) const 				{ return get(index); }
			T& get(size_type index);
			const T& get(size_type index) const;
		
			T& front()									{ return pageVec[0][0];	}	// The first element in the first page
			const T& front() const						{ return pageVec[0][0];	}	// The first element in the first page
			T& back()									{ return pageVec.back()[(usedSize-1) % pageSize];	}	// The last stored element in the last page
			const T& back()	const						{ return pageVec.back()[(usedSize-1) % pageSize];	}	// The last stored element in the last page
			
			T* getPage(page_size_type index) { return pageVec[index]; }		// Returns the address of the index-th page
			page_size_type getPageSize() { return pageSize; }				// The number of objects in a single page
			page_size_type getNumPages() { return pageVec.size(); }			// The number of allocated pages
			
			size_type size() const { return usedSize; }
			size_type capacity() { return (size_type)pageSize * pageVec.size(); }
			
			void push_back(const T& newVal);
			
			// Returns the number of elements after index in the page containing index (including index itself)
			page_size_type remainingElementsInPage(size_type index) const { return pageSize - (index % pageSize); }
			
			const std::vector<T*>& getPageVec() { return pageVec; }
		private:
			size_type usedSize;
			page_size_type pageSize;
			std::vector<T*> pageVec;
	};
}

template <class T>
Module::Book<T>::Book() : usedSize(0)
{
	pageSize = maxPageSize / sizeof(T);
	//pageVec.push_back(new T[pageSize]);
}

template <class T>
Module::Book<T>::~Book()
{
	for (unsigned int i = 0; i < pageVec.size(); i++)
		delete[] pageVec[i];
}

template <class T>
T& Module::Book<T>::get(size_type index)
{
	page_size_type page = index / pageSize;			// The page to read from
	page_size_type pageIndex = index % pageSize;	// The index in that page to return
	return pageVec[page][pageIndex];
}

template <class T>
const T& Module::Book<T>::get(size_type index) const
{
	page_size_type page = index / pageSize;			// The page to read from
	page_size_type pageIndex = index % pageSize;	// The index in that page to return
	return pageVec[page][pageIndex];
}

template <class T>
void Module::Book<T>::push_back(const T& newVal)
{
	if (usedSize % pageSize != 0) // the page still has space
	{
		pageVec.back()[usedSize%pageSize] = newVal;
	}
	else // allocate a new page
	{
		pageVec.push_back(new T[pageSize]);
		pageVec.back()[0] = newVal;
	}
	usedSize++;
}

#endif