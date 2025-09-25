#include <iostream>
using namespace std;

void swap(int *a, int *b) 
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void sortArr(int *arr, int *length) 
{
    for (int i = 0; i < *length; i++)
    {
        
    }
}

int main() {
    int umur = 10;
    int umur2 = 20;

    swap(umur, umur2);

    cout << umur << umur2 << endl;

    return 0;
}
