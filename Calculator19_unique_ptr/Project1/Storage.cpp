
#include<iostream>
#include<cmath>
#include<cassert>
#include"SymbolTable.h"
#include "Storage.h"



Storage::Storage(SymbolTable& tbl)
{
	AddConstants(tbl);
}

void Storage::Serialize(Serializer& out)const
{
	out << cells_.size();
	for (unsigned int i = 0; i < cells_.size(); ++i)
	{
		out << cells_[i] << inits_[i];
	}
}

void Storage::DeSerialize(DeSerializer& in)
{
	cells_.clear();
	inits_.clear();
	unsigned int size;
	in >> size;
	cells_.resize(size);
	inits_.resize(size);

	for (unsigned int i = 0; i < size; ++i)
	{
		double d;
		bool b;
		in >> d >> b;
		cells_[i] = d;
		inits_[i] = b;
	}
}

void Storage::Clear()
{
	cells_.clear();
	inits_.clear();
}

bool Storage::IsInit(unsigned int id) const
{
	return id<cells_.size()&&inits_[id];
}

void Storage::AddConstants(SymbolTable& tbl)
{
	unsigned int id = tbl.Add("e");
	AddValue(id, exp(1.0));
	std::cout << "e = " << exp(1.0) << std::endl;

	id = tbl.Add("pi");
	AddValue(id, 2.0*acos(0.0));
	std::cout << "pi = " << 2.0*acos(0.0) << std::endl;
}

double Storage::GetValue(unsigned int id)const
{
	assert(id < cells_.size());
	return cells_[id];
}

void Storage::SetValue(unsigned int id, double val)
{
	if (id < cells_.size())
	{
		cells_[id] = val;
		inits_[id] = true;
	}
	else /*if(id==cells_.size())*/		//这里有点问题
	{
		AddValue(id, val);
	}
}

void Storage::AddValue(unsigned int id, double val)
{
	cells_.resize(id + 1);
	inits_.resize(id + 1);
	cells_[id] = val;
	inits_[id] = true;
}

Storage::~Storage()
{
}
