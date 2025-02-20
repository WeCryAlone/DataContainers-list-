#include "Element.h"
#include "ForwardList.h"
#include "Iterator.h"

template<typename T>Iterator<T> ForwardList<T>::getHead()
{
	return Head;
}
template<typename T>Iterator<T>ForwardList<T>::begin()
{
	return Head;
}
template<typename T>Iterator<T>ForwardList<T>::end()
{
	return nullptr;
}

template<typename T>ForwardList<T>::ForwardList()
{
	Head = nullptr;
	size = 0;
	cout << "LConstructor:\t" << this << endl;
}
template<typename T>ForwardList<T>::ForwardList(initializer_list<T> il) : ForwardList() // ������������� ������������ �� ���������
{
	// il - ��� ���������, ����� ��, ��� ��� ForwardList
	// � ������ ���������� ���� ������ begin() � end(),
	// ������� ���������� ��������� �� ������ � ����� ����������
	cout << typeid(il.begin()).name() << endl;
	for (T const* it = il.begin(); it != il.end(); it++)
	{
		// it - ��� ��������, ������� �������� �� il.
		push_back(*it);
	}
}
template<typename T>ForwardList<T>::ForwardList(const ForwardList<T>& other)
{
	Element* Temp = other.Head;
	while (Temp)
	{
		push_back(Temp->Data);
		Temp = Temp->pNext;
	}
	cout << "LCopyConstructor:" << this << endl;
}
template<typename T>ForwardList<T>::~ForwardList()
{
	while (Head)pop_front();
	cout << "LDestructor:\t" << this << endl;
}

// Operators
template<typename T>ForwardList<T>& ForwardList<T>::operator=(const ForwardList<T>& other)
{
	if (this == &other)return *this;
	while (Head)pop_front();
	Element<T>* Temp = other.Head;
	while (Temp)
	{
		push_back(Temp->Data);
		Temp = Temp->pNext;
	}
	cout << "LCopyAssignment:" << this << endl;
	return *this;
}

// Adding elements
template<typename T>void ForwardList<T>::push_front(T Data)
{
	/*Element* New = new Element(Data);
	New->pNext = Head;
	Head = New;*/
	Head = new Element<T>(Data, Head);
	size++;
}
template<typename T>void ForwardList<T>::push_back(T Data)
{
	// ���� ����� �� ����� �������� � ������ �������
	if (Head == nullptr)
	{
		push_front(Data);
		return;
	}

	//Element* New = new Element(Data);
	Element<T>* Temp = Head;
	while (Temp->pNext != nullptr)
	{
		Temp = Temp->pNext;
	}
	Temp->pNext = new Element<T>(Data);
	size++;
}
template<typename T>void ForwardList<T>::insert(T Data, T index)
{
	if (index == 0)
	{
		push_front(Data);
		return;
	}
	//Element* New = new Element(Data);
	Element<T>* Temp = Head;
	for (int i = 0; i < index - 1; i++, Temp = Temp->pNext)
		if (Temp->pNext == nullptr)break;
	//New->pNext = Temp->pNext;
	Temp->pNext = new Element<T>(Data, Temp->pNext);
	size++;
}

// Erasing elements
template<typename T>void ForwardList<T>::pop_front()
{
	// ������ ��� ��������� ������� �� ������, ����� ��������� ��� �����, ��� ���� ����� ����� ���� ���� ���
	Element<T>* Temp = Head;
	// ������� ������� �� ������
	Head = Head->pNext;
	// ������� ������� �� ������
	delete Temp;
	size--;
}
template<typename T>void ForwardList<T>::pop_back()
{
	Element<T>* Temp = Head;
	//Element* Temp2 = Head = Head->pNext;
	while (Temp->pNext != nullptr)
	{
		Temp = Temp->pNext;
		//Temp2 = Temp2->pNext;
		if (Temp->pNext->pNext == nullptr)
		{
			delete Temp->pNext;
			Temp->pNext = nullptr;
		}
	}
	size--;
}
template<typename T>void ForwardList<T>::erase(int index)
{
	if (index > size)return;
	if (index == 0)
	{
		pop_front();
		return;
	}

	// ������� �� ������� ��������
	Element<T>* Temp = Head;
	for (int i = 0; i < index; i++)
	{
		Temp = Temp->pNext;
	}
	// ���������� ����� ���������� ��������
	Element<T>* to_del = Temp->pNext;
	// ��������� ��������� ������� �� ������
	Temp->pNext = Temp->pNext->pNext;
	// ������� ������� �� ������
	delete to_del;
	size--;
}

// Methods
template<typename T>void ForwardList<T>::Print()
{
	/*Element* Temp = Head;
	while (Temp != nullptr)
	{
		cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		Temp = Temp->pNext;
	}*/
	//for(Element* Temp = Head; Temp; Temp = Temp->pNext)
	for (Iterator<T> Temp = Head; Temp != nullptr; Temp++)
		//cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		/*cout << Temp.get_current_address() << tab << Temp->Data << tab << Temp->pNext << endl;*/
		cout << *Temp << tab;
	cout << endl;
	cout << "���-�� ��������� � ������: " << size << endl;
	cout << "����� ���-�� ���������: " << Element<T>::count << endl;
}