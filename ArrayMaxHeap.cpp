#include "ArrayMaxHeap.h"
#include <iostream>
using namespace std;
ArrayMaxHeap::ArrayMaxHeap()
{
	the_size=0; //arxika exei size 0
	start=NULL;
	end=NULL;
}

ArrayMaxHeap::~ArrayMaxHeap()
{
	NodeMaxHeap * temp1=start;
	while(temp1!=NULL) {
		NodeMaxHeap * temp2=temp1->next;
		delete temp1;
		temp1=temp2;
	}
}

NodeMaxHeap* ArrayMaxHeap::getStart()
{
	return start;
}

int ArrayMaxHeap::size()
{
	return the_size;
}

void ArrayMaxHeap::add(ListOfCDR* list)
{
	if(start==NULL) {
		start=new NodeMaxHeap(list,NULL,NULL);
		end=start;
	} else { //to vazw stin arxi
		NodeMaxHeap * newnode=new NodeMaxHeap(list,NULL,start);
		start->previous=newnode;
		start=newnode;
	}
	the_size++;
}

bool ArrayMaxHeap::contains(long long caller)//epistrefei true an o caller uparxei mesa stin lista
{
	NodeMaxHeap * temp=start;
	while(temp!=NULL) {
		if(temp->data->getKey()==caller) {
			return true;
		}
		temp=temp->next;
	}
	return false;
}

ListOfCDR* ArrayMaxHeap::find(long long caller) //dinoume san orisma enan arithmo caller kai mas epistrefei tin CDR lista pou antistoixei se auton ton arithmo
{
	NodeMaxHeap * temp=start;
	while(temp!=NULL) {
		if(temp->data->getKey()==caller) {
			return temp->data;
		}
		temp=temp->next;
	}
	return NULL;
}

void ArrayMaxHeap::print(std::ostream& out)
{
	out<<"Printing max heap..."<<endl;
}

ListOfCDR* ArrayMaxHeap::getAt(int position) //dinoume mia thesi kai mas epistrefei tin CDR lista pou antistoixei se autin tin thesi
{
	if(position>=the_size || position<0) {
		cout<<"Error getAt -1"<<endl;
		return NULL;
	}
	int counter=0;
	NodeMaxHeap * temp=start;
	while(temp!=NULL) {
		if(counter==position) {
			return temp->data;
		}
		counter++;
		temp=temp->next;
	}
	cout<<"Error getAt -2"<<endl;
	return NULL;
}

void ArrayMaxHeap::setAt(int position, ListOfCDR* d)//vazei mia CDR lista se mia sugekrimeni thesi
{
	if(position>=the_size || position<0) {
		cout<<"Error getAt"<<endl;
		return;
	}
	int counter=0;
	NodeMaxHeap * temp=start;
	while(temp!=NULL) {
		if(counter==position) {
			temp->data=d;
			return;
		}
		counter++;
		temp=temp->next;
	}
}

ListOfCDR* ArrayMaxHeap::pop_back() //epistrefei tin teleutaia CDR lista sto maxheap mas
{
	NodeMaxHeap * temp=end;
	if(temp!=NULL) {
		ListOfCDR* result=end->data;
		NodeMaxHeap * p=end->previous;
		if(p!=NULL) {
			p->next=NULL;
		}
		if(temp==start){
			start=NULL;
		}
		end=p;
		
		delete temp;
		the_size--;
		return result;
	} else {
		cout<<"No element in list"<<endl;
		return NULL;
	}
}

void ArrayMaxHeap::push_back(ListOfCDR* d)//vazei mia CDR lista sto telos tis maxheap
{
	if(end==NULL) {
		start=new NodeMaxHeap(d,NULL,NULL);
		end=start;
	} else {
		// valto stin arxi
		if(end->next!=NULL){
			cout<<"WHAT THE"<<endl;
		}
		end->next=new NodeMaxHeap(d,end,NULL);
		end=end->next;
	}
	the_size++;
}
