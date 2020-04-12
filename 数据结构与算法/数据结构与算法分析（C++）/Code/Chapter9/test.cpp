#include"Graph.h"
#include<iostream>
#include<vector>

using namespace std;

int main()
{
    vector<int> v{1,4,7,5,3,2,6};

    Graph<int, int> g{v};

    g.addArc(1, 2);
    g.addArc(1, 3);
    g.addArc(1, 4);
    g.addArc(2, 4);
    g.addArc(2, 5);
    g.addArc(3, 6);
    g.addArc(4, 3);
    g.addArc(4, 6);
    g.addArc(4, 7);
    g.addArc(5, 4);
    g.addArc(5, 7);
    g.addArc(7, 6);

    vector<int> result = g.topsort();

    for (auto &i : result)
    {
        cout<<i<<endl;
    }

    // g.printGraph();
    
    return 0;
}