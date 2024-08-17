#ifndef MODMINHEAP_
#define MODMINHEAP_

#include <stdexcept> // std::runtime_error
#include "util.hpp"

class ModMinHeap
{
private:
   Pair<Pair<int, double>, int> *heap; // vertex, peso, portais usados
   int capacity;
   int size;

   void heapifyUp(int index);
   void heapifyDown(int index);

public:
   ModMinHeap();
   ModMinHeap(int capacity);
   ~ModMinHeap();

   Pair<Pair<int, double>, int> getMin_without_remove();
   int getSize() const { return size; }
   bool isEmpty() const { return size == 0; }
   void enqueue(const Pair<Pair<int, double>, int> &obj);
   Pair<Pair<int, double>, int> dequeue();
   void clear();
};

ModMinHeap::ModMinHeap() : capacity(10000), size(0)
{
   heap = new Pair<Pair<int, double>, int>[capacity];
}

ModMinHeap::ModMinHeap(int capacity) : capacity(capacity), size(0)
{
   heap = new Pair<Pair<int, double>, int>[capacity];
}

ModMinHeap::~ModMinHeap()
{
   delete[] heap;
}

void ModMinHeap::heapifyUp(int index)
{
   while (index > 0)
   {
      int parent = (index - 1) / 2; // pela propriedade de árvore completa na representação por array
      if (heap[index].getFirst().getSecond() < heap[parent].getFirst().getSecond())
      {
         swapp(heap[index], heap[parent]);
         index = parent;
      }
      else
      {
         break;
      }
   }
}

void ModMinHeap::heapifyDown(int index)
{
   while (true)
   {
      int leftChild = 2 * index + 1;  // propriedade
      int rightChild = 2 * index + 2; // propriedade
      int smallest = index;

      if (leftChild < size && heap[leftChild].getFirst().getSecond() < heap[smallest].getFirst().getSecond())
      {
         smallest = leftChild;
      }
      if (rightChild < size && heap[rightChild].getFirst().getSecond() < heap[smallest].getFirst().getSecond())
      {
         smallest = rightChild;
      }

      if (smallest != index)
      {
         swapp(heap[index], heap[smallest]);
         index = smallest;
      }
      else
      {
         break;
      }
   }
}

void ModMinHeap::enqueue(const Pair<Pair<int, double>, int> &obj)
{
   if (size >= capacity)
   {
      throw std::runtime_error("Error: Heap is full.");
   }

   heap[size++] = obj;
   heapifyUp(size - 1);
}

Pair<Pair<int, double>, int> ModMinHeap::dequeue()
{
   if (isEmpty())
   {
      throw std::runtime_error("Error: Heap is empty.");
   }

   Pair<Pair<int, double>, int> min = heap[0];
   heap[0] = heap[size - 1];
   size--;
   heapifyDown(0);

   return min;
}

void ModMinHeap::clear()
{
   size = 0;
}

Pair<Pair<int, double>, int> ModMinHeap::getMin_without_remove()
{
   if (isEmpty())
   {
      throw std::runtime_error("Error: Heap is empty.");
   }
   return heap[0];
}

#endif // MIN_HEAP_
