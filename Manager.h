#ifndef MANAGER_H
#define MANAGER_H
#include <iostream>
#include "CDR.h"
#include "HashTable.h"
#include "MaxHeap.h"
#include "List.h"

#define ORIGINATOR 0
#define DESTINATION 1


//enum TYPE{
//	ORIGINATOR,DESTINATION;
//}

class Manager
{
	int hashtable_size1;
	int hashtable_size2;
	int max_bytes_bucket;
	double sum_amount; //to sunoliko amount pou exoun ksodepsei oi sundromites
	
	HashTable * originator_to_cdrs;
	HashTable * destination_to_cdrs;
	MaxHeap * mh;
public:
	Manager(int hashtable_size1,int hashtable_size2,int max_bytes_bucket);
	~Manager();
	
	bool add(CDR * cdr); // erwtima 1
	bool remove(long long caller,std::string cdr_id); // erwtima 2
	ListOfCDR *  findByCaller(long long caller); // erwtima 3
	ListOfCDR *  findByCaller(long long caller, int hour1,int minute1, int hour2,int minute2); // erwtima 3
	ListOfCDR *  findByCaller(long long caller, int hour1,int minute1, int hour2,int minute2,int day1,int month1, int year1,int day2,int month2, int year2); // erwtima 3
	ListOfCDR *  lookupByCallee(long long callee); // erwtima 4
	ListOfCDR *  lookupByCallee(long long callee, int hour1,int minute1, int hour2,int minute2); // erwtima 4
	ListOfCDR *  lookupByCallee(long long callee, int hour1,int minute1, int hour2,int minute2,int day1,int month1, int year1,int day2,int month2, int year2); // erwtima 4
	
	List * indist1(long long caller1,long long caller2); //erwtima 5
	int topdest(long long caller,int * emfaniseis); //erwtima 6
	
	long long top(int k); //erwtima 7
	
	void print(int which_hashtable,std::ostream & out=std::cout); //erwtima 9 kai 10
	void bye(); //erwtima 8
};

#endif // MANAGER_H
