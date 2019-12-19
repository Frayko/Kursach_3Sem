#pragma once
#include <iostream>
#include <fstream>
#include "Error.h"
using namespace std;

template<class Data>
class Binary : public fstream {
private:
	template <class Data>
	struct Elem {
		int left, right;
		Data obj;
		Elem(Data _obj = NULL) : obj(_obj), left(-1), right(-1) {}
	};
	char* filename;
	void set_root(int pos);
	int get_root();
	void set_Elem(int pos, Elem<Data> elem);
	void get_Elem(int pos, Elem<Data>& elem);
	void insert(int pos, int add_pos, Elem<Data> t);
	bool isEmpty();
	void writeElem(ofstream& file, int &pos, int old_pos, Elem<Data> cur);
public:
	Binary();
	Binary(char* _filename);
	~Binary();
	void push(Data _obj);
	void print(int pos, int size);
	void rename();
	void pop(Data s);
	int search(Data s);		//Возвращать объект
	void update();
};

template <class Data>
Binary<Data>::Binary() {
	filename = new char[strlen("data.bin") + 1];
	strcpy(filename, "data.bin");
	open(filename, ios::binary | ios::in | ios::out);
	if (!is_open()) {
		cerr << "File cannot be read! Create new file...\n";
		ofstream(filename); close();
		open(filename, ios::binary | ios::in | ios::out);
	}
}

template <class Data>
Binary<Data>::Binary(char* _filename) {
	filename = new char[strlen(_filename) + 1];
	strcpy(filename, _filename);
	open(filename, ios::binary | ios::in | ios::out);
	if (!is_open()) {
		cerr << "File cannot be read! Create new file...\n";
		ofstream file(filename); file.close();
		open(filename, ios::binary | ios::in | ios::out);
	}
}

template <class Data>
Binary<Data>::~Binary() {
	close();
}

template <class Data>
void Binary<Data>::set_root(int pos) {
	seekp(0, ios_base::beg);
	write((char*)&pos, sizeof(pos));
}

template <class Data>
int Binary<Data>::get_root() {
	seekg(0, ios_base::beg);
	int pos;
	read((char*)&pos, sizeof(pos));
	return pos;
}

template <class Data>
void Binary<Data>::set_Elem(int pos, Elem<Data> elem) {
	seekp(pos, ios_base::beg);
	write((char*)&elem, sizeof(elem));
}

template <class Data>
void Binary<Data>::get_Elem(int pos, Elem<Data>& elem) {
	seekg(pos, ios_base::beg);
	read((char*)&elem, sizeof(elem));
}

template <class Data>
bool Binary<Data>::isEmpty() {
	seekg(0, ios_base::end);
	return (tellg() < 1 || get_root() == 0);
}

template <class Data>
void Binary<Data>::insert(int pos, int add_pos , Elem<Data> t) {
	Elem<Data> cur;
	get_Elem(pos, cur);
	if (cur.obj > t.obj) {
		if (cur.left == -1) {
			seekp(pos, ios_base::beg);
			write((char*)&add_pos, sizeof(add_pos));
		}
		else {
			insert(cur.left, add_pos, t);
		}
	}
	else {
		if (cur.right == -1) {
			seekp(pos + 4, ios_base::beg);
			write((char*)&add_pos, sizeof(add_pos));
		}
		else {
			insert(cur.right, add_pos, t);
		}
	}
}

template <class Data>
void Binary<Data>::push(Data _obj) {
	Elem<Data> temp(_obj);
	seekp(0, ios_base::end);
	int add_pos = tellp();
	if (isEmpty()) {
		add_pos += 4;
		set_root(add_pos);
	}
	else {
		insert(get_root(), add_pos, temp);
	}
	set_Elem(add_pos, temp);
}

