#ifndef ARRAYMAXHEAP_H
#define ARRAYMAXHEAP_H
#include "ListOfCDR.h"

//i max heap exei ulopoiithei san CDR lista kai leitourgei san dentro
class NodeMaxHeap{
	public:
	ListOfCDR * data;
	NodeMaxHeap * previous;
	NodeMaxHeap * next;
	
	NodeMaxHeap(ListOfCDR * d,NodeMaxHeap *p,NodeMaxHeap *n){
		this->data=d;
		this->previous=p;
		this->next=n;
	}
	~NodeMaxHeap(){
	}
};

class ArrayMaxHeap
{
	int the_size;
	NodeMaxHeap * start;
	NodeMaxHeap * end;
public:
	ArrayMaxHeap();
	~ArrayMaxHeap();
	
	NodeMaxHeap * getStart();
	int size();
	void add(ListOfCDR* list);
	bool contains(long long caller);
	ListOfCDR * find(long long caller);
	
	void print(std::ostream & out=std::cout);
	
	ListOfCDR * getAt(int position);
	void setAt(int position,ListOfCDR * d);
	ListOfCDR * pop_back();
	void push_back(ListOfCDR * d);

};

#endif // ARRAYMAXHEAP_H
