#include<iostream>
#include<map>
#include<set>
#include<string>
#include<cctype>
#include<algorithm>

// using namespace std;
/*
void dispContent(const map<string,size_t> &m)
{
    for (auto &w : m)
    {
        cout<<w.first<<" occurs "<<
              w.second<<((w.second>1)?" times.":" time.")<<endl;
    }    
}
void handleString(string &s)
{
    for (auto &i : s)
    {
        if (isalpha(i))
        {
            if (isupper(i))
            {
                tolower(i);
            }
        }
        else if(ispunct(i))
        {
            // s.erase(remove_if(s.begin(),s.end(),ispunct),s.end());
        }
        
    }
            // s.erase(remove_if(s.begin(),s.end(),ispunct),s.end());
}
*/
// using namespace std;
int main()
{
    std::map<std::string,size_t> word_count;
    
    std::string word;
    while (std::cin>>word)
    {
            word.erase(std::remove_if(word.begin(),word.end(),ispunct),word.end());

        ++word_count[word];
    }
    
    // dispContent(word_count);
    return 0;
}