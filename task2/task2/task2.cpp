#include <iostream>
#include <fstream>

using namespace std;
int main()
{
    string str;
    bool is_stopword = false;
    int l, k, j;

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
    int real_len_words = 20000;
    int* amount_words = new int[real_len_words];
    string* words = new string[real_len_words];
    

    int** pages_words = new int* [real_len_words];
    l = 0;
    for6:
    if (l < real_len_words)
    {
        pages_words[l] = new int[101];
        l++;
        goto for6;
    }

    int current_string = 0;


    ifstream fin("input.txt");

for1:

        //перевірка номера рядка
check_cur_str:
    if (fin.peek() == '\n')
    {
        current_string++;
        fin.get();
        goto check_cur_str;
    }
    
        //зчитати слово
    if (fin >> str)
    {

        str = str + " ";
        string buf_str = "";

                //нормалізація слів і відрізання не слівних символів
        j = 0;
    for69:
        if (str[j] != ' ')
        {
            if ((str[j] >= 'A' && str[j] <= 'Z') || (str[j] >= 'a' && str[j] <= 'z') || (str[j] == '-'))
            {
                if ((str[j] >= 'A' && str[j] <= 'Z'))
                {
                    str[j] = str[j] + 32;
                }
                buf_str += str[j];
            }
            j++;
            goto for69;
        }
        if (buf_str[0] == ' ' || buf_str == "" || buf_str == "-")
            goto for1;
        else
            str = buf_str + " ";

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
                        new_pages_words[l] = new int[101];
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

                delete[] amount_words;
                amount_words = new_amount_words;
                new_amount_words = nullptr;

                delete[] words;
                words = new_words;
                new_words = nullptr;

                delete[] pages_words;
                pages_words = new_pages_words;
                new_pages_words = nullptr;

            }



            //обрахунок слів
            k = 0;
        for2:
            if (k == len_words)     //нове слово
            {
                amount_words[k] = 1;
                words[k] = str;
                pages_words[k][0] = (current_string / 45) + 1;
                len_words++;
            }
            else
                if (str == words[k] && amount_words[k] < 101)       //слово вже є + кількість (таких слів було знайдено менше 101)
                {
                    pages_words[k][amount_words[k]] = (current_string / 45) + 1;
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


            //Чистка слів більше 100 
    int n_len = len_words;
    int* n_amount_words = new int[n_len];
    string* n_words = new string[n_len];
    int** n_pages_words = new int* [n_len];

    l = 0;
    j = 0;
    clean:
    if (l < len_words)
    {
        if (amount_words[l] <= 100)
        {
            n_words[j] = words[l];
            n_amount_words[j] = amount_words[l];
            n_pages_words[j] = pages_words[l];
            j++;
        }
        else
        {
            delete[] pages_words[l];
            pages_words[l] = nullptr;
        }
        l++;
        goto clean;
    }
    len_words = j;

    delete[] amount_words;
    amount_words = n_amount_words;
    n_amount_words = nullptr;

    delete[] words;
    words = n_words;
    n_words = nullptr;

    delete[] pages_words;
    pages_words = n_pages_words;
    n_pages_words = nullptr;
    

    //сортування
    k = 0;
sort_for1:              //вибір першого слова (зовн цикл)
    if (k < len_words)
    {
        l = k + 1;
    sort_for2:                //вибір другого слова (внутр цикл)
        if (l < len_words)
        {
                    // перевірка чи два слова потрібно поміняти місцями за алфавітом
            bool is_swap = false;
            j = 0;
            sort_words:
            if (words[k][j] != ' ' || words[l][j] != ' ')
            {
                if (words[k][j] == words[l][j])
                {
                    j++;
                    goto sort_words;
                }
                else
                {
                    if (words[k][j] > words[l][j])
                    {
                        is_swap = true;
                    }
                }
            }
            else            //одне з слів закінчилося
            {
                if(words[l][j] != ' ')          //друге слово коротше і співпадає з частиною першого
                    is_swap = true;
            }

                //зміна місцями слів
            if (is_swap)
            {
                str = words[k];
                words[k] = words[l];
                words[l] = str;

                int buf = amount_words[k];
                amount_words[k] = amount_words[l];
                amount_words[l] = buf;

                int* b = pages_words[k];
                pages_words[k] = pages_words[l];
                pages_words[l] = b;
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
forfout:
    if (l < len_words)
    {
        fout << words[l] << "-";
        if (amount_words[l] <= 100)
        {
            k = 0;
        forfout2:
            if (k < amount_words[l] && k == 0)
            {
                fout << " " << pages_words[l][k];
                k++;
                goto forfout2;
            }
            else
                if(k < amount_words[l] && k > 0)
                {
                    fout << ", " << pages_words[l][k];
                    k++;
                    goto forfout2;
                }
            fout << "\n";
        }
        l++;
        goto forfout;
    }
    fout.close();

    return 0;
}

