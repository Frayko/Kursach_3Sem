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
		Elem() : left(-1), right(-1) {}
		Elem(Data _obj) : obj(_obj), left(-1), right(-1) {}
	};
	char* filename;
	void set_root(int pos);
	void set_Elem(int pos, Elem<Data> elem);
	void get_Elem(int pos, Elem<Data>& elem);
	void insert(int pos, int add_pos, Elem<Data> t);
	bool isEmpty();
	void writeElem(ofstream& file, int &pos, int old_pos, Elem<Data> cur);
	int find_del_elem(int cur_pos, int &parent_pos, Data target);
	int find_max_min(int cur_pos, int parent_pos);
	void edit(int pos);
public:
	Binary();
	Binary(char* _filename);
	~Binary();
	int get_root();
	void push(Data _obj);
	void print(int pos, int size);
	void rename();
	void pop(Data target);
	int search(Data target);
	void select(Data target);
	void update();
	void info();
};

template <class Data>
Binary<Data>::Binary() {
	filename = new char[strlen("data.bin") + 1];
	strcpy(filename, "data.bin");
	open(filename, ios_base::binary | ios_base::in | ios_base::out);
	if (!is_open()) {
		cerr << "File cannot be read! Create new file...\n";
		ofstream(filename); close();
		open(filename, ios_base::binary | ios_base::in | ios_base::out);
	}
}

template <class Data>
Binary<Data>::Binary(char* _filename) {
	filename = new char[strlen(_filename) + 1];
	strcpy(filename, _filename);
	open(filename, ios_base::binary | ios_base::in | ios_base::out);
	if (!is_open()) {
		cerr << "File cannot be read! Create new file...\n";
		ofstream file(filename); file.close();
		open(filename, ios_base::binary | ios_base::in | ios_base::out);
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
	int pos = 0;
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
	return ((int)tellg() < 1 || get_root() == 0);
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

template <>
void Binary<Conversation>::print(int pos, int size) {
	if (isEmpty())
		throw ErrorIsEmpty();
	Elem<Conversation> temp;
	get_Elem(pos, temp);
	if (temp.right != -1)
		print(temp.right, size + 1);
	for (int i = 0; i < size; i++)
		cout << "		";
	temp.obj.print(); cout << endl;
	if (temp.left != -1)
		print(temp.left, size + 1);
}

template <class Data>
void Binary<Data>::rename() {
	throw ErrorNoImplementation();
}

template <>
void Binary<int>::rename() {
	system("DEL int.bin");
	system("REN update.bin int.bin");
	open(filename, ios_base::binary | ios_base::in | ios_base::out);
}

template <>
void Binary<double>::rename() {
	system("DEL double.bin");
	system("REN update.bin double.bin");
	open(filename, ios_base::binary | ios_base::in | ios_base::out);
}

template <>
void Binary<Conversation>::rename() {
	system("DEL Conversation.bin");
	system("REN update.bin Conversation.bin");
	open(filename, ios_base::binary | ios_base::in | ios_base::out);
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
				if (cur.left == -1) {
					cerr << "No results...\n";
					return -1;
				}
				else
					pos = cur.left;
			}
			else {
				if (cur.right == -1) {
					cerr << "No results...\n";
					return -1;
				}
				else
					pos = cur.right;
			}
		}
	}
	if (cur.obj == target)
		return pos;
	else {
		cerr << "No results...\n";
		return -1;
	}
}

template <class Data>
void Binary<Data>::pop(Data target) {
	if (isEmpty())
		return;
	Elem<Data> cur;
	int parent_pos, cur_pos, new_pos, pos;
	parent_pos = -1;
	cur_pos = get_root();
	cur_pos = find_del_elem(cur_pos, parent_pos, target);
	if (cur_pos == -1) {
		return;
	}
	get_Elem(cur_pos, cur);
	if (parent_pos == -1) {
		if (cur.left == -1 && cur.right != -1) {
			set_root(cur.right);
		}
		else {
			if (cur.right == -1) {
				set_root(0);
				return;
			}
			new_pos = find_max_min(cur.left, cur_pos);
			get_Elem(cur_pos, cur);
			seekp(new_pos, ios_base::beg);
			write((char*)&cur.left, sizeof(int));
			seekp(new_pos + 4, ios_base::beg);
			write((char*)&cur.right, sizeof(int));
			set_root(new_pos);
		}
	}
	else {
		if (cur.left == -1) {
			seekp(parent_pos, ios_base::beg);
			write((char*)&cur.right, sizeof(int));
		}
		else {
			new_pos = find_max_min(cur.left, cur_pos);
			get_Elem(cur_pos, cur);
			seekp(parent_pos, ios_base::beg);
			write((char*)&new_pos, sizeof(int));
			seekp(new_pos, ios_base::beg);
			write((char*)&cur.left, sizeof(int));
			seekp(new_pos + 4, ios_base::beg);
			write((char*)&cur.right, sizeof(int));
		}
	}

}

