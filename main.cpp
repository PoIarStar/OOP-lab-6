#include <iostream>
#include "Queue.h"

int main() {
    Queue<int> queue;
    std::cout << queue.toString() << std::endl;
    //std::cout << queue.peek() << std::endl; // первый элемент пустой очереди

    queue.enqueue(1);
    std::cout << queue.toString() << std::endl; // добавление

    queue.enqueue(2);
    queue.enqueue(3);
    std::cout << queue.toString() << std::endl; // добавление

    std::cout << queue.peek() << std::endl; // первый элемент

    queue.dequeue();
    queue.dequeue();
    std::cout << queue.peek() << std::endl;
    std::cout << queue.toString() << std::endl; // удаление


    queue.enqueue(4);
    std::cout << queue.toString() << std::endl; // добавление в очередь без начала

    queue.dequeue();
    queue.dequeue();
    queue.enqueue(5);
    std::cout << queue.toString() << std::endl; // добавление в пустую очередь

    queue.enqueue(6);
    queue.enqueue(7);


    std::cout << queue.toString() << std::endl;

    std::cout << *queue.end();
    std::cout << std::endl;
    for (const int iter : queue) { // демонстрация работоспособности итератора
        std::cout << iter << "\t";
    }
    std::cout << std::endl;

    queue.enqueue(1);

    queue.dequeue();
    queue.dequeue();
    queue.dequeue();

    queue.enqueue(2);
    queue.enqueue(3);
    queue.enqueue(4);
    queue.enqueue(5);
    queue.enqueue(6);
    queue.enqueue(7);
    std::cout << queue.toString() << std::endl; // массив заполнен
    queue.enqueue(8);
    std::cout << queue.toString() << std::endl; // добавление в начало
    queue.enqueue(9);
    std::cout << queue.toString() << std::endl; // очередь заполнена

    for (const int iter : queue) { // демонстрация работоспособности итератора
        std::cout << iter << "\t";
    }
    std::cout << std::endl;

    queue.enqueue(10);
    queue.enqueue(11);
    std::cout << queue.toString() << std::endl; // расширение массива и добавление

    for (const int iter : queue) { // демонстрация работоспособности итератора
        std::cout << iter << "\t";
    }
    std::cout << std::endl;

    int arr[4]{0, 0, 1, 2};
    Queue<int> queue2(arr, 4);
    std::cout << queue2.toString() << std::endl;
    queue2.dequeue();
    queue2.dequeue();

    Queue<int> queue3 = queue2;
    std::cout << queue3.toString() << std::endl; // оператор присваивания

    Queue<int> queue4(queue2);
    std::cout << queue4.toString() << std::endl; // оператор копирования

    queue.dequeue(); // чтобы начинал не сначала

    for (const int iter : queue) { // демонстрация работоспособности итератора
        std::cout << iter << "\t";
    }

    Queue<int> queue5 = queue;
    std::cout << queue5.toString() << std::endl;
    for (const int iter : queue5) { // демонстрация работоспособности итератора
        std::cout << iter << "\t";
    }

    return 0;
}