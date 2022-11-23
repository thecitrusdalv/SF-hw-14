//trie.cpp

#include "trie.h"
Trie::Trie(const std::string &path) //Инициализация дерева с указанием файла-словаря
{
	//Открываем файл-словарь, добавляем в дерево все строки со словами из него
	std::ifstream file;
	file.open(path);
	if (!file.is_open())
		throw "Cannot open dictionary file";

	std::string newWord;
	while (file >> newWord)
		insert(newWord);
}

Trie::TrieNode* Trie::getNewNode() const
{
	TrieNode *newNode = new TrieNode;
	for (size_t i = 0; i < ALPHABET_SIZE; i++)
		newNode->children[i] = nullptr;

	return newNode;
}

Trie::TrieNode* Trie::getRoot()
{
	return root;
}

void Trie::insert(const std::string& key)
{
	if (!key.size())
		return;

	if (!root)
		root = getNewNode();

	insert(root, key);
}

void Trie::insert(TrieNode *node, const std::string &key)
{
	for (size_t i = 0; i < key.size(); i++) {
		size_t index = key[i]-'a';

		if (!node->children[index])
			node->children[index] = getNewNode();
		node = node->children[index];
	}
	node->isEndOfWord = true;
}

bool Trie::find(const std::string& key) const
{
	TrieNode* temp = root;
	for (size_t i = 0; i < key.size(); i++) {

		int cur = key[i]-'a';

		if (temp->children[cur])
			temp = temp->children[cur];
		else
			return false;

		if (i == key.size()-1)
			return temp->isEndOfWord;
	}
	return true;
}

/*
 * Функция-обертка autocomplete возвращает строку, выбранную пользователем
 * Подходящие строки добавляются в вектор перегруженной
 * ф-ей autocomplete
 */
std::string Trie::autocomplete(const std::string& pref) const
{
	if (!pref.size())
		return "";

	TrieNode *node = root;
	for (size_t i = 0; i < pref.size(); i++) { //В цикле происходит перемещение к последнему узлу, согласно префиксу

		size_t index = (pref[i] >= 'A' && pref[i] <= 'Z') ? pref[i] - 'A' : pref[i] - 'a';

		if (index > ALPHABET_SIZE)
			return "";

		node = node->children[index];
			if (!node)
				return "";
	}

	std::vector <std::string> foundedWords; //Вектор найденных подходящих слов

	autocomplete(node, foundedWords);

	//Если вектор найденных слов не пуст, вывести его и предоставить выбор.
	if (foundedWords.size()) {
		for (size_t i = 0; i < foundedWords.size(); i++) {
			std::cout << "\t(" << i+1 << ") " << pref <<  foundedWords[i] << std::endl;
		}

		unsigned int choice; //Переменная для выбора
		std::cout << "\t(0) - cancel: ";
		std::cin >> choice;

		if (!choice)
			return "";

		if (choice > foundedWords.size()) {
			std::cout << "Incorrect";
			return "";
		}

		return foundedWords[choice-1];
	}

	return "";
}

void Trie::autocomplete(TrieNode *node, std::vector<std::string> &fw) const
{
	static std::string temp;

	for (size_t i = 0; i < ALPHABET_SIZE; i++) {
		if (node->children[i]) {
			temp += char(i + 'a');

			if (node->children[i]->isEndOfWord)
				fw.push_back(temp);

			autocomplete(node->children[i], fw);
		}
	}

	if (temp.size())
		temp.pop_back();
}
