// 1:: Funtion with int agru
#include <iostream>
#include <cstdlib>
#include <pthread.h>

using namespace std;

void *my_thread(void *arg){
    int * p = (int*) arg;
    for(int i=0; i<=*p; i++){
        cout << i << endl;
    }
    return arg;
}

int main(){
    pthread_t thread1;
    pthread_t thread2;
    int rc, n;
    int* p = &n;
    
    n = 10;
    rc = pthread_create(&thread1, NULL, my_thread, p);
    n = 20;
    rc = pthread_create(&thread2, NULL, my_thread, p);

    pthread_exit(NULL);
}