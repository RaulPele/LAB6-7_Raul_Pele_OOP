#include "validators.h"
#include "Errors.h"
#include <cctype>
#include <string>
#include <sstream>
using namespace std;

bool DisciplineValidator::validateName(const string& name) const {
	stringstream a{ name };
	string word;

	while (a >> word) {
		for (char c : word) {
			if (!isalpha(c)) {
				return false;
			}
		}
	}
	return true;
}

bool DisciplineValidator::validateHoursPerWeek(const int hoursPerWeek) const {
	if (hoursPerWeek <= 0) {
		return false;
	}
	return true;
}

bool DisciplineValidator::validateTeacher(const string& teacher) const {
	return validateName(teacher);
}

