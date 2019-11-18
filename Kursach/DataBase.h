#pragma once
#include "Conversation.h"

class DataBase {
private:
	Conversation* list[100];
	int count_conversation;
public:
	DataBase();
	DataBase(Conversation& A);
	DataBase(DataBase& D);
	void add(Conversation& A);
	void sort();
};