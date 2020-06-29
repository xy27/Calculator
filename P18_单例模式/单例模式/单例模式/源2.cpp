#include<iostream>
using namespace std;


class Singleton
{
public:
	static Singleton& GetInstance()
	{
		static Singleton instance_;		//静态局部对象  静态局部对象只初始化一次
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
	Singleton& ps1 = Singleton::GetInstance();//静态成员函数的作用
	Singleton& ps2 = Singleton::GetInstance();

	//Singleton ps3(*ps1);		//调用拷贝构造函数
	//*ps2 = *ps1;


	//Singleton::Free();
	return 0;
}

//析构函数被调用   在return语句后