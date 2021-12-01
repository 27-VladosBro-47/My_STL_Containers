#ifndef LINKED_LIST
#define LINKED_LIST

#include <cassert>
#include <initializer_list>
#include <iterator>


// =========================== LinkedList ===========================

template<typename T>
class LinkedList
{
protected:
	// Included class - "Node"
	// Type of relationship - composition
	// =============== Node ===============

	template<typename T>
	class Node
	{
	private:
		// --- Remark ---
		// I didn't plase class'es elements in private sections
		// Besause Node class is internal class of LinkedList class

	public:
		Node *ptrNextNode;			// A pointer to next element of list 
									// (or "to nullptr" if the next item doesn't exist)
		T data;						// Variable storages a custom data

		Node(const T data = T(), Node *ptrNextNode = nullptr) :
			data{ data },
			ptrNextNode{ ptrNextNode }
		{

		}

		~Node()
		{

		}
	};
	// ====================================


	Node<T> *head;				// Top of the list - first element
	int quantityElem;			// Quentity of list's elements


public:

	// Included class - "MyIterator"
	// Type of relationship - composition
	// =============== MyIterator ===============
	template<typename T>
	class MyIterator : public std::iterator<std::forward_iterator_tag, Node<T>>
	{
	public:

		MyIterator(Node<T> *ptr) : ptr{ ptr }
		{

		}

		T& operator*()
		{
			return ptr->data;
		}

		const T& operator*() const
		{
			return ptr->data;
		}

		T* operator->()
		{
			return ptr->data;
		}

		const T* operator->() const
		{
			return ptr->data;
		}

		const MyIterator<T> operator++()
		{
			ptr = ptr->ptrNextNode;
			return *this;
		}

		const MyIterator<T> operator++(int)
		{
			MyIterator<T> buffer = *this;
			++(*this);
			return buffer;
		}

		friend bool operator== (const MyIterator<T>& a, const  MyIterator<T>& b)
		{
			return a.ptr == b.ptr;
		}

		friend bool operator!= (const  MyIterator<T>& a, const  MyIterator<T>& b)
		{
			return a.ptr != b.ptr;
		};

	private:
		Node<T>* ptr;
	};
	// ==========================================

	LinkedList() : head{ nullptr }, quantityElem{ 0 }
	{

	}

	// Copy constructor
	LinkedList(const LinkedList &copy) : head{ nullptr }, quantityElem{ 0 }
	{
		*this = copy;
	}

	// Constructor initializer list
	LinkedList(const std::initializer_list<T> &init_list)
	{
		// Init ptrInitList with iterator init_list.begin() and use it such as pointer
		auto ptrInitList{ init_list.begin() };
		for (auto &element : init_list)
		{
			pushBack(*(ptrInitList++));
		}
	}

	MyIterator<T> begin();
	MyIterator<T> end();
	const MyIterator<T> cbegin() const;
	const MyIterator<T> cend() const;
	void pushBack(const T &data);
	void popBack();
	void pushFront(const T &data);
	void popFront();
	void insert(int index, const T &data);
	void remove(int index);
	void clear();
	int size() const;
	void assign(int size, const T &data);
	bool isEmpty() const;
	void swap(LinkedList<T> &list);
	LinkedList<T>& operator= (const LinkedList<T> &list);
	T& operator[] (const int index);
	const T& operator[] (const int index) const;

	// ========== friend-functions ==========
	template<typename T>
	friend void swap(LinkedList<T> &list1, LinkedList<T> &list2);

	template<typename T>
	friend bool operator<(const LinkedList<T> &list1, const LinkedList<T> &list2);

	template<typename T>
	friend bool operator<= (const LinkedList<T> &list1, const LinkedList<T> &list2);

	template<typename T>
	friend bool operator> (const LinkedList<T> &list1, const LinkedList<T> &list2);

	template<typename T>
	friend bool operator>= (const LinkedList<T> &list1, const LinkedList<T> &list2);

	template<typename T>
	friend bool operator== (const LinkedList<T> &list1, const LinkedList<T> &list2);

	template<typename T>
	friend bool operator!= (const LinkedList<T> &list1, const LinkedList<T> &list2);
	// ======================================

