#ifndef ListTemplate
#define ListTemplate


#include "stdafx.h"
#include <iostream>
#include <assert.h>

namespace lt
{

	template <class T>
	class ListNode
	{
	public:
	    ListNode();
		~ListNode();
		ListNode<T> *&getNextptr();
		ListNode<T> *&getPreviousptr();
		T &getData();
		bool isEnd();
		bool isBegining();
	private:
		T _data;
		ListNode<T> *_nextptr;
		ListNode<T> *_previousptr;
	};

	template <class T>
	ListNode<T>::ListNode()
	{
		_data = 0;
		_nextptr = nullptr;
		_previousptr = nullptr;
	}

	template <class T>
	ListNode<T>::~ListNode() {}

	template <class T>
	bool ListNode<T>::isEnd()
	{
		return _nextptr == nullptr;
	}

	template <class T>
	bool ListNode<T>::isBegining()
	{
		return _previousptr == nullptr;
	}

	template <class T>
	ListNode<T> *&ListNode<T>::getNextptr()
	{
		return _nextptr;
	}

	template <class T>
	ListNode<T> *&ListNode<T>::getPreviousptr()
	{
		return _previousptr;
	}

	template <class T>
	T &ListNode<T>::getData()
	{
		return _data;
	}

	template <class T>
	using ListNodeptr = ListNode<T> *;

	using namespace std;

	template <class T>
	class ListIterator;
	template <class T>
	class List
	{
	public:
		List();
		List(const List<T> &toCopy);
		~List();
		ListIterator<T> insert(ListIterator<T> pos, const T &idata);
		ListIterator<T> erase(ListIterator<T> pos); 
		List<T> &operator=(const List<T> &toCopy);
		ListIterator<T> begin();
		ListIterator<T> end();
		ListIterator<T> cbegin() const;
		ListIterator<T> cend() const;
		void clear();
		T &front();
		T &back();
		bool empty();
		int size() const;
	private:
		ListNodeptr<T> _node_ptr;
		ListNodeptr<T> _last_ptr;
		int _nodesCount;
	};

	template <class T>
	List<T>::List()
	{
		_nodesCount = 0;
		_node_ptr = nullptr;
		_last_ptr = nullptr;
	}

	template <class T>
	ListIterator<T> List<T>::begin()
	{
		ListIterator<T> temp(this->_node_ptr);
		return temp;
	}

	template <class T>
	ListIterator<T> List<T>::cbegin() const
	{
		ListIterator<T> temp(this->_node_ptr);
		return temp;
	}

	template <class T>
	ListIterator<T> List<T>::end()
	{
		ListIterator<T> temp(nullptr);
		return temp;
	}

	template <class T>
	ListIterator<T> List<T>::cend() const
	{
		ListIterator<T> temp(nullptr);
		return temp;
	}

	template <class T>
	List<T>::List(const List<T> &toCopy)
	{
		ListNodeptr<T> newptr = nullptr, previousptr = nullptr;
		ListNodeptr<T> *Currentptr = &_node_ptr;

		for (auto it = toCopy.cbegin(); it != toCopy.cend(); it++)
		{
			newptr = new ListNode<T>;
			assert(newptr != nullptr);
			newptr->getData() = *it;
			newptr->getPreviousptr() = previousptr;
			previousptr = newptr;
			*Currentptr = newptr;
			Currentptr = &((*Currentptr)->getNextptr());
		}

		_last_ptr = newptr;
		_nodesCount = toCopy.size();
	}

	template <class T>
	List<T>::~List() 
	{
		ListNodeptr<T> currentNodeptr = _node_ptr;

		if (_node_ptr == nullptr)
		{
			_nodesCount = 0;
			_last_ptr = nullptr;
			return;
		}

		while (!currentNodeptr->isEnd())
		{
			currentNodeptr = currentNodeptr->getNextptr();
		}

		while (!currentNodeptr->isBegining())
		{
			currentNodeptr = currentNodeptr->getPreviousptr();
			delete currentNodeptr->getNextptr();
		}

		delete _node_ptr;
		_node_ptr = nullptr;
		_nodesCount = 0;
		_last_ptr = nullptr;
	}

	template <class T>
	ListIterator<T> List<T>::insert(ListIterator<T> pos, const T &idata)
	{
		ListNodeptr<T> newptr;

		if (_last_ptr == nullptr)
		{
			newptr = new ListNode<T>;
			assert(newptr != nullptr);
			newptr->getData() = idata;
			_node_ptr = newptr;
			_last_ptr = _node_ptr;
		}
		else if (pos == this->begin())
		{
			newptr = new ListNode<T>;
			assert(newptr != nullptr);
			*newptr = *_node_ptr;
			newptr->getPreviousptr() = _node_ptr;

			if (_node_ptr->getNextptr() != nullptr)
				(_node_ptr->getNextptr())->getPreviousptr() = newptr;

			_node_ptr->getNextptr() = newptr;
			_node_ptr->getData() = idata;
			_last_ptr = newptr;
		}
		else if(pos == this->end())
		{
			newptr = new ListNode<T>;
			assert(newptr != nullptr);
			newptr->getData() = idata;
			newptr->getPreviousptr() = _last_ptr;
			_last_ptr->getNextptr() = newptr;
			_last_ptr = newptr;

		}
		else
		{
			ListNodeptr<T> toInsert = pos.getPtr();

			newptr = new ListNode<T>;
			assert(newptr != nullptr);
			newptr->getData() = idata;
			newptr->getNextptr() = toInsert;
			newptr->getPreviousptr() = toInsert->getPreviousptr();
			toInsert->getPreviousptr()->getNextptr() = newptr;
			toInsert->getPreviousptr() = newptr;
		}

		ListIterator<T> temp(newptr);
		++_nodesCount;

		return temp;
	}

