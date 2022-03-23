#include <iostream>
#include <algorithm>
#include <stdio.h> 
#include <time.h> 
#include <chrono>
#define N_Max 100000000
#pragma comment(linker, "/STACK:1000000000")

// Вариант 2 Ханаев Михаил

// ✅ Реализуйте алгоритм быстрой сортировки по его псевдокоду
// ✅ Реализуйте алгоритм сортировки пузырьком из лекции 1
// ✅ Исследуйте при помощи класса Timer время выполнения на разных объемах входных данных(n = 10, n = 100, n = 100 000, n = 1 000 000).
// Объясните полученный результат.



// Факториал через рекурсию
int f(int n) {
	// Это терминирующее условие. То есть условие, при котором произойдёт выход из рекурсии
	if (n == 0) 
		return 1;
	
	// Запуск рекурсии с отличающимися параметрами
	return n * f(n - 1);
}

void SwapSort(int mas[N_Max], int n) {
	for (int i = 0; i < n - 1; i++)
		for (int j = i + 1; j < n; j++)
			if (mas[i] > mas[j])
				std::swap(mas[i], mas[j]);
}

// Сортировка пузырьком
void BubleSort(int mas[N_Max], int n) {
	for (int i = 1; i < n; i++) {
		if (mas[i] >= mas[i - 1]) {
			continue;
		}
		int j = i - 1;

		while ((j >= 0) && (mas[j] > mas[j + 1])) {
			std::swap(mas[j], mas[j + 1]);
			j--;
		}
	}
}


// Это алгоритм быстрой сортировки, написанный по псевдокоду
// Его сложность равна n*log(n) в среднем случае (и n^2 в худшем случае)
// Суть алгоритма состоит в том, чтобы разбить исходный массив на два подмассива
// Затем каждый из полученных массив сортируем, после этого объединяем
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


int main() {
	//std::cout << f(5);
	srand(time(0));
	int mas[N_Max];
	for (int i = 0; i < N_Max; i++) {
		mas[i] = rand();
	}

	auto start = std::chrono::high_resolution_clock::now();
    QuickSort(mas, N_Max);
	auto end = std::chrono::high_resolution_clock::now();

	//for (int i = 0; i < 10; i++) {
	//	std::cout << mas[i] << std::endl;
	//}

	std::chrono::duration<float> duration = end - start;
	std::cout << "Time: " << duration.count() << " seconds" << std::endl;


	return 0;
}



// Область памяти, в которой хранятся шаги рекурсии, называется стек
// Стек может переполняться, поэтому важно всегда писать терминирующее условие



//clock_t start = clock();
//clock_t end = clock(); // а тут соответственно заканчиваю считать
//double seconds = (double)(end - start) / CLOCKS_PER_SEC;
//std::cout << "Time: " << seconds << " seconds" << std::endl;