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
	
	NodePtr np2 = np;	//��ʱӦ�ý���Դת�ƣ�np�ͷ���Դ����Ȩ��np2�����Դ����Ȩ

	NodePtr np3;
	np3 = np2;
	return 0;
}