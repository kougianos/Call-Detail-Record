#include "CountryCodesList.h"
#include <iostream>
CountryCodesList::CountryCodesList()
{
	start=NULL;
}

CountryCodesList::~CountryCodesList()
{
	CountryCodeNode * temp1=start;
	while(temp1!=NULL) {
		CountryCodeNode * temp2=temp1->next;
		delete temp1;
		temp1=temp2;
	}
}

void CountryCodesList::add(int code)
{
	if(start==NULL) { //gia tin proti eisagogi pou den uparxei kanenas komvos
		start=new CountryCodeNode(code,NULL);
	} else {
		CountryCodeNode * temp=start; //ton vazw stin arxi tis listas
		while(temp!=NULL) { //pernaw enan enan tous komvous, an vrw ton tripsifio counter++ kai return
			if(temp->code==code) {
				temp->counter++;
				return;
			}
			temp=temp->next;
		}

		CountryCodeNode * temp_start=new CountryCodeNode(code,start);//an de uparxei o tripsifios ftiaxnw neo komvo
		start=temp_start;
	}
}

int CountryCodesList::findPopular(int * emfaniseis)//vriskw ton pio suxna emfanizomeno tripsifio kai epistrefw auton kai ton arithmo emfanisewn tou
{
	if(start==NULL) {
		return -1;
	}
	int max_counter=start->counter;
	int max_code=start->code;

	CountryCodeNode * temp=start;
	while(temp!=NULL) {
		if(temp->counter > max_counter) {
			max_counter=temp->counter;
			max_code=temp->code;
		}
		temp=temp->next;
	}
	*emfaniseis=max_counter;
	return max_code;
}
