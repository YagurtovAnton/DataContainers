#include<iostream>
using namespace std;

#define tab "\t"
class Element
{
protected:
	int Data;		//�������� ��������
	Element* pNext;	//��������� �� ��������� �������
	static int count;
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		count++;
#ifdef DEBUG
		cout << "EConstructor:\t" << this << endl;
#endif // DEBUG
	}
	~Element()
	{
		count--;
#ifdef DEBUG
		cout << "EDestructor:\t" << this << endl;
#endif // DEBUG
	}
	friend class ForwardList;
};

int Element::count = 0;

class ForwardList
{
	Element* Head;
	unsigned int size;
public:
	ForwardList()
	{
		Head = nullptr; //����� ������ ����, ��� ������ ��������� �� 0
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(const ForwardList& other) :ForwardList()
	{
		/*for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);*/
		*this = other;	//����� ������ �������� CopyAssignment
		cout << "LCopyConstructor:" << this << endl;
	}
	~ForwardList()
	{
		while (Head)pop_front();
		pop_back();
		cout << "LDestructor:\t" << this << endl;
	}

	//				Operators:
	ForwardList& operator=(const ForwardList& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);
		cout << "LCopyAssignment:" << this << endl;
		return *this;
	}

	//				Adding elements:
	void push_front(int Data)
	{
		////1) ������� ����� �������:
		//Element* New = new Element(Data);
		////2) �������� ����� ������� � ������:
		//New->pNext = Head;
		////3) ��������� ������ �� ����� �������:
		//Head = New;

		Head = new Element(Data, Head);

		size++;
	}

	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		//1) ������� �� ����� ������:
		Element* Temp = Head;
		while (Temp->pNext)
		{
			Temp = Temp->pNext;
		}

		////2) ������� ����� �������:
		//Element* New = new Element(Data);
		////3) �������� ����� ������� � ������:
		//Temp->pNext = New;

		Temp->pNext = new Element(Data);

		size++;
	}
	void insert(int Data, int Index)
	{
		if (Index > Head->count)return;
		if (Index == 0)return push_front(Data);
		//1) ������� �� ������� ��������:
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;

		////2) ������� ����� �������:
		//Element* New = new Element(Data);
		////3) �������� ������� � ������:
		//New->pNext = Temp->pNext;
		//Temp->pNext = New;

		Temp->pNext = new Element(Data, Temp->pNext);

		size++;
	}

	//				Removing elements:
	void pop_front()
	{
		if (Head == nullptr)return;
		Element* erased = Head;	//1) ���������� ����� ���������� ��������
		Head = Head->pNext;		//2) ������� ������ �� ��������� ������� (��������� ������� �� ������)
		delete erased;			//3) ������� ������� �� ������
		size--;
	}
	void pop_back()
	{
		if (Head == nullptr || Head->pNext == nullptr)return pop_front();
		//1) ������� �� �������������� �������� ������:
		Element* Temp = Head;
		while (Temp->pNext->pNext)Temp = Temp->pNext;

		//2) ������� ��������� ������� �� ������:
		delete Temp->pNext;

		//3) �������� ��������� �� ��������� �������:
		Temp->pNext = nullptr;
		size--;
	}
	void erase(int Index)
	{
		if (Index >= size)return;
		if (Index == 0)return pop_front();

		//1) ������� �� ��������� ����� ���������:
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;

		//2) ���������� ����� ���������� ��������:
		Element* erased = Temp->pNext;

		//3) ��������� ��������� ������� �� ������:
		Temp->pNext = Temp->pNext->pNext;

		//4) ������� ������� �� ������:
		delete erased;

		size--;
	}

	//				Methods:
	void print()const
	{
		cout << "Head:\t" << Head << endl;
		/*Element* Temp = Head;	//Temp - ��� ��������.
		//�������� - ��� ���������, ��� ������ �������� ����� ���������� �������� ��������� ������.
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;	//������� �� ��������� �������
		}*/
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "���������� ��������� ������: " << size << endl;
		cout << "����� ���������� ��������� ������: " << Element::count << endl;
		//cout << "����� ���������� ��������� ������: " << Head->count << endl;
	}
};

//#define BASE_CHECK
//#define COUNT_CHECK

void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	//Element element(5);
	int n;
	cout << "������� ���������� ���������: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
		//list.push_front(rand() % 100);
	}
	list.print();
	//list.push_back(123);
	//list.print();
	//list.pop_back();
	//list.print();

	int index;
	int value;
	cout << "������� ������ ������ ��������: "; cin >> index;
	cout << "������� �������� ������ ��������: "; cin >> value;
	list.insert(value, index);
	list.print();

	cout << "������� ������ ���������� ��������: "; cin >> index;
	list.erase(index);
	list.print();

#endif // BASE_CHECK

#ifdef COUNT_CHECK
	ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);
	list1.print();

	ForwardList list2;
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);
	list2.print();
#endif // COUNT_CHECK

	int n;
	cout << "������� ���������� ���������: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
		//list.push_front(rand() % 100);
	}
	cout << "List filled" << endl;
	list.print();

	ForwardList list2 = list;	//CopyConstructor
	//ForwardList list2;
	//list2 = list;
	list2.print();
}