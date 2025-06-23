#include <bits/stdc++.h>
using namespace std;

int edit_distance(string a, string b)
{
    int n = a.size(), m = b.size();
    vector<vector<int>> dp(n+1, vector<int>(m+1));

    for(int i = 0; i <= n; i++)
    for(int j = 0; j <= m; j++)
    {
        if(i == 0) dp[i][j] = j;
        else if(j == 0) dp[i][j] = i;
        else if(a[i-1] == b[j-1]) dp[i][j] = dp[i-1][j-1];
        else dp[i][j] = 1 + min({ dp[i-1][j], dp[i][j-1], dp[i-1][j-1] });
    }

    return dp[n][m];
}

vector<string> autocorrect_text(string text, const vector<string> &dictionary)
{
    stringstream ss(text);
    string word;
    vector<string> corrected;

    while(ss >> word)
    {
        string best = word;
        int min_dist = INT_MAX;

        for(const string &dict_word : dictionary)
        {
            if(abs((int)dict_word.size() - (int)word.size()) > 2) continue; // Skip if length difference > 2

            int dist = edit_distance(word, dict_word);
            if(dist < min_dist)
            {
                min_dist = dist;
                best = dict_word;
            }
        }


        corrected.push_back(best);
    }

    return corrected;
}
