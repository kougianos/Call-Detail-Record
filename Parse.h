#ifndef PARSE_H
#define PARSE_H
#include <iostream>
#include <fstream>
#include <sstream>
#include "CDR.h"
#include "Manager.h"
using namespace std;
class Parse
{
	public:
		Parse();
		~Parse();
		void readFile(string filename,Manager * m);
		CDR * parseRecord(string line);
		void parseCommand(string line,Manager *m);
};

#endif // PARSE_H
