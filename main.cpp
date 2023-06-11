#include <iostream>
#include <ctime>
#include <algorithm>
#include <map>

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
			std::cout << "Node " << _data << " deleted.\n";
		}

		T GetData()
		{
			return _data;
		}

		void SetData(const T& data)
		{
			_data = data;
		}

		void ShowNode()
		{
			std::cout << _data << ' ';
		}


	private:
		T _data;
	};



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
	Node* _head = nullptr;
	size_t _size = 0;

};




int main()
{
	srand(time(NULL));
	List<int> list;
	for (size_t i = 0; i < 10; i++)
	{
		list.PushBack(rand() % 100);
	}
	std::cout << "Number of elements - " << list.GetSize() << std::endl;
	list.ShowList();
	list.Sort();
	list.ShowList();
	return 0;
}