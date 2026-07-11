#include "CharacterTrie.h"
#include <algorithm>

CharacterTrie::CharacterTrie() {}

void CharacterTrie::insert(const string& CurrentWord, const string& NextWord) {
    TrieNode* curr = &root;

    for (char c : CurrentWord) {
        if (curr->children.find(c) == curr->children.end()) {
            curr->children[c] = new TrieNode();
        }
        curr = curr->children[c];
    }
    curr->isEndOfWord = true;

    if (!NextWord.empty()) {
        curr->NextWord[NextWord]++;
    }
}

TrieNode* CharacterTrie::LookupPrefix(const string& prefix) {
    TrieNode* curr = &root;

    for (char c : prefix) {
        if (curr->children.find(c) == curr->children.end()) {
            return nullptr;
        }
        curr = curr->children[c];
    }
    return curr;
}

vector<pair<string, int>> CharacterTrie::Recommendations(const string& prefix) {
    TrieNode* TargetNode = LookupPrefix(prefix);
    if (!TargetNode || !TargetNode->isEndOfWord) {
        return{};
    }

    vector<pair<string, int>> candidates(
        TargetNode->NextWord.begin(),
        TargetNode->NextWord.end()
    );

    sort(candidates.begin(), candidates.end(),
        [](const pair<string, int>& a, const pair<string, int>& b) {
            return a.second > b.second;
        }
    );

    return candidates;
}