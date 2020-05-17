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
	//afisarea informatiei din radacina
	Node<T>* getRoot()
	{
		return this->root->getInfo();
	}

	MultiSet& operator=(const MultiSet&);
	//supraincarcarea operatorului de afisare
	friend ostream& operator<<(ostream& out, MultiSet<T, F> &M)
	{
		M.SRD(out,M.root);
		if (!M.root) cout << "MultiSet-ul este gol.";
		out << endl;
		return out;
	}
};

//constructor fara parametrii care initializeaza radacina ca null ptr
template<typename T, typename F>
MultiSet<T, F>::MultiSet()
{
	root = nullptr;
}

//constructor de copiere care se foloseste de metoda copy
template<typename T, typename F>
MultiSet<T, F>::MultiSet(const MultiSet& S)
{
	copy(S.root);
}

//destructor
template<typename T, typename F>
MultiSet<T, F>::~MultiSet()
{
	dilit(root);
}

//functia de insertie
template<typename T, typename F>
void MultiSet<T, F>::insert(T x)
{
	//daca radacina este null creem o radacina noua
	if (!root) 
	{
		root = new Node<T>(x);
	}
	else
	{
		Node<T>* W = root;
		Node<T>* aux = W;
		//folosim W pentru a merge din nod in nod pana a ajunge la margine si aux sta in spatele lui W/ parintele acestuia
		//pentru a face posibila adaugarea
		while (W) 
		{
			aux = W;
			if  ( F::less(x, W->getInfo()) || F::equals(x,W->getInfo()) )
			{
				//daca x e <= val curenta mergem stanga
				W = W->getLeft(); 
			}
			else
			{
				//daca x e >= val curenta mergem dreapta
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

//functie de afisare recusiva folosind SRD
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

//copy constructor folosind functiile de dilit si copy recusive
template<typename T, typename F>
MultiSet<T, F>& MultiSet<T, F>::operator=(const MultiSet& N)
{
	if (this == &N) return *this;
	dilit(root);
	root = nullptr;
	copy(N.root);
	return *this;
}

//metoda recursiva de stergere
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

//metoda recursiva de copiere care se ajuta de insertie
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

//metoda care sterge un element dat din MultiSet
template<typename T, typename F>
void MultiSet<T, F>::remove(T x)
{
	//daca elementul dat exista in sir
	if (search(x))
	{
		Node<T>* W = root;
		Node<T>* aux = W;
		while (W)
		{
			//merg cu W pana il gasesc
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
				//il gasesc
				if (W == root && !W->getRight() && !W->getLeft())
				{
					//exista doar radacina
					delete root;
					root = nullptr;
				}
				else if (W == root && !W->getRight() && W->getLeft())
				{
					//radacina si copii pe stanga
					root = root->getLeft();
					delete W;
				}
				else if (W == root && W->getRight() && !W->getLeft())
				{
					//radacina si copii pe dreapta
					root = root->getRight();
					delete W;
				}
				else if (!W->getLeft() && !W->getRight())
				{
					//frunza
					if (aux->getLeft() == W) {//pe stanga
						aux->setLeft(nullptr);
					}
					else {//pe dreapta
						aux->setRight(nullptr);
					}
					delete W;
				}
				else if (W->getLeft() && !W->getRight())
				{
					//are fii stangi
					if (aux->getLeft() == W)
						aux->setLeft(W->getLeft());
					else
						aux->setRight(W->getLeft());
					delete W;
				}
				else if (!W->getLeft() && W->getRight())
				{
					//are fii drepti
					if (aux->getLeft() == W)
						aux->setLeft(W->getRight());
					else
						aux->setRight(W->getRight());
					delete W;
				}
				else
				{
					//are si fii drepti si stangi asa ca o ducem pana in dreapta->stanga jos de tot si apelam recursiv
					Node<T>* help = W->getRight();
					while (help->getLeft())
						help = help->getLeft();
					T v = help->getInfo();
					//pastram valoarea din nodul de jos ce va fi sters si o punem in locul nodului din mijloc care avea valoare ce trebuia stearsa
					remove(help->getInfo());
					W->setInfo(v);
				}
				return;
			}
		}
		return;
	}
	else
		//daca elementul nu exista in MultiSet afisam pe ecran ca nu exista
		cout << "elementul " << x << " nu exista in MultiSet.";
}

//metoda care cauta un element in MultiSet
template<typename T, typename F>
bool MultiSet<T, F>::search(T x)
{
	Node<T>* W = root;
	while (W)
	{
		//ne plimbam cu W prin arbore pana gasim
		if (W->getInfo() == x)
			return true;
		else if (F::less(W->getInfo(), x))
			W = W->getRight();
		else
			W = W->getLeft();
	}
	//daca nu gasim returnam false
	return false;
}

//metoda care cauta numarul de aparitii ale unui element in MultiSet
template<typename T, typename F>
int MultiSet<T, F>::searchNr(T x)
{
	//contor
	int count = 0;
	Node<T>* W = root;
	while (W)
	{
		//ne plimbam prin arbore si crestem contodul de fiecare data cand gasim elementul dorit
		if (W->getInfo() == x)
			count++;
		if (F::less(x, W->getInfo()) || F::equals(x, W->getInfo()))
			W = W->getLeft();
		else
			W = W->getRight();
	}
	//returnam contorul
	return count;
}

//metoda care sterge toate aparitiile unui element din MultiSet
//se foloseste de search si remove
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

//metoda care afiseaza numarul de elemente diferite din MultiSet
template<typename T, typename F>
int MultiSet<T, F>::all()
{
	int cont = 0;//contor
	vector<T> sirDala;//vector de aparitii
	allHelper(root, sirDala, cont);
	return cont;
}

//metoda ajutatoare
//de fiecare data cand gasim un element ce n-a mai fost gasit il bagam in vector si crestem contorul
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

//verificare daca a mai aparut elementul in MultiSet
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
