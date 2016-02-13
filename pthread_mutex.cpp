/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   pthread_mutex.cpp
 * Author: golo
 *
 * Created on 13 февраля 2016 г., 0:46
 */

/*
 Напишите многопоточную программу (POSIX Threads).

Должны быть как минимум:

    Один поток, ожидающий освобождения мьютекса.
    Один поток, ожидающий освобождения спин-блокировки.
    Два потока, ожидающих освобождения RW-блокировки 
    (один должен ожидать чтения, другой - записи).

Текст программы должен находиться в файле /home/box/main.cpp
PID запущенного процесса должен быть сохранен в файле /home/box/main.pid
 */
#include <cstdlib>
#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;
int counter1 = 0;
int counter2 = 0;
pthread_mutex_t mLock;
pthread_spinlock_t sLock;

void *helloMutex(void *args){

    pthread_mutex_lock(&mLock);

    counter1 +=1;    
    cout << "Under Mutex...start:" << counter1 << endl;
//    for(int i=0; i<(0xFFFFFFFF);i++);
    sleep(5);
    cout << "Under Mutex...finished:" << counter1 << endl;

    pthread_mutex_unlock(&mLock);
    
    pthread_exit(0);
}

void *helloSpin(void *args){

    pthread_spin_lock(&sLock);

    counter2 +=1;    
    cout << "Under SpinLock...start:" << counter2 << endl;
//    for(int i=0; i<(0xFFFFFFFF);i++);
    sleep(2);
    cout << "Under SpinLock...finished:" << counter2 << endl;

    pthread_spin_unlock(&sLock);
    
    pthread_exit(0);
}

/*
 * 
 */
int main(int argc, char** argv) {

    pthread_t thread1, thread2; // array of threads better
    pthread_t thread3, thread4; // array of threads better
    int t1, t2, t3, t4, err1;
    
    mLock = PTHREAD_MUTEX_INITIALIZER;
//    err1 = pthread_mutex_init(&mLock, NULL);
    err1 = pthread_spin_init(&sLock, PTHREAD_PROCESS_PRIVATE);
            
    t1 = pthread_create(&thread1, NULL, helloMutex, NULL);
    t2 = pthread_create(&thread2, NULL, helloMutex, NULL);
    
    t3 = pthread_create(&thread3, NULL, helloSpin, NULL);
    t4 = pthread_create(&thread4, NULL, helloSpin, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    pthread_join(thread3, NULL);
    pthread_join(thread4, NULL);
    
    cout << "Mutex hello!" << endl;
    pthread_mutex_destroy(&mLock);
    pthread_spin_destroy(&sLock);
    
    return 0;
}

