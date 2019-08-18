#include <iostream>
#include <fstream>
#include "TextQuery.h"

using namespace std;

int main()
{
    ifstream ifs("data_for_query.in");

    TextQuery tq(ifs);

    string s;
    while (true)
    {
        cout << "enter word to look for, or q to quit: ";
        if (!(cin >> s) || s == "q")
            break;

        print(cout, tq.query(s));
    }

    return 0;
}