	~LinkedList()
	{
		// Clear allocated memory
		Node<T> *ptrCurrentElem{ head };
		Node<T> *ptrNextElem{ nullptr };
		while (ptrCurrentElem != nullptr)
		{
			ptrNextElem = ptrCurrentElem->ptrNextNode;
			delete ptrCurrentElem;
			ptrCurrentElem = ptrNextElem;
		}
	}
};

template<typename T>
LinkedList<T>::MyIterator<T> LinkedList<T>::begin()
{
	return MyIterator<T>(head);
}

template<typename T>
LinkedList<T>::MyIterator<T> LinkedList<T>::end()
{
	// Go to the last element of list
	Node<T> *ptrBuffElem{ head };
	for (int element = 0; element < (quantityElem); ++element)
	{
		ptrBuffElem = ptrBuffElem->ptrNextNode;
	}
	return MyIterator<T>(ptrBuffElem);
}

template<typename T>
const LinkedList<T>::MyIterator<T> LinkedList<T>::cbegin() const
{
	return MyIterator<T>(head);
}

template<typename T>
const LinkedList<T>::MyIterator<T> LinkedList<T>::cend() const
{
	// Go to the last element of list
	Node<T> *ptrBuffElem{ head };
	for (int element = 0; element < (quantityElem); ++element)
	{
		ptrBuffElem = ptrBuffElem->ptrNextNode;
	}
	return MyIterator<T>(ptrBuffElem);
}

template<typename T>
void LinkedList<T>::pushBack(const T &data)
{
	// If head is empty, so add an element
	// Else - find the last element of list
	if (head == nullptr)
	{
		head = new (std::nothrow) Node<T>(data);
		if (head == nullptr)
		{
			std::cerr << "LinkedList::pushBack\n Cannot allocate memory to new elemment!\n";
		}

		// Increase counter of elements
		++quantityElem;
	}
	else
	{
		// Create buffer ptr to Node class, which will use to find the last element of list 
		Node<T> *ptrCurrentElem{ head };

		// Start finding the last element
		while (ptrCurrentElem->ptrNextNode != nullptr)
		{
			ptrCurrentElem = ptrCurrentElem->ptrNextNode;
		}

		// Add new element to the end of list
		ptrCurrentElem->ptrNextNode = new (std::nothrow) Node<T>(data);
		if (ptrCurrentElem->ptrNextNode == nullptr)
		{
			std::cerr << "LinkedList::pushBack()\n Cannot allocate memory to new elemment!\n";
		}

		// increase counter of elements
		++quantityElem;
	}
}

template<typename T>
void LinkedList<T>::popBack()
{
	remove(quantityElem - 1);
}

template<typename T>
void LinkedList<T>::pushFront(const T &data)
{
	// If head is empty, so add an element
	// Else - to move list and add new element to the top
	if (head == nullptr)
	{
		head = new (std::nothrow) Node<T>(data);
		if (head == nullptr)
		{
			std::cerr << "LinkedList::pushFront\n Cannot allocate memory to new elemment!\n";
		}

		// Increase counter of elements
		++quantityElem;
	}
	else
	{
		Node<T> *ptrBuffElem{ head };
		head = new (std::nothrow) Node<T>(data, ptrBuffElem);
		if (head == nullptr)
		{
			std::cerr << "LinkedList::pushFront()\n Cannot allocate memory to new elemment!\n";
		}

		// Increase counter of elements
		++quantityElem;
	}
}

template<typename T>
void LinkedList<T>::popFront()
{
	// If list isn't empty, then delete first element
	if (head != nullptr)
	{
		// Create buffer ptr to Node class and save next elem after head elem
		Node<T> *ptrBuffElem{ head->ptrNextNode };
		// Free memory
		delete head;
		// Make ptrBuffElem the first element
		head = ptrBuffElem;

		// Decrease counter of elements
		--quantityElem;
	}
}

