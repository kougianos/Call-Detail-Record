#ifndef LIST_H
#define LIST_H
#include <iostream>

//voithitiki lista pou kathe komvos periexei enan double* , previous, kai next

class Node{
	public:
	double * data;
	Node * previous;
	Node * next;
	
	Node(double d,Node *p,Node *n){
		this->data=new double[1];
		*(this->data)=d;
		this->previous=p;
		this->next=n;
	}
	~Node(){
	}
};

class List
{
	int the_size;
	Node * start;
	Node * end;
public:
	List();
	~List();
	
	Node * getStart();
	int size();
	double * add(double d);
	bool remove(double d);
	bool contains(double d);
	Node * find(double d);
	
	void print(std::ostream & out=std::cout);
	
	double * getAt(int position);
	void setAt(int position,double * d);
	double pop_back(bool delete_data);
	double * push_back(double d);
};
#endif // LIST_H
