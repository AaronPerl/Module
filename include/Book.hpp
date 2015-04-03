#ifndef __MODULE_BOOK_HPP__
#define __MODULE_BOOK_HPP__

#include <iostream>
#include <vector>

namespace Module
{
	template <class T>
	class Book
	{
		public:		
			typedef typename std::vector<T*>::size_type page_size_type;	// The size type for Books
			typedef unsigned long size_type;
			static const page_size_type maxPageSize = 4 * 1024; // 4 kilobyte pages
				
			Book();
			~Book();
				
			T& operator[] (size_type index) 						{ return get(index); }
			const T& operator[](size_type index) const 				{ return get(index); }
			T& get(size_type index);
			const T& get(size_type index) const;
		
			T& front()									{ return pageVec[0][0];	}	// The first element in the data
			const T& front() const						{ return pageVec[0][0];	}	// The first element in the data
			T& back()									{ return pageVec.back()[(usedSize-1) % pageSize];	}	// The last element in the data
			const T& back()	const						{ return pageVec.back()[(usedSize-1) % pageSize];	}	// The last element in the data
			
			T* getPage(page_size_type index) { return pageVec[index]; }
			page_size_type getPageSize() { return pageSize; }
			page_size_type getNumPages() { return pageVec.size(); }
			
			size_type size() { return usedSize; }
			size_type capacity() { return (size_type)pageSize * pageVec.size(); }
			
			void push_back(const T& newVal);
			
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
	page_size_type page = index / pageSize;
	page_size_type pageIndex = index % pageSize;
	return pageVec[page][pageIndex];
}

template <class T>
void Module::Book<T>::push_back(const T& newVal)
{
	if (usedSize % pageSize != 0) // the page still has space
	{
		pageVec.back()[usedSize%pageSize] = newVal;
	}
	else
	{
		pageVec.push_back(new T[pageSize]);
		pageVec.back()[0] = newVal;
	}
	usedSize++;
}

#endif