#pragma once

#include "Queue.h"

#include <stdexcept>

template<typename T>
size_t Queue<T>::last_index() {
    return *this->first + *this->size - 1;
}

template<typename T>
void Queue<T>::shift_to_left() {
    for (int i = 0; i < *this->size; i++) {
        this->array[i] = this->array[i + *first];
    }
    *this->first = 0;
}

template<typename T>
Queue<T>::Queue() {
    this->first = new std::size_t(0);
    this->capacity = new std::size_t(10);
    this->size = new std::size_t(0);
    this->array = new T[*capacity];
}

template<typename T>
Queue<T>::Queue(T *array, const size_t size) {
    this->first = new std::size_t(0);
    this->size = new std::size_t(size);
    this->capacity = new std::size_t(size > 10 ? size : 10);
    this->array = new T[*capacity];
    for (int i = 0; i < size; i++) {
        this->array[i] = array[i];
    }
}

template<typename T>
Queue<T>::Queue(const Queue<T> &other) : Queue() {
    *this = other;
}

template<typename T>
Queue<T>::~Queue() {
    delete this->array;
    delete this->size;
    delete this->capacity;
    delete this->first;
}

template<typename T>
Queue<T> &Queue<T>::operator=(const Queue &other) {
    if (this != &other) {
        if (*this->capacity < *other.size) {
            *this->capacity = *other.capacity;
            delete this->array;
            this->array = new T[*this->capacity];
        }
        for (int i = 0; i < *other.size; i++) {
            this->array[i] = other.array[i + *other.first];
        }
        *this->size = *other.size;
        *this->first = 0;
    }
    return *this;
}

template<typename T>
void Queue<T>::clear() {
    *first = 0;
    *this->size = 0;
}

template<typename T>
void Queue<T>::enqueue(T elem) {
    if (isEmpty()) {
        // самый крайний случай: очередь опустела
        *this->first = 0;
        this->array[0] = elem;
    }
    else if (last_index() == *this->capacity - 1 && *this->first > 0) {
        // места в конце нет, но можно сдвинуть к началу
        shift_to_left();
        this->array[last_index() + 1] = elem;
    }
    else if (last_index() == *this->capacity - 1) {
        // массив заполнен, перевыделяем память
        T* newArray = new T[*this->capacity * 2]; // увеличиваем размер вдвое просто потому что так было в примере
        for (int i = 0; i < *this->capacity; i++) {
            newArray[i] = this->array[i];
        }
        *this->capacity = *this->capacity * 2;
        delete this->array;
        this->array = newArray;
        array[last_index() + 1] = elem;
    }
    else // стандартный случай, есть место для вставки
        array[last_index() + 1] = elem;
    (*this->size)++;
}

template<typename T>
void Queue<T>::dequeue() {
    if (isEmpty()) {
        throw std::out_of_range("Queue is empty");
    }
    (*this->size)--;
    (*this->first)++;
}

template<typename T>
T Queue<T>::peek() const {
    if (isEmpty()) {
        throw std::out_of_range("Queue is empty");
    }
    return this->array[*this->first];
}

template<typename T>
bool Queue<T>::isEmpty() const {
    return *this->size == 0;
}

template<typename T>
size_t Queue<T>::get_size() const {
    return *this->size;
}

template<typename T>
std::string Queue<T>::toString() const {
    std::string result = "[";
    for (int i = 0; i < *this->capacity; i++) {
        result += std::to_string(this->array[i]) + ", ";
    }
    result += "]";
    return result;
}
