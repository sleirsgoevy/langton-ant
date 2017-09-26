#include <iostream>
#include <unordered_set>

using namespace std;

int main()
{
    unordered_set<long long> white_pixels;
    int x = 0;
    int y = 0;
    int dx = 1;
    int dy = 0;
    int turn = 0;
    while(true)
    {
        swap(dx, dy);
        long long key = (((long long)x) << 32) | y;
        unordered_set<long long>::iterator it = white_pixels.find(key);
        if(it == white_pixels.end())
        {
            dx = -dx;
            white_pixels.insert(key);
            if(turn % 1000000 == 0)
                cout << "l[" << x << ", " << y << "] = white" << endl;
        }
        else
        {
            dy = -dy;
            white_pixels.erase(key);
            if(turn % 1000000 == 0)
                cout << "l[" << x << ", " << y << "] = black" << endl;
        }
        x += dx;
        y += dy;
        turn++;
    }
    return 0;
}
