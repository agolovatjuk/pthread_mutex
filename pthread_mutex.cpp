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
int counter = 0;
pthread_mutex_t mut;

void *helloMutex(void *args){

    pthread_mutex_lock(&mut);

    counter +=1;    
    cout << "Under Mutex...start:" << counter << endl;
//    for(int i=0; i<(0xFFFFFFFF);i++);
    sleep(5);
    cout << "Under Mutex...finished:" << counter << endl;

    pthread_mutex_unlock(&mut);
    
    pthread_exit(0);
}

/*
 * 
 */
int main(int argc, char** argv) {

    pthread_t thread1, thread2;
    int t1, t2;
    
    mut = PTHREAD_MUTEX_INITIALIZER;

    t1 = pthread_create(&thread1, NULL, helloMutex, NULL);
    t2 = pthread_create(&thread2, NULL, helloMutex, NULL);
    
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    
    cout << "Mutex hello!" << endl;
    return 0;
}

