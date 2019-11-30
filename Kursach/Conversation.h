#pragma once
#include "Date.h"
#include "Time.h"
#include <iostream>
#include <fstream>

class Conversation {
private:
	static int count_obj;
	char city[20];
	char code_city[4];
	char number_phone[7];
	double tariff;
	int call_duration;
	double pay;
	Date date_pay;
	Date date;
	Time time;
public:
	Conversation();
	Conversation(char* _city, char* _code_city, char* _number_phone, double _tariff, int _call_duration, Date _date, Time _time, Date _date_pay);
	Conversation(Conversation& C);
	void calcPayment();
	bool verificationOfPayment();
	bool operator>(Conversation& B);
	Conversation operator=(Conversation& B);
	friend ostream& operator<<(ostream& os, Conversation& c);
	friend fstream& operator<<(fstream& os, Conversation& c);
	friend fstream& operator>>(fstream& is, Conversation& c);
	~Conversation();
};