#ifndef ADJ_LIST
#define ADJ_LIST

#include "iostream"
using std::cout;
#include "Container.hpp"
#include "util.hpp"

struct Adjacency_List
{

    LinkedList<Pair<int, double>> *adj_list;
    int numberOfV;

    Adjacency_List(int n_Vert);
    ~Adjacency_List();
    void addEdge(int from, int to, double cost);
    void Change_cost(int from, int to, double new_cost);
};

Adjacency_List::Adjacency_List(int n_Vert)
{
    numberOfV = n_Vert;

    adj_list = new LinkedList<Pair<int, double>>[numberOfV]();
}

Adjacency_List::~Adjacency_List()
{
    delete[] adj_list;
}

void Adjacency_List::addEdge(int from, int to, double cost)
{
    adj_list[from].insertEnd(Pair<int, double>(to, cost));
}

void Adjacency_List::Change_cost(int from, int to, double new_cost)
{
    for (int i = 0; i < adj_list[from].getSize(); i++)
    {
        if (adj_list[from].getObject(i).getFirst() == to)
        {
            adj_list[from].setObject({to, new_cost}, i);
        }
    }
}

#endif