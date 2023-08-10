#include <iostream>
#include <vector>
#include "PriorityQueue.h"
using namespace std;

int main() {
    vector<int> vec {23,45,67,89,1,2,3,4,5,6,7,8,9,10};
    PriorityQueue<int> fila(vec);
    fila.print();
    cout << fila.top() << endl;
}