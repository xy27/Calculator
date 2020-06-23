#ifndef PARSER_H_
#define PARSER_H_

#include "Node.h"		//���ͷ�ļ�һ��Ҫ����		

class Scanner;
class Node;
class Calc;

enum STATUS
{
	STATUS_OK,
	STATUS_ERROR,
	STATUS_QUIT
};

class Parser
{
public:
	Parser(Scanner& scanner,Calc& calc) 
		:scanner_(scanner),calc_(calc),tree_(nullptr),status_(STATUS_OK) {}
	~Parser();
	STATUS Parse();						//�������ʽ
	std::unique_ptr<Node> Expr();			//������������Ҳû�����,���ضԾֲ����������  �������ʽ
	std::unique_ptr<Node> Term();			//������
	std::unique_ptr<Node> Factor();		//��������
	double Calculate()const;			//��������ʽ��ֵ
private:
	Scanner& scanner_;
	Calc& calc_;
	std::unique_ptr<Node> tree_;
	STATUS status_;

};
#endif //PARSER_H_
