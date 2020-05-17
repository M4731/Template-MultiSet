#pragma once
#include "Node.h"
#include "Comparator.h"
#include<iostream>

using namespace std;

template<typename T, typename F = Comparator<T> >
class MultiSet
{
	Node<T>* root;

	void copy(Node<T>*);
public:
	MultiSet();
	MultiSet(const MultiSet&);

	void insert(T);
	void remove(T);
	void dilit(Node<T>*);
	void SRD(ostream&, Node<T>*);
	T getRoot()
	{
		return this->root->getInfo();
	}

	MultiSet& operator=(const MultiSet&);
	friend ostream& operator<<(ostream& out, MultiSet<T, F> &M)
	{
		M.SRD(out,M.root);
		out << endl;
		return out;
	}
};

template<typename T, typename F>
MultiSet<T, F>::MultiSet()
{
	root = nullptr;
}

template<typename T, typename F>
MultiSet<T, F>::MultiSet(const MultiSet& S)
{
	copy(S.root);
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
			if  ( F::less(x, W->getInfo()) || F::equals(x,W->getInfo()) )
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

template<typename T, typename F>
MultiSet<T, F>& MultiSet<T, F>::operator=(const MultiSet& N)
{
	if (this == &N) return *this;
	dilit(root);
	root = nullptr;
	copy(N.root);
	return *this;
}

template<typename T, typename F>
void MultiSet<T, F>::dilit(Node<T>* N)
{
	if (N)
	{
		dilit(N->getLeft());
		dilit(N->getRight());
		delete N;
	}
}

template<typename T, typename F>
void MultiSet<T, F>::copy(Node<T>* N)
{
	if (N)
	{
		insert(N->getInfo());
		copy(N->getLeft());
		copy(N->getRight());
	}
}

template<typename T, typename F>
void MultiSet<T, F>::remove(T x)
{
	Node<T>* W = root;
	Node<T>* aux = W;
	while (W)
	{
		if (F::greater(W->getInfo(), x))
		{
			aux = W;
			W = W->getLeft();
		}
		else if (F::less(W->getInfo(), x))
		{
			aux = W;
			W = W->getRight();
		}
		else
		{
			if (!W->getLeft() && !W->getRight())
			{
				if (aux->getLeft() == W) {
					aux->setLeft(nullptr);
				}
				else {
					aux->setRight(nullptr);
				}
				delete W;
			}
			else if (W->getLeft() && !W->getRight())
			{
				if (aux->getLeft() == W)
					aux->setLeft(W->getLeft());
				else
					aux->setRight(W->getLeft());
				delete W;
			}
			else if (!W->getLeft() && W->getRight())
			{
				if (aux->getLeft() == W)
					aux->setLeft(W->getRight());
				else
					aux->setRight(W->getRight());
				delete W;
			}
			else
			{
				Node<T>* help = W->getRight();
				while (help->getLeft())
					help = help->getLeft();
				T v = help->getInfo();
				remove(help->getInfo());
				W->setInfo(v);
			}
			return;
		}
	}
	return;
}

