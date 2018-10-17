#include "Bucket.h"
#include <iostream>
#include <ctime>
using namespace std;

Bucket::Bucket(int s) : max_size(s)
{
	the_size=0;
	this->records=new ListOfCDR*[max_size];
	for(int i=0; i<max_size; i++)
		this->records[i]=NULL; //arxika oles oi theseis einai kenes
}

Bucket::~Bucket()
{
	//cout<<"The bucketCDR size is"<<the_size<<endl;
	if(this->records!=NULL) {
		for(int i=0; i<max_size; i++) {
			//cout<<"i="<<i<<endl;
			if(this->records[i]!=NULL) {
				delete this->records[i];
			}
		}
		delete [] this->records;
	}
}

bool Bucket::add(ListOfCDR * r) //prothesi CDR listas
{
	if(the_size==max_size) {
		return false;
	}
	the_size++;
	for(int i=max_size-1; i>=0; i--) {
		if(records[i]==NULL) {
			records[i]=r;
			return true;
		}
	}
	return true;
}


bool Bucket::remove(ListOfCDR * r)//diagrafi CDR listas
{
	for(int i=0; i<max_size; i++) {
		if(r==records[i]) {
			delete records[i];
			records[i]=NULL;
			the_size--;
			return true;
		}
	}
	return false;
}

bool Bucket::remove(long long key)//diagrafi CDR listas me vasi to number_key tis listas
{
	for(int i=0; i<max_size; i++) {
		if(records[i]!=NULL) {
			if(records[i]->getKey()==key) {
				delete records[i];
				records[i]=NULL;
				the_size--;
				return true;
			}
		}
	}
	return false;
}


bool Bucket::contains(long long key)
{
	for(int i=0; i<max_size; i++) {
		if(records[i]!=NULL) {
			if(records[i]->getKey()==key) {
				return true;
			}
		}
	}
	return false;
}

ListOfCDR * Bucket::find(long long key)//epistrefei mia CDR lista
{
	for(int i=0; i<max_size; i++) {
		if(records[i]!=NULL) {
			if(records[i]->getKey()==key) {
				return records[i]; // return a copy
			}
		}
	}
	return NULL;
}

ListOfCDR * Bucket::findCopy(long long key)//epistrefei antigrafo CDR listas
{
	for(int i=0; i<max_size; i++) {
		if(records[i]!=NULL) {
			if(records[i]->getKey()==key) {
				return new ListOfCDR(records[i]); 
			}
		}
	}
	return NULL;
}

void Bucket::print(ostream & out)
{
	//cout<<"the_size="<<the_size<<endl;
	out<<"Bucket(";
	bool first_found=true;
	for(int i=0; i<max_size; i++) {
		if(records[i]!=NULL) {
			if(first_found) {
				out<<"key-"<<records[i]->getKey();
				records[i]->print();
			} else {
				first_found=false;
				out<<", key-"<<records[i]->getKey();
				records[i]->print();
			}
		}
	}
	out<<")"<<endl;
}

int Bucket::size()
{
	return the_size;
}

bool Bucket::isFull()
{
	return the_size==max_size;
}

ListOfCDR* Bucket::findCopy(long long key, struct tm start, struct tm end)
{
	for(int i=0; i<max_size; i++) {
		if(records[i]!=NULL) {
			if(records[i]->getKey()==key) {
				return records[i]->findCopy(start,end); // epistrefei antigrafo CDR listas pou periexei ta filtrarismena CDRs
				//return records[i];
			}
		}
	}
	return NULL;
}

ListOfCDR * Bucket::findCopy(long long key,int hour1,int minute1, int hour2,int minute2){
	for(int i=0; i<max_size; i++) {
		if(records[i]!=NULL) {
			if(records[i]->getKey()==key) {
				return records[i]->findCopy(hour1,minute1,hour2,minute2); // creates a new list with the filtered cdrs
				//return records[i];
			}
		}
	}
	return NULL;
}

void Bucket::bye()
{
	for(int i=0; i<max_size; i++) {
		//cout<<"i="<<i<<endl;
		if(this->records[i]!=NULL) {
			this->records[i]->bye();
			delete this->records[i];
		}
	}
	delete [] this->records;
	this->records=NULL;
}
