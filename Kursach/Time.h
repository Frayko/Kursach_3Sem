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
	friend istream& operator >> (istream& is, Time& t);
	friend fstream& operator << (fstream& os, Time& t);
	friend fstream& operator >> (fstream& is, Time& t);
};