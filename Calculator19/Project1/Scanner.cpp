#include<cctype>
#include<iostream>
#include "Scanner.h"


Scanner::Scanner(std::istream& in) :in_(in)
{
	Accept();							//注意初始化Scanner时就进行了一次Accept操作
	isEmpty_ = (token_ == TOKEN_END);	//判断表达式是否为空
}
Scanner::~Scanner()
{
}

void Scanner::ReadChar()
{
	look_ = in_.get();
	while (look_ == ' ' || look_ == '\t')
		look_ = in_.get();
}

double Scanner::Number()const
{
	return number_;
}

std::string Scanner::GetSymbol() const
{
	return symbol_;
}

EToken Scanner::Token()const
{
	return token_;
}

//void Scanner::SkipWhite()
//{
//	while (isspace(buf_[curpos_]))
//		++curpos_;
//}

void Scanner::Accept()
{
	ReadChar();
	switch (look_)
	{
	case '!':
		token_ = TOKEN_COMMAND;
		break;
	case '+':
		token_ = TOKEN_PLUS;
		break;
	case'-':
		token_ = TOKEN_MINUS;
		break;
	case'*':
		token_ = TOKEN_MULTIPLY;
		break;
	case'/':
		token_ = TOKEN_DIVIDE;
		break;
	case'=':
		token_ = TOKEN_ASSIGN;
		break;
	case'(':
		token_ = TOKEN_LPARENTHESIS;
		break;
	case')':
		token_ = TOKEN_RPARENTHESIS;
		break;
	case'0':case'1':case'2':case'3':case'4':
	case'5':case'6':case'7':case'8':case'9':
	case'.':
		token_ = TOKEN_NUMBER;
		//char* p;
		//number_ = strtod(&buf_[curpos_], &p);
		//curpos_ = p - &buf_[0];
		in_.putback(look_);
		in_ >> number_;
		break;
	case'\0':case'\n':case'\r':case EOF:
		token_ = TOKEN_END;
		break;
	default:	//标识符
		if (isalpha(look_) || look_ == '_')
		{
			token_ = TOKEN_INDETIFIER;
			symbol_.erase();
			do
			{
				symbol_ += look_;
				look_ = in_.get();
			} while (isalnum(look_) ||look_ == '_');
			in_.putback(look_);
		}
		else
			token_ = TOKEN_ERROR;
		break;
	}
}

void Scanner::AcceptCommand()
{
	ReadChar();
	symbol_.erase();
	while (!isspace(look_))
	{
		symbol_ += look_;
		look_ = in_.get();
	}
}

bool Scanner::IsEmpty() const
{
	//Accept(); const成员函数不能调用非const成员函数，是这个意思吗？
	return isEmpty_;
}

bool Scanner::IsDone() const
{
	return token_==TOKEN_END;
}

bool Scanner::IsCommand()const
{
	return token_ == TOKEN_COMMAND;
}
