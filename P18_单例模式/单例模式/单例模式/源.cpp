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
		cout << "~Singleton..."<<endl;
	}
private:
	Singleton()
	{
		cout << "Singleton..."<<endl;
	}
	Singleton(const Singleton& other);
	Singleton& operator=(const Singleton& other);
	static Singleton* instance_;
};
	Singleton* Singleton::instance_=nullptr;

int main()
{
	//Singleton s1;
	//Singleton s2;
	Singleton* ps1 = Singleton::GetInstance();//静态成员函数的作用
	Singleton* ps2 = Singleton::GetInstance();

	//Singleton ps3(*ps1);		//调用拷贝构造函数
	//*ps2 = *ps1;


	Singleton::Free();
	return 0;
}