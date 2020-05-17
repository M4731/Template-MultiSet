#pragma once
#include "Node.h"
#include "Comparator.h"
#include<iostream>
#include<vector>

using namespace std;

template<typename T, typename F = Comparator<T> >
class MultiSet
{
	Node<T>* root;

	void copy(Node<T>*);
	void dilit(Node<T>*);
	int allHelper(Node<T>*, vector<T>&, int&);
	bool test(Node<T>*, vector<T>);
public:
	MultiSet();
	MultiSet(const MultiSet&);
	~MultiSet();

	void insert(T);
	void remove(T);
	bool search(T);
	int searchNr(T);
	void removeAll(T);
	int all();
	void SRD(ostream&, Node<T>*);
	Node<T>* getRoot()
	{
		return this->root;
	}

	MultiSet& operator=(const MultiSet&);
	friend ostream& operator<<(ostream& out, MultiSet<T, F> &M)
	{
		M.SRD(out,M.root);
		if (!M.root) cout << "MultiSet-ul este gol.";
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
MultiSet<T, F>::~MultiSet()
{
	dilit(root);
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
	if (search(x))
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
				if (W == root && !W->getRight() && !W->getLeft())
				{
					delete root;
					root = nullptr;
				}
				else if (W == root && !W->getRight() && W->getLeft())
				{
					root = root->getLeft();
					delete W;
				}
				else if (W == root && W->getRight() && !W->getLeft())
				{
					root = root->getRight();
					delete W;
				}
				else if (!W->getLeft() && !W->getRight())
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
	else
		cout << "elementul " << x << " nu exista in MultiSet.";
}

template<typename T, typename F>
bool MultiSet<T, F>::search(T x)
{
	Node<T>* W = root;
	while (W)
	{
		if (W->getInfo() == x)
			return true;
		else if (F::less(W->getInfo(), x))
			W = W->getRight();
		else
			W = W->getLeft();
	}
	return false;
}

template<typename T, typename F>
int MultiSet<T, F>::searchNr(T x)
{
	int count = 0;
	Node<T>* W = root;
	while (W)
	{
		if (W->getInfo() == x)
			count++;
		if (F::less(x, W->getInfo()) || F::equals(x, W->getInfo()))
			W = W->getLeft();
		else
			W = W->getRight();
	}
	return count;
}

template<typename T, typename F>
void MultiSet<T, F>::removeAll(T x)
{
	if (search(x))
		while (search(x))
		{
			remove(x);
		}
	else
		cout << "elementul " << x << " nu exista in MultiSet.";
}

template<typename T, typename F>
int MultiSet<T, F>::all()
{
	int cont = 0;
	vector<T> sirDala;
	allHelper(root, sirDala, cont);
	return cont;
}

template<typename T, typename F>
int MultiSet<T, F>::allHelper(Node<T>* N, vector<T>& sirDala, int &cont)
{
	if (test(N, sirDala))
	{
		cont++;
		sirDala.push_back(N->getInfo());
	}
	if (N->getLeft()) {
		allHelper(N->getLeft(), sirDala, cont);
	}
	if(N->getRight()){
		allHelper(N->getRight(), sirDala, cont);
		}
	return cont;
}

template<typename T, typename F>
bool MultiSet<T, F>::test(Node<T>* N, vector<T> sirDala)
{
	if (N)
	{
		for (T x : sirDala)
			if (N->getInfo() == x) return false;
	}
	return true;
}
