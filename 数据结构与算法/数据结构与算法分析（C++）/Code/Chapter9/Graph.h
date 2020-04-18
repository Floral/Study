#ifndef MY_GRAPH
#define MY_GRAPH

#include<vector>
#include<list>
#include<map>
#include<set>
#include<queue>
#include<utility>
#include<exception>
#include<iostream>

class CycleFoundException:std::exception
{
    //todo
};


template<typename T, typename C = int>    //T是顶点的键值类型，C是边的距离（权重or其他费用）类型
class Graph
{
private:
    //该图类采用邻接表存储
    //默认为有向(有权)图
    //由于是我自己实现的，肯定没有别人写的库里的效率高，仅作学习参考
    static const C INF = 65535;
    struct VertexNode;  //顶点类型
    struct ArcNode;     //边类型
    std::vector<VertexNode> vertexList;         //如果用map数据结构来存vertex，那么find的效率会提高，现在是O(N)

    VertexNode* findVertex(const T& key);
    void printPath(const VertexNode* desV) const;

public:
    Graph(/* args */);
    Graph(const std::vector<T>& vec);
    ~Graph();

    void printGraph() const;
    void printPath(const T& desKey);  //打印源节点到目标节点的最短路径

    void addVertex(const T& key);
    void addVertex(T&& key);

    void addArc(const T& key, const T& adjKey, const C& cost=1);
    
    void delVertex(const T& key);
    void delArc(const T& key, const T& adjKey);

    std::vector<T> topsort();   //有向图的拓扑排序 
    void unweighted(const T& sKey);     //无权最短路径算法
    void dijkstra(const T& sKey);        //dijstra算法（有权最短路径）
};

template<typename T, typename C>
struct Graph<T, C>::VertexNode
{
    T key;          //顶点的键值
    int indegree;   //入度
    C dist;         //距离
    bool known;     //节点是否被访问过的标志
    VertexNode* prePath;    //路径上的上一个节点的指针
    ArcNode* firstAdjNode;

    VertexNode(const T& keyValue = T{}, ArcNode* firstAdj = nullptr)
    :key{keyValue}, indegree{0}, known{false}, prePath{nullptr}, firstAdjNode{firstAdj} {}

    VertexNode(T&& keyValue, ArcNode* firstAdj = nullptr)
    :key{std::move(keyValue)}, indegree{0}, known{false}, prePath{nullptr}, firstAdjNode{firstAdj} {}
};

template<typename T, typename C>
struct Graph<T, C>::ArcNode
{
    T adjKey;
    C arcCost;
    VertexNode* adjAddr;
    ArcNode* next;

    ArcNode(const T& keyValue, const C& costValue, ArcNode* n = nullptr)
    :adjKey{keyValue}, arcCost{costValue}, adjAddr{nullptr}, next{n} {}

    ArcNode(T&& keyValue, C&& costValue, ArcNode* n = nullptr)
    :adjKey{std::move(keyValue)}, arcCost{costValue}, adjAddr{nullptr},next{n} {}
};

template<typename T, typename C>
Graph<T, C>::Graph(/* args */)
{}

template<typename T, typename C>
Graph<T, C>::Graph(const std::vector<T>& vec)
{
    for (const T& i : vec)
    {
        VertexNode v(i);
        vertexList.push_back(std::move(v));
    }
}

template<typename T, typename C>
Graph<T, C>::~Graph()
{
    //todo
}

template<typename T, typename C>
typename Graph<T, C>::VertexNode* Graph<T, C>::findVertex(const T& key)
{
    // int numOfVertex = vertexList.size();
    for (auto i = vertexList.begin(); i != vertexList.end(); ++i)
    {
        if (key == (*i).key)
            return &(*i);
    }
    return nullptr;
}

template<typename T, typename C>
void Graph<T, C>::addVertex(const T& key)
{
    vertexList.push_back(VertexNode{key});
}

template<typename T, typename C>
void Graph<T, C>::addVertex(T&& key)
{
    vertexList.push_back(VertexNode{std::move(key)});
}

template<typename T, typename C>
void Graph<T, C>::addArc(const T& key, const T& adjKey, const C& cost)
{
    VertexNode* vertex = findVertex(key);
    VertexNode* adjVertex = findVertex(adjKey);   //这里暂时不知道该怎么改进，感觉目前有点慢，因为是暴力搜索
    //好像可以直接用stl里面的find方法2333，懒得改了
    if (vertex)
    {
        ArcNode* newArc = new ArcNode{adjKey, cost};      //析构函数要删掉这些new的ArcNode
        newArc->adjAddr = adjVertex;             //把该ArcNode链接到原本的VertexNode上，为topsort做准备
        newArc->next = vertex->firstAdjNode;
        vertex->firstAdjNode = newArc;
        ++(adjVertex->indegree);
    }
}

