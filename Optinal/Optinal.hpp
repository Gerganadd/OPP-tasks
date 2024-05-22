#pragma once
#include <iostream>

template <typename T> 
class Optinal {
private:
	T* data = nullptr;

	void free();
	void copyFrom(const Optinal<T>& other);
	void moveFrom(Optinal<T>&& other);

public:
	Optinal() = default;
	Optinal(const T& data);
	Optinal(T&& data);

	Optinal(const Optinal<T>& other);
	Optinal(Optinal<T>&& other);

	Optinal<T>& operator=(const Optinal<T>& other);
	Optinal<T>& operator=(Optinal<T>&& other);

	~Optinal<T>();

	void set(const T& data);
	void set(T&& data);

	const T& operator*() const; // getter
	T& operator*(); // getter

	explicit operator bool() const;

	const T* operator->() const;
	T* operator->();
};

template<typename T>
Optinal<T>::operator bool() const {
	return data != nullptr;
}

template<typename T>
void Optinal<T>::free() {
	delete data;
	data = nullptr;
}

template<typename T>
void Optinal<T>::copyFrom(const Optinal<T>& other) {
	data = other.data;
}

template<typename T>
void Optinal<T>::moveFrom(Optinal<T>&& other) {
	data = std::move(other.data);
}

template<typename T>
Optinal<T>::Optinal(const T& data){
	this->data = new T(data);
}

template<typename T>
Optinal<T>::Optinal(T&& data) {
	this->data = new T(std::move(data));
}

template<typename T>
Optinal<T>::Optinal(const Optinal<T>& other) {
	copyFrom(other);
}

template<typename T>
Optinal<T>::Optinal(Optinal<T>&& other) {
	moveFrom(std::move(other));
}

template<typename T>
Optinal<T>& Optinal<T>::operator=(const Optinal<T>& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

template<typename T>
Optinal<T>& Optinal<T>::operator=(Optinal<T>&& other) {
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

template<typename T>
Optinal<T>::~Optinal<T>() {
	free();
}

template<typename T>
void Optinal<T>::set(const T& data) {
	if (*this) { // OP=
		(*this->data) = data;
	}
	else { // CC()
		this->data = new T(data);
	}
}

template<typename T>
void Optinal<T>::set(T&& data) {
	if (*this) { // MOP=
		(*this->data) = std::move(data);
	}
	else { // MC()
		this->data = new T(std::move(data));
	}
}

template<typename T>
const T& Optinal<T>::operator*() const {
	return *data;
}

template<typename T>
T& Optinal<T>::operator*() {
	return *data;
}

template<typename T>
const T* Optinal<T>::operator->() const {
	return data;
}

template<typename T>
T* Optinal<T>::operator->() {
	return data;
}