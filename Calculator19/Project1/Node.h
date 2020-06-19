#ifndef _NODE_H_
#define _NODE_H_
#include<vector>
#include<cassert>
#include<memory>
#include"FunctionTable.h"

class Storage;


class Noncopyable
{
protected:
	Noncopyable() {}
	~Noncopyable() {}
private:
	Noncopyable(const Noncopyable&) {};
	const Noncopyable& operator=(const Noncopyable&) {};
};

class Node:private Noncopyable
{
public:
	Node();
	virtual double Calc()const = 0;
	virtual bool IsLvalue()const
	{
		return false;
	}
	virtual void Assign(double)		//在VariableNode中重新定义，这个函数需要定义成虚函数
	{
		assert(!"Assign called incorrectlly");
	}
	//~Node();
	virtual ~Node();		//虚函数！！！
};

class NumberNode :public Node
{
public:
	NumberNode(double number) :number_(number) {}
	double Calc()const;
private:
	const double number_;	//const成员只能在初始化列表中初始化。存储NumberNode结点的值
};

class BinaryNode :public Node
{
public:
	BinaryNode(std::auto_ptr<Node>& left, std::auto_ptr<Node>& right)
		:left_(left), right_(right) {}
	~BinaryNode();
//private:
protected:			//要知道这里为什么设置为protected
	//Node*const left_;
	//Node*const right_;
	std::auto_ptr<Node> left_;
	std::auto_ptr<Node> right_;
};

class UnaryNode :public Node
{
public:
	UnaryNode(std::auto_ptr<Node>& child) :child_(child) {}
	~UnaryNode();
protected:
	std::auto_ptr<Node>  child_;
};

class FunctionNode :public UnaryNode
{
public:
	FunctionNode(std::auto_ptr<Node>& child, PtrFun pFun)
		:UnaryNode(child), pFun_(pFun) {}
	double Calc()const;
private:
	PtrFun pFun_;
};

class UMinusNode :public UnaryNode
{
public:
	//UMinusNode(std::auto_ptr<Node>& child) :UnaryNode(child) {}
	UMinusNode(std::auto_ptr<Node> child) :UnaryNode(child) {}
	double Calc()const;
};

class MultipleNode :public Node
{
public:
	MultipleNode(std::auto_ptr<Node>& node)
	{
		AppendChild(node, true);
	}
	void AppendChild(std::auto_ptr<Node>& node, bool positive)
	{
		childs_.push_back(node.release());
		positives_.push_back(positive);
	}
	~MultipleNode();
protected:
	std::vector<Node*> childs_;
	std::vector<bool> positives_;
};

class SumNode :public MultipleNode
{
public:
	SumNode(std::auto_ptr<Node>& node)
		: MultipleNode(node) {}
	double Calc()const;
};

class ProductNode :public MultipleNode
{
public:
	ProductNode(std::auto_ptr<Node>& node)
		:MultipleNode(node) {}
	double Calc()const;
};

class VariableNode :public Node //变量结点，注意这个结点的实现
{
public:
	VariableNode(unsigned int id, Storage& storage)
		:id_(id), storage_(storage) {}
	double Calc()const;
	bool IsLvalue()const;
	void Assign(double val);	//注意这个函数，将值赋给变量
private:
	const unsigned int id_;
	Storage& storage_;
};

class AssignNode :public BinaryNode //赋值结点
{
public:
	AssignNode(std::auto_ptr<Node>& left, std::auto_ptr<Node>& right)
		:BinaryNode(left, right) 
	{
		//assert(left->IsLvalue());//断定左结点是左值
		assert(left_->IsLvalue());  //使用智能指针后，所有权转移至left_
	}
	double Calc()const;
};
#endif //_NODE_H_
