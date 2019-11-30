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
		if (_day <= 0 || _day > 31 || _month <= 0 || _month > 12) { cout << "������ �����!"; return; }
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
	friend fstream& operator << (fstream& os, Date& d);
	friend fstream& operator >> (fstream& is, Date& d);
};

ostream& operator << (ostream& os, Date& d) {
	if (d.day == 0 || d.month == 0)
		os << "�����������";
	else
		os << d.day << '.' << d.month << '.' << d.year;
	return os;
}

fstream& operator << (fstream& os, Date& d) {
	os.write((char*)&d.day, sizeof(int));
	os.write((char*)&d.month, sizeof(int));
	os.write((char*)&d.year, sizeof(int));
	return os;
}

fstream& operator >> (fstream& is, Date& d) {
	is.read((char*)&d.day, sizeof(int));
	is.read((char*)&d.month, sizeof(int));
	is.read((char*)&d.year, sizeof(int));
	return is;
}