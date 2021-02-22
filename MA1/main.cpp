#include <iostream>
#include "testQueue.h"

using namespace std;

/*  Poor attributes
 *  1. File Structure   - Storing the queue class Definitions in the header file is only acceptable when the class is a
 *                        template and they should be stored in a .cpp file instead.
 *  2. Class Name       - Class names should always start with a capital letter to easily identify that it is an object.
 *  3. Array            - The use of an array is a poor choice for a queue because it limits the capacity, but doesn't
 *                        offer increased speed over a linked list with the functions that queues use. Linked lists
 *                        have no capacity limit. Plus if you were to have the array large, even if the queue is empty
 *                        it still uses all the memory of the large array while a linked list only uses the memory needed
 *                        for objects already in the queue.
 *  4. delete           - Although it doesn't throw errors, delete should be delete[] because it is an array, without
 *                        the [] a memory leak will occur.
 *  5. SIZE             - Having Size be a global variable allows it to be accessed and changed anywhere throughout the
 *                        program. If you want a size that can't be changed then it could just be set by the constructor
 *                        by default, otherwise the constructor could require a size input to be passed so that
 *                        the size is optional. Or even make two separate constructors for the two cases.
 * */
void line(const string& code) {
    cout << "---------------------------------------------------------------------------\n";
    cout << "\t\tTest " << code << endl;
}

// main function
int main()
{
    line("QSC");
    testSize();
    line("QEC");
    testIsEmpty();
    line("QFC");
    testIsFull();
    line("QDCU");
    testDeQueueEmpty();
    line("QDC");
    testDeQueue();
    line("QEC");
    testEnQueueEmpty();
    line("QECO");
    testEnQueueFull();
    line("QPCE");
    testPeekEmpty();
    line("QPC");
    testPeek();

    return 0;
}
