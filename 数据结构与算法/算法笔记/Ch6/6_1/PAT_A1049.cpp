#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>

using namespace std;

bool cmp(char s1[], char s2[])
{
    return strcmp(s1, s2)<0;
}

int main()
{
    int N, K;

    scanf("%d%d", &N, &K);
    vector<char*> courses[K+1];

    int numOfCourses = 0;
    int cId = 0;
    char* name;
    while (N--)
    {
        name = (char*)malloc(5*sizeof(char));
        scanf("%s%d", name, &numOfCourses);
        while (numOfCourses--)
        {
            scanf("%d", &cId);
            courses[cId].push_back(name);
        }
    }

    for (int i = 1; i <= K; i++)
    {
        printf("%d %d\n", i, courses[i].size());
        sort(courses[i].begin(), courses[i].end(), cmp);
        int len = courses[i].size();
        for (int j = 0; j < len; j++)
            printf("%s\n", courses[i][j]);
    }
    
    return 0;
}