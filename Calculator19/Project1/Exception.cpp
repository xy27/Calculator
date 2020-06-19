#include "Exception.h"

const char* Exception::what()const throw()
{
	return message_.c_str();
}
