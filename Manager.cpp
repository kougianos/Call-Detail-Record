#include "Manager.h"
#include "CDR.h"
#include "CountryCodesList.h"
#include "MaxHeap.h"
#include <ctime>
using namespace std;

Manager::Manager(int hashtable_size1,int hashtable_size2,int max_bytes_bucket)
{
	this->hashtable_size1=hashtable_size1;
	this->hashtable_size2=hashtable_size2;
	this->max_bytes_bucket=max_bytes_bucket;
	this->sum_amount=0.0; //arxika to sunoliko kostos einai 0
	originator_to_cdrs =new HashTable(hashtable_size1,max_bytes_bucket,ORIGINATOR);
	destination_to_cdrs =new HashTable(hashtable_size2,max_bytes_bucket,DESTINATION);
	mh=new MaxHeap();
}

Manager::~Manager()
{
	originator_to_cdrs->bye(); //diagrafontai ta cdrs mono mia fora
	delete originator_to_cdrs;
	delete destination_to_cdrs;
	delete mh;
}

bool Manager::add(CDR* cdr)
{
	ListOfCDR * result1=originator_to_cdrs->add(cdr);
	ListOfCDR * result2=destination_to_cdrs->add(cdr);

	if(result1!=NULL) {
		//prostethike neos caller edw, ara exoume nea listofcdr
		//tin opoia tha prosthesoume kai sto max heap
		mh->Insert(result1);
	}
	mh->Heapify();
	sum_amount+=cdr->computeCost();
	return true;
}

bool Manager::remove(long long caller, string cdr_id)
{
	CDR * deleted=originator_to_cdrs->remove(caller,cdr_id); 
	if(deleted==NULL) {
		return false;
	}
	destination_to_cdrs->remove(deleted->GetDestination(),cdr_id);
	mh->Heapify();
	sum_amount-=deleted->computeCost(); //afairoume apo to sum_amount to kostos tis CDR pou diagrapsame
	delete deleted;
	return true;
}

void Manager::print(int which_hashtable,ostream & out) //gia 1 ektiponei originators, gia 2 destinations
{
	if(which_hashtable==1) {
		originator_to_cdrs->print(out);
	} else {
		destination_to_cdrs->print(out);
	}

}

ListOfCDR* Manager::findByCaller(long long caller, int hour1,int minute1, int hour2,int minute2,int day1,int month1, int year1,int day2,int month2, int year2)
{
	time_t rawtime;
	time ( &rawtime );
	struct tm start=*(gmtime(&rawtime));
	start.tm_year=year1;
	start.tm_hour=hour1;
	start.tm_min=minute1;
	start.tm_sec=0;
	start.tm_mon=month1;
	start.tm_mday=day1;
//	start.tm_zone = "GMT";
	start.tm_isdst=-1;

	struct tm end=*(gmtime(&rawtime));
	end.tm_year=year2;
	end.tm_hour=hour2;
	end.tm_min=minute2;
	end.tm_sec=0;
	end.tm_mon=month2;
	end.tm_mday=day2;
	//end.tm_zone = "GMT";
	end.tm_isdst=-1;

	return originator_to_cdrs->findCopy(caller,start,end);
}

ListOfCDR *  Manager::findByCaller(long long caller, int hour1,int minute1, int hour2,int minute2)
{
	return originator_to_cdrs->findCopy(caller,hour1,minute1,hour2,minute2);
}

ListOfCDR* Manager::lookupByCallee(long long callee, int hour1,int minute1, int hour2,int minute2,int day1,int month1, int year1,int day2,int month2, int year2)
{
	time_t rawtime;
	time ( &rawtime );
	struct tm start=*(gmtime(&rawtime));
	start.tm_year=year1-1900;
	start.tm_hour=hour1;
	start.tm_min=minute1;
	start.tm_sec=0;
	start.tm_mon=month1-1;
	start.tm_mday=day1;
	start.tm_isdst=-1;

	struct tm end=*(gmtime(&rawtime));
	end.tm_year=year2-1900;
	end.tm_hour=hour2;
	end.tm_min=minute2;
	end.tm_sec=0;
	end.tm_mon=month2-1;
	end.tm_mday=day2;
	end.tm_isdst=-1;

	return destination_to_cdrs->findCopy(callee,start,end);
}

ListOfCDR *  Manager::lookupByCallee(long long callee, int hour1,int minute1, int hour2,int minute2)
{
	return destination_to_cdrs->findCopy(callee,hour1,minute1,hour2,minute2);
}

