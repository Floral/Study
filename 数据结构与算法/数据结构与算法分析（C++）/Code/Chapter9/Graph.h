#ifndef MY_GRAPH
#define MY_GRAPH

#include<vector>
#include<list>
#include<map>
#include<queue>
#include<utility>
#include<exception>
#include<iostream>

class CycleFoundException:std::exception
{
    //todo
};


template<typename T, typename C>    //T是顶点的键值类型，C是边的距离（权重or其他费用）类型
class Graph
{
private:
    //该图类采用邻接表存储
    //默认为有向图
    struct VertexNode;  //顶点类型
    struct ArcNode;     //边类型
    std::vector<VertexNode> vertexList;

    VertexNode* findVertex(const T& key);

public:
    Graph(/* args */);
    Graph(const std::vector<T>& vec);
    ~Graph();

    void printGraph() const;

    void addVertex(const T& key);
    void addVertex(T&& key);

    void addArc(const T& key, const T& adjKey, const C& cost=1);
    
    void delVertex(const T& key);
    void delArc(const T& key, const T& adjKey);

    std::vector<T> topsort();   //有向图的拓扑排序 
};

template<typename T, typename C>
struct Graph<T, C>::VertexNode
{
    T key;          //顶点的键值
    int indegree;   //入度
    ArcNode* firstAdjNode;

    VertexNode(const T& keyValue = T{}, ArcNode* firstAdj = nullptr)
    :key{keyValue}, indegree{0}, firstAdjNode{firstAdj} {}

    VertexNode(T&& keyValue, ArcNode* firstAdj = nullptr)
    :key{std::move(keyValue)}, indegree{0}, firstAdjNode{firstAdj} {}
};

template<typename T, typename C>
struct Graph<T, C>::ArcNode
{
    T adjKey;
    C cost;
    VertexNode* adjAddr;
    ArcNode* next;

    ArcNode(const T& keyValue, const C& costValue, ArcNode* n = nullptr)
    :adjKey{keyValue}, cost{costValue}, adjAddr{nullptr}, next{n} {}

    ArcNode(T&& keyValue, C&& costValue, ArcNode* n = nullptr)
    :adjKey{std::move(keyValue)}, cost{costValue}, adjAddr{nullptr},next{n} {}

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
    for (auto &vertex : vertexList)
    {
        if (key == vertex.key)
            return &vertex;
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
    std::queue<VertexNode> q;
    std::vector<T> sorted;

    for (auto &vertex : vertexList)
        if (vertex.indegree == 0)
            q.push(vertex);

    ArcNode* tmp = nullptr;
    while (!q.empty())
    {
        VertexNode v = q.front();
        q.pop();

        sorted.push_back(v.key);
        tmp = v.firstAdjNode;
        while (tmp!=nullptr)
        {
            //这里曾经存在一个if后面的分号，埋葬着我一个小时的青春。。。
            if(--tmp->adjAddr->indegree == 0)        //todo,这里还有原vertexList的处理问题，因为indegree被改变了
            {
                // std::cout<<tmp->adjAddr->indegree<<" ";
                q.push(*(tmp->adjAddr));
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

#endif