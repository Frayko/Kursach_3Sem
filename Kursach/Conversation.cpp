#define _CRT_SECURE_NO_WARNINGS
#include "Conversation.h"
#include <iostream>
using namespace std;

Conversation::Conversation() {
	count_obj++;
}

Conversation::Conversation(char* _city, char* _code_city, char* _number_phone, double _tariff, int _call_duration, Date _date, Time _time, Date _date_pay) {
	strcpy(city, _city);
	strcpy(code_city, _code_city);
	strcpy(number_phone, _number_phone);
	call_duration = _call_duration;
	tariff = _tariff;
	calcPayment();
	date = _date;
	time = _time;
	date_pay = _date_pay;
	count_obj++;
}

Conversation::Conversation(Conversation& C) {
	strcpy(city, C.city);
	strcpy(code_city, C.code_city);
	strcpy(number_phone, C.number_phone);
	call_duration = C.call_duration;
	tariff = C.tariff;
	calcPayment();
	date = C.date;
	time = C.time;
	date_pay = C.date_pay;
	count_obj++;
}

bool Conversation::operator>(Conversation& B) {
	return (date.calcDayCount() > B.date.calcDayCount());
}

Conversation Conversation::operator=(Conversation& B) {
	strcpy(city, B.city);
	strcpy(code_city, B.code_city);
	strcpy(number_phone, B.number_phone);
	call_duration = B.call_duration;
	tariff = B.tariff;
	date = B.date;
	time = B.time;
	date_pay = B.date_pay;
	return *this;
}

void Conversation::calcPayment() {
	pay = tariff * (double)call_duration;
}

Conversation::~Conversation() {
	count_obj--;
}