#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include "Conversation.h"
#include "TemplateOfTree.h"
#include "BinaryFile.h"
using namespace std;

#define CurrentType double

void addStr(char*& str, char* add_str) {
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
		 << "[0]. Exit\n\n>>> ";
}

int Conversation::count_obj = 0;

int main() {
	setlocale(LC_ALL, "rus");
	bool flag = true;
	int p_menu;
	char* filename = new char[strlen(typeid(CurrentType).name()) + 1];
	strcpy(filename, typeid(CurrentType).name());
	addStr(filename, (char*)".bin");
	Binary<CurrentType> test(filename);

	while (flag) {
		system("cls");
		printMenu();
		cin >> p_menu;
		try {
			switch (p_menu) {

			case 1: {
				double a = 11.2;
				double b = 22;
				double c = 12;
				double d = 22.33;
				double g = 1213.3;
				double h = 222;
				double k = 21231;
				double s = 10.2;
				test.push(a);
				test.push(b);
				test.push(c);
				test.push(d);
				test.push(g);
				test.push(h);
				test.push(k);
				test.push(s);
				system("pause");
				break;
			}

			case 2: {
				test.print(4, 0);
				system("pause");
				break;
			}

			case 3: {
				test.pop(55);
				system("pause");
				break;
			}

			case 4: {
				cout << test.search(21231);
				system("pause");
				break;
			}

			case 5: {
				test.update();
				break;
			}

			case 0: { flag = false; break; }
			default: { cout << "Ошибка ввода!\n"; system("pause"); break; }
			}
		}
		catch (Error & err) {
			err.ErrMsg();
		}
	}
	return 0;
}