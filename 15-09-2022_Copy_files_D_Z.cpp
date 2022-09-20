// 15-09-2022_Copy_files_D_Z.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib,"user32.lib")
#include <string>
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdio.h>
#include<stdio.h>
#include<io.h>
#include<WinUser.h>
using namespace std;
//Функция, выводящая на экран строку
void Message (char* str) {
	 char message[100];
	//перевод строки из кодировки Windows
	//в кодировку MS DOS
	//CharToOem(message,str);
	cout << message;
}
//Функция копирования файла
bool CopyFile(char* source, char* destination) {
	const int size = 65536;
	FILE* src, * dest;
	//Открытие Файла
	if (!(src = fopen(source, "rb"))) {
		return false;
	}
	//Получение дескриптора файла
	int handle = _fileno(src);
	//выделение памяти под буффер
	char* data = new char[size];
	if (!data) {
		return false;
	}
	//Открытие файла, куда будет производиться копирование
	if (!(dest = fopen(destination, "wb"))) {
		delete[]data;
		return false;
	}
	int realsize;
	while (!feof(src)) {
		//Чтение данных из файла
		realsize = fread(data, sizeof(char), size, src);
		//Запись данных в файл
		fwrite(data, sizeof(char), realsize, dest);
	}
	//Закрытие файлов
	fclose(src);
	fclose(dest);
	return true;
}
int main(void) {
	system("chcp 1251");
	// __MAX_PATH - Константа, определяющая максимальный размер пути.
	// Даная константа содержится в stdlib.h
	char source[_MAX_PATH];
	char destination[_MAX_PATH];
	char answer[20];
	cout <<"\nВведите путь и название копируемого файлу:\n";
	// Получение пути к первому файлу
	cin.getline(source, _MAX_PATH);
	// Проверка Существует ли файл
	if (_access(source, 00) == -1) {
		cout <<"\nУказан неверный путь или название файла\n";
		return 1;
	}
	cout <<"\nВведите путь и название нового файла:\n";
	// Получение пути к второму файлу
	cin.getline(destination, _MAX_PATH);
	// Проверка на существование файла
	if (_access(destination, 00) == 0) {
		cout <<"\nТакой Файл уже существует перезаписать его(1 - Да /2 - Нет)?\n";
		cin.getline(answer, 20);
		if (!strcmp(answer, "2")) {
			cout <<"\nОперация отменена\n";
			return 1;
		}
		else if (strcmp(answer, "1")) {
			cout <<"\nНеправильный ввод\n";
			return 1;
		}
		if (_access(destination, 02) == -1) {
			cout <<"\nНет доступа к записи.\n";
			return 1;
		}
	}

	// Копирование файла 
	if (!CopyFile(source, destination)) {
		cout <<"\nОшибка при работе с файлом\n";
	}

	return 0;
}