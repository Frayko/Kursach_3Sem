#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "DataBase.h"
using namespace std;

void printMenu() {
}

int main() {
	bool flag = true;
	int p_menu;

	while (flag) {
		system("cls");
		printMenu();
		cin >> p_menu;
		switch (p_menu) {
		case 1: {
			Tariff tar((char*)"Test", 1.2);
			Date dat(12, 5, 2000);
			Date_pay dat_p(13, 5, 2000);
			Time tim(25, 55, 12);
			Conversation first((char*)"Ust-Ilimsk", (char*)"395", (char*)"555555", tar, 12, dat, tim, dat_p);
			dat.set(13, 5, 2000);
			Conversation second((char*)"Ust-Ilimsk", (char*)"395", (char*)"555555", tar, 12, dat, tim, dat_p);
			dat.set(8, 5, 2000);
			Conversation third((char*)"Ust-Ilimsk", (char*)"395", (char*)"555555", tar, 12, dat, tim, dat_p);
			DataBase test(first);
			test.add(second); test.add(third);
			//bool kek = first > second;
			//Conversation list[2];				�������� ������������� ���������
			//list[0] = first;					���������� ��� ������ ���� ������, ���� ������������ ������� ��� ��������� ���� � ������� ����������
			//list[1] = second;					
			//bool kek = list[0] > list[1];
			test.sort();
			system("pause");
			break;
		}
		case 0: { flag = false; break; }
		default: { cout << "������ �����!\n"; system("pause"); break; }
		}
	}
	return 0;
}