#include <iostream>
#include <fstream>

using namespace std;
int main()
{
    string str;
    bool is_stopword = false;

    int len_array = 10;
    string stop_words[10];
    stop_words[0] = "the ";
    stop_words[1] = "in ";
    stop_words[2] = "a ";
    stop_words[3] = "for ";
    stop_words[4] = "to ";
    stop_words[5] = "on ";
    stop_words[6] = "at ";
    stop_words[7] = "with ";
    stop_words[8] = "about ";
    stop_words[9] = "before ";


    ifstream fin("input.txt");

for1:
    if (fin >> str)
    {
        str = str + " ";

        is_stopword = false;
        goto stop_word;
        backfor:

        if (!is_stopword)
        {
            cout << str;
        }
            

        str = "";
        goto for1;
    }

    fin.close();

    return 0;

stop_word:
    int j = 0;
    for_chech_stopword:
        if (j < len_array)
        {
            char ch = stop_words[j][0];
            ch = ch - 32;
            string stop_word = stop_words[j];
            stop_word[0] = ch;

            if (str == stop_words[j] || str == stop_word)
            {
                is_stopword = true;
                goto backfor;
            } 

            j++;
            goto for_chech_stopword;
        }
    goto backfor;

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


