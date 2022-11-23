//func.cpp

#include "func.h"

void inputReq(const Trie& dict, std::string& in)
{
	std::cout << "\tFor autocomplete type TAB+Enter\n";
	std::cout << "\tFor exit type ':q'" << std::endl;
	std::cout << "Input: ";

	char c;
	while ((c = getchar()) != EOF) { //Запрос очередного символа для ввода в строку

		if (c == '\t') { //Если символ TAB

			//Поиск индекса начала последнего слова уже введенной части строки
			size_t lwi = in.size()-1;

			while (lwi != 0 && in[lwi-1] != ' ')
				lwi--;

			//Добавление во временную строку последнего слова
			std::string temp;
			while (lwi != in.size())
				temp += in[lwi++];

			//Если пользователем выбрано автодополнение, добавление его в конец вводимой строки
			in += dict.autocomplete(temp);

			getchar(); //Для игнорирования ENTER

			std::cout << '\n' << "Input: " << in;
			continue;
		}

		//Если ввод не завершен, добавление в строку очередного символа,
		//иначе очистка строки, возврат к началу цикла
		if (c != '\n') {
			in += char(c);
			if (in == ":q")
				break;
		}
		else {
			std::cout << "Input: ";
			in.clear();
		}
	}
}
