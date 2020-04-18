#include"Graph.h"
#include<iostream>
#include<vector>

using namespace std;

int main()
{
    vector<int> v{1,4,7,5,3,2,6};

    Graph<int, int> g{v};

    g.addArc(1, 2, 2);
    g.addArc(3, 1, 4);
    g.addArc(1, 4, 1);
    g.addArc(2, 4, 3);
    g.addArc(2, 5, 10);
    g.addArc(3, 6, 5);
    g.addArc(4, 3, 2);
    g.addArc(4, 6, 8);
    g.addArc(4, 7, 4);
    g.addArc(4, 5, 2);
    g.addArc(5, 7, 6);
    g.addArc(7, 6, 1);

    // vector<int> result = g.topsort();

    // for (auto &i : result)
    // {
    //     cout<<i<<endl;
    // }

    g.dijkstra(1);

    g.printPath(1);
    cout<<endl;
    g.printPath(3);
    cout<<endl;
    g.printPath(5);
    cout<<endl;
    // g.printGraph();
    
    return 0;
}