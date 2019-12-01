#include "Date.h"
#include <iostream>
#include <fstream>
using namespace std;

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