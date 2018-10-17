#ifndef BUCKET_H
#define BUCKET_H
#include "CDR.h"
#include "ListOfCDR.h"
#include <ctime>
#include <iostream>

class Bucket
{
	const int max_size;
	int the_size;
	ListOfCDR ** records;
	public:
		Bucket(int s);
		~Bucket();
		bool add(ListOfCDR * r);
		bool remove(ListOfCDR * r);
		bool remove(long long key);
		bool contains(long long key);
		ListOfCDR * find(long long key);
		ListOfCDR * findCopy(long long key);
		ListOfCDR * findCopy(long long key,struct tm start,struct tm end);
		ListOfCDR * findCopy(long long key,int hour1,int minute1, int hour2,int minute2);
		void print(std::ostream & out=std::cout);
		int size();
		bool isFull();
		void bye();
};

#endif // BUCKET_H