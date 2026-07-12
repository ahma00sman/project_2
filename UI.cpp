#include "CharacterTrie.h"
#include "Corpus.h"
#include "Corpus.cpp"
#include "CharacterTrie.cpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <iomanip>

using namespace std;

void PrintBanner()
{
cout << "\n";
cout << "==============================================================\n";
cout << " MOVIE DIALOGUE PREDICTOR\n";
cout << "==============================================================\n";
cout << " Cornell Movie Dialog Corpus + Trie Engine\n";
cout << "==============================================================\n\n";
}

void PrintLine()
{
cout << "--------------------------------------------------------------\n";
}

void DisplaySuggestions(const vector<pair<string,int>>& suggestions)
{
if (suggestions.empty())
{
cout << "\nNo suggestions found.\n";
return;
}

PrintLine();
cout << left
<< setw(8) << "Rank"
<< setw(25) << "Word"
<< setw(10) << "Count" << endl;

PrintLine();

size_t limit = min((size_t)5, suggestions.size());

for (size_t i = 0; i < limit; i++)
{
cout << left
<< setw(8) << i + 1
<< setw(25) << suggestions[i].first
<< setw(10) << suggestions[i].second
<< endl;
}

PrintLine();
}

int main()
{
CharacterTrie engine;
vector<string> CorpusLines;

PrintBanner();

ifstream file("movie_lines.txt");

if (!file.is_open())
{
cout << "ERROR: movie_lines.txt could not be opened.\n";
return 1;
}

cout << "Loading Cornell Movie Dialog Corpus...\n";

string line;

while (getline(file, line))
{
size_t pos = line.rfind("+++$+++ ");

if (pos != string::npos)
{
CorpusLines.push_back(line.substr(pos + 8));
}
}

file.close();

cout << "Loaded "
<< CorpusLines.size()
<< " dialogue lines.\n\n";

cout << "Building Trie...\n";

auto startLoad = chrono::high_resolution_clock::now();

CorpusProcessor::LoadFromText(engine, CorpusLines);

auto endLoad = chrono::high_resolution_clock::now();

chrono::duration<double, milli> loadDuration = endLoad - startLoad;

cout << "Trie built successfully!\n";
cout << "Index Time: "
<< fixed << setprecision(2)
<< loadDuration.count()
<< " ms\n\n";

while (true)
{
PrintLine();
cout << "MENU\n";
PrintLine();

cout << "1. Search for next-word predictions\n";
cout << "2. Exit\n\n";

cout << "Choice: ";

int choice;
cin >> choice;

if (choice == 2)
{
cout << "\nThank you for using Movie Dialogue Predictor!\n";
break;
}

if (choice != 1)
{
cout << "Invalid option.\n\n";
continue;
}

string query;

cout << "\nEnter a word: ";
cin >> query;

auto startQuery = chrono::high_resolution_clock::now();

vector<pair<string,int>> suggestions =
engine.Recommendations(query);

auto endQuery = chrono::high_resolution_clock::now();

std::chrono::duration<double, std::micro> queryDuration =
endQuery - startQuery;

cout << "\n";
PrintLine();
cout << "Search Results for \"" << query << "\"\n";
PrintLine();

DisplaySuggestions(suggestions);

cout << "\nSearch Time: "
<< fixed << setprecision(2)
<< queryDuration.count()
<< " microseconds\n\n";
}

return 0;
}