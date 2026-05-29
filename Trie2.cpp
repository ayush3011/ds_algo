#include <bits/stdc++.h>
using namespace std;

struct Node
{
    Node *links[26];
    int cntEndWith = 0;
    int cntPrefix = 0;

    Node()
    {
        for (int i = 0; i < 26; i++)
            links[i] = nullptr;
    }

    bool containsChar(char ch)
    {
        return links[ch - 'a'] != NULL;
    }

    void put(char ch, Node *node) { links[ch - 'a'] = node; }

    Node *get(char ch) { return links[ch - 'a']; }

    void increaseEnd()
    {
        cntEndWith++;
    }

    void increasePrefix()
    {
        cntPrefix++;
    }

    void deleteEnd()
    {
        cntEndWith--;
    }

    void reducePrefix()
    {
        cntPrefix--;
    }

    int getEnd()
    {
        return cntEndWith;
    }

    int getPrefix()
    {
        return cntPrefix;
    }
};

class Trie
{
private:
    Node *root;

public:
    Trie() { root = new Node(); }

    void insert(const string &word)
    {
        Node *node = root;
        for (int i = 0; i < word.size(); i++)
        {
            char ch = word[i];
            if (!(node->containsChar(ch)))
                node->put(ch, new Node());
            node = node->get(ch);
            node->increasePrefix();
        }
        node->increaseEnd();
    }

    int countWordsEqualTo(const string &word)
    {
        Node *node = root;
        for (int i = 0; i < word.size(); i++)
        {
            char ch = word[i];
            if (!(node->containsChar(ch)))
                return 0;
            node = node->get(ch);
        }
        return node->getEnd();
    }

    int countWordsStartingWith(const string &word)
    {
        Node *node = root;
        for (int i = 0; i < word.size(); i++)
        {
            char ch = word[i];
            if (!(node->containsChar(ch)))
                return 0;
            node = node->get(ch);
        }
        return node->getPrefix();
    }

    void erase(const string &word)
    {
        if (countWordsEqualTo(word) == 0)
            return;

        Node *node = root;

        for (int i = 0; i < word.size(); i++)
        {
            char ch = word[i];
            node = node->get(ch);
            node->reducePrefix();
        }

        node->deleteEnd();
    }
};

int main()
{
    Trie trie;
    trie.insert("apple");
    trie.insert("apple");
    cout << trie.countWordsEqualTo("apple") << endl;
    cout << trie.countWordsStartingWith("tapp") << endl;
    trie.erase("apple");
    cout << trie.countWordsEqualTo("apple") << endl;
    return 0;
}

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
