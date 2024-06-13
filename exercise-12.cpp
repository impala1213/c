#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

bool isAlpha(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

char toLower(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c + ('a' - 'A');
    }
    return c;
}

void bubbleSort(vector<pair<string, int>>& vec) {
    bool swapped;
    for (size_t i = 0; i < vec.size() - 1; i++) {
        swapped = false;
        for (size_t j = 0; j < vec.size() - i - 1; j++) {
            if (vec[j].second < vec[j + 1].second ||
                (vec[j].second == vec[j + 1].second && vec[j].first > vec[j + 1].first)) {
                swap(vec[j], vec[j + 1]);
                swapped = true;
            }
        }
        if (!swapped)
            break;
    }
}

int main()
{
    string input;
    vector<string> tokens;
    map<string, int> wcount;
    getline(cin, input);

    for (int i = 0; i < input.length(); i++) {
        if (!isAlpha(input[i])) {
            input[i] = ' ';
        }
    }

    istringstream iss(input);
    string token;
    while (iss >> token) {
        tokens.push_back(token);
    }

    for (int i = 0; i < tokens.size(); i++) {
        string word = tokens[i];
        for (int j = 0; j < word.length(); j++) {
            word[j] = toLower(word[j]);
        }
        if (word.length() > 2) {
            if (wcount.find(word) == wcount.end()) {
                wcount[word] = 1;
            } else {
                wcount[word]++;
            }
        }
    }

    vector<pair<string, int>> sortedwcount;
    for (map<string, int>::iterator it = wcount.begin(); it != wcount.end(); it++) {
        sortedwcount.push_back(make_pair(it->first, it->second));
    }

    bubbleSort(sortedwcount);

    for (int i = 0; i < 3 && i < sortedwcount.size(); i++) {
        cout << sortedwcount[i].first << " " << sortedwcount[i].second << endl;
    }

    return 0;
}
