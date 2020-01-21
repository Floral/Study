#include<stdio.h>
#include<string.h>

int p,x,y;  //记录空格位置和坐标
char matrix[25];

int isLegal(int choice)
{
    int flag = 1,tX,tY;
    tX = x = p/5;
    tY = y = p%5;
    switch (choice)
    {
        case 0:
            tX--;
            break;
        case 1:
            tX++;
            break;
        case 2:
            tY--;
            break;
        case 3:
            tY++;
        default:
            break;
    }
    if (tX<0 || tX>=5 || tY<0 || tY>=5)
    {
        flag = 0;
    }
    else
    {
        //移动空格位置
        matrix[5*x+y] = matrix[5*tX+tY];
        x = tX; y = tY; p = 5*x+y;
        matrix[5*x+y] = ' ';
    }
    
    
    return flag;
}
int move(char move)
{
    int flag=1;
    switch (move)
    {
        case 'A':
            flag = isLegal(0);
            break;
        case 'B':
            flag = isLegal(1);
            break;
        case 'L':
            flag = isLegal(2);
            break;
        case 'R':
            flag = isLegal(3);
            break;
        default:
            break;
    }

    return flag;
}

int main()
{
    freopen("data.in","r",stdin);
    int T = 1;
    while (1)
    {
        char c;
        for (size_t i = 0; i < 25; i++)
        {
            scanf("%c",&c);
            if (c!='\n')
            {
                // printf("test%c\n",c);
                if (c==' ')
                {
                    p=i;
                }
                matrix[i]=c;
            }
            else 
            {
                i--;
                continue;
            }
            if (c=='Z')
            {
                T=0;
                break;
            }
            
        }
        if (!T)
        {
            break;
        }
        else
        {
            printf("\n");
        }
        
        
        int flag = 1;
        while (scanf("%c",&c)==1 && (c!='0'))
        {
            if (c!='\n' && flag)
            {
                // printf("%c\n",c);
                flag = move(c);
            }
            
        }
        printf("Puzzle #%d:\n",T++);
        if (flag)
        {
            for (size_t i = 0; i < 25; i++)
            {
                if (i%5==0 && i>0)
                {
                    printf("\n");
                }else if(i>0)
                {
                    printf(" ");
                }
                    printf("%c",matrix[i]);
            }
            printf("\n");
        }
        else
        {
            printf("This puzzle has no final configuration.\n");
        }
    }
    
    return 0;
}