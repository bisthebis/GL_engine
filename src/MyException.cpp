#include "../include/MyException.h"
#include <fstream>
#include <iostream>

#include "../include/easylogging++.h"


MyException::MyException(const std::string& err) : error(err)
{
	LOG(ERROR) << err;
}
