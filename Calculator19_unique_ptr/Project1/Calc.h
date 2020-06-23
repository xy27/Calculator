#ifndef _CALC_H_
#define _CALC_H_
#include<string>
#include"SymbolTable.h"
#include"Storage.h"
#include"FunctionTable.h"
#include"Serial.h"



class Calc:public Serializable
{
	friend class Parser;
public:
	Calc() :storage_(symTbl_),funTbl_(symTbl_) {}//symTbl_构造完毕再传递给storage_
	~Calc();
	virtual void Serialize(Serializer& out)const;
	virtual void DeSerialize(DeSerializer& in);
	void ListFun()const;
	void ListVar()const;
	bool GetVariableValue(unsigned int id, double& val)const;
private:
	Storage& GetStorage()
	{
		return storage_;
	}
	bool IsFunction(unsigned int id)const
	{
		return id < funTbl_.Size();
	}
	PtrFun GetFunction(unsigned int id)const
	{
		return funTbl_.GetFunction(id);
	}
	unsigned int AddSymbol(const std::string& str);
	unsigned int FindSymbol(const std::string& str);
	SymbolTable symTbl_;  //定义了类对象不能使用前向声明
	FunctionTable funTbl_;//先构造函数表。函数表中的函数是固定的
	Storage storage_;//再构造变量表。变量是不固定的
	
};

#endif //_CALC_H_