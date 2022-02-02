#include <iostream>
#include <fstream>

using namespace std;
int main()
{
    ifstream fin("input.txt");

    char* str = new char[100];

for1:
    if (fin >> str)
    {
        cout << str << " ";
        goto for1;
    }

    /*
    int* s =(int*) malloc(40);
    for (int i = 0; i < 10; i++)
    {
        s[i] = i;
        cout << s[i] << " ";
    }
    cout << endl;
    s = (int*) realloc(s, 80);


    for (int i = 0; i < 20; i++)
    {
        cout << s[i] << " ";
    }
    */
}


