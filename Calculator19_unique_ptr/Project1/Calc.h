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
	Calc() :storage_(symTbl_),funTbl_(symTbl_) {}//symTbl_��������ٴ��ݸ�storage_
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
	SymbolTable symTbl_;  //�������������ʹ��ǰ������
	FunctionTable funTbl_;//�ȹ��캯�����������еĺ����ǹ̶���
	Storage storage_;//�ٹ�������������ǲ��̶���
	
};

#endif //_CALC_H_