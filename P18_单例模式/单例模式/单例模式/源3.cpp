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

	static Singleton& GetInstance()	//必须返回引用
	{
		if (instance_.get() == nullptr)		//只实例化一个对象
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

//类型     变量名		初始值
shared_ptr<Singleton> Singleton::instance_;		//利用了智能指针自动释放其管理的资源的特性
												//也可以用auto_ptr、shared_ptr

int main()
{
	//Singleton s1;
	//Singleton s2;
	Singleton& ps1 = Singleton::GetInstance();//静态成员函数的作用
	Singleton& ps2 = Singleton::GetInstance();//这里必须定义为引用类型
	Singleton& ps3 = Singleton::GetInstance();

	//Singleton ps3(*ps1);		//调用拷贝构造函数
	//*ps2 = *ps1;


	//Singleton::Free();
	return 0;
}