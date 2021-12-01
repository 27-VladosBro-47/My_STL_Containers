#ifndef BINARY_TREE
#define BINARY_TREE

#include <iostream>

// Remark
// Root of tree is external object
// When calling BinaryTree class methods to interact with a tree
// you must pass the tree root (Node<T>*) to the class method
//
// !!! Node<int>* YourRootOfTree must initialize by nullptr before using
//
// --- Exemple---
//
//int main()
//{
//	Node<int>* myRoot = nullptr;
//	BinaryTree<int> myTree;
//
//	myTree.insert(30, myRoot);
//	myTree.insert(20, myRoot);
//	myTree.insert(50, myRoot);
//
//	myTree.upwards(myRoot);
//
//	return 0;
//}



// =========================== BinaryTree ===========================

// Extra class - "Node"
// Type of relationship - aggregation
// =============== Node ===============
template <typename T>
class Node
{
public:
	T element;
	Node *left;
	Node *right;
	int height;

	Node()
	{
		element = 0;
		left = nullptr;
		right = nullptr;
		height = 0;
	}

	Node(T element, Node *left, Node *right, int height)
	{
		this->element = element;
		this->left = left;
		this->right = right;
		this->height = height;
	}

	~Node()
	{

	}
};

// ====================================

template<typename T>
class BinaryTree
{
private:

	int max(int val1, int val2);
	int balance(Node<T>* &ptrNode);
	void balanceHeight(Node<T>* &ptrNode);
	int deleteMinNode(Node<T>* &ptrNode);
	Node<T>* leftRotation(Node<T>* &ptrNode);
	Node<T>* doubleLeftRotation(Node<T>* &ptrNode);
	Node<T>* rightRotation(Node<T>* &ptrNode);
	Node<T>* doubleRightRotation(Node<T>* &ptrNode);

public:

	BinaryTree()
	{

	}

	bool insert(T data, Node<T>* &ptrNode);
	Node<T>* findMinNode(Node<T>* ptrNode);
	Node<T>* findMaxNode(Node<T>* ptrNode);
	bool isExist(T data, Node<T>* &ptrNode);
	void clear(Node<T>* &ptrNode);
	int height(Node<T>* ptrNode);
	bool deleteNode(T data, Node<T>* &ptrNode);
	void topDown(Node<T>* ptrNode);
	void symmetrical(Node<T>* ptrNode);
	void upwards(Node<T>* ptrNode);

	~BinaryTree()
	{

	}
};

// ---------------- private-methods ---------------- 

// Àunction to get more value 
template<typename T>
int BinaryTree<T>::max(int val1, int val2)
{
	return val1 > val2 ? val1 : val2;
}

// Get the difference between the heights of the two descendants, to determine further "rotation"
template<typename T>
int BinaryTree<T>::balance(Node<T>* &ptrNode)
{
	return abs(height(ptrNode->left) - height(ptrNode->right));
}

// Function balances the height after adding an element
template<typename T>
void BinaryTree<T>::balanceHeight(Node<T>* &ptrNode)
{
	int hLeft = height(ptrNode->left);
	int hRight = height(ptrNode->right);
	ptrNode->height = max(hLeft, hRight) + 1;
}

// Data transfer from the last node 
template<typename T>
int BinaryTree<T>::deleteMinNode(Node<T>* &ptrNode)
{
	int buffData;
	if (ptrNode->left == nullptr)
	{
		buffData = ptrNode->element;
		ptrNode = ptrNode->right;
		return buffData;
	}
	else
	{
		buffData = deleteMinNode(ptrNode->left);
		return buffData;
	}
}

// Make Left-Rotation
template<typename T>
Node<T>* BinaryTree<T>::leftRotation(Node<T>* &ptrNode)
{
	Node<T>* ptrNode1;
	ptrNode1 = ptrNode->left;
	ptrNode->left = ptrNode1->right;
	ptrNode1->right = ptrNode;
	ptrNode->height = max(height(ptrNode->left), height(ptrNode->right)) + 1;
	ptrNode1->height = max(height(ptrNode1->left), ptrNode->height) + 1;
	return ptrNode1;
}

// Make Right-Rotation
template<typename T>
Node<T>* BinaryTree<T>::rightRotation(Node<T>* &ptrNode)
{
	Node<T>* ptrNode1;
	ptrNode1 = ptrNode->right;
	ptrNode->right = ptrNode1->left;
	ptrNode1->left = ptrNode;
	ptrNode->height = max(height(ptrNode->left), height(ptrNode->right)) + 1;
	ptrNode1->height = max(ptrNode->height, height(ptrNode1->right)) + 1;
	return ptrNode1;
}

// Make double Left-Rotation
template<typename T>
Node<T>* BinaryTree<T>::doubleLeftRotation(Node<T>* &ptrNode)
{
	ptrNode->left = rightRotation(ptrNode->left);
	return leftRotation(ptrNode);
}

// Make double Right-Rotation
template<typename T>
Node<T>* BinaryTree<T>::doubleRightRotation(Node<T>* &ptrNode)
{
	ptrNode->right = leftRotation(ptrNode->right);
	return rightRotation(ptrNode);
}

// -------------------------------------------------


// ---------------- public-methods ---------------- 

