#pragma once
#include <iostream>
#include <fstream>
#include "Error.h"
using namespace std;

template<class Data>
class Binary : public fstream {
private:
	//ios_base::seekdir add_pos;
	template <class Data>
	struct Elem {
		ios_base::seekdir left, right;
		Data obj;
		Elem() : obj(NULL), left(-1), right(-1) {}
		Elem(Data _obj = NULL) : obj(_obj), left(-1), right(-1) {}
	};
	char* filename;
	void set_root(ios_base::seekdir pos);
	ios_base::seekdir get_root();
	void set_Elem(ios_base::seekdir pos, Elem<Data>* elem);
	void get_Elem(ios_base::seekdir pos, Elem<Data>*& elem);
	void insert(ios_base::seekdir pos, ios_base::seekdir add_pos, Elem<Data>* t);
	bool isEmpty();
public:
	Binary();
	Binary(char* _filename);
	~Binary();
	void push(Data _obj);
	void print(ios_base::seekdir pos, int size);
	void clean() { close(); open(filename, ios::in | ios::out | ios::binary | ios::trunc); }
};

template <class Data>
Binary<Data>::Binary() {
	filename = new char[strlen("data.dat") + 1];
	strcpy(filename, "data.dat");
	open(filename, ios::binary | ios::in | ios::out);
	if (!is_open()) {
		throw ErrorOpenFile();
	}
}

template <class Data>
Binary<Data>::Binary(char* _filename) {
	filename = new char[strlen(_filename) + 1];
	strcpy(filename, _filename);
	open(filename, ios::binary | ios::in | ios::out | ios::app);
	if (!is_open()) {
		throw ErrorOpenFile();
	}
}

template <class Data>
Binary<Data>::~Binary() {
	close();
}

template <class Data>
void Binary<Data>::set_root(ios_base::seekdir pos) {
	seekp(0, ios_base::beg);
	write((char*)&pos, sizeof(pos));
}

template <class Data>
ios_base::seekdir Binary<Data>::get_root() {
	seekg(0, ios_base::beg);
	ios_base::seekdir pos;
	read((char*)&pos, sizeof(pos));
	return pos;
}

template <class Data>
void Binary<Data>::set_Elem(ios_base::seekdir pos, Elem<Data>* elem) {
	seekp(pos, ios_base::beg);
	write((char*)&elem, sizeof(elem));
}

template <class Data>
void Binary<Data>::get_Elem(ios_base::seekdir pos, Elem<Data>*& elem) {
	seekg(pos, ios_base::beg);
	read((char*)&elem, sizeof(elem));
}

template <class Data>
bool Binary<Data>::isEmpty() {
	seekg(0, ios_base::end);
	return (tellg() < 1 || get_root() == 0);
}

template <class Data>
void Binary<Data>::insert(ios_base::seekdir pos, ios_base::seekdir add_pos ,Elem<Data>* t) {
	Elem<Data>* cur;
	get_Elem(pos, cur);
	if (cur->obj > t->obj) {
		if (cur->left == -1) {
			cur->left = add_pos;
			seekp(pos, ios_base::beg);
			write((char*)&cur, sizeof(cur));
		}
		else {
			insert(pos + sizeof(cur), add_pos, t);
		}
	}
	else {
		if (cur->right == -1) {
			cur->right = add_pos;
			seekp(pos, ios_base::beg);
			write((char*)&cur, sizeof(cur));
		}
		else {
			insert(pos + sizeof(cur), add_pos, t);
		}
	}
}

template <class Data>
void Binary<Data>::push(Data _obj) {
	Elem<Data>* temp = new Elem<Data>(_obj);
	seekp(0, ios_base::end);
	ios_base::seekdir add_pos = tellp();
	if (isEmpty()) {
		add_pos += sizeof(ios_base::seekdir);
		set_root(add_pos);
	}
	else {
		seekg(get_root(), ios_base::beg);
		ios_base::seekdir pos = tellg();
		insert(pos, add_pos, temp);
	}
	set_Elem(add_pos, temp);
}

template <class Data>
void Binary<Data>::print(ios_base::seekdir pos, int size) {
	Elem<Data>* temp;
	get_Elem(pos, temp);
	if (isEmpty())
		throw ErrorIsEmpty();
	if (temp->right != -1)
		print(temp->right, size + 1);
	for (int i = 0; i < size; i++)
		cout << "		";
	cout << temp->obj << endl;
	if (temp->left != -1)
		print(temp->left, size + 1);
}