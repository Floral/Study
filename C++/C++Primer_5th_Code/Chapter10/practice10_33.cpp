#include<iostream>
#include<iterator>
#include<fstream>
#include<vector>
#include<string>

using namespace std;

int main(int argc,char *argv[])
{
    string infile(argv[1]);
    string outfile1(argv[2]),outfile2(argv[3]);

    fstream fis(infile);
    ofstream fos1(outfile1),fos2(outfile2);
    istream_iterator<int> int_it(fis),eof;
    ostream_iterator<int> odd_out(fos1," "),even_out(fos2,"\n");
    
    while (int_it!=eof)
    {
        int t = *(int_it++);
        if (t%2==1)
        {
            fos1<<t<<" ";
        }
        else
        {
            fos2<<t<<endl;
        }
    }
    

    return 0;
}