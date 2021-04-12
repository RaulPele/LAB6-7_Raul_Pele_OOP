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

class InvalidDataError : public Error {
public:
	InvalidDataError(const string& message): Error(message){}
};

class OutOfBoundsError : public Error {
public: 
	OutOfBoundsError(const string& message):Error(message){}
};
