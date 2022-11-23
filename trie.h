//trie.h
#pragma once

#include <iostream>
#include <fstream>
#include <vector>

constexpr int ALPHABET_SIZE = int('z'-'a'+1);

class Trie
{
public:
	Trie(const std::string&);

	struct TrieNode
	{
		struct TrieNode *children[ALPHABET_SIZE];
		bool isEndOfWord = false;
	};

	TrieNode* getNewNode() const;
	TrieNode* getRoot();

	//Обертка для приватной ф-ии insert.
	void insert(const std::string &);

	//Поиск слов
	bool find(const std::string &) const;
	
	//Возвращает выбранную строку, найденную по префиксу (обертка)
	std::string autocomplete(const std::string &) const; 
private:
	TrieNode *root = nullptr;
	
	//Вставка слова
	void insert(TrieNode *, const std::string &);												  

	//Поиск подходящих по префиксу слов и добавление в вектор.
	void autocomplete(TrieNode *node, std::vector<std::string> &fw) const; 
};
