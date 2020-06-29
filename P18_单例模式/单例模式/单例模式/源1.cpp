#include<iostream>
using namespace std;


class Singleton
{
public:
	static Singleton* GetInstance()
	{
		if (instance_ == nullptr)
		{
			instance_ = new Singleton;
		}
		return instance_;
	}

	static void Free()
	{
		if (instance_)
		{
			delete instance_;
		}
	}

	~Singleton()
	{
		cout << "~Singleton..." << endl;
	}

	class Garbo
	{
	public:
		~Garbo()
		{
			if (Singleton::instance_)
			{
				delete instance_;
			}
		}
	};

private:
	Singleton()
	{
		cout << "Singleton..." << endl;
	}
	Singleton(const Singleton& other);
	Singleton& operator=(const Singleton& other);
	static Singleton* instance_;

	static Garbo garbo_;		//���ö����ȷ��������������garbo_����ɾ�̬�ıȽϷ���
};

//����     ������		��ʼֵ
Singleton* Singleton::instance_ = nullptr;
Singleton::Garbo Singleton::garbo_; 

int main()
{
	//Singleton s1;
	//Singleton s2;
	Singleton* ps1 = Singleton::GetInstance();//��̬��Ա����������
	Singleton* ps2 = Singleton::GetInstance();

	//Singleton ps3(*ps1);		//���ÿ������캯��
	//*ps2 = *ps1;


	//Singleton::Free();
	return 0;
}