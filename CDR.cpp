#include "CDR.h"
#include <iostream>
using namespace std;

void CDR::print(ostream & out)
{
	out<<"CDR("<<id<<", "<<originator<<", "<<destination<<", "<<datetime.tm_mday<<"/"<<datetime.tm_mon<<"/"<<datetime.tm_year<<", "<<datetime.tm_hour<<":"<<datetime.tm_min<<", "<<duration<<", "<<type<<", "<<tarrif<<", "<<faulcondition<<")"<<endl;
}
