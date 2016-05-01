#include <iostream>
#include"heap.h"
using namespace std;

int main()
{
    int i;
    Heap<int, isLessThan<int> > h;
    Heap<int, isGreaterThan<int> > H;

    h.insert(4);
    h.insert(1);
    h.insert(9);
    h.insert(8);
    h.insert(-3);

    for(i = 1; i <= 5; i++)
    {
        cout<<h.pop()<<' ';
    }

    cout<<endl;

    H.insert(4);
    H.insert(1);
    H.insert(9);
    H.insert(8);
    H.insert(-3);

    for(i = 1; i <= 5; i++)
    {
        cout<<H.pop()<<' ';
    }

    return 0;
}
