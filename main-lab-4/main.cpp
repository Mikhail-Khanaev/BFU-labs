#include <iostream>
#include <chrono>
#include <vector>

#define N 10000
#define M 1000
#pragma comment(linker, "/STACK:10000000000000")

// Вариант 2 Ханаев Михаил
// Лабораторная работа N4 "Односвязный список"


struct T_List {
	T_List* next;
	int number;
};

void ADD(T_List* head, int number) {
	T_List* p = new T_List;
	p->number = number;

	p->next = head->next;
	head->next = p;
}

void PRINT(T_List* head){
	T_List* p = head->next;
	while (p != nullptr)
	{
		std::cout << p->number << std::endl;
		p = p->next;
	}
}

void DELETE(T_List* head, int k) {
	T_List* tmp;
	T_List* p = head;
	while (p->next != nullptr) {
		if (p->next->number == k) {
			tmp = p->next;
			p->next = p->next->next;
			delete tmp;
			//std::cout << "delete" << std::endl;
		}
		else
			p = p->next;
	}
}

void CLEAR(T_List* head)
{
	T_List* tmp;
	T_List* p = head->next;
	while (p != nullptr)
	{
		tmp = p;
		p = p->next;
		delete tmp;
	}
}

void DUPLICATE(T_List* head)
{
	T_List* p = head->next;
	while (p != nullptr)
	{
		if (p->number % 2 == 1)
		{
			T_List* q = new T_List;
			q->next = p->next;
			p->next = q;
			q->number = p->number;
			p = p->next;
		}
		p = p->next;
	}
}

void SWAPSORT(T_List* head)
{
	//for(int i=0;i<n-1;i++)
	//	for(int j=i+1;j<n;j++)

	T_List* p = head->next;
	while (p->next->next != nullptr)
	{
		T_List* q = p->next;
		while (q->next != nullptr)
		{
			if (p->number > q->number)
				std::swap(p->number, q->number);
			q = q->next;
		}
		p = p->next;
	}
}

void MasInit(std::vector<int>& mas, int n){
	for (int i = 0; i < n; i++) {
		mas.push_back(rand());
		//cout << mas[i] << endl;
	}
}

void ElemErase(std::vector<int>& mas, int key1){
	for (int i = 0; i < mas.size(); i++)
	{
		if (mas[i] == key1)
		{
			mas.erase(mas.begin() + i);
		}
	}

}

void MasPrint(std::vector<int> mas)
{
	for (int i = 0; i < mas.size(); i++)
	{
		std::cout << mas[i] << std::endl;
	}
}


int main() {
	srand(time(0));
	T_List* head = new T_List;
	head->next = nullptr;

	// заполнение списка
	for (int i = 0; i < N; i++) {
		int d = rand();
		ADD(head, d);
	}
	
	// заполнение массива
	std::vector<int> mas;
	MasInit(mas, N);


	// Время удаления в списке
	auto start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < M; i++) {
		int key = rand();
		DELETE(head, key);
	}
	auto end = std::chrono::high_resolution_clock::now();

	std::chrono::duration<float> duration = end - start;
	std::cout << "======================================================" << std::endl;
	std::cout << std::endl << "    List time : " << duration.count() << " seconds" << std::endl << "" << std::endl;
	std::cout << "======================================================" << std::endl;




	auto start_2 = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < M; i++) {
		int key = rand();
		ElemErase(mas, key);
	}
	auto end_2 = std::chrono::high_resolution_clock::now();

	std::chrono::duration<float> duration_2 = end_2 - start_2;
	std::cout << "======================================================" << std::endl;
	std::cout << std::endl << "    Array time : " << duration_2.count() << " seconds" << std::endl << "" << std::endl;
	std::cout << "======================================================" << std::endl;


	std::cout << duration_2 / duration << std::endl;

	delete head;
	return 0;
}
