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
	STATUS Parse();						//解析表达式
	std::auto_ptr<Node> Expr();			//返回引用类型也没问题吧,返回对局部对象的引用  解析表达式
	std::auto_ptr<Node> Term();			//解析项
	std::auto_ptr<Node> Factor();		//解析因子
	double Calculate()const;			//计算出表达式的值
private:
	Scanner& scanner_;
	Calc& calc_;
	std::auto_ptr<Node> tree_;
	STATUS status_;

};
#endif //PARSER_H_
