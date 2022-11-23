#include <iostream>

#include "trie.h"
#include "func.h"

int main()
{
	try {
		Trie dictionary("dict.txt"); //создаем словарь из файла.

		std::string input; //Строка для ввода

		//Передача в ф-ию словаря и строки для ввода
		inputReq(dictionary, input);
	}
	catch (const char* err) {
		std::cout << err << std::endl;
	}

	catch (...) {
		std::cerr << "Unknown error" << std::endl;
	}

	return 0;
}
