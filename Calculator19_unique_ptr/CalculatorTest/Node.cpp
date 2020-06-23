#include<iostream>
#include "Node.h"



Node::Node()
{
	std::cout << "Node..." << std::endl;
}

Node::~Node()
{
	std::cout << "~Node..." << std::endl;
}

void Node::Calc()
{
	std::cout << "Node::Calc..." << std::endl;
}
