# AppGuard Interview Question

## Description:
Write a multithreaded program that:
1. Generates N random integers between 0-9
2. Counts how many times each integer was repeated
The program shall use:
1. A queue of max 10 elements to store the integers
2. A tracking array of exactly 10 elements to store the repetition counts. The array index
corresponds to the numbers 0-9.
What you need to do:
- Use C/C++ language.
- Create 4 threads.
- Threads #1 and #2 generate a total of N random integers between 0-9 and put them into
the queue with a maximum size of 10 elements. If the queue is full - the threads wait.
- Threads #3 and #4 read from the queue and increment the array value at the
corresponding index. If the queue is empty - the threads wait.
- When all N numbers are generated and counted, the threads must exit gracefully and
the program then outputs the resulting tracking array.
- You may use any editor/compiler of your choice. We prefer if Visual Studio is used but
anything that gets the job done is acceptable.
What we are looking for (in order of importance):

1. Correct multithreading synchronization:
a. We will examine your choice of synchronization primitives
b. How you use these primitives to achieve the best performance.
2. Clean readable code
3. Comments

Example:
Input (N=7): [1,2,1,2,2,9,0] (7 randomly generated numbers between 0-9)
Output: [1, 2, 3, 0, 0, 0, 0, 0, 0 , 1] (resulting 'count' array)
