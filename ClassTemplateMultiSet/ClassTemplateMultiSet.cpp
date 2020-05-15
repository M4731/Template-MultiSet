#include "MultiSet.h"
#include <iostream>

int main()
{
    MultiSet<int> M;
    M.insert(1);
    M.insert(33);
    M.insert(0);
    cout << M;
    return 0;
}
