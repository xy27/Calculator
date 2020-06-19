#ifndef _TRACER_H_
#define _TRACER_H_
#include<map>

void* operator new(size_t size, const char* file, unsigned int line);
void operator delete(void* p, const char*, unsigned int);//���Ӧ�ò��ᱻ����
//
void* operator new(size_t size);	//���������������޵ݹ飬stack overflow
void operator delete(void* p);
//
void* operator new[](size_t size);//���Ӧ�ò��ᱻ����
void operator delete[](void* p);
//
void* operator new[](size_t size, const char* file, unsigned int line);
void operator delete[](void* p, const char*, unsigned int);//���Ӧ�ò��ᱻ����


class Tracer
{
private:
	class Entry
	{
	public:
		Entry(const char* file = 0, long line = 0)
			:file_(file), line_(line) {}
		const char* File()const { return file_; }
		long Line()const { return line_; }
	private:
		const char* file_;
		long line_;
	};

	class Lock
	{
	public:
		Lock(Tracer& tracer) :tracer_(tracer) 
		{
			tracer_.lock();
		}
		~Lock()
		{
			tracer_.unlock();
		}
	private:
		Tracer& tracer_;
	};

public:
	Tracer();
	~Tracer();

	void Add(void* p, const char* file, long line);
	void Remove(void*);
	void Dump(); 
	static bool Ready;
private:
	//static bool Ready;
	std::map<void*, Entry> mapEntry_;
	int lockCount_;
	void lock() { ++lockCount_; }
	void unlock() { --lockCount_; }
	
};

extern Tracer NewTrace;
#endif //_TRACER_H
