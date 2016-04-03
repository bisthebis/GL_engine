#ifndef DEF_MYEXCEPTION_H
#define DEF_MYEXCEPTION_H

#include <exception>
#include <string>


struct MyException : public std::exception
{
	std::string error;
	MyException(const std::string& err);
	virtual const char* what() const noexcept {return error.c_str();}

};

#endif
