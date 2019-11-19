#define _CRT_SECURE_NO_WARNINGS
#pragma once
class Tariff {
private:
	char* name;
	double pay_per_min;
public:
	Tariff() {
		name = nullptr;
		pay_per_min = 0.0;
	}

	Tariff(char* _name, double _pay_per_min) : pay_per_min(_pay_per_min) { 
		name = new char[strlen(_name) + 1]; 
		strcpy(name, _name);
	}

	Tariff(Tariff& t) {
		pay_per_min = t.pay_per_min;
		name = new char[strlen(t.name) + 1];
		strcpy(name, t.name);
	}

	~Tariff() {
		if (name) { 
			delete[] name; 
			name = nullptr; 
		}
	}

	void set(char* _name, double _pay_per_min) {
		if (name) 
			delete[] name;
		name = new char[strlen(_name) + 1];
		strcpy(name, _name);
		pay_per_min = _pay_per_min;
	}

	Tariff& operator=(Tariff& t) {
		if (name)
			delete[] name;
		name = new char[strlen(t.name) + 1];
		strcpy(name, t.name);
		pay_per_min = t.pay_per_min;
		return *this;
	}
};