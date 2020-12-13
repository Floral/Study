#include<cstdio>
#include<cstring>
#define maxn 110

bool ifExist[2000] = {false};   //存在哪些数
bool clsExist[maxn] = {false};  //存在哪些组

int firstLine[maxn] = {0};
int cls[maxn][2000] = {0};

int main()
{

    int m, n, c;    //c是类别
    int maxc = 0;   //最大类别

    scanf("%d", &m);
    while (m--)
    {
        memset(ifExist, 0, sizeof(ifExist));
        memset(clsExist, 0, sizeof(clsExist));
        memset(firstLine, 0, sizeof(firstLine));
        memset(cls, 0, sizeof(cls));
        maxc = 0;

        scanf("%d", &n);
        for (size_t i = 0; i < n; i++)
        {
            scanf("%d", firstLine+i);
            ifExist[firstLine[i]] = true;
        }

        for (size_t i = 0; i < n; i++)
        {
            scanf("%d", &c);
            clsExist[c] = true;
            cls[c][firstLine[i]]++;
            if (c>maxc)
            {
                maxc = c;
            }
        }

        for (size_t i = 0; i <= maxc; i++)
        {
            if (clsExist[i] == false)
                continue;
            
            printf("%d={", i);
            int flag = 1;
            for (size_t j = 0; j <= 2000; j++)
            {
                if (ifExist[j])
                {
                    if (flag)
                    {
                        flag = 0;
                    }else
                    {
                        printf(",");
                    }
                    printf("%d=%d",j, cls[i][j]);
                }
            }
            printf("}\n");
        }
    }

    return 0;
}