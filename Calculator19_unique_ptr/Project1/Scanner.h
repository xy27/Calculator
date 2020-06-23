#ifndef _SCANNER_H_
#define _SCANNER_H_
#include<string>

enum EToken									//扫描状态标志
{
	TOKEN_COMMAND,
	TOKEN_END,
	TOKEN_ERROR,
	TOKEN_NUMBER,
	TOKEN_PLUS,
	TOKEN_MINUS,
	TOKEN_MULTIPLY,
	TOKEN_DIVIDE,
	TOKEN_LPARENTHESIS,
	TOKEN_RPARENTHESIS,
	TOKEN_INDETIFIER,
	TOKEN_ASSIGN
};

class Scanner
{
public:
	//Scanner(const std::string& buf);
	explicit Scanner(std::istream& in);
	void Accept();						//读取一个有效字符or操作数or标识符，并设置相应状态。该过程忽略空白字符
	void AcceptCommand();
	bool IsEmpty()const;				//判断表达式是否为空
	bool IsDone()const;					//判断表达式是否解析完
	bool IsCommand()const;				
	double Number()const;				//获取扫面到的数字
	std::string GetSymbol()const;		//获取扫描到的标识符
	EToken Token()const;				//获取扫描状态标志
	~Scanner();
private:
	//void SkipWhite();
	void ReadChar();					//从输入流读取字符，忽略空白字符
	//const std::string buf_;
	std::istream& in_;					//标准输入流
	int look_;							//当前解析到的字符
	//unsigned int curpos_;
	std::string symbol_;				//扫描到的标识符
	EToken token_;						//扫描状态标志
	double number_;						//扫描到的数字
	bool isEmpty_;						//表达式是否为空标志
};
#endif //_SCANNER_H_
