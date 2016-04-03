#include "../include/MyException.h"
#include <fstream>
#include <iostream>

MyException::MyException(const std::string& err) : error(err)
{
	std::cerr << "Creation d'exception : " << err << std::endl;
}
