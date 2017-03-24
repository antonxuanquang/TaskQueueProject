# TaskQueueProject

This program illustrate threads synchronization is an Operating System. The main thread begins by initializing a user-specific number of threads. The main thread, then, generate a random of linked list operations and add these tasks to a task queue. Threads need to wait and will be signaled by the main thread to wake up and consume linked list operations. When there is no task in the task queue, main thread should do a global signaling to wake up all sleeping threads and finish the program.

Compile
```
make
```

Run: ./taskQueue <number of threads> <number of tasks>
```
./taskQueue 3 1000
```