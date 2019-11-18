#pragma once
class Tariff {
private:
	char* name;
	double pay_per_min;
public:
	Tariff(char* _name = nullptr, double _pay_per_min = 0.01) : pay_per_min(_pay_per_min) { 
		name = new char[strlen(_name) + 1]; 
		strcpy_s(name, strlen(_name) + 1, _name);
	}

	Tariff(Tariff& t) : pay_per_min(t.pay_per_min) {
		name = new char[strlen(t.name) + 1];
		strcpy_s(name, strlen(t.name) + 1, t.name);
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
		strcpy_s(name, strlen(_name) + 1,_name);
		pay_per_min = _pay_per_min;
	}

	Tariff& operator=(Tariff& t) {
		pay_per_min = t.pay_per_min;
		if (name)
			delete[] name;
		name = new char[strlen(t.name) + 1];
		strcpy_s(name, strlen(t.name) + 1, t.name);
		return *this;
	}
};