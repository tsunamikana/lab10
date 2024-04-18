#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{
	int count; 
	struct Trie* next[26];
	struct Trie* root;
};

// Inserts the word to the trie structure
void insert(struct Trie* pTrie, char* word)
{
	struct TrieNode* current = pTrie->root;
	int len = strlen(word);
	for (int i = 0; i < len; i++) {
		int index = word[i] - 'a';
		if (!current->next[index]) {
			current->next[index] = createTrieNode();
		}
		current = current->next[index];
	}
	current->count++;
}
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie* pTrie, char* word)
{
	struct TrieNode* current = pTrie->root;
	int len = strlen(word);
	for (int i = 0; i < len; i++) {
		int index = word[i] - 'a';
		if (!current->children[index]) {
			return 0; // Word not found
		}
		current = current->children[index];
	}
	return current->count;
}

// deallocate the trie structure
struct Trie* deallocateTrie(struct Trie* pTrie)
{
	if (pTrie) {
		for (int i = 0; i < 26; i++) {
			deallocateTrieNode(pTrie->next[i]);
		}
		free(pTrie);
	}
	return NULL;
}

// Initializes a trie structure
struct Trie* createTrie()
{
	struct Trie* pTrie = (struct Trie*)malloc(sizeof(struct Trie));
	if (pTrie) {
		pTrie->root = createTrieNode();
	}
	return pTrie;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char* filename, char** pInWords)
{
	FILE* file = fopen(filename, "r");
	if (!file) {
		printf("Error opening file %s\n", filename);
		exit(1);
	}

	int numWords = 0;
	char word[100]; // Assuming max word length is 99 characters

	while (fscanf(file, "%s", word) != EOF) {
		pInWords[numWords] = strdup(word);
		numWords++;
	}

	fclose(file);
	return numWords;
}

int main(void)
{
	char* inWords[256];

	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i = 0; i < numWords; ++i)
	{
		printf("%s\n", inWords[i]);
	}

	struct Trie* pTrie = createTrie();
	for (int i = 0; i < numWords; i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char* pWords[] = { "notaword", "ucf", "no", "note", "corg" };
	for (int i = 0; i < 5; i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}