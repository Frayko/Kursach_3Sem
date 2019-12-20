#pragma once
#include <iostream>
#include <fstream>
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
		day = _day;
		month = _month;
		year = _year;
	}

	int getDay() {
		return day;
	}

	int getMonth() {
		return month;
	}

	int calcDayCount() {
		return (year - 1) * 365 + (month - 1) * 30 + (month - 1) / 2 + day;
	}

	Date& operator=(Date& d) {
		day = d.day;
		month = d.month;
		year = d.year;
		return *this;
	}

	friend ostream& operator << (ostream& os, Date& d);
	friend istream& operator >> (istream& is, Date& d);
	friend fstream& operator << (fstream& os, Date& d);
	friend fstream& operator >> (fstream& is, Date& d);
};