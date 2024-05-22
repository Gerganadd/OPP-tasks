#pragma once
const size_t DEFAULT_CAPACITY = 8;

template <typename T>
class Queue {
private:
	T* elements = nullptr;

	size_t size = 0;
	size_t capacity = DEFAULT_CAPACITY;

	size_t get = 0;
	size_t put = 0;

	void free();
	void copyFrom(const Queue<T>& other);
	void moveFrom(Queue<T>&& other);

	void resize(size_t newCapacity);

public:
	Queue();
	Queue(const Queue<T>& other);
	Queue(Queue<T>&& other);

	Queue<T>& operator=(const Queue<T>& other);
	Queue<T>& operator=(Queue<T>&& other);

	~Queue();

	void push(const T& object);
	void push(T&& object);

	void pop();

	const T& peek() const;

	size_t getSize() const;

	bool isEmpty() const;
};

template <typename T>
void Queue<T>::free() {
	delete[] elements;
	elements = nullptr;

	size = capacity = get = put = 0;
}

template <typename T>
void Queue<T>::copyFrom(const Queue<T>& other) {
	elements = new T[other.capacity]; // required function: default constructor

	for (size_t i = 0; i < other.capacity; i++) {
		elements[i] = other.elements[i]; // required function: operator=()
	}

	size = other.size;
	capacity = other.capacity;
	get = other.get;
	put = other.put;
}

template <typename T>
void Queue<T>::moveFrom(Queue<T>&& other) {
	elements = other.elements;
	other.elements = nullptr;

	size = other.size;
	other.size = 0;

	capacity = other.capacity;
	other.capacity = 0;

	get = other.get;
	other.get = 0;

	put = other.put;
	other.set = 0;
}

template <typename T>
void Queue<T>::resize(size_t newCapacity) {
	if (size > newCapacity) {
		throw std::invalid_argument("New capacity mush be bigger than size");
	}

	T* temp = new T[newCapacity];
	size_t index = 0;

	while (index < size) {
		temp[index] = elements[get];

		(++get) %= capacity;
		index++;
	}

	get = 0;
	put = size;
	capacity = newCapacity;

	delete[] elements;
	elements = temp;
}

template <typename T> 
Queue<T>::Queue() {
	elements = new T[capacity]; // required function: default constructor 
}

template <typename T>
Queue<T>::Queue(const Queue<T>& other) {
	copyFrom(other);
}

template <typename T>
Queue<T>::Queue(Queue<T>&& other) {
	moveFrom(std::move(other));
}

template <typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

template <typename T>
Queue<T>& Queue<T>::operator=(Queue<T>&& other) {
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

template <typename T>
Queue<T>::~Queue() {
	free();
}

template <typename T>
void Queue<T>::push(const T& object) {
	if (size >= capacity) {
		resize(size * 2);
	}

	elements[put++] = object; // required function: operator=()
	put %= capacity; // for circular queue

	size++;
}

template <typename T>
void Queue<T>::push(T&& object) {
	if (size >= capacity) {
		resize(size * 2);
	}

	elements[put++] = object; // required function: Move operator=()
	put %= capacity; // for circular queue

	size++;
}

template <typename T>
void Queue<T>::pop() {
	(++get) %= capacity;
	size--;

	if (DEFAULT_CAPACITY <= size && size <= capacity / 4) {
		resize(capacity / 2);
	}
}

template <typename T>
const T& Queue<T>::peek() const {
	return elements[get];
}

template <typename T>
size_t Queue<T>::getSize() const {
	return size;
}

template <typename T>
bool Queue<T>::isEmpty() const {
	return size == 0;
}