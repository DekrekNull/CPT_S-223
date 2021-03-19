#ifndef UNTITLED_AVLNODE_H
#define UNTITLED_AVLNODE_H
template<class T> class AVLNode {
public:
    T data;
    int height;
    AVLNode<T>* left;
    AVLNode<T>* right;

    AVLNode(); //Default constructor
    explicit AVLNode(T value);
    ~AVLNode();
};

template<class T>
AVLNode<T>::AVLNode() {
    data = 0;
    height = -1;
    left = nullptr;
    right = nullptr;
}

template<class T>
AVLNode<T>::AVLNode(T value){
    data = value;
    height = 0;
    left = nullptr;
    right = nullptr;
}

template<class T>
AVLNode<T>::~AVLNode() {
    this->data = 0;
    this->height = -1;
    this->left = nullptr;
    this->right = nullptr;
}

#endif //UNTITLED_AVLNODE_H