template <class Data>
int Binary<Data>::find_del_elem(int cur_pos, int &parent_pos, Data target) {
	Elem<Data> cur;
	get_Elem(cur_pos, cur);
	if (cur.obj == target) {
		return cur_pos;
	}
	else {
		if (cur.obj > target) {
			if (cur.left == -1) {
				return -1;
			}
			else {
				parent_pos = (int)tellg() - sizeof(Elem<Data>);
				cur_pos = find_del_elem(cur.left, parent_pos, target);
			}
		}
		else {
			if (cur.right == -1) {
				return -1;
			}
			else {
				parent_pos = (int)tellg() - sizeof(Elem<Data>) + 4;
				cur_pos = find_del_elem(cur.right, parent_pos, target);
			}
		}
	}
	return cur_pos;
}

template <class Data>
int Binary<Data>::find_max_min(int cur_pos, int parent_pos) {
	Elem<Data> cur;
	get_Elem(cur_pos, cur);
	for (; cur.right != -1; get_Elem(cur.right, cur)) {
		cur_pos = cur.right;
		parent_pos = (int)tellg() - sizeof(Elem<Data>) + 4;
	}
	if (parent_pos != -1) {
		int null = -1;
		seekp(parent_pos, ios_base::beg);
		write((char*)&null, sizeof(int));
	}
	return cur_pos;
}

template <class Data>
void Binary<Data>::update() {
	Elem<Data> cur;
	ofstream file("update.bin", ios_base::binary | ios_base::out);
	int pos = get_root();
	if (pos == 0)
		return;
	get_Elem(pos, cur);
	int new_pos = 4;
	file.seekp(0, ios_base::beg);
	file.write((char*)&new_pos, sizeof(int));
	file.seekp(new_pos, ios_base::beg);
	file.write((char*)&cur, sizeof(Elem<Data>));
	writeElem(file, new_pos, pos, cur);
	close();
	file.close();
	rename();
}

template <class Data>
void Binary<Data>::writeElem(ofstream& file, int &new_pos, int old_pos, Elem<Data> cur) {
	int cur_pos = new_pos;
	get_Elem(old_pos, cur);
	file.seekp(cur_pos, ios_base::beg);
	file.write((char*)&cur, sizeof(cur));
	if (cur.left != -1) {
		new_pos += sizeof(Elem<Data>);
		file.seekp(cur_pos, ios_base::beg);
		file.write((char*)&new_pos, sizeof(int));
		writeElem(file, new_pos, cur.left, cur);
	}
	if (cur.right != -1) {
		new_pos += sizeof(Elem<Data>);
		file.seekp(cur_pos + 4, ios_base::beg);
		file.write((char*)&new_pos, sizeof(int));
		writeElem(file, new_pos, cur.right, cur);
	}
}

template <class Data>
void Binary<Data>::select(Data target) {
	int sel;
	int pos = search(target);
	if (pos == -1)
		return;
	Elem<Data> cur;
	get_Elem(pos, cur);
	cout << "Position in binary file: " << pos << endl << "Obj: " << cur.obj << endl << endl << "[1]. Edit\n[any]. Exit\n\n>>> "; cin >> sel;
	if (sel == 1)
		edit(pos);
	else
		return;
}

template <class Data>
void Binary<Data>::edit(int pos) {
	bool flag;
	Elem<Data> cur;
	get_Elem(pos, cur);
	cout << "Obj: " << cur.obj << endl << "New Obj: ";
	cin >> cur.obj;
	set_Elem(pos, cur);
}

template <class Data>
void Binary<Data>::info() {
	cout << "File name: " << filename << endl;
	seekg(0, ios_base::end);
	cout << "Size(byte): " << (int)tellg() << endl;
}