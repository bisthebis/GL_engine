#include <fstream>
#include <iostream>

#include "MyException.h"


MyException::MyException(const std::string& err) : error(err)
{
}
