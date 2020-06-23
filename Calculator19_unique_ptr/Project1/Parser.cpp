#include<cassert>
#include<iostream>
#include<cstring>
#include<memory>
#include<sstream>

#include "Parser.h"
#include"Scanner.h"
#include"Node.h"
#include"Exception.h"
#include"Calc.h"
#include"DebugNew.h"


Parser::~Parser()
{
	//delete tree_;
}

STATUS Parser::Parse()
{
	tree_ = Expr();
	if (!scanner_.IsDone())
	{
		status_ = STATUS_ERROR;
	}
	return status_;
}

double Parser::Calculate()const
{
	assert(tree_.get() != nullptr);
	return tree_->Calc();
}

std::unique_ptr<Node> Parser::Expr()//�������ʽ
{
	std::unique_ptr<Node> node = Term();
	EToken token = scanner_.Token();

	if (token == TOKEN_PLUS || token == TOKEN_MINUS)
	{
		//Expr ::= Term{('+' | '-') Term }
		//MultipleNode* multipleNode = new SumNode(node);
		std::unique_ptr<MultipleNode> multipleNode(new SumNode(node));
		do
		{
			scanner_.Accept();	//������һ����ʶ��
			std::unique_ptr<Node> nextNode = Term();
			multipleNode->AppendChild(nextNode, (token == TOKEN_PLUS));
			token = scanner_.Token();	//���±�־
		} while (token == TOKEN_PLUS || token == TOKEN_MINUS);
		node.reset(multipleNode.release());
	}
	else if (token == TOKEN_ASSIGN)
	{
		//Expr ::=Term=Expr
		scanner_.Accept();
		std::unique_ptr<Node> nodeRight = Expr();
		if (node->IsLvalue())//����Ӧ������ֵ
		{
			node = std::unique_ptr<Node>(new AssignNode(node, nodeRight));
		}
		else
		{
			status_ = STATUS_ERROR;
			//std::cout << "The left-hand side of an assignment must be a variable " << std::endl;
			//Ӧ���׳��쳣
			throw SyntaxError("The left-hand side of an assignment must be a variable.");
		}
	}
	return node;
}

std::unique_ptr<Node> Parser::Term()//������
{
	//Term :: = Factor{ ('*' | '/') Factor }
	std::unique_ptr<Node> node = Factor();
	EToken token = scanner_.Token();

	if (token == TOKEN_MULTIPLY || token == TOKEN_DIVIDE)
	{
		//MultipleNode* multipleNode = new ProductNode(node);
		std::unique_ptr<MultipleNode> multipleNode(new ProductNode(node));
		do
		{
			scanner_.Accept();
			std::unique_ptr<Node> nextNode = Factor();
			multipleNode->AppendChild(nextNode, (token == TOKEN_MULTIPLY));
			token = scanner_.Token();	//���±�־
		} while (token == TOKEN_MULTIPLY || token == TOKEN_DIVIDE);
		node.reset(multipleNode.release());
	}
	return node;
}

std::unique_ptr<Node> Parser::Factor()//������ʽ
{
	std::unique_ptr<Node> node;
	EToken token = scanner_.Token();
	if (token == TOKEN_LPARENTHESIS)	//'('Expr ')'
	{
		scanner_.Accept();	
		node = Expr();			//��ȡ��Ч�ַ���Ϊ��һ�ν�����׼��
		if (scanner_.Token() == TOKEN_RPARENTHESIS)
		{
			scanner_.Accept();	//��ȡ��Ч�ַ���Ϊ��һ�ν�����׼��
		}
		else
		{
			status_ = STATUS_ERROR;
			//std::cout << "missing a parenthesis" << std::endl;
			throw SyntaxError("Missing a parenthesis.");
			//node = nullptr;//������䲻�ᱻִ�е�
		}
	}
	else if (token == TOKEN_NUMBER)	//Number
	{
		node = std::unique_ptr<Node>(new NumberNode(scanner_.Number()));
		scanner_.Accept();				//���ν�����ϣ���ȡ��Ч�ַ���Ϊ��һ�ν�����׼��
	}
	else if (token == TOKEN_INDETIFIER)	//Identifier
	{
		std::string symbol = scanner_.GetSymbol();
		unsigned int id = calc_.FindSymbol(symbol);
		scanner_.Accept();

		if (scanner_.Token() == TOKEN_LPARENTHESIS)
		{
			scanner_.Accept();			//��ȡ��Ч�ַ���Ϊ��һ�ν�����׼��
			node = Expr();
			if (scanner_.Token() == TOKEN_RPARENTHESIS)
			{
				scanner_.Accept();		//��ȡ��Ч�ַ���Ϊ��һ�ν�����׼��
				if (id != SymbolTable::IDNOTFOUND&&calc_.IsFunction(id))
				{
					node = std::unique_ptr<Node>(new FunctionNode(node, calc_.GetFunction(id)));
				}
				else
				{
					status_ = STATUS_ERROR;
					//std::cout << "Unknown function " << "\"" << symbol << "\"" << std::endl;
					//char buf[256] = { 0 };
					//sprintf_s(buf, "Unknown function \"%s\".", symbol.c_str());
					std::ostringstream oss;
					oss << "Unknown function\"" << symbol << "\".";
					throw SyntaxError(oss.str());
				}
			}
			else
			{
				status_ = STATUS_ERROR;
				//std::cout << "Missing parenthesis in a function call." << std::endl;
				throw SyntaxError("Missing parenthesis in a function call.");
			}
		}
		else
		{
			if (id == SymbolTable::IDNOTFOUND)
			{
				id = calc_.AddSymbol(symbol);
			}
			node = std::unique_ptr<Node>(new VariableNode(id, calc_.GetStorage()));//�����������
		}
		
	}
	else if (token == TOKEN_MINUS)	//'-'Factor
	{
		scanner_.Accept();
		node = std::unique_ptr<Node>(new UMinusNode(Factor()));//�����е���֣����뽫���캯���Ĳ�����Ϊ��ͨ����
	}
	else
	{
		status_ = STATUS_ERROR;
		//std::cout << "Not a valid expression" << std::endl;
		throw SyntaxError("Not a valid expression.");
		//node = nullptr;
	}
	return node;
}