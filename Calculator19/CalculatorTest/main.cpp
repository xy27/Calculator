#include<iostream>
using namespace std;

#include"DebugNew.h"
#include"Node.h"

int main()
{
	//int* p = new int;
	//delete p;

	//int *p2 = new int[10];
	//delete[]p2;
	
	
	NodePtr np(new Node);
	np->Calc();
	
	NodePtr np2 = np;	//这时应该将资源转移，np释放资源所有权，np2获得资源所有权

	NodePtr np3;
	np3 = np2;
	return 0;
}