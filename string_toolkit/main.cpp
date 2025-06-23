#include <bits/stdc++.h>
using namespace std;

#include "trie.cpp"
#include "autocorrect.cpp"
#include "kmp.cpp"
#include "plagiarism.cpp"

// Helper to convert string to lowercase
string to_lowercase(const string &s) {
    string res = s;
    for (char &c : res) c = tolower(c);
    return res;
}


int main()
{
    Trie trie;
    vector<string> dictionary;

    cout << "Loading dictionary..." << endl;
    ifstream dict("dictionary.txt");
    if (!dict.is_open()) {
        cerr << "ERROR: Could not open dictionary.txt" << endl;
        return 1;
    }

    int count = 0;
    string word;
    while (dict >> word) {
        word = to_lowercase(word);
        dictionary.push_back(word);
        trie.insert(word);
        count++;
    }
    cout << "Loaded " << count << " words into the Trie." << endl;

    cout << "Enter a prefix to autocomplete: ";
    string prefix;
    cin >> prefix;
    prefix = to_lowercase(prefix);

    vector<string> suggestions = trie.getSuggestions(prefix);
    cout << "Suggestions: " << endl;
    for (const auto &s : suggestions)
        cout << s << endl;

    cin.ignore(); // clear newline after prefix input
    cout << "\nEnter a sentence to autocorrect (end with '$'):\n";
    string line, full_text;
    while (getline(cin, line)) {
        if (line == "$") break;
        full_text += line + " ";
    }
    full_text = to_lowercase(full_text);

    vector<string> corrected = autocorrect_text(full_text, dictionary);
    cout << "\nCorrected Output:\n";
    for (const auto &w : corrected) cout << w << " ";
    cout << endl;

    cout << "\n--- Plagiarism Detection ---" << endl;
    vector<string> flagged = detect_plagiarism(full_text, "banned.txt");
    if (flagged.empty()) {
        cout << "No plagiarized phrases detected.\n";
    } else {
        for (const auto &phrase : flagged)
            cout << "Plagiarized phrase found: " << phrase << endl;
    }

    return 0;
}
