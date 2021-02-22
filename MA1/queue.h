#include <limits>
#include <iostream>

#ifndef MA1_DEBUGGING_QUEUE_H
#define MA1_DEBUGGING_QUEUE_H

// define default capacity of the queue
#define SIZE 10

// Class for queue
class queue
{
    int* arr;		// array to store queue elements
    int capacity;	// maximum capacity of the queue
    int front;		// front points to front element in the queue (if any)
    int rear;		// rear points to last element in the queue
    int count;		// current sizeFull of the queue

public:
    explicit queue(int size = SIZE); 	// constructor
    ~queue();   				// destructor

    void dequeue();
    void enqueue(int item);
    int peek();
    int size() const;
    bool isEmpty() const;
    bool isFull() const;
};

// Constructor to initialize queue
queue::queue(int size)
{
    arr = new int[size];
    capacity = size;
    front = 0;
    rear = -1;
    count = 0;
}

// Destructor to free memory allocated to the queue
queue::~queue()
{
    delete arr; // you are not required to test this function;
    // however, are there issues with it?
}

// Utility function to remove front element from the queue
void queue::dequeue()
{
    // check for queue underflow
    if (isEmpty())
    {
        std::cout << "UnderFlow\nProgram Terminated\n";
        return;
    }

    std::cout << "Removing " << arr[front] << '\n';

    front = (front + 1) % capacity;
    count--;
}

// Utility function to add an item to the queue
void queue::enqueue(int item)
{
    // check for queue overflow
    if (isFull())
    {
        std::cout << "OverFlow\nProgram Terminated\n";
        return;
    }

    std::cout << "Inserting " << item << '\n';

    rear = (rear + 1) % capacity;
    arr[rear] = item;
    count++;
}

// Utility function to return front element in the queue
int queue::peek()
{
    if (isEmpty())
    {
        std::cout << "UnderFlow\nProgram Terminated\n";
        return std::numeric_limits<int>::min();
    }
    return arr[front];
}

// Utility function to return the sizeFull of the queue
int queue::size() const
{
    return count;
}

// Utility function to check if the queue is empty or not
bool queue::isEmpty() const
{
    return (size()== 0);
}

// Utility function to check if the queue is full or not
bool queue::isFull() const
{
    return (size() == capacity);
}

#endif //MA1_DEBUGGING_QUEUE_H
