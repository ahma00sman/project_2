#ifndef CHARACTERTRIE_H
#define CHARACTERTRIE_H

#include "TrieNode.h"
#include <string>
#include <vector>

using namespace std;

class CharacterTrie {
private:
    TrieNode root;

public:
    CharacterTrie();

    void insert(const string& CurrentWord, const string& NextWord);
    TrieNode* LookupPrefix(const string& prefix);
    vector<pair<string, int>> Recommendations(const string& prefix);
};

#endif