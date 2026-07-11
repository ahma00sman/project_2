#include "CharacterTrie.h"
#include "Corpus.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

using namespace std;

int main() {
    CharacterTrie engine;
    vector<string> CorpusLines;

    ifstream file("movie_lines.txt");

    if (!file.is_open()) {
        cerr << "Error" << endl;
        return 1;
    }

    cout << "Readind Cornell Corpus..." << endl;
    string line;

    while (getline(file, line)) {
        size_t pos = line.rfind("+++$+++ ");
        if (pos != string::npos) {
            CorpusLines.push_back(line.substr(pos + 8));
        }
    }
    file.close();

    cout << "Indexing text into Trie engine..." << endl;
    auto startLoad = chrono::high_resolution_clock::now();

    CorpusProcessor::LoadFromText(engine, corpusLines);

    auto EndLoad = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> LoadDuration = endLoad - startLoad;
    cout << LoadDuration.couny() << endl;
    
    cout << "--- Autocomplete Tests ---" <<endl;
    string Queries[] = {"i", "why", "the", "hello"};

    for (const string& query : Queries) {
        auto StartQuery = chrono::high_resolution_clock::now();

        vector<pair<string, int>> suggestions = engine.Recommendations(query);

        auto EndQuery = chrono::high_resolution_clock::now();
        chrono::duration<double, chrono::micro> QueryDuration = EndQuery - StartQuery;

        cout << query << "analyzed in: " << QueryDuration.count() << "ms" << endl;

        if (suggestions.empty()) {
            cout << "No suggestions tracked" << endl;
        } else {
            size_t DisplayLimit = min(suggestions.size(), size_t(5));
            for (size_t i = 0; i <DisplayLimit, ++i) {
                cout << suggestions[i].first << "\" (Count: " << suggestions[i].second << ")" << endl;
            }
        }
        cout << endl;
    }
    return 0;
}