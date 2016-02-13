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
int counter3 = 0;
pthread_mutex_t mLock;
pthread_spinlock_t sLock;
pthread_rwlock_t   rwLock;

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
    sleep(2);
    cout << "Under SpinLock...finished:" << counter2 << endl;
    pthread_spin_unlock(&sLock);
    
    pthread_exit(0);
}

void *helloRead(void *args){

    pthread_rwlock_rdlock(&rwLock);

    cout << "Under ReadLock...start:" << counter3 << endl;
    sleep(3);
    cout << "Under ReadLock...finished:" << counter3 << endl;
    pthread_rwlock_unlock(&rwLock);
    
    pthread_exit(0);
}

void *helloWrite(void *args){

    pthread_rwlock_wrlock(&rwLock);

    counter3 +=1;    
    cout << "Under WriteLock...start:" << counter3 << endl;
    sleep(5);
    cout << "Under WriteLock...finished:" << counter3 << endl;
    pthread_rwlock_unlock(&rwLock);
    
    pthread_exit(0);
}

/*
 * 
 */
int main(int argc, char** argv) {

//    cout << "Mutex hello!" << endl;

    pthread_t thread1, thread2; // array of threads better
    pthread_t thread3, thread4; // array of threads better
    pthread_t thread5, thread6; // array of threads better
//    pthread_t thread7, thread8; // array of threads better
    int t1, t2, t3, t4, t5, t6, t7, t8, err1;
    
    mLock = PTHREAD_MUTEX_INITIALIZER;
//    err1 = pthread_mutex_init(&mLock, NULL);
    err1 = pthread_spin_init(&sLock, PTHREAD_PROCESS_PRIVATE);
   
    rwLock = PTHREAD_RWLOCK_INITIALIZER;
    
    t1 = pthread_create(&thread1, NULL, helloMutex, NULL);
//    t2 = pthread_create(&thread2, NULL, helloMutex, NULL);
    
    t3 = pthread_create(&thread3, NULL, helloSpin, NULL);
//    t4 = pthread_create(&thread4, NULL, helloSpin, NULL);

    t5 = pthread_create(&thread5, NULL, helloRead, NULL);
    t6 = pthread_create(&thread6, NULL, helloWrite, NULL);
//    t7 = pthread_create(&thread7, NULL, helloRead, NULL);
//    t8 = pthread_create(&thread8, NULL, helloRead, NULL);

    pthread_join(thread1, NULL);
//    pthread_join(thread2, NULL);

    pthread_join(thread3, NULL);
//    pthread_join(thread4, NULL);

    pthread_join(thread5, NULL);
    pthread_join(thread6, NULL);
//    pthread_join(thread7, NULL);
//    pthread_join(thread8, NULL);

    pthread_mutex_destroy(&mLock);
    pthread_spin_destroy(&sLock);
    pthread_rwlock_destroy(&rwLock);
    
    return 0;
}

