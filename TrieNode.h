#ifndef TRIENODE_H
#define TRIENODE_H

#include  <unordered_map>
#include <string>

using namespace std;

struct TrieNode {
    unordered_map<char, TrieNode*> children;
    bool isEndOfWord = false;
    unordered_map<string, int> NextWord;
};

#endif
