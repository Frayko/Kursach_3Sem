#include "DataBase.h"
#include <iostream>
using namespace std;

DataBase::DataBase() {
	count_conversation = 0;
	list[count_conversation++] = new Conversation();
}

DataBase::DataBase(Conversation& A) {
	count_conversation = 0;
	list[count_conversation++] = (Conversation*)&A;
}

DataBase::DataBase(DataBase& D) {
	count_conversation = D.count_conversation;
	for (int i = 0; i < D.count_conversation; i++)
		list[i] = D.list[i];
}

void DataBase::add(Conversation& A) {
	list[count_conversation++] = (Conversation*)&A;
}

void DataBase::sort() {
	for (int i = 0; i < count_conversation - 1; i++) {
		for (int j = 0; j < count_conversation - i - 1; j++) {
			if (list[j] > list[j + 1]) {
				Conversation* temp = list[j];
				list[j] = list[j + 1];
				list[j + 1] = temp;
			}
		}
	}
}