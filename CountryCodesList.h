#ifndef COUNTRYCODESLIST_H
#define COUNTRYCODESLIST_H
#include <iostream>
class CountryCodeNode
{
	public:
		int code; //tripsifios kodikos
		int counter; //arithmos emfanisewn tou tripsifiou
		CountryCodeNode * next;
		CountryCodeNode(int code,CountryCodeNode *next) {
			this->code=code;
			this->next=next;
			this->counter=1; //otan dimiourgeitai neos countryCodeNode arxikopoieitai o arithmos emfanisis tou sto 1
		}
};

class CountryCodesList
{

		CountryCodeNode *start;

	public:
		void add(int code);
		int findPopular(int * emfaniseis);
		CountryCodesList();
		~CountryCodesList();

};

#endif // COUNTRYCODESLIST_H
