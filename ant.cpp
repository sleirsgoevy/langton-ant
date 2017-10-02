#include <iostream>
#include <map>
#include <cstring>

using namespace std;

class Storage
{
public:
    int& get(int x, int y);
    class Accessor
    {
        Storage* it;
        int y;
    public:
        Accessor(Storage* it, int y) : it(it), y(y) {}
        int& operator[](int x)
        {
            return it->get(x, y);
        }
    };
    Accessor operator[](int y)
    {
        return Accessor(this, y);
    }
};

Storage& new_storage();

int main()
{
    Storage& stor = new_storage();
    int x = 0;
    int y = 0;
    int dx = 1;
    int dy = 0;
    int turn = 0;
    while(true)
    {
        swap(dx, dy);
        if(stor[y][x])
        {
            dx = -dx;
            stor[y][x] = 0;
            if(turn % 1000000 == 0)
                cout << "l[" << x << ", " << y << "] = white" << endl;
        }
        else
        {
            dy = -dy;
            stor[y][x] = 1;
            if(turn % 1000000 == 0)
                cout << "l[" << x << ", " << y << "] = black" << endl;
        }
        x += dx;
        y += dy;
        turn++;
    }
    return 0;
}
