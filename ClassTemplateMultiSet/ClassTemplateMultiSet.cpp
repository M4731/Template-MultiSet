#include "MultiSet.h"
#include <iostream>

int main()
{
    MultiSet<int> M;
    M.insert(1);
    M.insert(33);
    M.insert(0);
    M.insert(22);
    M.insert(69);
    MultiSet<int> N = M;
    cout << M;
    M.remove(69);
    cout << M;
    M.remove(1);
    cout << M;
    M.remove(22);
    cout << M;
    cout << N;
    N = M;
    cout << N;
    N.remove(0);
    cout << N;
    cout << "search: " << N.search(33) << " " << N.search(22) << endl << "searchNr: " << N.searchNr(33) << " " << N.searchNr(22) << " ";
    N.insert(33);
    N.insert(1);
    cout << N.searchNr(33) << endl;
    cout << N;
    N.removeAll(33);
    N.remove(1);
    cout << N;
    N.insert(69);
    N.insert(11);
    N.insert(1);
    N.insert(69);
    N.insert(22);
    N.insert(69);
    N.insert(22);
    cout << N;
    N.remove(35);
    cout << endl << N.all()<< endl;
    cout << N;
    MultiSet<double> Q;
    Q.insert(3.142);
    Q.insert(4.149);
    Q.insert(20.142);
    cout << Q;
    return 0;
}