template<typename T, typename C>
std::vector<T> Graph<T, C>::topsort()
{
    std::queue<VertexNode*> q;
    std::vector<T> sorted;

    for (auto &vertex : vertexList)
        if (vertex.indegree == 0)
            q.push(&vertex);

    ArcNode* tmp = nullptr;
    while (!q.empty())
    {
        VertexNode* v = q.front();
        q.pop();

        sorted.push_back(v->key);
        tmp = v->firstAdjNode;
        while (tmp!=nullptr)
        {
            //这里曾经存在一个if后面的分号，埋葬着我一个小时的青春。。。
            if(--tmp->adjAddr->indegree == 0)        //todo,这里还有原vertexList的处理问题，因为indegree被改变了
            {
                // std::cout<<tmp->adjAddr->indegree<<" ";
                q.push(tmp->adjAddr);
            }
            tmp = tmp->next;
        }
    }
    
    if (sorted.size() != vertexList.size())
    {
        std::cout<<"sorted.size() : "<<sorted.size()<<std::endl;
        std::cout<<"vertexList.size() : "<<vertexList.size()<<std::endl;

        throw CycleFoundException{};
    }

    return sorted;
}

template<typename T, typename C>
void Graph<T, C>::printGraph() const
{
    for (auto &vertex: vertexList)
    {
        std::cout<<vertex.key<<" : "<<std::endl;
        std::cout<<"indegree: "<<vertex.indegree<<std::endl;
        std::cout<<"adjacent vertex:";
        auto tmp = vertex.firstAdjNode;
        while (tmp!=nullptr)
        {
            std::cout<<tmp->adjAddr->key<<" -> ";
            tmp = tmp->next;
        }
        std::cout<<"nullptr."<<std::endl;
    }
}

//@param sKey 源节点的key值
template<typename T, typename C>
void Graph<T, C>::unweighted(const T& sKey)    
{
    VertexNode* source = findVertex(sKey);
    std::queue<VertexNode*> q;

    for (auto &vertex : vertexList)
        vertex.dist = INF;

    source->dist = 0;
    q.push(source);

    ArcNode* tmp = nullptr;
    while (!q.empty())
    {
        VertexNode* v = q.front();
        q.pop();
        
        tmp = v->firstAdjNode;
        while (tmp!=nullptr)
        {
            if (tmp->adjAddr->dist == INF)
            {
                tmp->adjAddr->dist = v->dist + 1;
                tmp->adjAddr->prePath = v;
                q.push(tmp->adjAddr);
            }
            tmp = tmp->next;
        }
    }
    
    for (auto &v : vertexList)
    {
        std::cout<<"key: "<<v.key
        <<" dist: "<<v.dist
        <<" pre:"<<(v.prePath == nullptr ? -1 : v.prePath->key) //-1代表是源节点
        <<std::endl;
    }
}//已通过测试

//私有的递归方法
//打印到目标节点的路径
//@Param desV 目标节点的指针
template<typename T, typename C>
void Graph<T, C>::printPath(const VertexNode* desV) const
{
    if (desV->prePath!=nullptr)
    {
        printPath(desV->prePath);
        std::cout<<" to ";
    }
    std::cout<<desV->key;
}

//封装后的公有方法
template<typename T, typename C>
void Graph<T, C>::printPath(const T& desKey)
{
    VertexNode* desV = findVertex(desKey);
    printPath(desV);
}

template<typename T, typename C>
void Graph<T, C>::dijkstra(const T& sKey)
{
    std::set<VertexNode*> unknownVertexGroup;    //还未确定最短路径的顶点的集合
    // std::set<VertexNode*> knownVertexGroup;      //已经确定最短路径的集合

    for (auto &vertex : vertexList)
    {
        vertex.dist = INF;
        vertex.known = false;
        unknownVertexGroup.insert(&vertex);
    }
    
    VertexNode* source = findVertex(sKey);
    source->dist = 0;

    VertexNode* smallestDist = nullptr;
    ArcNode* tmp = nullptr;
    while (!unknownVertexGroup.empty())
    {
        smallestDist = *(unknownVertexGroup.begin());   
        //因为begin返回的是一个iterator（相当于指针），但是我们需要的是该指针所指向的指针，所以需要解指针
        for (auto &vertexPointer : unknownVertexGroup)
        {
            if (vertexPointer->dist < smallestDist->dist)
                smallestDist = vertexPointer;
        }//从未确定的集合中选取一个最小的距离的点，这个点到源节点的距离肯定是最小的
        
        smallestDist->known = true;
        
        tmp = smallestDist->firstAdjNode;
        while (tmp!=nullptr)
        {
            if (tmp->adjAddr->known == false)
            {
                if (tmp->arcCost + smallestDist->dist < tmp->adjAddr->dist)
                {
                    tmp->adjAddr->dist = tmp->arcCost + smallestDist->dist; //更新未确定集合中的dist以便选取新的最小值
                    tmp->adjAddr->prePath = smallestDist;
                }
            }
            tmp = tmp->next;
        }
        unknownVertexGroup.erase(smallestDist); //用完了smallestDist再删
    }
}//todo dijkstra还未测试


#endif