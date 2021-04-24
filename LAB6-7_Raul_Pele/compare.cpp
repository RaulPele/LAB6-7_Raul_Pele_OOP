#include "compare.h"

bool cmpName(const Discipline& a, const Discipline& b) {
	if (a.getName().compare(b.getName()) <= 0) {
		return true;
	}
	return false;
}

bool cmpOre(const Discipline& a, const Discipline& b) {
	if (a.getHoursPerWeek() <= b.getHoursPerWeek()) {
		return true;
	}
	return false;
}

bool cmpTeacherAndType(const Discipline& a, const Discipline& b) {
	int teacherCmp = a.getTeacher().compare(b.getTeacher());
	int typeCmp = a.getType().compare(b.getType());
	if (teacherCmp > 0 || (teacherCmp == 0 && typeCmp >= 0)) {
		return false;
	}
	return true;
}

