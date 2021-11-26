/*
INTEGRANTES:
-Suni Quispe Yanira Angie
-Bejar Roman Edson Bryan
-Bejar Roman Katherine Nikole
*/
#include <iostream>
#include <cstdlib>
#include <vector>
#include <iterator>
using namespace std;
class BHeap {
   private:
   vector <int> heap;
   int l(int parent);
   int r(int parent);
   int par(int child);
   void heapfy_up(int i);
   void heapfy_down(int i);
   public:
      BHeap() {}
      void Insert(int element);
      void DeleteMin();
      int ExtractMin();
      void print();
      int Size();
};
int main() {
   BHeap h;
   while (1) {
      cout<<"1.Insertar Elemento"<<endl;
      cout<<"2.Eliminar Elemento Minimo"<<endl;
      cout<<"3.Extraer Elemento Minimo"<<endl;
      cout<<"4.Mostrar"<<endl;
      cout<<"5.Salir"<<endl;
      int c, e;
      cout<<"Elige un numero: ";
      cin>>c;
      switch(c) {
         case 1:
            cout<<"Ingresa el elemento a insertar: ";
            cin>>e;
            h.Insert(e);
         break;
         case 2:
            h.DeleteMin();
         break;
         case 3:
            if (h.ExtractMin() == -1) {
               cout<<"Heap vacio"<<endl;
            }
            else
            cout<<"Elemento minimo: "<<h.ExtractMin()<<endl;
         break;
         case 4:
            cout<<"Heap: ";
            h.print();
         break;
         case 5:
            exit(1);
            default:
            cout<<"Vuelve a ingresar el numero correctamente"<<endl;
      }
   }
   return 0;
}
int BHeap::Size() {
   return heap.size();
}
void BHeap::Insert(int d) {
   heap.push_back(d);
   heapfy_up(heap.size() -1);
}
void BHeap::DeleteMin() {
   if (heap.size() == 0) {
      cout<<"Heap vacio"<<endl;
      return;
   }
   heap[0] = heap.at(heap.size() - 1);
   heap.pop_back();
   heapfy_down(0);
   cout<<"Elemento eliminado"<<endl;
}
int BHeap::ExtractMin() {
   if (heap.size() == 0) {
      return -1;
   }
   else
   return heap.front();
}
void BHeap::print() {
   vector <int>::iterator pos = heap.begin();
   cout<<"Heap -> ";
   while (pos != heap.end()) {
      cout<<*pos<<" ";
      pos++;
   }
   cout<<endl;
}
int BHeap::l(int parent) {
   int l = 2 * parent + 1;
   if (l < heap.size())
      return l;
   else
      return -1;
}
int BHeap::r(int parent) {
   int r = 2 * parent + 2;
   if (r < heap.size())
      return r;
   else
      return -1;
}
int BHeap::par(int child) {
   int p = (child - 1)/2;
   if (child == 0)
      return -1;
   else
      return p;
}
void BHeap::heapfy_up(int in) {
   if (in >= 0 && par(in) >= 0 && heap[par(in)] > heap[in]) {
      int temp = heap[in];
      heap[in] = heap[par(in)];
      heap[par(in)] = temp;
      heapfy_up(par(in));
   }
}
void BHeap::heapfy_down(int in) {
   int child = l(in);
   int child1 = r(in);
   if (child >= 0 && child1 >= 0 && heap[child] > heap[child1]) {
      child = child1;
   }
   if (child > 0 && heap[in] > heap[child]) {
      int t = heap[in];
      heap[in] = heap[child];
      heap[child] = t;
      heapfy_down(child);
   }
}