#include <iostream>
#include <string>
#include <cstring>
#include <cctype>

using namespace std;

const int MAX_WORDS = 500;
string words[MAX_WORDS];
int freq[MAX_WORDS];
int numWords = 0;

void toLowerCase(string& s) {
    for (char& c : s) {
        c = tolower(c);
    }
}

bool isEndChar(char c) {
    return c == '.' || c == ',';
}

string getSingularForm(const string& word) {
    if (word.length() >= 3 && word.substr(word.length() - 1) == "s") {
        return word.substr(0, word.length() - 1);
    }
    return word;
}
bool isLowerCase(const string& word) {
    for (char c : word) {
        if (!islower(c)) {
            return false;
        }
    }
    return true;
}

bool doesNotEndWithS(const string& word) {
    if (word.empty()) return true;
    return word.back() != 's';
}

string compareWord(const string& word1, const string& word2) {
    bool word1LowerCase = isLowerCase(word1);
    bool word2LowerCase = isLowerCase(word2);
    bool word1DoesNotEndWithS = doesNotEndWithS(word1);
    bool word2DoesNotEndWithS = doesNotEndWithS(word2);

    if (word1LowerCase && word1DoesNotEndWithS) {
        return word1;
    }

    if (word2LowerCase && word2DoesNotEndWithS) {
        return word2;
    }

    if (word1LowerCase) {
        return word1;
    }

    if (word2LowerCase) {
        return word2;
    }

    if (word1DoesNotEndWithS) {
        return word1;
    }

    if (word2DoesNotEndWithS) {
        return word2;
    }
}
void addWord(string word) {
    if (word.length() < 3) return;
    string originalword = word;
    toLowerCase(word);
    string processedWord = getSingularForm(word);
    for (int i = 0; i < numWords; i++) {
        string originalwords = words[i];
        toLowerCase(words[i]);
        string processedWords = getSingularForm(words[i]);
        if (processedWords == processedWord) {
            freq[i]++;
            if (originalwords != originalword){
                words[i] = compareWord(originalwords, originalword);
                return;
            }
            words[i] = originalwords;
            return;
        }
        words[i] = originalwords;

    }
    words[numWords] = originalword;
    freq[numWords] = 1;
    numWords++;
}

void sortWords() {
    for (int i = 0; i < numWords - 1; i++) {
        for (int j = i + 1; j < numWords; j++) {
            if (freq[i] < freq[j] || (freq[i] == freq[j] && words[i] > words[j])) {
                swap(freq[i], freq[j]);
                swap(words[i], words[j]);
            }
        }
    }
}

int main() {
    string text;
    getline(cin, text);

    string word = "";
    for (char c : text) {
        if (isspace(c) || isEndChar(c)) {
            addWord(word);
            word = "";
        } else {
            word += c;
        }
    }
    addWord(word);
    sortWords();

    for (int i = 0; i < 3 && i < numWords; i++) {
        cout << words[i] << " " << freq[i] << endl;
    }

    return 0;
}
