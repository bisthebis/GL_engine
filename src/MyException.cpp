#include <fstream>
#include <iostream>

#include "MyException.h"
#include "easylogging++.h"


MyException::MyException(const std::string& err) : error(err)
{
	LOG(ERROR) << err;
}
