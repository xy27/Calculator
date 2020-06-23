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
	~NumberNode();
};

class BinaryNode :public Node
{
public:
	BinaryNode(std::unique_ptr<Node>& left, std::unique_ptr<Node>& right)
		:left_(left.release()), right_(right.release()) {}
	~BinaryNode();
//private:
protected:			//要知道这里为什么设置为protected
	//Node*const left_;
	//Node*const right_;
	std::unique_ptr<Node> left_;
	std::unique_ptr<Node> right_;
};

class UnaryNode :public Node
{
public:
	UnaryNode(std::unique_ptr<Node>& child) :child_(child.release()) {}
	~UnaryNode();
protected:
	std::unique_ptr<Node>  child_;
};

class FunctionNode :public UnaryNode
{
public:
	FunctionNode(std::unique_ptr<Node>& child, PtrFun pFun)
		:UnaryNode(child), pFun_(pFun) {}
	double Calc()const;
	~FunctionNode();
private:
	PtrFun pFun_;
};

class UMinusNode :public UnaryNode
{
public:
	//UMinusNode(std::auto_ptr<Node>& child) :UnaryNode(child) {}
	UMinusNode(std::unique_ptr<Node> child) :UnaryNode(child) {}
	double Calc()const;
	~UMinusNode();
};

class MultipleNode :public Node
{
public:
	MultipleNode(std::unique_ptr<Node>& node)
	{
		AppendChild(node, true);
	}
	void AppendChild(std::unique_ptr<Node>& node, bool positive)
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
	SumNode(std::unique_ptr<Node>& node)
		: MultipleNode(node) {}
	double Calc()const;
};

class ProductNode :public MultipleNode
{
public:
	ProductNode(std::unique_ptr<Node>& node)
		:MultipleNode(node) {}
	double Calc()const;
	~ProductNode();
};

class VariableNode :public Node //变量结点，注意这个结点的实现
{
public:
	VariableNode(unsigned int id, Storage& storage)
		:id_(id), storage_(storage) {}
	double Calc()const;
	bool IsLvalue()const;
	void Assign(double val);	//注意这个函数，将值赋给变量
	~VariableNode();
private:
	const unsigned int id_;
	Storage& storage_;
};

class AssignNode :public BinaryNode //赋值结点
{
public:
	AssignNode(std::unique_ptr<Node>& left, std::unique_ptr<Node>& right)
		:BinaryNode(left, right) 
	{
		//assert(left->IsLvalue());//断定左结点是左值
		assert(left_->IsLvalue());  //使用智能指针后，所有权转移至left_
	}
	double Calc()const;
	~AssignNode();
};
#endif //_NODE_H_
