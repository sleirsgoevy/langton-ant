#include <string>
#include "trie.hpp"

using namespace std;

struct tick
{
    int x;
    int y;
    int new_value;
    int new_direction;
};

class Ant
{
    string program;
    Trie* trie;
    int x;
    int y;
    int dir;
public:
    Ant(const char* prog)
    {
        program = string(prog);
        trie = new_trie();
        x = 0;
        y = 0;
        dir = 0;
    }
    void tick(struct tick&);
    void walk(int, int, int, int, void(*)(void*, int, int, int), void*);
};

void Ant::tick(struct tick& t)
{
    t.x = x;
    t.y = y;
    int& value = trie->value();
    if(program[value] == 'L')
        dir++;
    else
        dir--;
    if(program.size() == ++value)
        value = 0;
    dir &= 3;
    t.new_value = value;
    t.new_direction = dir;
    switch(dir)
    {
    case 0:
        x++;
        trie->right();
        break;
    case 1:
        y--;
        trie->up();
        break;
    case 2:
        x--;
        trie->left();
        break;
    case 3:
        y++;
        trie->down();
        break;
    }
}

struct _callback
{
    void(*f)(void*, int, int, int);
    void* arg;
};

void _trie_callback(void* arg, int x, int y, int& val)
{
    struct _callback* cb = (struct _callback*)arg;
    cb->f(cb->arg, x, y, val);
}

void Ant::walk(int l, int r, int u, int d, void(*callback)(void*, int, int, int), void* arg)
{
    struct _callback cb;
    cb.f = callback;
    cb.arg = arg;
    trie->walk(l, r, u, d, _trie_callback, (void*)&cb);
}

Ant* new_ant(const char* program)
{
    return new Ant(program);
}
