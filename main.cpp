#include <iostream>
#include <ctime>
#include <algorithm>
#include <vector>
#include <string>
#include <cassert>
#include <set>

template <typename T>
class List
{
public:
	struct Node
	{
		Node() : _data(0), _next(nullptr) {}
		Node(T data) : _data(data), _next(nullptr) {}
		Node* _next;
		~Node()
		{
			//std::cout << "Node " << _data << " deleted.\n";
		}

		T GetData()
		{
			return _data;
		}

		T& Data()
		{
			return _data;
		}

		T* DataForSet()
		{
			return &_data;
		}

		void ShowNode()
		{
			std::cout << _data << ' ';
		}


	private:
		T _data;
	};

	List() : _head(nullptr), _size(0) {}

	List(const List& other) : _head(nullptr), _size(0) {
		for (auto cur = other._head; cur != nullptr; cur = cur->_next)
		{
			this->PushBack(cur->GetData());
		}
	}

	void PushBack(const T& data)
	{
		Node* newNode = new Node(data);
		if (_head == nullptr)
		{
			_head = newNode;
			_size++;
			return;
		}
		auto cur = _head;
		while (1)
		{
			if (cur->_next == nullptr)
			{
				cur->_next = newNode;
				break;
			}
			cur = cur->_next;
		}
		cur->_next = newNode;
		_size++;
		return;
	}

	void PopBack()
	{
		Node* cur = nullptr;
		for (int i = 0; i < _size - 1; ++i)
		{
			if (i == 0) {
				cur = _head;
				continue;
			}
			cur = cur->_next;
		}
		auto nodeToDelete = cur->_next;
		delete nodeToDelete;
		cur->_next = nullptr;
		--_size;
	}

	void PopFront()
	{
		auto nodeToDelete = _head;
		_head = _head->_next;
		delete nodeToDelete;
		--_size;
	}

	size_t GetSize()
	{
		return _size;
	}

	size_t GetCollectionSize()
	{
		size_t fullSize = 0;
		for (auto cur = this->_head; cur != nullptr; cur = cur->_next)
		{
			for (size_t i = 0; i < cur->Data().size(); ++i)
			{
				fullSize++;
			}
		}
		return fullSize;
	}

	size_t GetFullSize()
	{
		return _size + GetCollectionSize();
	}

	void PushFront(const T& data)
	{
		Node* newNode = new Node(data);
		if (_head == nullptr)
		{
			_head = newNode;
			_size++;
			return;
		}
		newNode->_next = _head;
		_head = newNode;
		_size++;
		return;
	}

	T* FindDataByIndex(size_t index)
	{
		auto cur = _head;
		for (size_t i = 0; i < _size; ++i)
		{
			if (i == index)
			{
				T tmp = cur->GetData();
				return &tmp;
			}
			cur = cur->_next;
		}
		return nullptr;
	}

	int FindIndexByData(const T& data)
	{
		int index = 0;
		for (auto cur = _head; cur != nullptr; cur = cur->_next)
		{
			if (cur->GetData() == data)
				return index;
			++index;
		}
		return -1;
	}

	void DeleteByIndex(int index)
	{
		if (index < 0 || index >= _size)
			return;
		if (index == 0)
		{
			PopFront();
			return;
		}
		else if (index == _size - 1)
		{
			PopBack();
			return;
		}
		Node* prevIndexElement = nullptr;
		Node* afterIndexElement = nullptr;
		Node* inIndexElement = nullptr;
		Node* cur = _head;
		for (int i = 0; i < _size; ++i)
		{
			if (i == index - 1)
			{
				prevIndexElement = cur;
			}
			else if (i == index)
			{
				inIndexElement = cur;
			}
			else if (i == index + 1)
			{
				afterIndexElement = cur;
				break;
			}
			cur = cur->_next;
		}
		prevIndexElement->_next = afterIndexElement;
		delete inIndexElement;
		--_size;
		return;
	}

	void DeleteByData(const T& data)
	{
		int index = FindIndexByData(data);
		DeleteByIndex(index);
		return;
	}

	void InsertByIndex(int index, const T& data)
	{
		if (index == 0)
		{
			PushFront(data);
			return;
		}
		else if (index == _size)
		{
			PushBack(data);
			return;
		}

		Node* prevElement = nullptr;
		Node* newElement = new Node(data);
		Node* cur = _head;
		for (int i = 1; i < index; ++i)
		{
			if (i == index - 1)
			{
				prevElement = cur;
			}

			cur = cur->_next;

		}
		prevElement->_next = newElement;
		newElement->_next = cur;
		++_size;
		return;
	}

	void ShowList()
	{
		for (auto it = _head; it != nullptr; it = it->_next)
		{
			it->ShowNode();
		}
		std::cout << std::endl;
	}

	void Sort()
	{
		Node** arr = new Node * [_size];
		Node* cur = _head;
		arr[0] = cur;
		//std::cout << cur->GetData() << ' ';
		for (int i = 1; i < _size; ++i)
		{
			cur = cur->_next;
			arr[i] = cur;
			//std::cout << arr[i]->GetData() << ' ';
		}
		T* mas = new T[_size];
		for (int i = 0; i < _size; ++i)
		{
			mas[i] = arr[i]->GetData();
		}
		std::sort(mas, mas + _size);
		for (int i = 0; i < _size; ++i)
		{
			arr[i]->SetData(mas[i]);
		}
		delete[] mas;
		std::cout << std::endl;
		delete[] arr;
	}

