#include "Corpus.h"
#include <sstream>
#include <cctype>
#include <iostream>

string CorpusProcessor::clean(const string& str) {
    string sanitized = "";
    for (char c : str) {
        if (isalnum(c)) {
            sanitized += tolower(c);
        }
    }
    return sanitized;
}

void CorpusProcessor::LoadFromText(CharacterTrie& trie, const vector<string>& lines) {
    long long Count = 0
    for (const auto& line : lines) {
        stringstream ss(line);
        string RawWord;
        vector<string> tokens;

        while (ss >> RawWord) {
            string sanitized = clean(RawWord);
            if (!sanitized.empty()) tokens.push_back(sanitized);
        }

        if (tokens.size() < 2) continue;
        for (size_t i = 0; i < tokens.size() - 1, ++i) {
            trie.insert(tokens[i], tokens[i + 1]);
            Count++;
        }
    }
}