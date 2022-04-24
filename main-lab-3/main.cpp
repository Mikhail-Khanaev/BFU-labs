#include <iostream>
#include <algorithm>
#include <stdio.h> 
#include <time.h> 
#include <chrono>
#define N_Max 100000
#pragma comment(linker, "/STACK:100000000000")

// Вариант 2 Ханаев Михаил
// Лабораторная работа N3 "Бинарный поиск и бисекция"

void ShowArray(int mas[]) {
    for (int i = 0; i < 100; i++) {
        std::cout << mas[i] << std::endl;
    }
}

void QuickSort(int mas[N_Max], int size) {
    //Указатели в начало и в конец массива
    int i = 0;
    int j = size - 1;

    // Центральный элемент массива
    int mid = mas[size / 2];

    //Делим массив
    do {
        //Пробегаем элементы, ищем те, которые нужно перекинуть в другую часть
        //В левой части массива пропускаем(оставляем на месте) элементы, которые меньше центрального
        while (mas[i] < mid) {
            i++;
        }
        //В правой части пропускаем элементы, которые больше центрального
        while (mas[j] > mid) {
            j--;
        }

        //Меняем элементы местами
        if (i <= j) {
            std::swap(mas[i], mas[j]);
            i++;
            j--;
        }
    } while (i <= j);


    //Рекурсивные вызовы
    if (j > 0) {
        QuickSort(mas, j + 1); // Правая часть
    }
    if (i < size) {
        QuickSort(&mas[i], size - i); // Левая часть
    }
}

int FindElementInArray(int mas[], int key, int size = N_Max) {
    for (int i = 0; i < N_Max; i++) {
        if (mas[i] == key) {
            return i;
            break;
        }
    }
    return -1;
}

int BinarySearch(int mas[], int key, int left = 0, int right = N_Max - 1) {
    if (key == mas[left])   return mas[left];
    if (key < mas[left])    return -1;
    if (key == mas[right])  return mas[right];
    if (key > mas[right])   return -1;

    while (left + 1 < right) {
        int c = (left + right) / 2;
        
        if (key > mas[c]) left = c;
        else right = c;
    }
    
    if (key == mas[right]) return right;
    else return -1;
}

double Function(double x) {
    return (x*x - 10);
}

double Bisection(double left, double right) {
    double eps = 1e-4;

    while (true) {
        double x = (left + right) / 2;
        if ((abs(x - left) < eps) && (abs(x - right) < eps))
            return x;
        else if (Function(x) * Function(left) > 0)
            left = x;
        else
            right = x;
    }
}

int main() {
    srand(time(0));
    int mas[N_Max];
    for (int i = 0; i < N_Max; i++) {
        mas[i] = rand();
    }
    //int mas[N_Max] = {35, 12, 213, 3123, 4 ,1324, 123, 4, 321, 32};
    QuickSort(mas, N_Max);
    //ShowArray(mas);


    int key = 24542;


    auto start = std::chrono::high_resolution_clock::now();
    int j = BinarySearch(mas, key);
    auto end = std::chrono::high_resolution_clock::now();

    if (j != -1)
        std::cout << "Found: " << mas[j] << " | index: " << j << std::endl;
    else
        std::cout << "There is no such element in the array" << std::endl;


    std::chrono::duration<float> duration = end - start;
    std::cout << "Time: " << duration.count() << " seconds" << std::endl;


    std::cout << "" << std::endl;
    std::cout << "==============================================================================" << std::endl;
    std::cout << "" << std::endl;



    auto start_2 = std::chrono::high_resolution_clock::now();
    int k = FindElementInArray(mas, key);
    auto end_2 = std::chrono::high_resolution_clock::now();

    if (k != -1) 
        std::cout << "Found: " << mas[k] << " | index: " << k << std::endl;
    else 
        std::cout << "There is no such element in the array" << std::endl;
    

    std::chrono::duration<float> duration_2 = end_2 - start_2;
    std::cout << "Time: " << duration_2.count() << " seconds" << std::endl;


    // Тут вторая часть лабораторной 
    std::cout << "" << std::endl;
    std::cout << "The root of the equation (x^2 - 10 = 0) is:" << std::endl;
    std::cout << Bisection(0, 10e64) << std::endl;
}

// Что-то типа конспекта
// Применяя бинарный поиск мы можем существенно сократить время работы нашего алгоритма
// Одно ограничение - массив должен быть отсортирован