#ifndef CDR_H
#define CDR_H
#include <ctime>
#include <iostream>
class CDR
{
		double timologio[4][4]; // thewrw oti to timologio exei na kanei me to kathe cdr, opote mporei na alla3ei gia kathe cdr

		std::string id;
		long long originator;
		long long destination;
		struct tm datetime;
//		struct tm date;
//		struct tm inittime;
		int duration;
		int type;
		int tarrif;
		int faulcondition;
	public:
		void print(std::ostream & out);
		CDR& SetDate(int day,int month,int year) {
			time_t rawtime;
			time ( &rawtime );
			this->datetime = *(gmtime ( &rawtime ));
			this->datetime.tm_isdst = -1;
//			this->datetime.tm_zone = "GMT";
			this->datetime.tm_mday = day;
			this->datetime.tm_mon = month-1;
			this->datetime.tm_year = year-1900;
			return *this;
		}
		CDR& SetDestination(long long destination) {
			this->destination = destination;
			return *this;
		}
		CDR& SetDuration(int duration) {
			this->duration = duration;
			return *this;
		}
		CDR& SetFaulcondition(int faulcondition) {
			this->faulcondition = faulcondition;
			return *this;
		}
		CDR& SetId(std::string id) {
			this->id = id;
			return *this;
		}
		CDR& SetInittime(int seconds,int minutes,int hours) {
			this->datetime.tm_sec = seconds;
			this->datetime.tm_min = minutes;
			this->datetime.tm_hour = hours;

			return *this;
		}
		CDR& SetOriginator(long long originator) {
			this->originator = originator;
			return *this;
		}
		CDR& SetTarrif(int tarrif) {
			this->tarrif = tarrif;
			return *this;
		}
		CDR& SetType(int type) {
			this->type = type;
			return *this;
		}
		struct tm GetDate() const {
			return datetime;
		}
		long GetDestination() const {
			return destination;
		}
		int GetDuration() const {
			return duration;
		}
		int GetFaulcondition() const {
			return faulcondition;
		}
		std::string GetId() const {
			return id;
		}
		struct tm GetInittime() const {
			return datetime;
		}
		long GetOriginator() const {
			return originator;
		}
		int GetTarrif() const {
			return tarrif;
		}
		int GetType() const {
			return type;
		}
		CDR(std::string id,long long origin,long long dest) {
			for(int i=0; i<4; i++) {
				for(int j=0; j<4; j++) {
					timologio[i][j]=(i+1)*(i+1);
				}
			}
			this->id=id;
			this->originator=origin;
			this->destination=dest;
		}
		CDR(std::string id,long long origin,long long dest,int duration,int type,int tarrif,int faulcondition) {
			for(int i=0; i<4; i++) {
				for(int j=0; j<4; j++) {
					timologio[i][j]=(i+1)*(i+1);
				}
			}
			this->id=id;
			this->originator=origin;
			this->destination=dest;
			this->duration=duration;
			this->type=type;
			this->tarrif=tarrif;
			this->faulcondition=faulcondition;
		}
		~CDR() {}

		long long getKey(int callerOrCallee) {
			return callerOrCallee==0?originator:destination;
		}

		int getCountryCodeOriginator() {
			return originator/10000000000;
		}

		int getCountryCodeDestination() {
			return destination/10000000000;
		}

		bool isInInterval(struct tm start,struct tm end) {
//			start.tm_mday=datetime.tm_mday;
//			start.tm_mon=datetime.tm_mon;
//			start.tm_sec=datetime.tm_sec;
//
//			time_t end_dt=mktime(&datetime)+duration*60;
//			struct tm * end_datetime=localtime(&end_dt);
//			end.tm_mday=end_datetime->tm_mday;
//			end.tm_mon=end_datetime->tm_mon;
//			end.tm_sec=end_datetime->tm_sec;

			time_t diff_start=difftime( mktime(&datetime)  ,mktime(&start)    );
			time_t diff_end=difftime(mktime(&end),mktime(&datetime)+(duration*60));
			return diff_start>=0 && diff_end>=0;
		}

		bool isInInterval(int hour1,int minute1,int hour2,int minute2) { //true an i klisi-CDR egine mesa sto dothen diastima

//			std::cout<<"The date time hour: "<<datetime.tm_hour<<std::endl;
//			std::cout<<"The date time minute: "<<datetime.tm_min<<std::endl;
//			std::cout<<std::endl;
//			std::cout<<"The given time hour: "<<hour1<<std::endl;
//			std::cout<<"The given time minute: "<<minute1<<std::endl;
			if(datetime.tm_hour < hour1) {
				return false;
			} else {
				if(datetime.tm_hour == hour1) {
					if(datetime.tm_min < minute1) {
						return false;
					} else {
						// return true;
					}
				} else {
					// return true;
				}
			}

//			std::cout<<datetime.tm_hour<<std::endl;
//			std::cout<<datetime.tm_min<<std::endl;
//			std::cout<<datetime.tm_sec<<std::endl;
//			std::cout<<datetime.tm_mday<<std::endl;
//			std::cout<<datetime.tm_mon<<std::endl;
//			std::cout<<datetime.tm_year<<std::endl<<std::endl;
//			//std::cout<<"The time is "<< mktime(&datetime) <<std::endl;
			time_t end_datetime_timet=mktime(&datetime)+(duration*60);
//			std::cout<<"AFTER"<<std::endl;
//			std::cout<<datetime.tm_hour<<std::endl;
//			std::cout<<datetime.tm_min<<std::endl;
//			std::cout<<datetime.tm_sec<<std::endl;
//			std::cout<<datetime.tm_mday<<std::endl;
//			std::cout<<datetime.tm_mon<<std::endl;
//			std::cout<<datetime.tm_year<<std::endl<<std::endl;

			struct tm * end_datetime=gmtime(&end_datetime_timet); // vrikame to struct tm gia to end
//			std::cout<<"The end date time hour: "<<end_datetime->tm_hour<<std::endl;
//			std::cout<<"The end date time minute: "<<end_datetime->tm_min<<std::endl;
//			std::cout<<std::endl;
//			std::cout<<"The given end time hour: "<<hour2<<std::endl;
//			std::cout<<"The given end time minute: "<<minute2<<std::endl;
			//exoume kalupsei oti i klisi-CDR ksekinise meta tin dothisa ora
			if(end_datetime->tm_hour > hour2) {
				//std::cout<<"Vgike 1"<<std::endl;
				return false;
			} else {
				if(end_datetime->tm_hour == hour2) {
					if(end_datetime->tm_min > minute2) {
						//std::cout<<"Vgike 2"<<std::endl;
						return false;
					} else {
						return true;
					}
				} else {
					return true;
				}
			}
		} //exoume kalupsei oti i klisi-CDR teliose prin tin dothisa ora
		double computeCost() {
			//std::cout<<"duration: "<<duration<<" type: "<<type<<" tarrif: "<<tarrif<<std::endl;
			return timologio[type][tarrif]*duration; //to sunoliko kostos tis ekastote klisis-CDR
		}
};

#endif // CDR_H
