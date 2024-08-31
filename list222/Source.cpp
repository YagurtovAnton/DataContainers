#include<iostream>
using namespace std;

#define tab "\t"
#define delimiter "\n--------------------------------\n"

class List
{
public:
	class Element
	{
		int Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr)
			:Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		friend class List;
	}*Head, *Tail;
	size_t size;
};

void main()
{
	cout << "NULLPTR" << endl;
	setlocale(LC_ALL, "");
	List list;
}