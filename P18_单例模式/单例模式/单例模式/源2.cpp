#include<iostream>
using namespace std;


class Singleton
{
public:
	static Singleton& GetInstance()
	{
		static Singleton instance_;		//��̬�ֲ�����  ��̬�ֲ�����ֻ��ʼ��һ��
		return instance_;
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

};

int main()
{
	//Singleton s1;
	//Singleton s2;
	Singleton& ps1 = Singleton::GetInstance();//��̬��Ա����������
	Singleton& ps2 = Singleton::GetInstance();

	//Singleton ps3(*ps1);		//���ÿ������캯��
	//*ps2 = *ps1;


	//Singleton::Free();
	return 0;
}

//��������������   ��return����