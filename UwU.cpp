#include <iostream> //library C++
#include <thread> //membuat thread
#include <chrono> //untuk mengatur durasi delay
#include <mutex> //untuk menjadikan 1 thread saja yang dapat mengakses objek bersamaan
#include <condition_variable> //menjadikan thread berjalan bergantian

using namespace std; //mamnggil namespace yang memiliki nama STD

mutex mu; //fungsi akses thread
condition_variable cond;
int a = 1;

void Odd()
{
    for (; ;)
    {
        unique_lock<mutex> locker(mu);
        cond.wait(locker, []() { return (a % 2 == 1); }); //mengunci thread yang sudah terisi
        cout << "Print Odd Number: " << a << endl; //mencetak nilai variabel
        this_thread::sleep_for(chrono::milliseconds(1000)); //pemberian jeda waktu 
        a++;
        locker.unlock(); //membuka thread yang masih kosong
        cond.notify_all(); //untuk meneruskan thread
    }
}

void Even()
{
    for (; ;)
    {
        unique_lock<mutex> locker(mu); //mengunci thread yang sudah terisi
        cond.wait(locker, []() { return (a % 2 == 0); });
        cout << "Print Even Number: " << a << endl; //mencetak nilai variabel
        this_thread::sleep_for(chrono::milliseconds(2500)); //pemberian jeda waktu 
        a++;
        locker.unlock(); //membuka thread yang masih kosong 
        cond.notify_all(); //untuk meneruskan thread
    }
}

int main()
{
    thread t1(Odd);
    thread t2(Even);
    t1.join();
    t2.join();
    return 0;
}\