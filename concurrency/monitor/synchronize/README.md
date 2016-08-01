Attempt to create Synchronize wrapper class which uses a mutex to synchronize calls to wrapped object

Used RAII, drilled down behaviour of -> operator

gcc version used 4.8.4

To compile
```
g++ -std=c++1y -pthread main.cpp
```
