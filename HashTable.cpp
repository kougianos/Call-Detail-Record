#include "HashTable.h"
#include <iostream>
#include <ctime>
using namespace std;

long HashTable::hash(long long key)
{
	return key%size;
}

ListOfCDR * HashTable::add(CDR *r)//prosthetoume ena CDR kai epistrefetai i CDR lista pou antistoixei se auto to CDR
{
	long p=hash(r->getKey(typeofkey));
	if(table[p]==NULL) {
		table[p]=new Buckets(max_bytes_per_bucket,typeofkey);
	}
	return table[p]->add(r);
}

CDR * HashTable::remove(long long key,string cdr_id) //epistrefoume to CDR pou theloume na diagraftei
{
	long p=hash(key);
	if(table[p]==NULL) {
		return NULL;
	}
	return table[p]->remove(key,cdr_id);
}


HashTable::HashTable(long length_hashtable,int max_bytes_bucket,int callerOrCallee):size(length_hashtable),max_bytes_per_bucket(max_bytes_bucket),typeofkey(callerOrCallee)
{
	table=new Buckets*[size];
	for(long i=0; i<size; i++) { //dimiourgeitai ena hashtable me oles tis theseis NULL
		table[i]=NULL;
	}
}


HashTable::~HashTable()
{
	if(table!=NULL) {
		for(long i=0; i<size; i++) {
			if(table[i]!=NULL) {
				delete table[i];
			}
		}
		delete [] table;
	}
}

void HashTable::print(ostream & out)
{
	out<<"Hashtable("<<endl;
	for(int i=0; i<size; i++) {
		if(table[i]!=NULL) {
			out<<"["<<i<<"]"<<endl;
			table[i]->print();
		}
	}
	out<<")"<<endl;
}

ListOfCDR * HashTable::find(long long key)//dinoume ena key kai meso hashing mas epistrefei tin CDR lista pou antistoixei se auto to key
{
	long p=hash(key);
	if(table[p]==NULL) {
		return NULL;
	}
	return table[p]->find(key);
}

ListOfCDR* HashTable::findCopy(long long key,struct tm start,struct tm end)//idio me apopanw alla epistrefetai copy
{
	long p=hash(key);
	if(table[p]==NULL) {
		return NULL;
	}
	return table[p]->findCopy(key,start,end);
}

ListOfCDR * HashTable::findCopy(long long key,int hour1,int minute1, int hour2,int minute2){
	long p=hash(key);
	if(table[p]==NULL) {
		return NULL;
	}
	return table[p]->findCopy(key,hour1,minute1,hour2,minute2);
}

void HashTable::bye()
{
	for(long i=0; i<size; i++) {
		if(table[i]!=NULL) {
			table[i]->bye();
			delete table[i];
		}
	}
	delete [] table;
	table=NULL;
}
