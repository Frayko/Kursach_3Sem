#include "Time.h"
#include <iostream>
#include <fstream>
using namespace std;

ostream& operator << (ostream& os, Time& t) {
	os << t.hour << ':' << t.min << ':' << t.sec;
	return os;
}

istream& operator >> (istream& is, Time& t) {
	cout << "second: "; is >> t.sec;
	cout << "minute: "; is >> t.min;
	cout << "hour: "; is >> t.hour;
	return is;
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