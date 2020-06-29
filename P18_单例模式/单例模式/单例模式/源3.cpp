#include<iostream>
#include<memory>
using namespace std;


class Singleton
{
public:
	//static shared_ptr<Singleton> GetInstance()
	//{
	//	if (instance_ .get()== nullptr)
	//	{
	//		instance_.reset(new Singleton);
	//	}
	//	return instance_;
	//}

	static Singleton& GetInstance()	//���뷵������
	{
		if (instance_.get() == nullptr)		//ֻʵ����һ������
		{
			instance_.reset(new Singleton);
		}
		return *instance_;
	}


	~Singleton()
	{
		cout << "~Singleton..." << endl;
	}

private:
	Singleton()
	{
		cout << "Singleton..." << endl;
	}
	Singleton(const Singleton& other);
	Singleton& operator=(const Singleton& other);
	static shared_ptr<Singleton> instance_;

};

//����     ������		��ʼֵ
shared_ptr<Singleton> Singleton::instance_;		//����������ָ���Զ��ͷ���������Դ������
												//Ҳ������auto_ptr��shared_ptr

int main()
{
	//Singleton s1;
	//Singleton s2;
	Singleton& ps1 = Singleton::GetInstance();//��̬��Ա����������
	Singleton& ps2 = Singleton::GetInstance();//������붨��Ϊ��������
	Singleton& ps3 = Singleton::GetInstance();

	//Singleton ps3(*ps1);		//���ÿ������캯��
	//*ps2 = *ps1;


	//Singleton::Free();
	return 0;
}