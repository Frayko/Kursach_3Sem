#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>
using namespace std;

class Date {
protected:
	int day;
	int month;
	int year;
public:
	Date(int _day = 1, int _month = 1, int _year = 1970) : day(_day), month(_month), year(_year) {}
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

	virtual void show() {
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

class Date_pay : Date {
protected:
	char* date;
public:
	Date_pay(int _day = 0, int _month = 0, int _year = 0) : Date(_day, _month, _year) { 
		if (day == 0 || month == 0) 
			date = nullptr; 
		else 
			updateDate(); 
	}

	Date_pay(Date_pay& d) : Date(d) {
		date = new char[strlen(d.date) + 1]; 
		strcpy(date, d.date);
	};

	~Date_pay() {
		if (date) { 
			delete[] date; 
			date = nullptr; 
		}
	}

	void updateDate() {
		int i = 0, j = 0;
		char buf[30];
		char t_date[30] = {};

		_itoa_s(day, buf, 10);
		for (j = 0; buf[j] != '\0'; j++, i++)
			t_date[i] = buf[j];
		t_date[i++] = { '.' };

		_itoa_s(month, buf, 10);
		for (j = 0; buf[j] != '\0'; j++, i++)
			t_date[i] = buf[j];
		t_date[i++] = { '.' };

		_itoa_s(year, buf, 10);
		for (j = 0; buf[j] != '\0'; j++, i++)
			t_date[i] = buf[j];

		if (date)
			delete[] date;
		date = new char[strlen(t_date) + 1];
		strcpy(date, t_date);
	}

	void show() {
		cout << date;
	}

	Date_pay& operator=(Date_pay& d) {
		day = d.day;
		month = d.month;
		year = d.year;
		if (date)
			delete[] date;
		date = new char[strlen(d.date) + 1];
		strcpy(date, d.date);
		return *this;
	}
};

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