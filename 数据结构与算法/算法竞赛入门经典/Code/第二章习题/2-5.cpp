#include<iostream>

using namespace std;

int main()
{
    int a,b,c,kcase=0;

    while(~scanf("%d%d%d",&a,&b,&c)&&(a||b||c)){
        /* code */
        printf("Case %d: %d.",++kcase,a/b);
        
        for(int i = 0; i < c; i++)
        {
            //模拟除法过程
            a=a-(a/b)*b;
            a=a*10;
            if (i<c-1) {
                printf("%d",a/b);
                a=a-(a/b)*b;
            }
            else 
            {
                //判断最后一位是否进位
                int t1=a/b;
                a=a-t1*b;
                a=a*10;
                int t2=a/b;
                if (t2>=5) {
                    printf("%d",t1+1);
                }
                else
                {
                    printf("%d",t1);
                }
                
            }
        }
        printf("\n");
    }
    
    return 0;
}