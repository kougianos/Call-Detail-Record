#include "Parse.h"
#include <string>
using namespace std;
Parse::Parse()
{
}

Parse::~Parse()
{
}

void Parse::readFile(string filename,Manager * m)
{
	ifstream  data(filename.c_str());

	//
	string line;
	while(getline(data,line)) {
		cout<<"Parsing line: "<<line<<endl;
		//m->add(parseRecord(line));
		parseCommand(line,m);
	}
}

void Parse::parseCommand(string line,Manager *m)
{
	stringstream lineStream(line);	
	string command;
	lineStream>>command;
	if(command=="insert") {
		string record;
		lineStream>>record;
		CDR * cdr = parseRecord(record);
		cout<<"insert >>>>"<<endl;
		if(cdr==NULL){
			cout<<"InsertError"<<endl;
		}else{
			cout<<"Insert OK"<<endl;
		}
		m->add(cdr);
	} else if(command=="delete") {
		string caller, cdrid;
		if(!(lineStream>>caller)) {
			cout<<"DeleteError (Dwste caller)"<<endl;
			return;
		}
		if(!(lineStream>>cdrid)) {
			cout<<"DeleteError (Dwste ID)"<<endl;
			return;
		} else {
			m->remove(atoll(caller.erase(3,1).c_str()),cdrid); //vgazw tin paula apo to noumero
		}
		cout<<"Deleted "<<cdrid<<endl;
	} else if(command=="find" || command=="lookup") {
		ListOfCDR *list=NULL;
		string caller,t1,t2,t3,t4; //o arithmos kai ta 4 timestamps pou xrisimopoiountai ana 2
		lineStream>>caller;
		caller.erase(3,1);
		if(lineStream>>t1) {
			if(lineStream>>t2) {
				if(lineStream>>t3) {
					if(lineStream>>t4) {
						if(command=="find") { //spame tin imerominia kai tin ora se t1,t2,t3,t4. t1 kai t3 einai oi ores/lepta, t2 kai t4 oi imerominies
							list=m->findByCaller(atoll(caller.c_str()),atoi(t1.substr(0,2).c_str()),atoi(t1.substr(3,2).c_str()),atoi(t3.substr(0,2).c_str()),atoi(t3.substr(3,2).c_str()),
							                     atoi(t2.substr(0,2).c_str()),atoi(t2.substr(2,2).c_str()),atoi(t2.substr(4,4).c_str()),
							                     atoi(t4.substr(0,2).c_str()),atoi(t4.substr(2,2).c_str()),atoi(t4.substr(4,4).c_str()));
						} else {
							list=m->lookupByCallee(atoll(caller.c_str()),atoi(t1.substr(0,2).c_str()),atoi(t1.substr(3,2).c_str()),atoi(t3.substr(0,2).c_str()),atoi(t3.substr(3,2).c_str()),
							                       atoi(t2.substr(0,2).c_str()),atoi(t2.substr(2,2).c_str()),atoi(t2.substr(4,4).c_str()),
							                       atoi(t4.substr(0,2).c_str()),atoi(t4.substr(2,2).c_str()),atoi(t4.substr(4,4).c_str()));
						}

					} else {
						cout<<"Error, doste kai deuteri imerominia"<<endl;
						return;
					}
				} else {
					// exoume mono t1 kai t2, diladi exoun dothei mono ores/lepta
					if(command=="find") {
						list=m->findByCaller(atoll(caller.c_str()),atoi(t1.substr(0,2).c_str()),atoi(t1.substr(3,2).c_str()),atoi(t2.substr(0,2).c_str()),atoi(t2.substr(3,2).c_str()));
					} else {
						list=m->lookupByCallee(atoll(caller.c_str()),atoi(t1.substr(0,2).c_str()),atoi(t1.substr(3,2).c_str()),atoi(t2.substr(0,2).c_str()),atoi(t2.substr(3,2).c_str()));
					}
				}
			} else {
				cout<<"Error, doste kai deuteri ora"<<endl;
				return;
			}
		} else {
			// de dothike xronos
			if(command=="find") {
				list=m->findByCaller(atoll(caller.c_str()));
			} else {
				list=m->lookupByCallee(atoll(caller.c_str()));
			}
		}
		if(list!=NULL) {
			list->print(cout);
			if(t1!=""){
				delete list;
			}
		} else {
			cout<<"De vrethikan apotelesmata gia ton arithmo "<<caller<<endl;
			return;
		}
	} else if(command=="indist1") {
		string caller1,caller2;
		if(!(lineStream>>caller1)) {
			cout<<"Doste caller1"<<endl;
			return;
		}
		if(!(lineStream>>caller2)) {
			cout<<"Doste caller2"<<endl;
			return;
		}else{
			caller1.erase(3,1);
			caller2.erase(3,1);
			List * list=m->indist1(atoll(caller1.c_str()),atoll(caller2.c_str()));
			if(list!=NULL) {
				list->print(cout);
				delete list;
			} else {
				cout<<"Den yparxoun apotelesmata gia tin entoli indist1  "<<caller1<<","<<caller2<<"..."<<endl;
			}
		}
	} else if(command=="topdest") {
		string caller;
		if(!(lineStream>>caller)) {
			cout<<"Doste caller"<<endl;
			return;
		} else {
			caller.erase(3,1); //diagrafw tin -
			int emfaniseis;
			int topdest=   m->topdest(atoll(caller.c_str()),&emfaniseis);
			if(topdest==-1){
				cout<<"Den vrethikan cdrs gia ton caller "<<caller<<endl;;
			}else{
				cout<<"Top dest = "<<topdest<<" me "<<emfaniseis<<" emfaniseis"<<endl;
			}
		}
	} else if(command=="top") {
		double k;
		lineStream>>k;
		m->top(k);
	} else if(command=="bye") {
		m->bye();
		cout<<"bye done successfully"<<endl;
	} else if(command=="end") {
		cout<<"Exiting Program :)"<<endl;
		exit(1);
	}
	  else if(command=="print") {
		string which_hashtable;
		lineStream>>which_hashtable;
		if(which_hashtable=="hashtable1") {
			m->print(1,cout);
		} else if(which_hashtable=="hashtable2") {
			m->print(2,cout);
		} else {
			cout<<"Lathos orisma"<<endl;
		}
	} else if(command=="dump") {
		string filename;
		lineStream>>filename;
		ofstream output(filename.c_str());
		m->print(1,output);
	} else {
		 cout<<"Lathos entoli"<<endl;
	}
}

CDR * Parse::parseRecord(string line)
{
	stringstream lineStream(line);
	string cell;
	string a[9]; //9 pedia tou record
	int i=0;
	while(getline(lineStream,cell,';')) { //diaxorizontai ta pedia me ;
		a[i]=cell;
		i++;
	}
	a[1].erase(3,1); // diwxnw tin - apo to tilefwno caller
	a[2].erase(3,1); // diwxnw tin - apo to tilefwno callee
	CDR * result=new CDR(a[0],atoll(a[1].c_str()),atoll(a[2].c_str()),atoi(a[5].c_str()),atoi(a[6].c_str()),atoi(a[7].c_str()),atoi(a[8].c_str()));
	long long date=atoll(a[3].c_str());

	stringstream time(a[4]);

	getline(time,cell,':');
	int hours=atoi(cell.c_str());
	getline(time,cell,':');
	int minutes=atoi(cell.c_str());
	result->SetDate(date/1000000,(date%1000000)/10000,(date%10000));
	result->SetInittime(0,minutes,hours);
	return result;
}
