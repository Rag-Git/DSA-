#include <bits/stdc++.h>
using namespace std;

struct TrieNode
{
    bool is_end;
    TrieNode* children[26];

    TrieNode()
    {
        is_end = false;
        for (int i = 0; i < 26; i++)
            children[i] = nullptr;
    }
};

struct Trie
{
    TrieNode* root;

    Trie()
    {
        root = new TrieNode();
    }

    void insert(const string &word)
    {
        TrieNode* node = root;
        for (char c : word)
        {
            int idx = c - 'a';
            if (node->children[idx] == nullptr)
                node->children[idx] = new TrieNode();
            node = node->children[idx];
        }
        node->is_end = true;
    }

    TrieNode* getNode(const string &prefix)
    {
        TrieNode* node = root;
        for (char c : prefix)
        {
            int idx = c - 'a';
            if (node->children[idx] == nullptr)
                return nullptr;
            node = node->children[idx];
        }
        return node;
    }

    vector<string> getSuggestions(string prefix)
    {
        TrieNode* node = getNode(prefix);
        if (!node) return {};

        vector<string> result;
        dfs(node, prefix, result);
        return result;
    }

private:
    void dfs(TrieNode* node, string current, vector<string> &result)
    {
        if (node->is_end)
            result.push_back(current);

        for (int i = 0; i < 26; i++)
        {
            if (node->children[i])
            {
                char next_char = 'a' + i;
                dfs(node->children[i], current + next_char, result);
            }
        }
    }
};
