#include<cstdio>
#include<algorithm>
#include<cstdint>
#include<cstring>
#define maxn 100010

using namespace std;

typedef struct student
{
    char id[10];
    int tScore;
    int vScore;
    int total;
    uint8_t type;

    bool operator<(const student &b) const{
        // if (this->total!=b.total)
        // {
        //     return this->total > b.total && this->type <= b.type;
        // }else if (this->vScore!=b.vScore)
        // {
        //     return (this->vScore > b.vScore && this->type <= b.type);
        // }else
        // {
        //     return strcmp(this->id, b.id) <= 0;
        // }

        if (this->type!=b.type)
        {
            return this->type <= b.type;
        }else if (this->total!=b.total)
        {
            return this->total > b.total;
        }else if (this->vScore!=b.vScore)
        {
            return this->vScore > b.vScore;
        }else
        {
            return strcmp(this->id, b.id) <= 0;
        }
    }
} stu;

stu students[maxn];

int main()
{
    int N, L, H;
    int count = 0;

    scanf("%d %d %d", &N, &L, &H);
    for (size_t i = 0; i < N; i++)
    {
        scanf("%s %d %d", students[i].id, &students[i].vScore, &students[i].tScore);
        students[i].total = students[i].tScore+students[i].vScore;
        if (students[i].tScore >= H && students[i].vScore >= H)
        {
            students[i].type = 1;
            ++count;
        }else if (students[i].vScore >= H && students[i].tScore>= L)
        {
            students[i].type = 2;
            ++count;
        }else if (students[i].vScore >= students[i].tScore && students[i].tScore>=L)
        {
            students[i].type = 3;
            ++count;
        }else if (students[i].vScore >= L && students[i].tScore >= L)
        {
            students[i].type = 4;
            ++count;
        }else
        {
            students[i].type = 5;
        }
        // printf("%s %d %d %d %d\n",students[i].id, students[i].vScore, students[i].tScore, students[i].total, students[i].type);
    }

    // printf("%d\n", students[0]<students[1]);

    sort(students, students+N);

    printf("%d\n", count);
    for (size_t i = 0; i < count; i++)
    {
        printf("%s %d %d\n", students[i].id, students[i].vScore, students[i].tScore);
    }
    
    return 0;
}