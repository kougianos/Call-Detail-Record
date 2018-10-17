#include <iostream>
#include "List.h"
#include "MaxHeap.h"
#include "Manager.h"
#include "Parse.h"
#include <ctime>
#include <cstring>

using namespace std;

int main(int argc, char **argv)
{
	cout<<"WELCOME TO WERHAUZ :)"<<endl;
	string Operations="";
	long h1=-1,h2=-1,bucket_size=-1;
	for (int i = 1; i < argc; i++) {
		if(strcmp(argv[i],"-o")==0) {
			if(i<argc-1) {
				Operations=string(argv[i+1]);
			} else {
				cout<<"dwste to arxeio operations"<<endl;
				return -1;
			}
		} else if(strcmp(argv[i],"-h1")==0) {
			if(i<argc-1) {
				h1=atoll(argv[i+1]);
				cout<<h1<<endl;
			} else {
				cout<<"dwste to size tou hashtable1"<<endl;
				return -2;
			}
		} else if(strcmp(argv[i],"-h2")==0) {
			if(i<argc-1) {
				h2=atoll(argv[i+1]);
			} else {
				cout<<"dwste to size tou hashtable2"<<endl;
				return -2;
			}
		} else if(strcmp(argv[i],"-s")==0) {
			if(i<argc-1) {
				bucket_size=atoll(argv[i+1]);
			} else {
				cout<<"dwste to size se bytes tou bucket"<<endl;
				return -2;
			}
		}
	}
	if(h1 < 1 || h2 < 1 || bucket_size < 1) {
		cout<<"dwste ta h1 h2 kai bucketsize"<<endl;
		return -3;
	}

	Manager * m =new Manager(h1,h2,bucket_size);
	Parse * p=new Parse();
	if(Operations!="") {
		p->readFile(Operations,m);
	}
	string line;
	while(getline(cin, line)) {
		p->parseCommand(line,m);
	}
	delete p;
	delete m;
	return 0;
}
