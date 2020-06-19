#ifndef PARSER_H_
#define PARSER_H_

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
		:scanner_(scanner),calc_(calc),tree_(0),status_(STATUS_OK) {}
	~Parser();
	STATUS Parse();						//�������ʽ
	std::auto_ptr<Node> Expr();			//������������Ҳû�����,���ضԾֲ����������  �������ʽ
	std::auto_ptr<Node> Term();			//������
	std::auto_ptr<Node> Factor();		//��������
	double Calculate()const;			//��������ʽ��ֵ
private:
	Scanner& scanner_;
	Calc& calc_;
	std::auto_ptr<Node> tree_;
	STATUS status_;

};
#endif //PARSER_H_
