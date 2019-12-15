#pragma once
#include <iostream>
using namespace std;

class Error {
public:
	Error() {}

	virtual void ErrMsg() const {
		cerr << "Unforeseen exception!\n";
	}

	void Continue() const {
		cerr << "Continue...\n";
	}
};

class ErrorOpenFile : public Error {
public:
	ErrorOpenFile() {}

	void ErrMsg() const {
		cerr << "File cannot be read!\n";
		Continue();
	}
};

