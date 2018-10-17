#ifndef MAXHEAP_H
#define MAXHEAP_H
#include <iostream>
#include "ArrayMaxHeap.h"
#include "ListOfCDR.h"
/*
 o kodikas gia tin heap einai apo tin pigi:
  https://www.codeproject.com/Tips/816934/Min-Binary-Heap-Implementation-in-Cplusplus
  diamorfomenos katallila gia na ginei max heap
  xrisimopoiisa episis kai tin voithitiki List pou exo ftiaksei
 * */
class MaxHeap
{
	private:
		ArrayMaxHeap _vector;
		void BubbleDown(int index);
		void BubbleUp(int index);


	public:
		MaxHeap();
		void Heapify();
		void Insert(ListOfCDR * newValue);
		ListOfCDR * GetMin();
		void DeleteMin();
		void print(std::ostream & out=std::cout);
		bool isEmpty();
		void printTop(double etaireia_profit,double k);
};


#endif // MAXHEAP_H
