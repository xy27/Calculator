#ifndef _NODE_H_
#define _NODE_H_

class Node
{
public:
	Node();
	~Node();
	void Calc();
};

class NodePtr
{
public:
	NodePtr(Node* ptr = nullptr)
		:ptr_(ptr) {}
	~NodePtr() { delete ptr_; }
	NodePtr(/*const*/ NodePtr& other)
		:ptr_(other.Release()) {}
	NodePtr& operator=(/*const*/ NodePtr& other)
	{
		Reset(other.Release());
		return *this;
	}
	Node& operator*()const { return *Get(); }	//重载*运算符
	Node* operator->()const { return Get(); }  //重载->运算符
	Node* Get()const { return ptr_; }
	Node* Release()
	{
		Node* tmp = ptr_;
		ptr_ = nullptr;
		return tmp;
	}
	void Reset(Node* ptr)
	{
		if (ptr_ != ptr)
		{
			delete ptr_;
		}
		ptr_ = ptr;
	}
private:
	Node* ptr_;
};

#endif //_NODE_H_