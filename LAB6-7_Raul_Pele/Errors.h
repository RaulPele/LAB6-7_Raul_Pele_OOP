#pragma once
#include <string>
using namespace std;

class Error {
private:
	string message;

public:
	Error(const string& message): message(message){}
	const string& getMessage() { return this->message; };
};

class DiscNotFoundError : public Error {
public:
	DiscNotFoundError(const string& message) : Error(message) {}
};

class DiscExistsError : public Error {
public:
	DiscExistsError(const string& message) : Error(message) {}
};
