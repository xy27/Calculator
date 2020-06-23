#ifndef _COMMAND_PARSER_H
#define _COMMAND_PARSER_H

#include"Parser.h"

class Scanner;
class Calc;

class CommandParser
{
	enum ECommand
	{
		CMD_HELP,
		CMD_QUIT,
		CMD_VAR,
		CMD_FUN,
		CMD_LOAD,
		CMD_SAVE,
		CMD_ERROR
	};
public:
	CommandParser(Scanner& scanner, Calc& calc);
	~CommandParser();
	STATUS Execute();
private:
	void Help()const;
	void ListFun()const;
	void ListVar()const;
	STATUS Load(const std::string& fileName);
	STATUS Save(const std::string& fileName);
	Scanner& scanner_;
	Calc& calc_;
	ECommand cmd_;
	std::string cmdName_;
};
#endif //_COMMAND_PARSER_H
