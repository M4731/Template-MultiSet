#pragma once
#include "Node.h"
#include "Comparator.h"
#include<iostream>

using namespace std;

template<typename T, typename F = Comparator<T> >
class MultiSet
{
	Node<T>* root;
public:
	MultiSet();

	void insert(T);
	void SRD(ostream&, Node<T>*);
	T getRoot()
	{
		return this->root->getInfo();
	}

	friend ostream& operator<<(ostream& out, MultiSet<T, F> &M)
	{
		M.SRD(out,M.root);
		return out;
	}
};

template<typename T, typename F>
MultiSet<T, F>::MultiSet()
{
	root = nullptr;
}

template<typename T, typename F>
void MultiSet<T, F>::insert(T x)
{
	if (!root)
	{
		root = new Node<T>(x);
	}
	else
	{
		Node<T>* W = root;
		Node<T>* aux = W;
		while (W)
		{
			aux = W;
			if (F::less(x, W->getInfo()) || F::equals(x,W->getInfo()) )
			{
				W = W->getLeft();
			}
			else
			{
				W = W->getRight();
			}
		}
		Node<T>* Q = new Node<T>(x);
		if (F::greater(x, aux->getInfo()))
		{
			aux->setRight(Q);
		}
		else
		{
			aux->setLeft(Q);
		}
	}
}

template<typename T, typename F>
void MultiSet<T, F>::SRD(ostream& out, Node<T>* N)
{
	if (N)
	{
		SRD(out,N->getLeft());
		out << N->getInfo() << " ";
		SRD(out,N->getRight());
	}
}