template <class Data>
void Binary<Data>::print(int pos, int size) {
	if (isEmpty())
		throw ErrorIsEmpty();
	Elem<Data> temp;
	get_Elem(pos, temp);
	if (temp.right != -1)
		print(temp.right, size + 1);
	for (int i = 0; i < size; i++)
		cout << "		";
	cout << temp.obj << endl;
	if (temp.left != -1)
		print(temp.left, size + 1);
}

template <class Data>
void Binary<Data>::rename() {
	throw ErrorNoImplementation();
}

template <>
void Binary<int>::rename() {
	system("DEL double.bin");
	system("REN update.bin int.bin");
	open(filename, ios::binary | ios::in | ios::out);
}

template <>
void Binary<double>::rename() {
	system("DEL double.bin");
	system("REN update.bin double.bin");
	open(filename, ios::binary | ios::in | ios::out);
}

template <>
void Binary<Conversation>::rename() {
	system("DEL double.bin");
	system("REN update.bin Conversation.bin");
	open(filename, ios::binary | ios::in | ios::out);
}

template <class Data>
int Binary<Data>::search(Data target) {
	Elem<Data> cur;
	int pos = get_root();
	get_Elem(pos, cur);
	for (; cur.left != -1 || cur.right != -1; get_Elem(pos, cur)) {
		if (cur.obj == target) {
			return pos;
		}
		else {
			if (cur.obj > target) {
				if (cur.left == -1)
					return -1;
				else
					pos = cur.left;
			}
			else {
				if (cur.right == -1)
					return -1;
				else
					pos = cur.right;
			}
		}
	}
	if (cur.obj == target)
		return pos;
	else
		return -1;
}

template <class Data>
void Binary<Data>::pop(Data target) {
	Elem<Data> cur;
	int cur_pos, next_pos, l_pos, r_pos, parent_pos, prev_pos;
	cur_pos = get_root();
	get_Elem(cur_pos, cur);
	for (; cur.left != -1 || cur.right != -1; get_Elem(next_pos, cur)) {
		if (cur.obj == target) {
			if (cur.left == -1) {
				set_root(cur.right);
			}
			else {
				l_pos = cur.left, r_pos = cur.right;
				get_Elem(cur.left, cur);
				for (; cur.right != -1; get_Elem(cur.right, cur)) {
					prev_pos = tellg();
				}
				cur_pos = tellg();
				write((char*)&l_pos, sizeof(int));
				seekp(4, ios::cur);
				write((char*)&r_pos, sizeof(int));
				set_root(cur_pos);
				seekp(prev_pos + 4, ios_base::beg);
				write((char*)(-1), sizeof(int));
			}
		}
		else {
			if (cur.obj > target) {
				if (cur.left == -1) {
					cout << "No results...\n";
					return;
				}
				else {
					next_pos = cur.left;
				}
			}
			else {
				if (cur.right == -1) {
					cout << "No results...\n";
					return;
				}
				else {
					next_pos = cur.right;
				}
			}
		}
	}
}

template <class Data>
void Binary<Data>::update() {
	Elem<Data> cur;
	ofstream file("update.bin", ios::binary | ios::out);
	int pos = get_root();
	file.seekp(0, ios::beg);
	file.write((char*)&pos, sizeof(int));
	writeElem(file, pos, pos, cur);
	close();
	file.close();
	rename();
}

template <class Data>
void Binary<Data>::writeElem(ofstream& file, int &new_pos, int old_pos, Elem<Data> cur) {
	int cur_pos = new_pos;
	get_Elem(old_pos, cur);
	file.seekp(cur_pos, ios::beg);
	file.write((char*)&cur, sizeof(cur));
	if (cur.left != -1) {
		new_pos += sizeof(Elem<Data>);
		file.seekp(cur_pos, ios::beg);
		file.write((char*)&new_pos, sizeof(int));
		writeElem(file, new_pos, cur.left, cur);
	}
	if (cur.right != -1) {
		new_pos += sizeof(Elem<Data>);
		file.seekp(cur_pos + 4, ios::beg);
		file.write((char*)&new_pos, sizeof(int));
		writeElem(file, new_pos, cur.right, cur);
	}
}