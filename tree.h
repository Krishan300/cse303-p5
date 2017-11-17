#pragma once
#include <algorithm>    // std::max


/// TODO: complete this implementation of a thread-safe (concurrent) AVL
///       tree of integers, implemented as a set of Node objects.
///       In addition, the API now allows for multiple insertions on each
///       operation.
///       Less than goes to the left. Greater than goes to the right.
class tree
{
//This is for testing purposes. Do not access your Node directly.
public:
	struct Node
	{
		public:
			int value;
			Node* left;
			Node* right;
	};
	Node* head;



public:
	tree(int)
	: head(NULL)
	{}


	bool inserthelper(int data){
		if(head == NULL)
		{
			head = new Node;
			head -> value = *data;
			head -> left = NULL;
			head -> right = NULL;
		}
		else if(key< head->value)
		{
			head->left = insert((int*)(head->left->value), results, num);
			head = balance(head);
		}
		else if(key >= head->value)
		{
			head->right = insert(head->right->value, key);
			head = balance(head);
		}


	}
	/// insert /num/ values from /data/ array into the tree, and return the
	/// success/failure of each insert in /results/ array.
	void insert(int* data, bool* results, int num)
	{
	
		for(int i=0; i<num; i++){
			int insertvalue=data[i];
			bool retval=inserthelper(insertvalue);
			results[i]=retval;

		}
	}

	int findHeight(Node* node)
	{
		int height = 0;
		if(node != NULL)
		{
			int leftHeight = findHeight(node->left);
			int rightHeight = findHeight(node->right);
			int max = std::max(leftHeight, rightHeight);
			height = max +1;
		}
		return height;
	}

	Node* balance(Node* head)
	{
		int balanceFactor = findHeight(head->left)-findHeight(head->right);
		return head;
	}

	/// remove *data* from the list if it was present; return true if the data
	/// was removed successfully.
	void remove(int* data, bool* results, int num)
	{}
	/// return true if *data* is present in the list, false otherwise
	void lookup(int* data, bool* results, int num) const
	{}

	//The following are not tested by the given tester but are required for grading
	//No locks are required for these.

	//Total number of elements in the tree
	size_t getSize() const
	{
		return 0;
	}

	int getElement(size_t idx) const
	{
		return getElement(0, head);
	}


	//These functions need to exist, they do not need to do anyting
	size_t getBucketSize() const
	{
		return 0;
	}
	int getElement(size_t bucket, size_t idx) const
	{
		return 0;
	}



private:
	//Returns the idx'th element from the tree assuming an inorder traversal.
	int getElement(size_t idx, Node* at) const
	{
		return 0;
	}
};
