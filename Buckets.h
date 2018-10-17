#ifndef BUCKETS_H
#define BUCKETS_H
#include "Bucket.h"
#include "CDR.h"
#include <cstdlib>
#include <iostream>
#include <ctime>


class NodeBucket{
	const int typeofkey; //0 an einai caller 1 an einai callee
	public:
	Bucket * data;
	NodeBucket * previous;
	NodeBucket * next;
	
	NodeBucket(int max_bytes_per_bucket,NodeBucket *p,NodeBucket *n,int callerOrCallee): typeofkey(callerOrCallee){
		//std::cout<<"The size per Bucket is"<<sizeof(BucketCDR)<<std::endl;
		//std::cout<<max_bytes_per_bucket<<std::endl;
		int max_records_per_bucket=(max_bytes_per_bucket-sizeof(Bucket))/sizeof(CDR*);
		
		if(max_records_per_bucket==0){
			std::cout<<"Den xoraei kanena record sto bucket"<<std::endl;
			exit(-1);
		}
		this->data=new Bucket(max_records_per_bucket);
		this->previous=p;
		this->next=n;
	}
	~NodeBucket(){
		delete this->data;
	}
};

class Buckets
{
	const int typeofkey;
	const int max_bytes_per_bucket;
	int the_size;
	NodeBucket * start;
	NodeBucket * end;
public:
	Buckets(int max_bytes_bucket,int callerOrCallee);
	~Buckets();
	
	int size();
	ListOfCDR * add(CDR * r);
	CDR * remove(long long key,std::string cdr_id);
	bool contains(long long key);
	ListOfCDR * find(long long key);
	ListOfCDR * findCopy(long long key);
	ListOfCDR * findCopy(long long key, struct tm start_datetime, struct tm end_datetime);
	ListOfCDR * findCopy(long long key,int hour1,int minute1, int hour2,int minute2);
	void print(std::ostream & out=std::cout);
	void bye();
};

#endif // BUCKETS_H
