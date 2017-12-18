#define NULL nullptr

struct trie_node
{
    trie_node* parent = NULL;
    trie_node* ul = NULL;
    trie_node* ur = NULL;
    trie_node* dl = NULL;
    trie_node* dr = NULL;
};

class Trie
{
    struct trie_node* cur;
    bool isLeft()
    {
        return cur == cur->parent->ul || cur == cur->parent->dl;
    }
    bool isRight()
    {
        return cur == cur->parent->ur || cur == cur->parent->dr;
    }
    bool isUp()
    {
        return cur == cur->parent->ul || cur == cur->parent->ur;
    }
    bool isDown()
    {
        return cur == cur->parent->dl || cur == cur->parent->dr;
    }
    void trie_up()
    {
        cur = cur->parent;
    }
    void trie_down(trie_node*& where)
    {
        if(where == NULL)
        {
//          std::cout << "new node" << std::endl;
            where = new trie_node;
            where->parent = cur;
        }
        cur = where;
    }
    void trie_walk(trie_node* node, int l0, int r0, int u0, int d0, int l, int r, int u, int d, void(*callback)(void*, int, int, int&), void* arg)
    {
        if(l0 > r || r0 < l || u0 > d || d0 < u)
            return;
        if(r0 == l0 && d0 == u0)
            callback(arg, l0, u0, *((int*)&node->ul));
        else
        {
            int mx = (l0 + (long long)r0) / 2;
            int my = (u0 + (long long)d0) / 2;
            if(node->ul)
                trie_walk(node->ul, l0, mx, u0, my, l, r, u, d, callback, arg);
            if(node->ur)
                trie_walk(node->ur, mx + 1, r0, u0, my, l, r, u, d, callback, arg);
            if(node->dl)
                trie_walk(node->dl, l0, mx, my + 1, d0, l, r, u, d, callback, arg);
            if(node->dr)
                trie_walk(node->dr, mx + 1, r0, my + 1, d0, l, r, u, d, callback, arg);
        }
    }
public:
    Trie()
    {
        cur = new trie_node;
        trie_down(cur->dr);
        for(int i = 1; i < 32; i++) 
            trie_down(cur->ul);
    }
    void up();
    void down();
    void left();
    void right();
    int& value();
    void walk(int, int, int, int, void(*)(void*, int, int, int&), void*);
};

void Trie::up()
{
    bool left = isLeft();
    if(isUp())
    {
        trie_up();
        up();
        trie_down(left?cur->dl:cur->dr);
    }
    else
    {
        trie_up();
        trie_down(left?cur->ul:cur->ur);
    }
}

void Trie::down()
{
    bool left = isLeft();
    if(isDown())
    {
        trie_up();
        down();
        trie_down(left?cur->ul:cur->ur);
    }
    else
    {
        trie_up();
        trie_down(left?cur->dl:cur->dr);
    }
}

void Trie::left()
{
    bool up = isUp();
    if(isLeft())
    {
        trie_up();
        left();
        trie_down(up?cur->ur:cur->dr);
    }
    else
    {
        trie_up();
        trie_down(up?cur->ul:cur->dl);
    }
}

void Trie::right()
{
    bool up = isUp();
    if(isRight())
    {
        trie_up();
        right();
        trie_down(up?cur->ul:cur->dl);
    }
    else
    {
        trie_up();
        trie_down(up?cur->ur:cur->dr);
    }
}

int& Trie::value()
{
    return *((int*)&cur->ul);
}

void Trie::walk(int l, int r, int u, int d, void(*callback)(void*, int, int, int&), void* arg)
{
    struct trie_node* node = cur;
    while(node->parent)
        node = node->parent;
    return trie_walk(node, 1 << 31, (1 << 31) - 1, 1 << 31, (1 << 31) - 1, l, r, u, d, callback, arg);
}

Trie* new_trie()
{
    return new Trie();
}
