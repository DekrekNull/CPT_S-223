#ifndef __BST_H
#define __BST_H

#include <iostream>
#include <limits>
#include <tgmath.h>

using namespace std;


/*
 *  Data structure for a single tree node
 */
template <typename T>
struct Node {
public:
	T value;
	Node* left;
	Node* right;

	Node(T val) {
		this->value = val;
		this->left = nullptr;
		this->right = nullptr;
	}

	~Node()
	{
		this->value = 0;
		this->left = nullptr;
		this->right = nullptr;
	}
};

/*
 * Binary Search Tree (BST) class implementation
 */
template <typename T>
class BST {

protected:
	Node<T>* _root;         // Root of the tree nodes

	/* Add new T val to the tree */
	void addHelper(Node<T>* root, T val) {
		if (root->value > val) {
			if (!root->left) {
				root->left = new Node<T>(val);
			}
			else {
				addHelper(root->left, val);
			}
		}
		else {
			if (!root->right) {
				root->right = new Node<T>(val);
			}
			else {
				addHelper(root->right, val);
			}
		}
	}

	/* Print tree out in inorder (A + B) */
	void printInOrderHelper(Node<T>* root) {
		if (!root) return;
		printInOrderHelper(root->left);
		cout << root->value << ' ';
		printInOrderHelper(root->right);
	}

	/* Return number of nodes in tree */
	int nodesCountHelper(Node<T>* root) {
		if (!root) {
			return 0;
		}
		else {
			return 1 + nodesCountHelper(root->left) + nodesCountHelper(root->right);
		}
	}

	/* Return height of tree (root == nullptr -> 0) */
	int heightHelper(Node<T>* root) {
		if (!root) {
			return -1;
		}
		else {
			return 1 + max(heightHelper(root->left), heightHelper(root->right));
		}
	}

	/* Delete a given <T> value from tree */
	bool deleteValueHelper(Node<T>* parent, Node<T>* current, T value) {
		if (!current) return false;
		if (current->value == value) {
			if (current->left == nullptr || current->right == nullptr) {
				Node<T>* temp = current->left;
				if (current->right) temp = current->right;
				if (parent) {
					if (parent->left == current) {
						parent->left = temp;
					}
					else {
						parent->right = temp;
					}
				}
				else {
					this->_root = temp;
				}
			}
			else {
				Node<T>* validSubs = current->right;
				while (validSubs->left) {
					validSubs = validSubs->left;
				}
				T temp = current->value;
				current->value = validSubs->value;
				validSubs->value = temp;
				return deleteValueHelper(current, current->right, temp);
			}
			delete current;
			return true;
		}
		return deleteValueHelper(current, current->left, value) ||
			deleteValueHelper(current, current->right, value);
	}

	/* Determines if a given <T> value is in the tree or not */
	bool containsHelper(Node<T>* current, T value) {
	    if(!current) {
	        return false;
	    }else if (current->value == value) {
	        return true;
	    } else if (current->value > value){
	        return this->containsHelper(current->left, value);
	    }else {
	        return this->containsHelper(current->right, value);
	    }
	}
    /* Prints all of the values at the given level */
    void printLevel(Node<T>* current, int level){
	   if(!current) return;
	   if(level == 1) cout << current->value << " ";
	   else if (level > 1){
	       printLevel(current->left, level - 1);
           printLevel(current->right, level - 1);
	   }
	}

	/* Prints the tree one level at a time */
	void printLevelOrderHelper(Node<T>* current) {
	    int height = this->height();
	    for(int i = 1; i <= height + 1; i++){
	        this->printLevel(current, i);
	        cout << endl;
	    }
	}

	/* Returns the value of the first node at the lowest levelof the tree */
    int valueOfEndNode(Node<T>* current, int level){
	    if(current){
	        if(level == this->height()) return current->value;
	        return valueOfEndNode(current->left, level+1) + valueOfEndNode(current->right, level+1);
	    }else return 0;
	}

    /* Prints the path from the root to the first node at the lowest level of the tree */
    void printMaxPathHelper() {
	    int value = valueOfEndNode(this->_root, 0);
	    Node<T>* current = this->_root;
	    while(current != nullptr) {
	        cout << current->value << " ";
	        if(current->value > value) current = current->left;
	        else current = current->right;
	    }
	}

	/* Deletes every node in the tree */
	void destructorHelper(Node<T>* current){
	    if(current){
	        destructorHelper(current->left);
	        destructorHelper(current->right);
	        delete current;
	    }
	}

	/********************************* PUBLIC API *****************************/
public:

	BST() : _root(nullptr) { }               // Basic initialization constructor

	~BST() {
	    destructorHelper(this->_root);
	}

	/* Public API */
	void add(T val) {
		if (this->_root) {
			this->addHelper(this->_root, val);
		}
		else {
			this->_root = new Node<T>(val);
		}
	}

	void print() {
		printInOrderHelper(this->_root);
	}

	void printLevelOrder() {
	    if(this->_root) this->printLevelOrderHelper(this->_root);
	}

	int nodesCount() {
		return nodesCountHelper(this->_root);
	}

	int height() {
		return heightHelper(this->_root);
	}

	void printMaxPath() {
	    this->printMaxPathHelper();
	}

	bool deleteValue(T value) {
		return this->deleteValueHelper(nullptr, this->_root, value);
	}

	bool contains(T value) {
	    return this->containsHelper(this->_root, value);
	}
};

#endif

