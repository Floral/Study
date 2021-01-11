#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>

using namespace std;

int strHash(char name[])
{
    int ans = 0;
    // int len = strlen(name);

    for (int i = 0; i < 4; i++)
    {
        if (i<3)
            ans = ans*26+name[i]-'A';
        else
            ans += name[i]-'0';
    }

    return ans;
}

vector<int> students[26*26*26+10];

int main()
{
    int N, K;

    scanf("%d%d", &N, &K);

    int cId, numOfStu;
    char name[5];
    
    while (K--)
    {
        scanf("%d%d", &cId, &numOfStu);

        while (numOfStu--)
        {
            scanf("%s", name);
            students[strHash(name)].push_back(cId);
        }
    }

    while (scanf("%s", name)!=EOF)
    {
        int id = strHash(name);
        int len = students[id].size();
        sort(students[id].begin(), students[id].end());
        printf("%s %d", name, len);
        for (int i = 0; i < len; i++)
        {
            printf(" %d", students[id][i]);
        }
        putchar('\n');
    }
    return 0;
}