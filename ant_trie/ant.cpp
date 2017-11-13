#include <iostream>
#include "trie.hpp"

using namespace std;

const char program[] = "LR";

int main()
{
    Trie* trie = new_trie();
    int x = 0;
    int y = 0;
    int rotation = 0;
    int turn = 0;
    while(true)
    {
        int& value = trie->value();
//      cout << value << endl;
        if(program[value] == 'L')
            rotation++;
        else
            rotation--;
        if(program[++value] == '\0')
            value = 0;
        if(turn % 1000000 == 0)
            cout << '[' << x << ", " << y << "] = " << value << endl;
        rotation &= 3;
        switch(rotation)
        {
        case 0:
            x++;
            trie->right();
            break;
        case 1:
            y++;
            trie->up();
            break;
        case 2:
            x--;
            trie->left();
            break;
        case 3:
            y--;
            trie->down();
            break;
        }
        turn++;
    }
    return 0;
}
