#ifndef _SYMBOL_TABLE_H_
#define _SYMBOL_TABLE_H_

#include<map>
#include<string>
#include"Serial.h"

class SymbolTable:public Serializable
{
public:
	enum { IDNOTFOUND = 0xffffffff };
	SymbolTable() :curId_(0) {}
	~SymbolTable();
	virtual void Serialize(Serializer& out)const;
	virtual void DeSerialize(DeSerializer& in);
	unsigned int Add(const std::string& str);
	unsigned int Find(const std::string& str)const;
	void Clear();
	std::string GetSymbolName(unsigned int id)const;//这个是自己写的，说不定有点问题
	unsigned int GetCurId()const { return curId_; }
private:
	std::map<const std::string, unsigned int> dictionary_;
	unsigned int curId_;
};
#endif// _SYMBOL_TABLE_H_
