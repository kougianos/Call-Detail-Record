#include "ListOfCDR.h"
#include <iostream>
#include <ctime>
using namespace std;
ListOfCDR::ListOfCDR(long long key)
{
	number_key=key;
	amount=0.0;
	the_size=0;
	start=NULL;
	end=NULL;
	max_heap_node=NULL;
}

ListOfCDR::ListOfCDR(ListOfCDR * other)
{
	this->number_key=other->number_key;
	this->amount=other->amount;
	this->the_size=other->the_size;

	NodeCDR * current_previous=NULL;

	NodeCDR * temp=other->start;
	NodeCDR * newnode=NULL;
	while(temp!=NULL) {
		newnode=new NodeCDR(temp->data,current_previous,NULL);
		if(current_previous!=NULL) {
			current_previous->next=newnode;
		}
		if(temp==other->start) {
			start=newnode;
		}

		temp=temp->next;
	}
	this->end=newnode;
}

ListOfCDR::~ListOfCDR()
{
	NodeCDR * temp1=start;
	while(temp1!=NULL) {
		NodeCDR * temp2=temp1->next;
		delete temp1;
		temp1=temp2;
	}
}

bool ListOfCDR::add(CDR * d)
{
	amount+=d->computeCost();
	if(start==NULL) { //gia tin proti fora pou i lista einai keni
		start=new NodeCDR(d,NULL,NULL);
		end=start;
	} else {
		// to vazw stin arxi
		NodeCDR * newnode=new NodeCDR(d,NULL,start);
		start->previous=newnode;
		start=newnode;
	}
	if(start==NULL) {
		return false;
	}
	the_size++;
	return true;
}

CDR * ListOfCDR::remove(CDR * d)
{
	NodeCDR * temp=start; //ksekinaw apo tin arxi kai trexw enan enan tous komvous gia na diagrapsw to katallilo CDR
	while(temp!=NULL) {
		if(temp->data==d) {
			NodeCDR * p=temp->previous;
			NodeCDR * n=temp->next;
			if(p!=NULL) {
				p->next=n;
			}
			if(n!=NULL) {
				n->previous=p;
			}

			if(temp==start) {
				//cout<<"MPIKEEEEE!!!"<<endl;
				start=n;
			}
			if(temp==end) {
				end=p;
			}
			CDR * result=temp->data;
			amount-=result->computeCost();
			delete temp;
			the_size--;
			if(the_size==0) {
				start=NULL;
				end=NULL;
			}
			return result;
		}
		temp=temp->next;
	}
	return NULL;
}


CDR * ListOfCDR::remove(string cdr_id)//idio me apopanw alla tora i sigrisi ginetai sto cdr_id
{
	NodeCDR * temp=start;
	while(temp!=NULL) {
		if(temp->data->GetId()==cdr_id) {
			NodeCDR * p=temp->previous;
			NodeCDR * n=temp->next;
			if(p!=NULL) {
				p->next=n;
			}
			if(n!=NULL) {
				n->previous=p;
			}

			if(temp==start) {
				//cout<<"MPIKEEEEE!!!"<<endl;
				start=n;
			}

			if(temp==end) {
				end=p;
			}
			CDR * result=temp->data;
			amount-=result->computeCost();
			delete temp;
			the_size--;
			if(the_size==0) {
				start=NULL;
				end=NULL;
			}
			return result;
		}
		temp=temp->next;
	}
	return NULL;
}

bool ListOfCDR::contains(CDR * d) //true an periexetai to CDR sti lista mas
{
	NodeCDR * temp=start;
	while(temp!=NULL) {
		if(temp->data==d) {
			return true;
		}
		temp=temp->next;
	}
	return false;
}

bool ListOfCDR::contains(string cdr_id)
{
	NodeCDR * temp=start;
	while(temp!=NULL) {
		if(temp->data->GetId()==cdr_id) {
			return true;
		}
		temp=temp->next;
	}
	return false;
}

CDR * ListOfCDR::find(CDR * d)
{
	NodeCDR * temp=start;
	while(temp!=NULL) {
		if(temp->data==d) {
			return temp->data;
		}
		temp=temp->next;
	}
	return NULL;
}

CDR * ListOfCDR::find(string cdr_id)
{
	NodeCDR * temp=start;
	while(temp!=NULL) {
		if(temp->data->GetId()==cdr_id) {
			return temp->data;
		}
		temp=temp->next;
	}
	return NULL;
}

void ListOfCDR::print(ostream & out)
{
	out<<"ListOfCDR(";
	NodeCDR * temp=start;
	if(temp!=NULL) {
		//out<<temp->data->GetId();
		temp->data->print(out);
		temp=temp->next;
	}
	while(temp!=NULL) {
		out<<", "; //temp->data->GetId();
		temp->data->print(out);
		temp=temp->next;
	}
	out<<")"<<endl;
}

int ListOfCDR::size()
{
	return the_size;
}

long long ListOfCDR::getKey()
{
	return number_key;
}

ListOfCDR* ListOfCDR::findCopy(struct tm start_datetime,struct tm end_datetime)
{
	ListOfCDR * newlist=new ListOfCDR(number_key);
	NodeCDR * temp=start;
	while(temp!=NULL) {
		if(temp->data->isInInterval(start_datetime,end_datetime)) {
			newlist->add(temp->data);
		}
		temp=temp->next;
	}
	return newlist;
}

ListOfCDR * ListOfCDR::findCopy(int hour1,int minute1,int hour2,int minute2)
{
	ListOfCDR * newlist=new ListOfCDR(number_key);
	NodeCDR * temp=start;
	while(temp!=NULL) {
		//cout<<"checking interval "<<hour1<<","<<minute1<<" ews "<<hour2<<","<<minute2<<endl;
		if(temp->data->isInInterval(hour1,minute1,hour2,minute2)) {
			newlist->add(temp->data);
		}
		temp=temp->next;
	}
	return newlist;
}

void ListOfCDR::bye()
{
	NodeCDR * temp1=start;
	while(temp1!=NULL) {
		NodeCDR * temp2=temp1->next;
		delete temp1->data;
		delete temp1;
		temp1=temp2;
	}
	start=NULL;
}

bool ListOfCDR::containsCDRwithCallee(long long callee)
{
	NodeCDR * temp=start;
	while(temp!=NULL) {
		if(temp->data->GetDestination()==callee) {
			return true;
		}
		temp=temp->next;
	}
	return false;
}

int ListOfCDR::findMostUsedPrefix()
{
	NodeCDR * temp=start;
	while(temp!=NULL) {

		temp=temp->next;
	}
	return false;
}

NodeCDR * ListOfCDR::getStart()
{
	return start;
}

double ListOfCDR::getAmount()
{
	return amount;
}