	List& operator+(const List& l) 
	{
		for (auto cur = l._head; cur != nullptr; cur = cur->_next)
		{
			this->PushBack(cur->GetData());
		}
		return *this;
	}

	List& operator=(const List& l)
	{
		for (auto cur = l._head; cur != nullptr; cur = cur->_next)
		{
			this->PushBack(cur->GetData());
		}
		return *this;
	}

	T& operator[](int index)
	{
		if (index < 0 || index >= this->_size)
		{
			exit(1);
		}
		auto cur = this->_head;
		for (size_t i = 0; i < _size; ++i)
		{
			if (i == index)
			{
				return cur->Data();
			}
			cur = cur->_next;
		}
		//return this->_head->Data();
	}

	~List()
	{
		auto cur = _head;
		while (cur)
		{
			cur = cur->_next;
			delete _head;
			_head = cur;
		}
		_size = 0;
	}

private:
	Node* _head;
	size_t _size;

};




int main()
{
	system("chcp 1251");
	srand(time(NULL));
	List<int> list;
	List<int> list1;
	int number = 0;
	for (size_t i = 0; i < 10; i++)
	{
		if (i == 9)
		{
			number = rand() % 100;
			list.PushBack(number);
		}
		else list.PushBack(rand() % 100);
	}
	list.ShowList();
	std::cout << list[9] << std::endl;
	assert(number == list[9]);						// проверка оператора перегрузки []
	std::cout << "Number of elements - " << list.GetSize() << std::endl;
	int number1 = 0;
	for (size_t i = 0; i < 5; i++)
	{
		if (i == 4)
		{
			number1 = rand() % 100;
			list.PushBack(number1);
		}
		else list.PushBack(rand() % 100);
	}
	list1.ShowList();
	std::cout << "Number of elements - " << list1.GetSize() << std::endl;
	List<int> list2;
	list2 = list + list1;
	list2.ShowList();
	std::cout << "Number of elements - " << list2.GetSize() << std::endl;
	// проверка правильности работы перегрузки оператора "+" списков
	assert(list2.GetSize() == 15);			// проверка длины итогового списка
	std::cout << "number = " << number << std::endl;
	std::cout << "list2[9] = " << list2[9] << std::endl;
	std::cout << "number1 = " << number1 << std::endl;
	std::cout << "list2[14] = " << list2[14] << std::endl;
	assert(number == list2[9]);				// проверка наличия элемента под индексом 9
	assert(number1 == list2[14]);			// проверка наличия элемента под индексом 14
	
	// Создано два списка для векторов и для строк. Метод GetCollectionSize() для 
	// этих коллекций работают т.к. эти коллекции имеют метод size()

	//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	
	List<std::vector<int>> listOfVectors;				// создание списка целочисленных векторов
	for (int i = 0; i < 5; i++)							
	{
		std::vector<int> vec;
		listOfVectors.PushBack(vec);					// вставка нового вектора в список
		for (int j = 0; j < 3; j++)
		{
			listOfVectors[i].push_back(rand() % 100);	// заполнение вставленного вектора
		}
	}

	for (int i = 0; i < listOfVectors.GetSize(); i++)		// вывод на экран содержимого списка целочисленных векторов
	{
		for (int j = 0; j < listOfVectors[i].size(); j++)
		{
			std::cout << listOfVectors[i].at(j) << ' ';
		}
		std::cout << std::endl;
	}
	std::cout << listOfVectors.GetFullSize() << std::endl;	// вывод размера списка с учётом содержимого векторов
	assert(listOfVectors.GetFullSize() == listOfVectors.GetCollectionSize() + listOfVectors.GetSize());				// проверка правильности работы метода GetFullSize()
	
	//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

	List<std::string> listOfStrings;						// создание списка объектов string
	for (int i = 0; i < 5; i++)
	{
		std::string str;
		std::cout << "Введите строку: ";
		std::getline(std::cin, str);
		listOfStrings.PushBack(str);						// добавление нового объекта string в список
	}
	std::cout << listOfStrings.GetFullSize() << std::endl;
	assert(listOfStrings.GetFullSize() == listOfStrings.GetCollectionSize() + listOfStrings.GetSize());
	listOfStrings.ShowList();

	//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

	List<std::set<int>> listOfSet;
	for (int i = 0; i < 5; i++)
	{
		std::set<int> s;
		listOfSet.PushBack(s);
		for (int j = 0; j < 3; j++)
		{
			listOfSet[i].insert(rand() % 100);	// заполнение вставленной коллекции
		}
	}
	

	// НЕ ПОЛУЧИЛОСЬ ВЫВЕСТИ НА ПЕЧАТЬ СОДЕРЖИМОЕ SET ЧЕРЕЗ ИТЕРАТОРЫ!

	for (int i = 0; i < listOfSet.GetSize(); i++)		// вывод на экран содержимого списка целочисленных векторов
	{
		for (auto it = listOfSet[i].begin(); it != listOfSet[i].end(); ++it)
		{
			std::cout << *it << ' ';
		}
		std::cout << std::endl;
	}
	
	std::cout << listOfSet.GetFullSize() << std::endl;
	assert(listOfSet.GetFullSize() == listOfSet.GetCollectionSize() + listOfSet.GetSize());

	return 0;
}