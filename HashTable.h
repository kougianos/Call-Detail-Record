#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <iostream>
#include "Buckets.h"
#include "CDR.h"
#include "ListOfCDR.h"
class HashTable
{
	const long size;
	const int max_bytes_per_bucket;
	const int typeofkey;
	Buckets **table;
	long hash(long long number);
public:
	HashTable(long length_hashtable,int max_bytes_bucket,int callerOrCallee);
	~HashTable();
	
	ListOfCDR * add(CDR *r);
	CDR * remove(long long key,std::string cdr_id);
	ListOfCDR * find(long long key);
	ListOfCDR * findCopy(long long key,struct tm start,struct tm end);
	ListOfCDR * findCopy(long long key, int hour1,int minute1, int hour2,int minute2);
	void print(std::ostream & out=std::cout);
	void bye();
};

#endif // HASHTABLE_H
