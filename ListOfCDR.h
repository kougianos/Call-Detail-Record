#ifndef LISTOFCDR_H
#define LISTOFCDR_H
#include "CDR.h"
#include <ctime>
#include <iostream>
class NodeCDR
{
	public:
		CDR * data;
		NodeCDR * previous;
		NodeCDR * next;

		NodeCDR(CDR * d,NodeCDR *p,NodeCDR *n) {
			this->data=d;
			this->previous=p;
			this->next=n;
		}
};

class ListOfCDR
{
		long long number_key; //o tilefonikos arithmos tou pelati tha einai kai to monadiko key gia kathe lista
		double amount; //to sunoliko kostos tou ekastote pelati
		int the_size;
		NodeCDR * start;
		NodeCDR * end;
		double * max_heap_node;
	public:
		ListOfCDR(long long key);
		ListOfCDR(ListOfCDR * other);
		~ListOfCDR();

		NodeCDR * getStart();
		int size();
		bool add(CDR * d);
		CDR * remove(CDR * d);
		CDR * remove(std::string cdr_id);
		bool contains(CDR * d);
		bool contains(std::string cdr_id);
		CDR * find(CDR * d);
		CDR * find(std::string cdr_id);
		ListOfCDR * findCopy(struct tm start_datetime, struct tm end_datetime);
		ListOfCDR * findCopy(int hour1,int minute1,int hour2,int minute2);
		void print(std::ostream & out=std::cout);
		long long getKey();
		void bye();
		bool containsCDRwithCallee(long long callee);
		int findMostUsedPrefix(); //gia ton tripsifio kodiko xoras
		double getAmount();
};
#endif // LISTOFCDR_H
