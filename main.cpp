#include <iostream>

#include <exception>

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

	catch (const std::exception &ex) {
		std::cerr << ex.what() << std::endl;
	}
	
	catch (const char* err) {
		std::cerr << err << std::endl;
	}

	catch (...) {
		std::cerr << "Unknown error" << std::endl;
	}

	return 0;
}
