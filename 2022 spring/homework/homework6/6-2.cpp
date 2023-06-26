#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Alarm;

class AlarmClock {
public:
	// Your constructors and destructor.
	AlarmClock() : n(0),h(0),m(0){while(!m_alarms.empty())m_alarms.pop_back();}
	void AddAlarm(Alarm* alarm);
	void Input();
	void TimeElapse();
	~AlarmClock()
	{
		while(!m_alarms.empty())
		{
			Alarm* alarm=m_alarms.back();
			m_alarms.pop_back();
			delete alarm;
		}
	}
	// ...
	
private:
	std::vector<Alarm*> m_alarms;
	// ...
	int n,m,h;
};

class Alarm {
public:
	// Your constructors and destructor.
	Alarm(int hour,int minute,string s) : h(hour),m(minute),name(s),work(1) {} 
	virtual void Trigger() = 0;
	int get_hour(){return h;}
	int get_minute(){return m;}
	// ...

protected:
	// Declare protected members so that child classes have access to them.
	// ...
	string name;
	int h,m;
	int work;
};

class RepeatableAlarm : public Alarm{
	friend RepeatableAlarm *make_R(int,int,string);
	RepeatableAlarm(int hour,int minute,string s) : Alarm(hour,minute,s){}
	virtual void Trigger();
};
inline RepeatableAlarm *make_R(int hour,int minute,string s){
	return new RepeatableAlarm(hour,minute,s);
}

void RepeatableAlarm::Trigger()
{
//Alarm CS100 has triggered at 10:00.
	cout<<"Alarm "<<name<<" has triggered at ";
	if(h<10)cout<<"0";
	cout<<h<<":";
	if(m<10)cout<<"0";
	cout<<m<<".\n";
}

class SnoozeableAlarm : public Alarm{
	friend SnoozeableAlarm *make_S(int,int,string);
	SnoozeableAlarm(int hour,int minute,string s) : Alarm(hour,minute,s){}//基类和派生类都有构造函数 
	
	virtual void Trigger();
};
inline SnoozeableAlarm *make_S(int hour,int minute,string s){
	return new SnoozeableAlarm(hour,minute,s);
}
void SnoozeableAlarm::Trigger()
{
//Alarm MyWeekend has triggered at 08:00. Snooze? (Y/N)
	if(work==0)return;
	cout<<"Alarm "<<name<<" has triggered at ";
	if(h<10)cout<<"0";
	cout<<h<<":";
	if(m<10)cout<<"0";
	cout<<m<<". Snooze? (Y/N)\n";
	char reply=getchar();
	getchar();
	if(reply=='Y')
	{
		m+=10;
		if(m>=60)
			m-=60,h++;
		if(h>=24)
			h-=24;	
	}
	else
		work=0;
}

/**************** Implementations ******************/
void AlarmClock::AddAlarm(Alarm* alarm) {
	n++;
	m_alarms.push_back(alarm);
}

void AlarmClock::Input() {
//	h=0,m=0;
	int num;
	scanf("%d",&num);
	getchar();
	char type;
	int h,m;
	string name;
	for(int i=1;i<=num;++i)
	{
		scanf("%c %d:%d ",&type,&h,&m);
		cin>>name;
		getchar();
//		cout<<"2333333:"<<type<<' '<<h<<' '<<m<<' '<<name<<'\n';
		Alarm* alarm;
		if(type=='R')
			alarm=make_R(h,m,name);
		else
			alarm=make_S(h,m,name);
		AddAlarm(alarm);
	}
}

void AlarmClock::TimeElapse() {
//	cout<<h<<":"<<m<<'\n';
	for(int i=0;i<n;++i)
	{
		Alarm *alarm=m_alarms[i];
//		cout<<"---------------"<<'\n';
//		cout<<alarm->get_hour()<<' '<<alarm->get_minute()<<'\n';
//		cout<<"---------------"<<'\n';
		int alarm_h=alarm->get_hour(),alarm_m=alarm->get_minute();
		if(h==alarm_h&&m==alarm_m)
			alarm->Trigger();
	}
//	cout<<'\n';
	m++;
	if(m>=60)
	{
		m-=60;
		h++;
	}
	if(h>=24)
		h-=24;
}

// ...

int main() {
	AlarmClock clock;
	for (int days = 0; days < 3; days++) {
		std::cout << "Do you want to add any alarms?" << std::endl;
		clock.Input();
		for (int minute = 0; minute < 24 * 60; minute++) {
			clock.TimeElapse();
		}
		std::cout << "A day has elapsed." << std::endl;
	}
	return 0;
}
