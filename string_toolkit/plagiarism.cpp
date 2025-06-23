#include <bits/stdc++.h>
using namespace std;

extern bool kmp_search(const string &text, const string &pattern);

// Load banned phrases from a file, check if any appear in text
vector<string> detect_plagiarism(const string &text, const string &banned_file) {
    ifstream fin(banned_file);
    vector<string> flagged;
    if (!fin.is_open()) {
        cerr << "ERROR: Could not open " << banned_file << endl;
        return flagged;
    }

    string phrase;
    while (getline(fin, phrase)) {
        if (phrase.empty()) continue;
        if (kmp_search(text, phrase)) {
            flagged.push_back(phrase);
        }
    }
    return flagged;
}
