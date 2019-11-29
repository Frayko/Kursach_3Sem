#pragma once
#include <iostream>
using namespace std;

class Date {
private:
	int day;
	int month;
	int year;
public:
	Date(int _day = 0, int _month = 0, int _year = 0) : day(_day), month(_month), year(_year) {}
	Date(Date& d) : day(d.day), month(d.month), year(d.year) {}
	void set(int _day, int _month, int _year) {
		if (_day <= 0 || _day > 31 || _month <= 0 || _month > 12) { cout << "Ошибка ввода!"; return; }
		day = _day;
		month = _month;
		year = _year;
	}

	int calcDayCount() {
		return (year - 1) * 365 + (month - 1) * 30 + (month - 1) / 2 + day;
	}

	void show() {
		printf("%02d.%02d.%04d", day, month, year);
	}

	void edit(int mode, int value) {
		switch (mode) {
		case 1: { if (value <= 0 || value > 31) { cout << "Ошибка ввода!"; return; } day = value; break; }
		case 2: { if (value <= 0 || value > 12) { cout << "Ошибка ввода!"; return; } month = value; break; }
		case 3: { year = value; break; }
		default: { cout << "Error";  break; }
		}
	}

	Date& operator=(Date& d) {
		day = d.day;
		month = d.month;
		year = d.year;
		return *this;
	}
};