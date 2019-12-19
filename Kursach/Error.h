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

class ErrorReadElement : public Error {
public:
	ErrorReadElement() {}

	void ErrMsg() const {
		cerr << "Element obj cannot be read!\n";
		Continue();
		system("pause");
	}
};

class ErrorNoImplementation : public Error {
public:
	ErrorNoImplementation() {}

	void ErrMsg() const {
		cerr << "No Implementation!\n";
		Continue();
		system("pause");
	}
};

class ErrorIsEmpty : public Error {
public:
	ErrorIsEmpty() {}

	void ErrMsg() const {
		cerr << "File is empty!\n";
		Continue();
		system("pause");
	}
};