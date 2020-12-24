#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
typedef long long LL;
//这题主要考虑溢出的问题

LL map[256] = {0};

void init()
{
    for (char i = '0'; i <= '9'; i++)
    {
        map[i] = i-'0';
    }
    for (char i = 'a'; i <= 'z'; i++)
    {
        map[i] = i-'a'+10;
    }
}

LL seq2decimal(char seq[], LL radix)
{
    LL ans = 0;
    int len = strlen(seq);
    for (int i = 0; i < len; i++)
    {
        ans = ans*radix + map[seq[i]];
        if (ans < 0)        //溢出
            return -1;
    }
#ifdef DEBUG
    printf("seq:%s radix:%d ans:%lld\n",seq, radix, ans);
#endif

    return ans;
}

int findRadix(char seq[], LL left, LL right, LL x)
{
    LL mid;
    LL temp;

    while (left <= right)
    {
        mid = (left+right)/2;
        temp = seq2decimal(seq, mid);

        if (temp == x)
            return mid;
        if (temp > x || temp == -1) //-1是N2溢出的情况
            right = mid-1;
        else
            left = mid+1;
    }

    return -1;
}

int findLargestDigit(char seq[])
{
    int ans = 1, len = strlen(seq);

    for (int i = 0; i < len; i++)
    {
        if (map[seq[i]] > ans)
        {
            ans = map[seq[i]];
        }
    }
    return ans+1;
}

int main()
{
    char N1[12], N2[12], temp[12];
    int flag;
    LL radix, ans, t, LOW;

    scanf("%s %s %d %lld", N1, N2, &flag, &radix);

    init();
    if (flag == 2)      //交换之后始终是N1为已知，需要求N2的radix
    {
        strcpy(temp, N1);
        strcpy(N1, N2);
        strcpy(N2, temp);
    }
    
    LOW = findLargestDigit(N2);
    t = seq2decimal(N1, radix);
    ans = findRadix(N2, LOW, std::max(LOW, t)+1, t);

    if (ans!=-1)
    {
        printf("%lld\n", ans);
    }else
    {
        printf("Impossible");
    }

    return 0;
}