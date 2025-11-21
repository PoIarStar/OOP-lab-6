#pragma once
#include <string>


template<typename T>
class Queue {
protected:
    T *array;
    std::size_t* capacity; //количество ячеек в массиве
    std::size_t* size; //количество значений в массиве
    std::size_t* first; //индекс первого значения

    size_t last_index();
    void shift_to_left();
public:
    Queue();

    Queue(T *array, size_t size);

    Queue(const Queue<T> &other);

    ~Queue();

    Queue &operator=(const Queue &other);

    void clear();

    void enqueue(T elem);

    void dequeue();

    T peek() const;

    [[nodiscard]] bool isEmpty() const;

    [[nodiscard]] size_t get_size() const;

    // функция только для отладки и демонстрации работоспособности
    [[nodiscard]] std::string toString() const;
};

#include "Queue.cpp"