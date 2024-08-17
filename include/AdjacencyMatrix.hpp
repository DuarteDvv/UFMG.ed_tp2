#ifndef ADJ_MATRIX
#define ADJ_MATRIX

#include "iostream"
using std::cout;


struct Adjacency_Matrix{

    
        double** matrix;
        int numberOfV;
        
        Adjacency_Matrix(int Vert);
        ~Adjacency_Matrix();
        void addEdge(int from, int to, double cost);

};


Adjacency_Matrix::Adjacency_Matrix(int Vert){
    numberOfV = Vert;

    matrix = new double*[Vert];
    for(int i = 0; i < Vert; i++){
        matrix[i] = new double[Vert];
    }

    for(int i = 0; i < Vert; i++){
      for(int j = 0; j < Vert; j++){
        matrix[i][j] = -1;
      }
    }
}

Adjacency_Matrix::~Adjacency_Matrix(){
    for (int i = 0; i < numberOfV; i++)
      delete[] matrix[i];

    delete[] matrix;

}

void Adjacency_Matrix::addEdge(int from, int to, double cost){
    matrix[from][to] = cost;
}





#endif