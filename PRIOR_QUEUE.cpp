
#include <algorithm>
#include <vector>
#include <iostream>

template<typename T, typename Container>
class priority_queue {
	Container _container;

	/**
	 * Возвращает индекс левого ребёнка по индексу родителя
	 * 2*i + 1
	 */
	int _leftChildIndex(int parentIndex);

	/**
	 * Возвращает индекс правого ребёнка по индексу родителя
	 * 2*i + 2
	 */
	int _rightChildIndex(int parentIndex);

	/**
	 * Возвращает индекс родителя по индексу ребёнка
	 * (int)(0.5 * i + 0.5) - 1
	 */
	int _parentIndex(int childIndex);

	/**
	 * "Просеивание" вверх
	 */
	void _siftUp(int index);

	/**
	 * "Просеивание" вниз
	 */
	void _siftDown(int index);

public:
	/**
	 * Добавление элемента в очередь
	 * Реализуется через siftUp
	 */
	void push(const T& a) {

		_container.push_back(a);
		_siftUp(_container.size() - 1);

	}

	/**
	 * Возвращает верхний элемент очереди,
	 * НЕ удаляя его
	 *
	 * Возвращает первый элемент
	 */
	T top() const {
		return _container[0];
	}

	/**
	 * Возвращает верхний элемент очереди,
	 * удаляя его
	 *
	 * Возвращает первый элемент, удаляет его, делает siftDown
	 */
	T pop() {

		std::swap(_container[0], _container[_container.size() - 1]);
		T temp = _container[_container.size() - 1];
		_container.pop_back();
		_siftDown(0);
		return temp;

	}

	/**
	 * Проверяет, пустая очередь или нет
	 */
	bool empty() const {
		return (_container.size() == 0);
	}
};


template<typename T, typename Container>
inline int priority_queue<T, Container>::_leftChildIndex(int parentIndex)
{
	return(parentIndex * 2 + 1);
}

template<typename T, typename Container>
inline int priority_queue<T, Container>::_rightChildIndex(int parentIndex)
{
	return(parentIndex * 2 + 2);
}

template<typename T, typename Container>
inline int priority_queue<T, Container>::_parentIndex(int childIndex)
{
	return ((childIndex * 0.5 + 0.5) - 1);
}

template<typename T, typename Container>
inline void priority_queue<T, Container>::_siftUp(int index)
{

	if (index == 0) {
		return;
	}

	while (_container[index] > _container[_parentIndex(index)]) {
		std::swap(_container[index], _container[_parentIndex(index)]);
		index = _parentIndex(index);
	}

}

template<typename T, typename Container>
inline void priority_queue<T, Container>::_siftDown(int index)
{
	while (((_container[index] < _container[_leftChildIndex(index)])
		|| (_container[index] < _container[_rightChildIndex(index)]))
		&& (_rightChildIndex(index) < _container.size()))
	{
		if (_container[index] < _container[_leftChildIndex(index)]) {
			std::swap(_container[index], _container[_leftChildIndex(index)]);
		}
		else if (_container[index] < _container[_rightChildIndex(index)]) {
			std::swap(_container[index], _container[_rightChildIndex(index)]);
		}
	}
}


int main() {
	priority_queue<int, std::vector<int> > q;
	q.push(45);
	q.push(11);
	q.push(12);
	q.push(7);
	q.push(100);

	std::cout << q.top() << " "; // == 100
	std::cout << q.pop() << " "; // == 100
	std::cout << q.empty() << std::endl;

	while (!q.empty())
		std::cout << q.pop() << " ";
}