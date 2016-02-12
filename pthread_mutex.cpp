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
    Два потока, ожидающих освобождения RW-блокировки (один должен ожидать чтения, другой - записи).

Текст программы должен находиться в файле /home/box/main.cpp
PID запущенного процесса должен быть сохранен в файле /home/box/main.pid
 */
#include <cstdlib>
#include <iostream>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    cout << "Mutex hello!" << endl;
    return 0;
}

