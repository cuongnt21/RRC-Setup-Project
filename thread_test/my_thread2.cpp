// 1:: Function without agru
// 2:: Function with char agru
// 3:: Call a method of a class
#include <iostream>
#include <cstdlib>
#include <pthread.h>
using namespace std;

void *hello(void *arg){
   cout << "Hello World"<< endl;
   pthread_exit(NULL);
}

void *sayName(void *arg){
    char* p = (char*) arg;
    cout << "My name is " << p << endl;
    return arg;
}

class obj{
private:
    char* p;
    int n;
public:
    obj(){
        this->p = (char*) "Cuong";
        this->n = 10;
    }

    obj(char* c){
        this->p = c;
        this->n = 10;
    }

    void callName(){
        cout << "Object's name is " << p << endl;
    }

    void display(){
        cout << n << endl;
    }
};

void* methodFun(void * arg){
    obj* p = (obj*) arg;
    p->callName();
    return arg;
}

int main()
{
   pthread_t thread1, thread2, thread3;

    obj* p;
    obj m;
    p = &m;
    // p->display();
   pthread_create(&thread1, NULL, hello, (char*) "Cuong");
   pthread_create(&thread2, NULL, sayName, (char*) "Cuong");
   pthread_create(&thread2, NULL, methodFun, (obj*) p);

   pthread_exit(NULL);
//    return 0;
}