List * Manager::indist1(long long callee1, long long callee2)
{
	List * commons=new List();
	ListOfCDR * list1=originator_to_cdrs->find(callee1); // CDR lista me caller ton callee1
	ListOfCDR * list11=destination_to_cdrs->find(callee1); // CDR lista me calee ton callee1

	ListOfCDR * list2=originator_to_cdrs->find(callee2); // CDR lista me caller ton callee2
	ListOfCDR * list22=destination_to_cdrs->find(callee2); // CDR lista me callee ton callee2
	
	List * list1_final=new List();//oi telikes listes tis opoies tha sugrinoume
	List * list2_final=new List();

	NodeCDR * temp1=list1->getStart();
	while(temp1!=NULL) { //i list1_final periexei osous exei kalesei o callee1 kai osous exoun kalesei ton callee1
		list1_final->add(temp1->data->GetDestination()); 
		temp1=temp1->next;
	}
	temp1=list11->getStart();
	while(temp1!=NULL) {
		list1_final->add(temp1->data->GetOriginator());
		temp1=temp1->next;
	}

	NodeCDR * temp2=list2->getStart(); //to idio kai i list2_final, gia ton callee2
	while(temp2!=NULL) {
		list2_final->add(temp2->data->GetDestination());
		temp2=temp2->next;
	}
	temp2=list22->getStart();
	while(temp2!=NULL) {
		list2_final->add(temp2->data->GetOriginator());
		temp2=temp2->next;
	}

	Node * temp11=list1_final->getStart();
	while(temp11!=NULL) {
		Node * temp22=list2_final->getStart();
		while(temp22!=NULL) {
			if(*(temp11->data)== *(temp22->data)) {
				commons->add(*(temp11->data)); //oi koinoi arithmoi stis 2 listes
			}
			temp22=temp22->next;
		}
		temp11=temp11->next;
	}

	List * invalids=new List();//se autin tin lista tha einai oi arithmoi apo tous commons pou tha exoun epikoinonisei metaksu tous

	temp11 = commons->getStart();
	while(temp11!=NULL) {
		Node * temp22 = commons->getStart();
		while(temp22!=NULL) {
			ListOfCDR * cdrs1=originator_to_cdrs->find(*(temp11->data));
			if(cdrs1!=NULL) {
				if(cdrs1->containsCDRwithCallee(*(temp22->data))) {
					invalids->add(*(temp11->data));
					invalids->add(*(temp22->data));
				}
			}
			ListOfCDR * cdrs2=originator_to_cdrs->find(*(temp22->data));
			if(cdrs2!=NULL) {
				if(cdrs2->containsCDRwithCallee(*(temp11->data))) {
					invalids->add(*(temp11->data));
					invalids->add(*(temp22->data));
				}
			}


			temp22=temp22->next;
		}
		temp11=temp11->next;
	}

	List * result=new List();
	Node * common = commons->getStart();
	while(common!=NULL) { //afairoume apo commons tous invalids, auto tha einai to teliko result mas
		bool found=false;
		Node * invalid = invalids->getStart();
		while(invalid!=NULL) {
			if( *(common->data) == *(invalid->data) ) {
				found=true;
				break;
			}
			invalid=invalid->next;
		}
		if(found==false) {
			result->add(*(common->data));
		}
		common=common->next;
	}
	delete list1_final;
	delete list2_final;
	delete commons;
	delete invalids;
	return result;
}

void Manager::bye() 
{	//diagrafontai ola alla dimiourgountai ksana nea kena hashtables kai maxheap gia eisagogi newn stoixeiwn
	originator_to_cdrs->bye();
	delete originator_to_cdrs;
	delete destination_to_cdrs;
	delete mh;
	originator_to_cdrs=new HashTable(hashtable_size1,max_bytes_bucket,ORIGINATOR);
	destination_to_cdrs=new HashTable(hashtable_size2,max_bytes_bucket,DESTINATION);
	mh=new MaxHeap();
}

ListOfCDR* Manager::findByCaller(long long caller)
{
	return originator_to_cdrs->find(caller);
}

ListOfCDR* Manager::lookupByCallee(long long callee)
{
	return destination_to_cdrs->find(callee);
}

int Manager::topdest(long long caller,int * emfaniseis) //epistrefei ton tripsifio kodiko me tis perissoteres emfaniseis
{
	ListOfCDR * list=originator_to_cdrs->find(caller);
	if(list==NULL) {
		return -1;
	}
	NodeCDR * temp=list->getStart();
	CountryCodesList * destinations=new CountryCodesList();
	while(temp!=NULL) {
		destinations->add(temp->data->getCountryCodeDestination());
		temp=temp->next;
	}

	int popular_dest=destinations->findPopular(emfaniseis);
	delete destinations;
	return popular_dest;
}

long long Manager::top(int k)
{
	mh->printTop(sum_amount,k);
}
