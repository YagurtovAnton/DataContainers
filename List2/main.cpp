#include<iostream>
using namespace std;

#define tab "\t"
#define delimiter "\n-------------------------------------------------\n"

class List
{
	class Elemert
	{
		int Data;
		Elemert* pNext;
		Elemert* pPrev;
	public:
		Elemert(int Data, Elemert* pNext = nullptr, Elemert* pPrev = nullptr)
			:Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Elemert()
		{
			cout << "EDestructor:\t" << this << endl;
		}
		friend class List;
	}*Head, * Tail;
	size_t size;
};
	

void main()
{
	setlocale(LC_ALL, "");
}