#pragma once
template <typename T>
class Node
{
	T info;
	Node* left, * right;
public:
	Node() = default;
	Node(T);

	void setInfo(T);
	T getInfo() const;
	void setLeft(Node*);
	Node* getLeft() const;
	void setRight(Node*);
	Node* getRight() const;
};

template <typename T>
Node<T>::Node(T info)
{
	this->info = info;
	this->left = nullptr;
	this->right = nullptr;
}

template <typename T>
void Node<T>::setInfo(T info)
{
	this->info = info;
}

template <typename T>
T Node<T>::getInfo() const
{
	return this->info;
}

template <typename T>
void Node<T>::setLeft(Node<T>* left)
{
	this->left = left;
}

template <typename T>
Node<T>* Node<T>::getLeft() const
{
	return this->left;
}

template <typename T>
void Node<T>::setRight(Node<T>* right)
{
	this->right = right;
}

template <typename T> 
Node<T>* Node<T>::getRight() const
{
	return this->right;
}