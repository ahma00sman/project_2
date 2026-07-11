#ifndef CORPUS_H
#define CORPUS_H

#include "CharacterTrie.h"
#include <string>
#include <vector>

using namespace std;

class CorpusProcessor {
private:
    static string clean(const string& str);
public:
    static void LoadFromText(CharacterTrie& trie, const vector<string>& lines);
};

#endif