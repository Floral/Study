#include<cstdio>

namespace myname{
    int var = 42;
}

extern "C" double _ZN6myname3varE;

int __attribute__((weak)) weak2 = 2;

int weak2 = 4;
int main()
{
    // printf("%d\n", _ZN6myname3varE);    
    printf("%d\n", weak2);
    return 0;
}

int global_init_var = 84;
int global_uninit_var;
void func1(int i)
{
    printf("%d\n", i);
}
int main()
{
    static int static_var = 85;
    static int static_var2;
    int a = 1;
    int b;
    func1(static_var+static_var2+a+b);
    return 0;
}