	template <class T>
	ListIterator<T> List<T>::erase(ListIterator<T> pos)
	{
		if (pos == this->end())
			return pos;

		ListIterator<T> temp;

		if (pos == begin())
		{
			if (_last_ptr == _node_ptr)
				_last_ptr = nullptr;

			pos++;
			delete _node_ptr;
			_node_ptr = pos.getPtr();
		}
		else if (pos.getPtr() == _last_ptr)
		{
			temp = pos;
			--pos;
			pos.getPtr()->getNextptr() = nullptr;
			_last_ptr = pos.getPtr();
			delete temp.getPtr();
			return pos;
		}
		else
		{
			temp = pos;
			--pos;
			pos.getPtr()->getNextptr() = temp.getPtr()->getNextptr();
			temp.getPtr()->getNextptr()->getPreviousptr() = pos.getPtr();
			delete temp.getPtr();
			return ++pos;
		}

		--_nodesCount;

		return pos;
	}

	template <class T>
	List<T> &List<T>::operator=(const List<T> &toCopy)
	{
		if (&toCopy == this)
			return *this;

		this->~List();

		ListNodeptr<T> newptr = nullptr, previousptr = nullptr;
		ListNodeptr<T> *Currentptr = &_node_ptr;

		for (auto it = toCopy.cbegin(); it != toCopy.cend(); it++)
		{
			newptr = new ListNode<T>;
			assert(newptr != nullptr);
			newptr->getData() = *it;
			newptr->getPreviousptr() = previousptr;
			previousptr = newptr;
			*Currentptr = newptr;
			Currentptr = &((*Currentptr)->getNextptr());
		}

		_last_ptr = newptr;
		_nodesCount = toCopy.size();

		return *this;
	}

	template <class T>
	void List<T>::clear()
	{
		this->~List();
	}

	template <class T>
	bool List<T>::empty()
	{
		return _node_ptr == nullptr;
	}

	template <class T>
	T &List<T>::front()
	{
		assert(_node_ptr != nullptr);
		return _node_ptr->getData();
	}

	template <class T>
	T &List<T>::back()
	{
		assert(_last_ptr != nullptr);
		return _last_ptr->getData();
	}

	template <class T>
	ostream &operator<<(ostream &output, const List<T> &toPrint)
	{
		for (auto it = toPrint.cbegin(); it != toPrint.cend(); it++)
		{
			output << *it << " ";
		}
	
		return output;
	}
	
	template <class T>
	int List<T>::size() const
	{
		return _nodesCount;
	}
	

	template <class T>
	class ListIterator
	{
	public:
		explicit ListIterator(ListNodeptr<T> ptr = nullptr);
		ListIterator<T> operator++();
		ListIterator<T> operator++(int);
		ListIterator<T> operator--();
		ListIterator<T> operator--(int);
		ListIterator<T> operator+(const int &count);
		bool operator==(const ListIterator<T> &it2);
		bool operator!=(const ListIterator<T> &it2);
		T & operator*();
		ListNodeptr<T> getPtr();
	private:
		ListNodeptr<T> _ptr;
	};

	template<class T>
	ListNodeptr<T> ListIterator<T>::getPtr()
	{
		return _ptr;
	}

	template<class T>
	ListIterator<T>::ListIterator(ListNodeptr<T> ptr)
	{
		_ptr = ptr;
	}

	template <class T>
	ListIterator<T> ListIterator<T>::operator++()
	{
		if (_ptr == nullptr)
			return *this;

		_ptr = _ptr->getNextptr();
		return *this;
	}
	
	template <class T>
	ListIterator<T> ListIterator<T>::operator++(int)
	{
		if (_ptr == nullptr)
			return *this;

		ListIterator<T> temp(_ptr);		
		_ptr = _ptr->getNextptr();
		return temp;
	}

	template <class T>
	ListIterator<T> ListIterator<T>::operator--()
	{
		if (_ptr == nullptr)
			return *this;

		_ptr = _ptr->getPreviousptr();
		return *this;
	}

	template <class T>
	ListIterator<T> ListIterator<T>::operator--(int)
	{
		if (_ptr == nullptr)
			return *this;

		ListIterator<T> temp(_ptr);
		_ptr = _ptr->getPreviousptr();
		return temp;
	}

	template <class T>
	ListIterator<T> ListIterator<T>::operator+(const int &count)
	{
		ListIterator<T> temp = *this;

		for (int i = 0; i < count; i++)
		{
			++temp;
		}

		return temp;
	}

	template <class T>
	bool ListIterator<T>::operator==(const ListIterator<T> &it2)
	{
		return _ptr == it2._ptr;
		
	}

	template <class T>
	bool ListIterator<T>::operator!=(const ListIterator<T> &it2)
	{
		return _ptr != it2._ptr;
	}

	template <class T>
	T &ListIterator<T>::operator*()
	{
		assert(_ptr != nullptr);
		return _ptr->getData();
	}

}


	
#endif
