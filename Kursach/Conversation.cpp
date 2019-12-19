#define _CRT_SECURE_NO_WARNINGS
#include "Conversation.h"
#include <iostream>
#include <fstream>
using namespace std;

Conversation::Conversation() {
	strcpy(city, "R.N.G.");
	strcpy(code_city, "999");
	strcpy(number_phone, "123456");
	tariff = rand() % 4 + 1;
	call_duration = rand() % 40 + 1;
	calcPayment();
	date.set(rand() % 30 + 1, rand() % 12 + 1, 1970 + rand() % 40);
	time.set(rand() % 60, rand() % 60, rand() % 24);
	date_pay.set(0, 0, 0);
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

bool Conversation::operator==(Conversation& B) {
	return (date.calcDayCount() == B.date.calcDayCount());
}

bool Conversation::operator>(Date t) {
	return (date.calcDayCount() > t.calcDayCount());
}

bool Conversation::operator==(Date t) {
	return (date.calcDayCount() == t.calcDayCount());
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

bool Conversation::verificationOfPayment() {
	if (date_pay.getDay() == 0 || date_pay.getMonth() == 0)
		return false;
	return true;
}

Conversation::~Conversation() {
	count_obj--;
}

ostream& operator << (ostream& os, Conversation& c) {
	cout << "---Междугородний звонок---" << endl
		 << "Номер абонента: +7 " << c.code_city << " " << c.number_phone << endl
		 << "Тариф: " << c.tariff << " рублей за минуту" << endl
		 << "Дата и время разговора: " << c.date << " " << c.time << endl
		 << "Длительность: " << c.call_duration << endl
		 << "Расчётная сумма: " << c.pay << endl
		 << "Дата оплаты: " << c.date_pay << endl;
	return os;
}

fstream& operator << (fstream& os, Conversation& c) {
	os.write((char*)&c.city, sizeof(c.city));
	os.write((char*)&c.code_city, sizeof(c.code_city));
	os.write((char*)&c.number_phone, sizeof(c.number_phone));
	os.write((char*)&c.tariff, sizeof(c.tariff));
	os.write((char*)&c.call_duration, sizeof(c.call_duration));
	os.write((char*)&c.pay, sizeof(c.pay));
	os << c.date;
	os << c.date_pay;
	os << c.time;
	return os;
}

fstream& operator >> (fstream& is, Conversation& c) {
	is.read((char*)&c.city, sizeof(c.city));
	is.read((char*)&c.code_city, sizeof(c.code_city));
	is.read((char*)&c.number_phone, sizeof(c.number_phone));
	is.read((char*)&c.tariff, sizeof(c.tariff));
	is.read((char*)&c.call_duration, sizeof(c.call_duration));
	is.read((char*)&c.pay, sizeof(c.pay));
	is >> c.date;
	is >> c.date_pay;
	is >> c.time;
	return is;
}