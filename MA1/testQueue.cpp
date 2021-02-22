#include "testQueue.h"
#include "queue.h"

/*Test ID: Queue Size Check - QSC
 * Unit: queue::size()
 * Description: Test to determine if queue::size() returns the correct size of the queue object.
 * Test Steps:
 *      1. Construct an empty queue object
 *      2. Invoke queue::size()
 *      3. Conditionally evaluate the value returned by queue::size()
 * Test Data: size = 0
 * Precondition: queue object is empty
 * Postcondition: queue object is still empty
 * Expected result: queue is empty: 0 is returned
 * Actual result: queue is empty: 1 is returned
 * Status: failed
 */
void testSize(){
    queue testQueue;
    int result = testQueue.size();
    std::cout << "Size: " << result << std::endl;
    std::cout << "Test QSC: ";
    if (result == 0) std::cout << "passed\n";
    else std::cout << "failed\n";
}

/*Test ID: Queue is Empty Check - QEC
 * Unit: queue::isEmpty()
 * Description: test to determine if queue::isEmpty() returns true if the queue object is empty
 * Test Steps:
 *      1. Construct an empty queue object
 *      2. Invoke queue::isEmpty()
 *      3. Conditionally evaluate the value returned by queue::isEmpty()
 * Test Data: size = 0
 * Precondition: queue object is empty
 * Postcondition: queue object is still empty
 * Expected result: queue is empty: queue::size() == 0; true is returned
 * Actual result: queue is empty: queue::size() == 1; false is returned
 * Status: failed
 */
void testIsEmpty(){
    queue testQueue;
    bool result = testQueue.isEmpty();
    int size = testQueue.size();
    std::cout << "Size: " << size << std::endl;
    std::cout << "Empty: " << result << std::endl;
    std::cout << "Test QEC: ";
    if(result && size == 0) std::cout << "passed\n";
    else std::cout << "failed\n";
}

/*Test ID: Queue is Full Check - QFC
 * Unit: queue::isFull()
 * Description: test to determine if queue::isFull() returns true when the queue is full
 * Test Steps:
 *      1. Construct an empty queue object
 *      2. Use a loop to add new values to the object invoking queue::enqueue() until it is at max capacity
 *      3. Invoke queue::isFull()
 *      4. Conditionally evaluate the value returned by queue::isFull()
 * Test Data: array of {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, size = 10
 * Precondition: array is full
 * Postcondition: array is still full and all values remain unchanged
 * Expected result: array is full and unchanged: queue::size() == 0; true is returned
 * Actual result: array is full and unchanged: queue::size() == 11; true is returned
 * Status: failed
 */
void testIsFull(){
    queue testQueue;
    for(int i = 1; i <= SIZE; i++){
        testQueue.enqueue(i);
    }
    bool result = testQueue.isFull();
    int size = testQueue.size();
    std::cout << "Size: " << size << std::endl;
    std::cout << "Full: " << result << std::endl;
    std::cout << "Test QFC: ";
    if(result && size == SIZE) std::cout << "passed\n";
    else std::cout << "failed\n";
}

/*Test ID: Queue Dequeue Check Underflow - QDCU
 * Unit: queue::dequeue()
 * Description: test to determine if queue::dequeue() sends the correct underflow message the terminal when the
 *              queue object is empty.
 * Test Steps:
 *      1. Construct and empty queue object.
 *      2. Invoke queue::dequeue()
 *      3. Evaluate the console output
 * Test Data: size = 0
 * Precondition: queue is empty
 * Postcondition: queue is still empty
 * Expected result: queue is empty: queue::size() == 0; console reads "underflow"
 * Actual result: queue is empty: queue::size() == 0; console reads "Removing 0"
 * Status: failed
 */
void testDeQueueEmpty(){
    queue testQueue;
    testQueue.dequeue();
    int size = testQueue.size();
    std::cout << "Size: " << size << std::endl << "Test QDCU: ";
    if (size == 0) std::cout << "passed if above output reads \"underflow\"\n";
    else std::cout << "failed\n";
}

/*Test ID: Queue Dequeue check - QDC
 * Unit: queue::dequeue()
 * Description: test to determine if queue::dequeue() sends the correct removal message to the console
 *              when the queue is not empty, and removes one value from the queue.
 * Test Steps:
 *      1. Construct an empty queue object
 *      2. Invoke queue::enqueue() to add a value to the queue
 *      3. Invoke queue::dequeue()
 *      4. Evaluate the console output and the size of the queue object
 * Test Data: size = 1;
 * Precondition: the queue object is not empty
 * Postcondition: the queue object has one less value in it
 * Expected result: console output reads "removing 5"; queue::size() == 0;
 * Actual result: console output reads "removing 1"; queue::size() == 1;
 * Status: failed
 */
void testDeQueue(){
    queue testQueue;
    testQueue.enqueue(5);
    testQueue.dequeue();
    int size = testQueue.size();
    std::cout << "Size: " << size << std::endl << "Test QDC: ";
    if (size == 0)
        std::cout << "passed if above output reads \"removing 5\"\n";
    else std::cout << "failed\n";
}

