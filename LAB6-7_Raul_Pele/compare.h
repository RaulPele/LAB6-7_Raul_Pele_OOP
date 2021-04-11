#pragma once
#include "Discipline.h"

typedef bool (*CompareFunction)(const Discipline&, const Discipline&);

bool cmpName(const Discipline& a, const Discipline& b);

bool cmpOre(const Discipline& a, const Discipline& b);

bool cmpTeacherAndType(const Discipline& a, const Discipline& b);


