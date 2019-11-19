#pragma once
#include "DateTime.h"
#include "Tariff.h"

class Conversation {
private:
	char* city;
	char code_city[4];
	char number_phone[7];
	Tariff tariff;
	Date_pay date_pay;
	Date date;
	Time time;
	int call_duration;
	double pay;
public:
	Conversation();
	Conversation(char* _city, char* _code_city, char* _number_phone, Tariff _tariff, int _call_duration, Date _date, Time _time, Date_pay _date_pay);
	Conversation(Conversation& C);
	void calcPayment();
	int GetCalcDayCount();
	bool operator>(Conversation& B);
	Conversation operator=(Conversation& B);
	~Conversation();
};