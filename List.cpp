#include "List.h"
#include <iostream>
using namespace std;
List::List()
{
	the_size=0;
	start=NULL;
	end=NULL;
}

List::~List()
{
	Node * temp1=start;
	while(temp1!=NULL) {
		Node * temp2=temp1->next;
		delete temp1->data;
		delete temp1;
		temp1=temp2;
	}
}

double * List::add(double d)
{
	if(start==NULL) {
		start=new Node(d,NULL,NULL);
		end=start;
	} else {
		Node * newnode=new Node(d,NULL,start);
		start->previous=newnode;
		start=newnode;
	}
	if(start==NULL) {
		return NULL;
	}
	the_size++;
	return start->data;
}

double * List::push_back(double d)
{
	if(end==NULL) {
		start=new Node(d,NULL,NULL);
		end=start;
	} else {
		if(end->next!=NULL){
			cout<<"WHAT THE"<<endl;
		}
		end->next=new Node(d,end,NULL);
		end=end->next;
	}
	if(end==NULL) {
		return NULL;
	}
	the_size++;
	return end->data;
}

bool List::remove(double d)
{
	Node * temp=start;
	while(temp!=NULL) {
		if(*(temp->data)==d) {
			Node * p=temp->previous;
			Node * n=temp->next;
			if(p!=NULL) {
				p->next=n;
			}
			if(n!=NULL) {
				n->previous=p;
			}

			if(temp==start) {
				start=n;
			}
			if(temp==end) {
				end=p;
			}
			delete temp->data;
			delete temp;
			the_size--;
			if(the_size==0) {
				start=NULL;
				end=NULL;
			}
			return true;
		}
		temp=temp->next;
	}
	return false;
}

bool List::contains(double d)
{
	Node * temp=start;
	while(temp!=NULL) {
		if(*(temp->data)==d) {
			return true;
		}
		temp=temp->next;
	}
	return false;
}

Node * List::find(double d)
{
	Node * temp=start;
	while(temp!=NULL) {
		if(*(temp->data) ==d) {
			return temp;
		}
		temp=temp->next;
	}
	return NULL;
}


void List::print(ostream & out)
{
	out<<"List(";
	Node * temp=start;
	if(temp!=NULL) {
		out<<*(temp->data);
		temp=temp->next;
	}
	while(temp!=NULL) {
		out<<", "<<*(temp->data);
		temp=temp->next;
	}
	out<<")"<<endl;
}

int List::size()
{
	return the_size;
}

double * List::getAt(int position)
{
	if(position>=the_size || position<0) {
		cout<<"Error getAt -1"<<endl;
		return NULL;
	}
	int counter=0;
	Node * temp=start;
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

void List::setAt(int position,double * d)
{
	if(position>=the_size || position<0) {
		cout<<"Error getAt"<<endl;
		return;
	}
	int counter=0;
	Node * temp=start;
	while(temp!=NULL) {
		if(counter==position) {
			temp->data=d;
			return;
		}
		counter++;
		temp=temp->next;
	}
}

double List::pop_back(bool delete_data)//epistrefei to teleutaio stoixeio, an dosoume true to kanei kai diagrafi
{
	Node * temp=end;
	if(temp!=NULL) {
		double result=*(end->data);
		Node * p=end->previous;
		if(p!=NULL) {
			p->next=NULL;
		}
		if(temp==start){
			start=NULL;
		}
		end=p;
		if(delete_data){
			delete temp->data;
		}
		delete temp;
		the_size--;
		return result;
	} else {
		cout<<"KANENA STOIXEIO STIN LISTA"<<endl;
		return -1.0;
	}
}

Node * List::getStart(){
	return start;
}