// Inserting a Node
// Return true if add is successful else return false
// If you add an existing item, the item will not be added
// and the function will return false
template<typename T>
bool BinaryTree<T>::insert(T data, Node<T>* &ptrNode)
{
	if (ptrNode == nullptr)
	{
		ptrNode = new Node<T>(data, nullptr, nullptr, 0);
		if (ptrNode == nullptr)
		{
			std::cerr << "BinaryTree::insert\nCannot allocate memory to new elemment!\n";
			return false;
		}
	}
	else
	{
		// If inserted data less then data of current node
		if (data < ptrNode->element)
		{
			// Move on left-side subtree
			insert(data, ptrNode->left);
			// After inserted, making balancing
			if (balance(ptrNode) == 2)
			{
				if (data < ptrNode->left->element)
				{
					// Make Left-Rotation
					ptrNode = leftRotation(ptrNode);
				}
				else
				{
					// Make double Left-Rotation
					ptrNode = doubleLeftRotation(ptrNode);
				}
			}
		}
		else if (data > ptrNode->element) // If inserted data bigger then data of current node
		{
			// Move on right-side subtree
			insert(data, ptrNode->right);
			// After inserted, making balancing
			if (balance(ptrNode) == 2)
			{
				if (data > ptrNode->right->element)
				{
					// Make Right-Rotation
					ptrNode = rightRotation(ptrNode);
				}
				else
				{
					// Make double Right-Rotation
					ptrNode = doubleRightRotation(ptrNode);
				}
			}
		}
		else // The element has already exists
		{
			std::cout << "The element has already exists." << std::endl;
			return false;
		}
	}

	// After inserting and balancing, need to correct height of Node
	balanceHeight(ptrNode);
	return true;
}

// Function finds the smallest element
// If tree is empty, return nullptr
template<typename T>
Node<T>* BinaryTree<T>::findMinNode(Node<T>* ptrNode)
{
	// Because it is binary tree, the smallest element will be the most "left" element
	// Ñheck that the node is not nullptr 
	if (ptrNode == nullptr)
	{
		return ptrNode;
	}
	else
	{
		// Find the most "left" element
		while (ptrNode->left != nullptr)
		{
			ptrNode = ptrNode->left;
		}
		return ptrNode;
	}
}

// Function finds the bigest element
// If tree is empty, return nullptr
template<typename T>
Node<T>* BinaryTree<T>::findMaxNode(Node<T>* ptrNode)
{
	// Because it is binary tree, the biggest element will be the most "right" element
	// Ñheck that the node is not nullptr 
	if (ptrNode == nullptr)
	{
		return ptrNode;
	}
	else
	{
		// Find the most "right" element
		while (ptrNode->right != nullptr)
		{
			ptrNode = ptrNode->right;
		}
		return ptrNode;
	}
}

// Function searches for the specified element in the nodes of the tree
// Return true if element is exist else return false
template<typename T>
bool BinaryTree<T>::isExist(T data, Node<T>* &ptrNode)
{
	if (ptrNode == nullptr)
	{
		// Element isn't exist
		return false;
	}
	else
	{
		// Move relative to the left-right-side subtree,
		// depending on the specified value to search and the current value of the node
		if (data < ptrNode->element)
		{
			isExist(data, ptrNode->left);
		}
		else
		{
			if (data > ptrNode->element)
			{
				isExist(data, ptrNode->right);
			}
			else // if data == p->element then its out searched element
			{
				// Element is exist
				return true;
			}
		}
	}
}

// Clear a binary tree
template<typename T>
void BinaryTree<T>::clear(Node<T>* &ptrNode)
{
	// Recursively clear memory
	if (ptrNode != nullptr)
	{
		clear(ptrNode->left);
		clear(ptrNode->right);
		delete ptrNode;
		ptrNode = nullptr;
	}
}

// Get height of tree/subtree
template<typename T>
int BinaryTree<T>::height(Node<T>* ptrNode)
{
	if (ptrNode == nullptr)
	{
		return -1;
	}
	else
	{
		return ptrNode->height;
	}
}

// Function deletes a node with the specified value
template<typename T>
bool BinaryTree<T>::deleteNode(T data, Node<T>* &ptrNode)
{
	Node<T>* ptrBuffNode;
	if (ptrNode == nullptr)
	{
		return false;
	}
	else if (data < ptrNode->element)
	{
		deleteNode(data, ptrNode->left);
	}
	else if (data > ptrNode->element)
	{
		deleteNode(data, ptrNode->right);
	}
	else if ((ptrNode->left == nullptr) && (ptrNode->right == nullptr))
	{
		delete ptrNode;
		ptrNode = nullptr;
		return true;
	}
	else if (ptrNode->left == nullptr)
	{
		ptrBuffNode = ptrNode;
		delete ptrNode;
		ptrNode = ptrBuffNode->right;
		return true;
	}
	else if (ptrNode->right == nullptr)
	{
		ptrBuffNode = ptrNode;
		ptrNode = ptrNode->left;
		delete ptrBuffNode;
		return true;
	}
	else
	{
		ptrNode->element = deleteMinNode(ptrNode->right);
	}
}

// PreOrder shows elements
template<typename T>
void BinaryTree<T>::topDown(Node<T>* ptrNode)
{
	if (ptrNode != nullptr)
	{
		std::cout << ptrNode->element << "  ";
		topDown(ptrNode->left);
		topDown(ptrNode->right);
	}

}

// InOrder shows elements
template<typename T>
void BinaryTree<T>::symmetrical(Node<T>* ptrNode)
{
	if (ptrNode != nullptr)
	{
		symmetrical(ptrNode->left);
		std::cout << ptrNode->element << "  ";
		symmetrical(ptrNode->right);
	}
}

// PostOrder shows elements
template<typename T>
void BinaryTree<T>::upwards(Node<T>* ptrNode)
{
	if (ptrNode != nullptr)
	{
		upwards(ptrNode->left);
		upwards(ptrNode->right);
		std::cout << ptrNode->element << "  ";
	}
}

// ------------------------------------------------

// ==================================================================

#endif