template<typename T>
void LinkedList<T>::insert(int index, const T &data)
{
	// Check index of list
	assert(index >= 0 && index <= quantityElem && "Error. Wrong index!\n");

	if (index == 0)
	{
		pushFront(data);
	}
	else
	{
		// First of all, we must find the previous element
		// Before the element below the specified index

		// Variable contains previous element
		Node<T> *ptrPrevElem{ head };
		// Finding previous element
		for (int element = 0; element < (index - 1); ++element)
		{
			ptrPrevElem = ptrPrevElem->ptrNextNode;
		}

		// Buffer var for new element with index "index"
		// And set ptr to next elem after our new element            \/ (here) \/
		Node<T> *ptrNewElem = new (std::nothrow) Node<T>(data, ptrPrevElem->ptrNextNode);
		assert(ptrNewElem != nullptr && "LinkedList::insert()\n Cannot allocate memory to new elemment!\n");

		// Set pointer to next elememt of ptrPrevElem to a new element
		ptrPrevElem->ptrNextNode = ptrNewElem;

		// Increase counter of elements
		++quantityElem;
	}
}

template<typename T>
void LinkedList<T>::remove(int index)
{
	// Check index of list
	assert(index >= 0 && index <= quantityElem && "Error. Wrong index!\n");

	if (index == 0)
	{
		popFront();
	}
	else
	{

		// Buffer variable contains previous element to delete
		Node<T> *ptrPrevElem{ head };
		// Finding previous element
		for (int element = 0; element < (index - 1); ++element)
		{
			ptrPrevElem = ptrPrevElem->ptrNextNode;
		}

		// Create buff variable for next elem after element to delete
		Node<T> *ptrNextNode = ptrPrevElem->ptrNextNode->ptrNextNode;
		// Free memory of deleted elem
		delete ptrPrevElem->ptrNextNode;
		// Restore the list "chain"
		ptrPrevElem->ptrNextNode = ptrNextNode;

		// Decrease counter of elements
		--quantityElem;
	}

}

template<typename T>
void LinkedList<T>::clear()
{
	// If list isn't empty, then delete all elements of list
	if (head != nullptr)
	{
		int size = quantityElem;
		for (int element = 0; element < size; ++element)
		{
			popFront();
		}
	}
}

template<typename T>
int LinkedList<T>::size() const
{
	return quantityElem;
}

template<typename T>
void LinkedList<T>::assign(int size, const T &data)
{
	// Check a correct number of element
	assert(size > 0 && "Error. Size must be more then 0!\n");

	if (size <= quantityElem)	// If size of list less then quentity of new elements
	{
		// Determine the number of items that need to be deleted
		int countElemForDelete{ (quantityElem - size) };

		// Delete excess elements
		for (int element = 0; element < countElemForDelete; ++element)
		{
			popBack();
		}

		// Edit data of list and appropriate new data
		Node<T> *ptrCurrentElem{ head };
		for (int element = 0; element < quantityElem; ++element)
		{
			ptrCurrentElem->data = data;
			ptrCurrentElem = ptrCurrentElem->ptrNextNode;
		}
	}
	else // If size of list more then quentity of new elements
	{
		// Determine the number of items that need to be add
		int countElemForAdd{ (size - quantityElem) };

		// Edit data of list and appropriate new data
		Node<T> *ptrCurrentElem{ head };
		for (int element = 0; element < quantityElem; ++element)
		{
			ptrCurrentElem->data = data;
			ptrCurrentElem = ptrCurrentElem->ptrNextNode;
		}

		// Add other elements
		for (int element = 0; element < countElemForAdd; ++element)
		{
			pushBack(data);
		}
	}
}

template<typename T>
bool LinkedList<T>::isEmpty() const
{
	return (head == nullptr) ? true : false;
}

template<typename T>
void swap(LinkedList<T> &list1, LinkedList<T> &list2)
{
	// self-assignment check
	if (&list1 != &list2)
	{
		LinkedList<T> buffList = list1;
		list1 = list2;
		list2 = buffList;
	}
}

