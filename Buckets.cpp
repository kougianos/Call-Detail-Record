#include "Buckets.h"
#include <iostream>
#include <ctime>
using namespace std;
Buckets::Buckets(int max_bytes_bucket,int callerOrCallee):max_bytes_per_bucket(max_bytes_bucket),typeofkey(callerOrCallee)
{
	the_size=0;
	start=NULL;
	end=NULL;
}

Buckets::~Buckets()
{
	NodeBucket * temp1=start;
	while(temp1!=NULL) {
		NodeBucket * temp2=temp1->next;
		delete temp1;
		temp1=temp2;
	}
}

ListOfCDR * Buckets::add(CDR * r)//prosthetei ena CDR sto bucket kai mas epistrefei tin lista stin opoia prostethike
{
	if(start==NULL) {
		start=new NodeBucket(max_bytes_per_bucket,NULL,NULL,typeofkey);
		end=start;
		if(start==NULL) {
			return NULL;
		}
		
		ListOfCDR * list=new ListOfCDR(r->getKey(typeofkey));
		list->add(r);
		start->data->add(list);
		the_size++;
		return list;
	} else {//an den einai NULL tsekarw an uparxei xoros gia na prostethei se auto to bucket
		if(contains(r->getKey(typeofkey))) {//an sto bucket periexetai idi lista me to number tou CDR pou tha prostethei
			ListOfCDR *returned_list=find(r->getKey(typeofkey)); //vriskw autin tin lista kai tis prosthetw to CDR
			returned_list->add(r);
			return NULL;
		} else {//an den uparxei sto bucket i lista pou prepei na mpei to CDR
			NodeBucket * temp=start;
			while(temp!=NULL) {
				if(temp->data->isFull()) { //elegxw ena ena ta buckets gia na dw poio den einai gemato
					temp=temp->next;
				} else {
					ListOfCDR * list=new ListOfCDR(r->getKey(typeofkey)); //an vrw kapoio pou den einai gemato
					list->add(r); //vazw stin CDR lista to record
					temp->data->add(list); //kai vazw tin lista sto bucket
					return list;
				}
			}

			// ola einai full
			// ftiaxnw neo bucket stin arxi kai to vazw ekei
			start=new NodeBucket(max_bytes_per_bucket,NULL,start,typeofkey);
			if(start==NULL) {
				return NULL;
			}
			ListOfCDR * list=new ListOfCDR(r->getKey(typeofkey));
			list->add(r);
			start->data->add(list);
			the_size++;
			return list;
		}


	}
	return NULL;
}


CDR * Buckets::remove(long long key,std::string cdr_id)//epistrefei ena diagrameno CDR apo to bucket, i sigrisi ginetai sta cdr_id
{
	ListOfCDR * list=find(key);
	if(list!=NULL){
		CDR * removed=list->remove(cdr_id);
		return removed;
	}else{
		return NULL;
	}
}

bool Buckets::contains(long long key)//true an periexetai ena CDR sto bucket
{
	NodeBucket * temp=start;
	while(temp!=NULL) {
		if(temp->data->contains(key)) {
			return true;
		}
		temp=temp->next;
	}
	return false;
}

ListOfCDR * Buckets::find(long long key)//epistrefei tin lista pou antistoixei sto key pou dosame
{
	NodeBucket * temp=start;
	while(temp!=NULL) {
		ListOfCDR * result=temp->data->find(key);
		if(result!=NULL) {
			return result;
		}
		temp=temp->next;
	}
	return NULL;
}

ListOfCDR * Buckets::findCopy(long long key)//epistrefei antigrafo tis listas
{
	NodeBucket * temp=start;
	while(temp!=NULL) {
		ListOfCDR * result=temp->data->findCopy(key);
		if(result!=NULL) {
			return result;
		}
		temp=temp->next;
	}
	return NULL;
}

void Buckets::print(ostream & out)
{
	out<<"ListBucket("<<endl;
	NodeBucket * temp=start;
	if(temp!=NULL) {
		//cout<<"111"<<temp->data<<endl;
		temp->data->print();
		temp=temp->next;
	}
	//cout<<"222"<<endl;
	while(temp!=NULL) {
		out<<", ";
		temp->data->print();
		temp=temp->next;
	}
	out<<")"<<endl;
}

int Buckets::size()
{
	return the_size;
}

ListOfCDR* Buckets::findCopy(long long key, tm start_datetime, tm end_datetime) //epistrefei filtrarismeno antigrafo listas
{
	NodeBucket * temp=start;
	while(temp!=NULL) {
		ListOfCDR * result=temp->data->findCopy(key,start_datetime,end_datetime);
		if(result!=NULL) {
			return result;
		}
		temp=temp->next;
	}
	return NULL;
}

ListOfCDR * Buckets::findCopy(long long key,int hour1,int minute1, int hour2,int minute2){
	NodeBucket * temp=start;
	while(temp!=NULL) {
		ListOfCDR * result=temp->data->findCopy(key,hour1,minute1,hour2,minute2);
		if(result!=NULL) {
			return result;
		}
		temp=temp->next;
	}
	return NULL;
}


void Buckets::bye()
{
	NodeBucket * temp1=start;
	while(temp1!=NULL) {
		NodeBucket * temp2=temp1->next;
		temp1->data->bye();
		delete temp1;
		temp1=temp2;
	}
	start=NULL;
}
