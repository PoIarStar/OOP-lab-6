#pragma once
#include <string>


template<typename T>
class Queue {
protected:
    T *array;
    std::size_t *capacity; //количество ячеек в массиве
    std::size_t *size; //количество значений в массиве
    std::size_t *first; //индекс первого значения

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


    //далее итератор, соответствующие поля и методы
    class QueueIterator : public std::iterator<std::input_iterator_tag, T> {
    protected:
        T *p;
        T *arr_start;
        T *arr_end;

    public:
        QueueIterator(T *p, T* arr_start, T* arr_end);

        QueueIterator(const QueueIterator &other);

        bool operator==(const QueueIterator &other) const;

        bool operator!=(const QueueIterator &other) const;

        typename QueueIterator::reference operator*() const;

        QueueIterator &operator++();
    };

    typedef QueueIterator iterator;
    typedef QueueIterator const_iterator;

    iterator begin();

    iterator end();

    const_iterator begin() const;

    const_iterator end() const;
};

#include "Queue.cpp"
