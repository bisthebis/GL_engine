#include "../include/MyException.h"
#include <fstream>
#include <iostream>

#include "../include/easylogging++.h"

INITIALIZE_EASYLOGGINGPP

MyException::MyException(const std::string& err) : error(err)
{
	LOG(ERROR) << err;
}
