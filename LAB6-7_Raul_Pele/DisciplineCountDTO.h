#pragma once

#include<string>
using namespace std;


class DisciplineCountDTO {
private:
	int count;
	string type;

public:
	int getCount() { return this->count; }
	void setCount(int newCount) { this->count = newCount; }
	string getType() { return this->type; }
	DisciplineCountDTO(string type):type(type), count(1){}
	DisciplineCountDTO(): count(0){};
};