#include <iostream>
#include "../ant.hpp"

using namespace std;

const char* directions[] = {"right", "up", "left", "down"};

int main(int argc, char** argv)
{
    if(argc != 2)
    {
        cerr << "usage: " << argv[0] << " <program>\n";
        return 1;
    }
    Ant& a = *new_ant(argv[1]);
    while(true)
    {
        struct tick t;
        a.tick(t);
        cout << "Ant at " << t.x << ", " << t.y << ", cell recolored to " << t.new_value << ", now moving " << directions[t.new_direction] << endl;
        string s;
        getline(cin, s);
    }
    return 179;
}
