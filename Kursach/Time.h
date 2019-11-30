#pragma once
#include <iostream>
#include <fstream>
using namespace std;

class Time {
private:
	int sec;
	int min;
	int hour;
public:
	Time(int _sec = 0, int _min = 0, int _hour = 0) : sec(_sec), min(_min), hour(_hour) {}
	Time(Time& t) : sec(t.sec), min(t.min), hour(t.hour) {}

	void set(int _sec, int _min, int _hour) {
		if (_sec < 0 || _sec > 60 || _min < 0 || _min > 60 || _hour < 0 || _hour > 24) { cout << "Ошибка ввода!"; return; }
		sec = _sec;
		min = _min;
		hour = _hour;
	}

	Time& operator=(Time& t) {
		sec = t.sec;
		min = t.min;
		hour = t.hour;
		return *this;
	}

	friend ostream& operator << (ostream& os, Time& t);
	friend fstream& operator << (fstream& os, Time& t);
	friend fstream& operator >> (fstream& is, Time& t);
};

ostream& operator << (ostream& os, Time& t) {
	os << t.hour << ':' << t.min << ':' << t.sec;
}

fstream& operator << (fstream& os, Time& t) {
	os.write((char*)&t.sec, sizeof(int));
	os.write((char*)&t.min, sizeof(int));
	os.write((char*)&t.hour, sizeof(int));
	return os;
}

fstream& operator >> (fstream& is, Time& t) {
	is.read((char*)&t.sec, sizeof(int));
	is.read((char*)&t.min, sizeof(int));
	is.read((char*)&t.hour, sizeof(int));
	return is;
}