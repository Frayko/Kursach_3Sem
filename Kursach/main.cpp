#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include "Conversation.h"
#include "TemplateOfTree.h"
using namespace std;

void printMenu() {
	cout << "[1]. Дерево с классом разговора\n"
		 << "[2]. Дерево с простым типом double\n"
		 << "[0]. Выход\n\n>>> ";
}

int Conversation::count_obj = 0;

int main() {
	setlocale(LC_ALL, "rus");
	bool flag = true;
	int p_menu;

	while (flag) {
		system("cls");
		printMenu();
		cin >> p_menu;
		switch (p_menu) {
		case 1: {
			Date dat(12, 5, 2000);
			Date dat_p(13, 5, 2000);
			Time tim(25, 55, 12);
			Conversation first((char*)"Ust-Ilimsk", (char*)"395", (char*)"555555", 1.2, 12, dat, tim, dat_p);
			dat.set(13, 5, 2000);
			Conversation second((char*)"Ust-Ilimsk", (char*)"395", (char*)"555555", 2.4, 12, dat, tim, dat_p);
			dat.set(8, 5, 2000);
			Conversation third((char*)"Ust-Ilimsk", (char*)"395", (char*)"555555", 5.1, 12, dat, tim, dat_p);
			Tree<Conversation> test;
			test.Push(&first);
			test.Push(&second);
			test.Push(&third);
			system("pause");
			break;
		}

		case 2: {
			double a = 11.2;
			double b = 22;
			double c = 12;
			double d = 22.33;
			double g = 1213.3;
			double h = 222;
			double k = 21231;
			double s = 10.2;
			Tree<double> test;
			test.Push(&a);
			test.Push(&b);
			test.Push(&c);
			test.Push(&d);
			test.Push(&g);
			test.Push(&h);
			test.Push(&k);
			test.Push(&s);
			break;
		}

		case 3: {
			Date dat(12, 5, 2000);
			Date dat_p(13, 5, 2000);
			Time tim(25, 55, 12);
			Conversation first((char*)"Ust-Ilimsk", (char*)"395", (char*)"555555", 1.2, 12, dat, tim, dat_p);
			fstream fout("test.dat", ios_base::binary | ios_base::out);
			fout << first;
			fout.close();
			Conversation qw;
			fstream fin("test.dat", ios_base::binary | ios_base::in);
			fin >> qw;
			fin.close();
			system("pause");
			break;
		}

		case 0: { flag = false; break; }
		default: { cout << "Ошибка ввода!\n"; system("pause"); break; }
		}
	}
	return 0;
}