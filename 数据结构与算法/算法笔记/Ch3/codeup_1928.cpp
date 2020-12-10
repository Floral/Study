#include<cstdio>

using namespace std;

int month_size[13][2] = {
    {0,0}, {31, 31}, {28, 29}, {31,31}, {30,30}, {31,31}, {30,30}, {31,31}, 
    {31,31}, {30,30}, {31,31}, {30,30}, {31,31}
};//[xx][1]是闰年的12个月的天数

int isLeap(int year){   //判断是否为闰年
    return (year%4==0 && year%100!=0) || (year%400==0);
}

int main(){
    int time1, time2;
    int year1, year2, month1, month2, day1, day2;

    int diff;   //结果

    while (scanf("%d%d", &time1, &time2)!=EOF)
    {
        if (time1>time2)
        {
            int temp = time1;
            time1 = time2;
            time2 = temp;
        }
        // time1永远小于time2
    
        diff = 0;
        //获取年月日
        year1 = time1/10000;
        year2 = time2/10000;

        month1 = time1%10000/100;
        month2 = time2%10000/100;

        day1 = time1%100;
        day2 = time2%100;

        while (year1 < year2-1) //先按年加
        {
            if ((month1 <=2 && isLeap(year1) )|| (month1>2 && isLeap(year1+1)) )
            {
                diff+=366;
            }else
            {
                diff+=365;
            }
            ++year1;
        }
        
        while (year1 < year2 || month1 < month2-1)   //再按月加
        {
            //如果month2==1,且day1>day2,就会出问题,所以直接break
            if (month2 == 1)
            {
                break;
            }
            
            diff+=month_size[month1][isLeap(year1)];
            ++month1;   
            if (month1 == 13)
            {
                month1 = 1;
                ++year1;
            }
        }
        
        while (year1 < year2 || month1 < month2 || day1 < day2)  //最后按天数加
        {
            ++diff;
            ++day1;
            if (day1 == month_size[month1][isLeap(year1)]+1)
            {
                day1 = 1;
                ++month1;
            }
            if (month1 == 13)
            {
                month1 = 1;
                ++year1;
            }
        }

        // printf("%d %d\n%d %d \n%d %d\n", year1, year2, month1, month2, day1, day2);
        printf("%d\n",diff+1);
    }

    return 0;
}