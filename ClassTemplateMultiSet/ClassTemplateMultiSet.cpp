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
    return 0;

}
