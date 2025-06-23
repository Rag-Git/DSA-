#include <bits/stdc++.h>
using namespace std;

// Build the longest prefix suffix (LPS) array for the pattern
vector<int> build_lps(const string &pattern) {
    int n = (int)pattern.size();
    vector<int> lps(n, 0);
    int len = 0; // length of previous longest prefix suffix
    int i = 1;

    while (i < n) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

// Return true if pattern exists in text, else false
bool kmp_search(const string &text, const string &pattern) {
    if (pattern.empty()) return false;
    vector<int> lps = build_lps(pattern);
    int i = 0, j = 0;  // indices for text and pattern

    while (i < (int)text.size()) {
        if (text[i] == pattern[j]) {
            i++; j++;
            if (j == (int)pattern.size()) {
                return true; // pattern found
            }
        } else {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }
    return false; // pattern not found
}
