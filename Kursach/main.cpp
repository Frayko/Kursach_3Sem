#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include "Conversation.h"
#include "BinaryFile.h"
#include <time.h>
using namespace std;

#define CurrentType int
#define COUNT_ELEMS 5

void addStr(char*& str, char* add_str) {
	if (strlen(add_str) > 4) {
		char target[6] = {}, temp[30] = {};
		for (int i = 0; i < 5; i++)
			target[i] = add_str[i];
		if (!strcmp(target, (char*)"class")) {
			for (int i = 0; i < strlen(add_str) - 6; i++)
				temp[i] = add_str[i + 6];
			if (str)
				delete[] str;
			str = new char[strlen(temp) + 1];
			strcpy(str, temp);
			return;
		}
	}
	char* buf;
	buf = new char[strlen(str) + strlen(add_str) + 1];
	strcpy(buf, str);
	strcat(buf, add_str);
	if (str)
		delete[] str;
	str = new char[strlen(buf) + 1];
	strcpy(str, buf);
}

void printMenu() {
	cout << "[1]. Add\n"
		 << "[2]. Print\n"
		 << "[3]. Delete\n"
		 << "[4]. Search\n"
		 << "[5]. Update\n"
		 << "[6]. File info\n"
		 << "[0]. Exit\n\n>>> ";
}

int Conversation::count_obj = 0;

int main() {
	srand(time(0));
	setlocale(LC_ALL, "rus");
	bool flag = true;
	int p_menu;
	char* filename = new char[strlen(typeid(CurrentType).name()) + 1];
	filename[0] = {};
	addStr(filename, (char*)typeid(CurrentType).name());
	addStr(filename, (char*)".bin");
	Binary<CurrentType> test(filename);

	//Date date(11, 12, 2000);
	//Date date_pay(0, 0, 0);
	//Time time(11, 22, 1);
	//Conversation a((char*)"Novosibirsk", (char*)"395", (char*)"256785", 2.6, 10, date, time, date_pay);
	//date.set(11, 12, 1976);
	//date_pay.set(0, 0, 0);
	//time.set(12, 3, 2);
	//Conversation b((char*)"Novosibirsk", (char*)"395", (char*)"321185", 10.5, 10, date, time, date_pay);
	//date.set(11, 12, 1954);
	//date_pay.set(12, 12, 1954);
	//time.set(54, 13, 0);
	//Conversation c((char*)"Novosibirsk", (char*)"395", (char*)"256785", 3.5, 10, date, time, date_pay);
	//test.push(a);
	//test.push(b);
	//test.push(c);

	while (flag) {
		system("cls");
		printMenu();
		cin >> p_menu;
		try {
			switch (p_menu) {

			case 1: {
				CurrentType obj;
				cout << "ADD\nObj: ";
				cin >> obj;
				test.push(obj);
				system("pause");
				break;
			}

			case 2: {
				test.print(test.get_root(), 0);
				system("pause");
				break;
			}

			case 3: {
				CurrentType obj;
				test.print(test.get_root(), 0);
				cout << endl << endl << "DELETE\nObj: ";
				cin >> obj;
				test.pop(obj);
				system("pause");
				break;
			}

			case 4: {
				CurrentType obj;
				cout << "SEARCH\nObj: ";
				cin >> obj;
				system("cls");
				test.select(obj);
				system("pause");
				break;
			}

			case 5: {
				test.update();
				break;
			}

			case 6: {
				test.info();
				system("pause");
				break;
			}

			case 9: {
				for (int i = 0; i < COUNT_ELEMS; i++)
					test.push(rand() % 15);
				break;
			}

			case 0: { flag = false; break; }
			default: { cerr << "Input Error!\n"; system("pause"); break; }
			}
		}
		catch (Error & err) {
			err.ErrMsg();
		}
		catch (...) {
			cerr << "Error in switch!\n";
			system("pause");
		}
	}
	return 0;
}