#pragma once
#include <iostream>
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

	void show() {
		printf("%02d:%02d:%02d", hour, min, sec);
	}

	void edit(int mode, int value) {
		switch (mode) {
		case 1: { if (value < 0 || value > 60) { cout << "Ошибка ввода!"; return; } sec = value; break; }
		case 2: { if (value < 0 || value > 60) { cout << "Ошибка ввода!"; return; } min = value; break; }
		case 3: { if (value < 0 || value > 24) { cout << "Ошибка ввода!"; return; } hour = value; break; }
		default: { cout << "Error";  break; }
		}
	}

	Time& operator=(Time& t) {
		sec = t.sec;
		min = t.min;
		hour = t.hour;
		return *this;
	}
};