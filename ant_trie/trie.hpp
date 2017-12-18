class Trie
{
public:
    void up();
    void down();
    void left();
    void right();
    int& value();
    void walk(int, int, int, int, void(*)(void*, int, int, int&), void*);
};

Trie* new_trie();