template<typename T>
void LinkedList<T>::swap(LinkedList<T> &list)
{
	// Self-assignment check
	if (this != &list)
	{
		LinkedList<T> buffList = *this;

		*this = list;
		list = buffList;
	}
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator= (const LinkedList<T> &list)
{
	// Self-assignment check
	if (this == &list)
	{
		return *this;
	}

	// Clear list, in which will copying
	clear();
	// Make copy of list's elements
	for (int element = list.size() - 1; element >= 0; --element)
	{
		pushFront(list[element]);
	}

	// Return list, in which copied
	return *this;
}

template<typename T>
T& LinkedList<T>::operator[] (const int index)
{
	// Check index of list
	assert(index >= 0 && index <= quantityElem && "Error. Wrong index!\n");

	// Create buffer ptr to Node class, which will use to find the necessary element of list 
	Node<T> *ptrCurrentElem{ head };
	for (int element = 0; element < index; ++element)
	{
		ptrCurrentElem = ptrCurrentElem->ptrNextNode;
	}

	return ptrCurrentElem->data;
}

template<typename T>
const T& LinkedList<T>::operator[] (const int index) const
{
	// Check index of list
	assert(index >= 0 && index <= quantityElem && "Error. Wrong index!\n");

	// Create buffer ptr to Node class, which will use to find the necessary element of list 
	Node<T> *ptrCurrentElem{ head };
	for (int element = 0; element < index; ++element)
	{
		ptrCurrentElem = ptrCurrentElem->ptrNextNode;
	}

	return ptrCurrentElem->data;
}

template<typename T>
bool operator<(const LinkedList<T> &list1, const LinkedList<T> &list2)
{
	int size = (list1.quantityElem <= list2.quantityElem) ? list1.quantityElem : list2.quantityElem;

	for (int element = 0; element < size; ++element)
	{
		if (list1[element] != list2[element])
		{
			return (list1[element] < list2[element]) ? true : false;
		}
	}

	return (list1.quantityElem < list2.quantityElem) ? true : false;
}

template<typename T>
bool operator<= (const LinkedList<T> &list1, const LinkedList<T> &list2)
{
	int size = (list1.quantityElem <= list2.quantityElem) ? list1.quantityElem : list2.quantityElem;

	for (int element = 0; element < size; ++element)
	{
		if (list1[element] != list2[element])
		{
			return (list1[element] < list2[element]) ? true : false;
		}
	}

	return (list1.quantityElem <= list2.quantityElem) ? true : false;
}

template<typename T>
bool operator> (const LinkedList<T> &list1, const LinkedList<T> &list2)
{
	int size = (list1.quantityElem <= list2.quantityElem) ? list1.quantityElem : list2.quantityElem;

	for (int element = 0; element < size; ++element)
	{
		if (list1[element] != list2[element])
		{
			return (list1[element] > list2[element]) ? true : false;
		}
	}

	return (list1.quantityElem > list2.quantityElem) ? true : false;
}

template<typename T>
bool operator>= (const LinkedList<T> &list1, const LinkedList<T> &list2)
{
	int size = (list1.quantityElem <= list2.quantityElem) ? list1.quantityElem : list2.quantityElem;

	for (int element = 0; element < size; ++element)
	{
		if (list1[element] != list2[element])
		{
			return (list1[element] > list2[element]) ? true : false;
		}
	}

	return (list1.quantityElem >= list2.quantityElem) ? true : false;
}

template<typename T>
bool operator== (const LinkedList<T> &list1, const LinkedList<T> &list2)
{
	if (list1.quantityElem == list2.quantityElem)
	{
		int size = list1.quantityElem;

		for (int element = 0; element < size; ++element)
		{
			if (list1[element] != list2[element])
			{
				return false;
			}
		}

		return true;
	}
	else
	{
		return false;
	}
}

template<typename T>
bool operator!= (const LinkedList<T> &list1, const LinkedList<T> &list2)
{
	if (list1.quantityElem == list2.quantityElem)
	{
		int size = list1.quantityElem;

		for (int element = 0; element < size; ++element)
		{
			if (list1[element] != list2[element])
			{
				return true;
			}
		}

		return false;
	}
	else
	{
		return true;
	}
}

// ==================================================================



template<typename T>
class TestLinkedList : public LinkedList<T>
{
public:
	TestLinkedList() : LinkedList<T>()
	{

	}

	~TestLinkedList()
	{

	}

	bool DefaultConstructorTest()
	{
		bool test[2]{ true, true };

		test[0] = (LinkedList<T>::head == nullptr) ? true : false;
		test[1] = (LinkedList<T>::quantityElem == 0) ? true : false;

		return (test[0] && test[1]);
	}

	bool NodeDefaultConstructorTest()
	{
		bool test[2]{ true, true };

		LinkedList<T>::template LinkedList::Node node<T>();

		test[0] = (node.data == T()) ? true : false;
		test[1] = (node.ptrNextNode == nullptr) ? true : false;

		return (test[0] && test[1]);
	}

};

#endif
