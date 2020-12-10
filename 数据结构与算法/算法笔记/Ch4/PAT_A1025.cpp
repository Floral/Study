#include<cstdio>
#include<algorithm>
#include<cstring>

struct student
{
    char    id[15];
    int     score;
    int     numOfLocation;
    int     localRank;
}   stu[30010];

int cmp(student a, student b)
{
    if (a.score!=b.score)
        return a.score > b.score;
    else
        return strcmp(a.id, b.id) < 0;
}

int main()
{
    int N, K, num = 0, start = 0;
    struct student temp;
    scanf("%d", &N);
    for(size_t i = 0; i < N; i++)
    {
        scanf("%d", &K);
           
        for (size_t j = 0; j < K; j++)
        {
            scanf("%s%d", temp.id, &temp.score);
            temp.numOfLocation = i+1;
            stu[num++] = temp;
        }

        std::sort(stu+start, stu+start+K, cmp);
        stu[start].localRank = 1;
        for (size_t j = 1; j < K; j++)
        {
            if (j>0 && stu[start+j].score != stu[start+j-1].score)
            {
                stu[start+j].localRank = j+1;
            }else
            {
                stu[start+j].localRank = stu[start+j-1].localRank;
            }
        }
        start += K;
    }
    
    std::sort(stu, stu+num, cmp);

    printf("%d\n", num);
    int lastRank = 1;
    for (size_t i = 0; i < num; i++)
    {
        if (i>0 && stu[i].score!=stu[i-1].score)
        {
            printf("%s %d %d %d\n", stu[i].id, i+1, stu[i].numOfLocation, stu[i].localRank);
            lastRank = i+1;
        }else
        {
            printf("%s %d %d %d\n", stu[i].id, lastRank, stu[i].numOfLocation, stu[i].localRank);
        }
    }

    return 0;
}
