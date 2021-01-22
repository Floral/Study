#include<cstdio>
#include<set>

using namespace std;

int main()
{
    int N;

    scanf("%d", &N);

    set<int> st[N];    
    int M;
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &M);
        int temp;
        for (int j = 0; j < M; j++)
        {
            scanf("%d", &temp);
            st[i].insert(temp);
        }
    }
    int K;
    scanf("%d", &K);

    for (int i = 0; i < K; i++)
    {
        int a, b;
        scanf("%d%d", &a, &b);

        if (st[a-1].size()>st[b-1].size())
            swap(a, b);
        
        int cnt = 0, len = st[a-1].size();
        for (auto it = st[a-1].cbegin(); it != st[a-1].cend(); it++)
        {
            if (st[b-1].find(*it)!=st[b-1].end())
                ++cnt;
        }
        printf("%.1f%%\n", 100.0*cnt/(st[a-1].size()+st[b-1].size()-cnt));
    }

    return 0;
}