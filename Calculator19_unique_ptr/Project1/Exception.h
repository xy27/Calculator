#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

#include<exception>
#include<string>

class Exception:public std::exception
{
public:
	explicit Exception(const char* message)
		:message_(message)
	{

	}

	explicit Exception(const std::string& message)
		:message_(message)
	{

	}
	virtual ~Exception()throw()//不抛出异常
	{

	}
	virtual const char* what()const throw();//不抛出异常

private:
	std::string message_;
};

class SyntaxError:public Exception
{
public:
	explicit SyntaxError(const std::string& message)
		:Exception(message)
	{

	}

	explicit SyntaxError(const char* message)
		:Exception(message)
	{

	}
	virtual ~SyntaxError()throw()
	{

	}
};

class FileStreamError :public Exception
{
public:
	explicit FileStreamError(const std::string& message)
		:Exception(message)
	{

	}

	explicit FileStreamError(const char* message)
		:Exception(message)
	{

	}
	virtual ~FileStreamError()throw()
	{

	}
};
#endif//_EXCEPTION_H_