/*Test ID: Queue Enqueue Check- QEC
 * Unit: queue::enqueue()
 * Description: test to determine that when the queue object is not full queue::enqueue() sends the correct inserting
 *              message to the console, and that a value is added to the queue.
 * Test Steps:
 *      1. Construct an empty queue object
 *      2. Invoke queue::enqueue()
 *      3. Evaluate the console output, queue size, and queue front value
 * Test Data: size = 0, add = 11
 * Precondition: the queue object is empty
 * Postcondition: the queue object has a size of 1
 * Expected result: size() == 1; peek() == 11; the console reads "inserting 11";
 * Actual result: size() == 2; peek() == 1; the console reads "inserting 11";
 * Status: failed
 */
void testEnQueueEmpty(){
    int add = 11;
    queue testQueue;
    testQueue.enqueue(add);
    int size = testQueue.size();
    int frontValue = testQueue.peek();
    std::cout << "Size: " << size << std::endl << "Front Value: " << frontValue << std::endl << "Test QEC: ";
    if (size == 1 && frontValue == add)
        std::cout << "passed if above output reads \"inserting 11\"\n";
    else std::cout << "failed\n";
}

/*Test ID: Queue Enqueue Check Overflow - QECO
 * Unit: queue::enqueue()
 * Description: test to determine that when the queue object is full that queue::enqueue() sends the correct overflow
 *              message to the console, and that a value is not added to the queue.
 * Test Steps:
 *      1. Construct an empty queue object
 *      2. Use a loop to add new values to the object invoking queue::enqueue() until it is at max capacity
 *      3. Invoke queue::enqueue()
 *      4. Evaluate the console output, queue::size() == 10, queue::peek() == 0
 * Test Data: array of {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, size = 10
 * Precondition: the queue object is full
 * Postcondition: the queue object is still full and unchanged
 * Expected result: the queue object is full: queue::size() == 10; queue::peek() == 1; the console reads "overflow"
 * Actual result: queue::size() == 11; queue::peek() == 10; the console reads "overflow"
 * Status: passed ********
 */
void testEnQueueFull(){
    int add = 11;
    queue testQueue;
    for(int i = 1; i <= SIZE; i++){
        testQueue.enqueue(i);
    }
    testQueue.enqueue(add);
    int size = testQueue.size();
    int frontValue = testQueue.peek();
    std::cout << "Size: " << size << std::endl << "Front Value: " << frontValue << std::endl << "Test QECO: ";
    if(size == SIZE && frontValue == 1)
        std::cout << "passed if above output reads \"Overflow\"\n";
    else std::cout << "failed\n";
}

/*Test ID: Queue Peek Check Empty - QPCE
 * Unit: queue::peek()
 * Description: test that when the queue object is empty queue::peek() returns the min int value and console reads
 *              correct underflow message
 * Test Steps:
 *      1. Construct an empty queue object.
 *      2. Invoke queue::peek().
 *      3. Conditionally evaluate the value returned by queue::peek().
 *      4. Evaluate the console output.
 * Test Data: size = 0
 * Precondition: the queue object is empty
 * Postcondition: the queue object is still empty
 * Expected result: the queue object is empty: queue::size() == 0; min int value is returned; console reads "underflow"
 * Actual result: the queue object is not empty: queue::size() == 1; 0 is returned no console "Underflow" message
 * Status: failed
 */
void testPeekEmpty(){
    queue testQueue;
    int result = testQueue.peek();
    int size = testQueue.size();
    std::cout << "Size: " << size << std::endl << "Return: " << result << std::endl << "Test QPCE: ";
    if(size == 0 && result == std::numeric_limits<int>::min())
        std::cout << "passed if above output reads \"Underflow\"\n";
    else std::cout << "failed\n";
}

/*Test ID: Queue Peek Check - QPC
 * Unit: queue::peek()
 * Description: test that when the queue object is not empty queue::peek() returns the front element of the queue
 * Test Steps:
 *      1. Construct an  empty queue object
 *      2. Invoke queue::enqueue()
 *      3. Invoke queue::peek()
 *      4. Conditionally evaluate the value returned by queue::peek() and the size of queue object
 * Test Data: int = 11, size = 1
 * Precondition: the queue object is not empty
 * Postcondition: the queue object is still not empty and remains unchanged
 * Expected result: the queue object is unchanged: queue::size() == 1; 11 is returned
 * Actual result: queue::size() == 2; 1 is returned
 * Status: failed
 */
void testPeek(){
    int add = 11;
    queue testQueue;
    testQueue.enqueue(add);
    int result = testQueue.peek();
    int size = testQueue.size();
    std::cout << "Size: " << size << std::endl << "Front Value: " << result << std::endl << "Test QPC: ";
    if (result == add && size == 1)
        std::cout << "passed\n";
    else std::cout << "failed\n";
}
