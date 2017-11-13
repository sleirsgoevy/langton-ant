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

Trie* new_trie()
{
    return new Trie();
}
