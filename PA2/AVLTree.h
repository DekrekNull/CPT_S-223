#include "AVLNode.h"
#ifndef UNTITLED_AVLTREE_H
#define UNTITLED_AVLTREE_H
template<class T> class AVLTree{
protected:
    AVLNode<T> *_root;

    AVLNode<T> *findImbalance(AVLNode<T> *current); /* Find the deepest node that has a height violation */
    int determineCase(AVLNode<T> *k); /* Determines the case of the height violation and returns it as an int 1-4 */
    void balance(); /* Uses AVL rotations to balance the tree when a height violation has been found */
    void updateTreeHeight(AVLNode<T> *current); /* Updates the height of every nod in the tree */
    int updateNodeHeightHelper(AVLNode<T> *current); /* Determines and returns the height of the given node */
    void updateNodeHeight(AVLNode<T> *current); /* Updates the height of a given node */
    int validateHelper(AVLNode<T> *current); /* Uses recursion to determine if the tree is balanced */
    int containsHelper(AVLNode<T> *current, T value); /* Recursively checks if the given node is in the tree */
    void destructorHelper(AVLNode<T> *current); /* Recursively deletes each node in a right, left, root order */
public:
    AVLTree();
    ~AVLTree();
    int height(); /* returns height of the AVLTree */
    void insert(T value); /* Add a new node to the tree with the given value, maintaining balance */
    int contains(T value); /* return 1 if value is in tree, 0 if not */
    int validate(); /* return 1 if tree is balanced, 0 if not */
};
                    /* Protected Methods */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void AVLTree<T>::balance() {
    AVLNode<T> *k= findImbalance(this->_root);
    int imbalanceCase = this->determineCase(k);
    AVLNode<T> *temp, *temp2, *newSubRoot, *parent;
    switch(imbalanceCase) {
        case 1:
            temp = k->left;
            k->left = k->left->right;
            temp->right = k;
            newSubRoot = temp;
            break;
        case 2:
            temp = k->left;
            temp2 = temp->right;
            k->left = temp2->right;
            temp2->right = k;
            temp->right = temp2->left;
            temp2->left = temp;
            newSubRoot = temp2;
            break;
        case 3:
            temp = k->right;
            temp2 = temp->left;
            k->right = temp2->left;
            temp2->left = k;
            temp->left = temp2->right;
            temp2->right = temp;
            newSubRoot = temp2;
            break;
        case 4:
            temp = k->right;
            k->right = k->right->left;
            temp->left = k;
            newSubRoot = temp;
            break;
        default:
            return;
    }
    if (k->data == this->_root->data) this->_root = newSubRoot;
    else {
        parent = this->_root;
        while(true){
            if(k->data > parent->data) {
                if(k->data == parent->right->data) {
                    parent->right = newSubRoot;
                    break;
                }
                else parent = parent->right;
            }
            else {
                if (k->data == parent->left->data) {
                    parent->left = newSubRoot;
                    break;
                }
                else parent = parent->left;
            }
        }
    }
    this->updateTreeHeight(this->_root);
}

template<class T>
int AVLTree<T>::determineCase(AVLNode<T> *k) {
    int kLeft = -1;
    int kRight = -1;
    int childLeft = -1;
    int childRight = -1;
    AVLNode<T> *child;
    if (k->left) kLeft = k->left->height;
    if (k->right) kRight = k->right->height;
    if (kLeft > kRight){
        child = k->left;
        if (child->left) childLeft = child->left->height;
        if(child->right) childRight = child->right->height;
        if(childLeft > childRight) return 1;
        else return 2;
    }
    else{
        child = k->right;
        if (child->left) childLeft = child->left->height;
        if(child->right) childRight = child->right->height;
        if(childLeft > childRight) return 3;
        else return 4;
    }
}

template<class T>
void AVLTree<T>::updateTreeHeight(AVLNode<T> *current) {
    if(current){
       this->updateNodeHeight(current);
       this->updateTreeHeight(current->left);
       this->updateTreeHeight(current->right);
    }
}

template<class T>
void AVLTree<T>::updateNodeHeight(AVLNode<T> *current) {
    current->height = this->updateNodeHeightHelper(current);
}

template<class T>
int AVLTree<T>::updateNodeHeightHelper(AVLNode<T> *current) {
    if (!current) return -1;
    else return std::max(this->updateNodeHeightHelper(current->left), this->updateNodeHeightHelper(current->right)) + 1;
}

template<class T>
AVLNode<T>* AVLTree<T>::findImbalance(AVLNode<T> *current) {
    if(current){
        int rightH = -1;
        int leftH = -1;
        AVLNode<T> *leftST = this->findImbalance(current->left);
        AVLNode<T> *rightST = this->findImbalance(current->right);
        if(leftST) return leftST;
        else if(rightST) return rightST;
        else {
            if(current->right) rightH = current->right->height;
            if(current->left) leftH = current->left->height;
            if(rightH +1 < leftH || rightH > leftH + 1) return current;
        }
    }
    return nullptr;
}

template<class T>
int AVLTree<T>::validateHelper(AVLNode<T> *current) {
    int left = -1;
    int right = -1;
    if(current){
        if(current->left) left = current->left->height;
        if(current->right) right = current->right->height;

        if((left + 1 < right) || (left > right + 1)) return 0;
        else return std::min(this->validateHelper(current->left), this->validateHelper(current->right));
    }
    return 1;
}

template<class T>
int AVLTree<T>::containsHelper(AVLNode<T> *current, T value) {
    if(current){
        if(current->data == value) return 1;
        else return this->containsHelper(current->left, value) + this->containsHelper(current->right, value);
    }
    return 0;
}

template<class T>
void AVLTree<T>::destructorHelper(AVLNode<T> *current) {
    if(current){
        this->destructorHelper(current->right);
        this->destructorHelper(current->left);
        delete current;
    }
}

                /* Public API */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
AVLTree<T>::AVLTree() {
    this->_root = nullptr;
}

template<class T>
AVLTree<T>::~AVLTree() {
    this->destructorHelper(this->_root);
}

template<class T>
int AVLTree<T>::height() {
    if(!this->_root) return -1;
    else return this->_root->height;
}

template<class T>
void AVLTree<T>::insert(T value) {
    if(!this->_root) this->_root = new AVLNode<T>(value);
    else if(!this->contains(value)) {
        AVLNode<T> *current = this->_root;
        while(true){
            if(value > current->data) {
                if(current->right) {
                    current = current->right;
                }
                else {
                    current->right = new AVLNode<T>(value);
                    break;
                }

            }else if (value < current->data) {
                if(current->left) {
                    current = current->left;
                }
                else {
                    current->left = new AVLNode<T>(value);
                    break;
                }
            }
        }
        current = this->_root;
        while(current){
            this->updateNodeHeight(current);
            if (value > current->data) current = current->right;
            else current = current->left;
        }
        if(!this->validate()){
            this->balance();
        }
    }
}

template<class T>
int AVLTree<T>::contains(T value) {
    return this->containsHelper(this->_root, value);
}

template<class T>
int AVLTree<T>::validate() {
    return this->validateHelper(this->_root);
}

#endif //UNTITLED_AVLTREE_H
