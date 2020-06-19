#ifndef _SCANNER_H_
#define _SCANNER_H_
#include<string>

enum EToken									//ɨ��״̬��־
{
	TOKEN_COMMAND,
	TOKEN_END,
	TOKEN_ERROR,
	TOKEN_NUMBER,
	TOKEN_PLUS,
	TOKEN_MINUS,
	TOKEN_MULTIPLY,
	TOKEN_DIVIDE,
	TOKEN_LPARENTHESIS,
	TOKEN_RPARENTHESIS,
	TOKEN_INDETIFIER,
	TOKEN_ASSIGN
};

class Scanner
{
public:
	//Scanner(const std::string& buf);
	explicit Scanner(std::istream& in);
	void Accept();						//��ȡһ����Ч�ַ�or������or��ʶ������������Ӧ״̬���ù��̺��Կհ��ַ�
	void AcceptCommand();
	bool IsEmpty()const;				//�жϱ��ʽ�Ƿ�Ϊ��
	bool IsDone()const;					//�жϱ��ʽ�Ƿ������
	bool IsCommand()const;				
	double Number()const;				//��ȡɨ�浽������
	std::string GetSymbol()const;		//��ȡɨ�赽�ı�ʶ��
	EToken Token()const;				//��ȡɨ��״̬��־
	~Scanner();
private:
	//void SkipWhite();
	void ReadChar();					//����������ȡ�ַ������Կհ��ַ�
	//const std::string buf_;
	std::istream& in_;					//��׼������
	int look_;							//��ǰ���������ַ�
	//unsigned int curpos_;
	std::string symbol_;				//ɨ�赽�ı�ʶ��
	EToken token_;						//ɨ��״̬��־
	double number_;						//ɨ�赽������
	bool isEmpty_;						//���ʽ�Ƿ�Ϊ�ձ�־
};
#endif //_SCANNER_H_
