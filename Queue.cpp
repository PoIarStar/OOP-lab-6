#pragma once

#include "Queue.h"

#include <stdexcept>

template<typename T>
size_t Queue<T>::last_index() {
    return (*this->first + *this->size - 1) % *this->capacity;
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
        if (*this->capacity < *other.size + 1) { // место под пустую ячейку
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
        *size = 1;
    }
    else if (get_size() == (*this->capacity - 1)) { // один элемент остаётся пустым во избежание наложения начала и конца итераторов
        // массив заполнен, перевыделяем память
        T* newArray = new T[*this->capacity * 2]; // увеличиваем размер вдвое просто потому что так было в примере

        int i = 0;
        for (T el : *this) {
            newArray[i++] = el;
        }
        *this->first = 0;
        *this->capacity = *this->capacity * 2;
        delete this->array;
        this->array = newArray;
        (*size)++;
        array[last_index()] = elem;
    }
    else // стандартный случай, есть место для вставки
        (*size)++;
        array[last_index()] = elem;
}

template<typename T>
void Queue<T>::dequeue() {
    if (isEmpty()) {
        throw std::out_of_range("Queue is empty");
    }
    --(*this->size);
    ++(*this->first);
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

template<typename T>
Queue<T>::QueueIterator::QueueIterator(T *p, T* arr_start, T* arr_end): p(p), arr_start(arr_start), arr_end(arr_end) {}

template<typename T>
Queue<T>::QueueIterator::QueueIterator(const QueueIterator &other): p(other.p), arr_start(other.arr_start), arr_end(other.arr_end) {}

template<typename T>
bool Queue<T>::QueueIterator::operator==(const QueueIterator &other) const {
    return p == other.p;
}

template<typename T>
bool Queue<T>::QueueIterator::operator!=(const QueueIterator &other) const {
    return p != other.p;
}

template<typename T>
typename Queue<T>::QueueIterator::reference Queue<T>::QueueIterator::operator*() const { // проверить p
    if (p != nullptr)
        return  *p;
    throw std::out_of_range("");
}

template<typename T>
typename Queue<T>::QueueIterator & Queue<T>::QueueIterator::operator++() {
    if (p == arr_end)
        p = arr_start;
    else
        p++;
    return *this;
}

template<typename T>
typename Queue<T>::iterator Queue<T>::begin() {
    return iterator(&this->array[*this->first], &this->array[0], &this->array[*capacity - 1]);
}

template<typename T>
typename Queue<T>::iterator Queue<T>::end() {
    return iterator(&this->array[this->last_index()] + 1, &this->array[0], &this->array[*capacity - 1]);
}

template<typename T>
typename Queue<T>::const_iterator Queue<T>::begin() const {
    return const_iterator(&this->array[*this->first], &this->array[0], &this->array[*capacity - 1]);
}

template<typename T>
typename Queue<T>::const_iterator Queue<T>::end() const {

    return const_iterator(&this->array[this->last_index()] + 1, &this->array[0], &this->array[*capacity - 1]);
}
