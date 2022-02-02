﻿#include <iostream>
#include <fstream>

using namespace std;
int main()
{
    string str;
    bool is_stopword = false;
    int l, k;
    int N = 25;

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

    int len_words = 0;
    int real_len_words = 1000;
    int* amount_words = new int[real_len_words];
    string* words = new string[real_len_words];

    int** pages_words = new int* [real_len_words];
    l = 0;
    for6:
    if (l < real_len_words)
    {
        pages_words[l] = new int[100];
        l++;
        goto for6;
    }

    int amount_string = 1;

    ifstream fin("input.txt");

for1:

        //перевірка номера рядка
    char symbol = fin.peek();
    if (symbol == '\n')
    {
        amount_string++;
    }
    
        //зчитати слово
    if (fin >> str)
    {
        str = str + " ";

        //визначення чи це стоп-слово
        is_stopword = false;
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
                //goto backfor;
            }

            j++;
            goto for_chech_stopword;
        }

        //слово потрібно опрацьовувати (не стоп слово)
        if (!is_stopword)
        {


            //збільшення масивів
            if (len_words == real_len_words)
            {
                int new_len = real_len_words * 2;
                int* new_amount_words = new int[new_len];
                string* new_words = new string[new_len];

                int** new_pages_words = new int* [new_len];
                l = 0;
            for7:
                if (l < len_words)
                {
                    new_pages_words[l] = pages_words[l];
                    l++;
                    goto for7;
                }
                else
                    if (l >= len_words && l < new_len)
                    {
                        new_pages_words[l] = new int[100];
                        l++;
                        goto for7;
                    }

                l = 0;
                rewrite:
                if (l < len_words)
                {
                    new_amount_words[l] = amount_words[l];
                    new_words[l] = words[l];
                    l++;
                    goto rewrite;
                }

                real_len_words = new_len;
                amount_words = new_amount_words;
                words = new_words;
                pages_words = new_pages_words;

                new_amount_words = nullptr;
                new_words = nullptr;
                new_pages_words = nullptr;

            }



            //обрахунок слів
            k = 0;
        for2:
            if (str[0] >= 65 && str[0] <= 90)
            {
                str[0] = str[0] + 32;
            }

            if (k == len_words)     //нове слово
            {
                amount_words[k] = 1;
                words[k] = str;
                len_words++;
            }
            else
                if (str == words[k])       //слово вже є + кількість 
                {
                    amount_words[k]++;
                }
                else                        // рухаємся далі по масиву слово не співпало і слова в масиві не закінчилися
                {
                    k++;
                    goto for2;
                }
        }

        str = "";
        goto for1;
    }
    fin.close();


    //сортування
    k = 0;
sort_for1:
    if (k < len_words)
    {
        l = k + 1;
    sort_for2:
        if (l < len_words)
        {
            if (amount_words[k] < amount_words[l])
            {
                str = words[k];
                words[k] = words[l];
                words[l] = str;

                int buf = amount_words[k];
                amount_words[k] = amount_words[l];
                amount_words[l] = buf;
            }
            l++;
            goto sort_for2;
        }
        k++;
        goto sort_for1;
    }

    //запис в файл
    ofstream fout;
    fout.open("output.txt");
    l = 0;
for3:
    if (l < len_words && l <= N)
    {
        fout << words[l] << "- " << amount_words[l] << "\n";
        l++;
        goto for3;
    }
    fout.close();


    cout << amount_string << endl;
    return 0;
}
