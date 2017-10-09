#include <unordered_map>
#include <cstring>

using namespace std;

#define WIDTH 500
#define HEIGHT 500

#define mod(a, b) (((a) % (b) + (b)) % (b))
#define div(a, b) (((a) - mod(a, b)) / (b))

class Storage
{
    unordered_map<long long, int*> main_storage;
    int* cache[4] = {NULL, NULL, NULL, NULL};
    int chunk_x = 0;
    int chunk_y = 0;
    int*& index(int x, int y)
    {
        return main_storage[(((long long)x)<<32)|y];
    }
    int* raw_get_chunk(int x, int y)
    {
        int*& ans = index(x, y);
        if(ans == NULL)
        {
            ans = new int[WIDTH * HEIGHT];
            memset(ans, 0, sizeof(sizeof(int) * WIDTH * HEIGHT));
        }
        return ans;
    }
    bool resolve_lock = false;
    void move_cache(int x, int y)
    {
        resolve_lock = true;
        int* new_cache[4];
        for(int dx = 0; dx <= 1; dx++)
            for(int dy = 0; dy <= 1; dy++)
                new_cache[dx * 2 + dy] = get_chunk(x + dx, y + dy);
        for(int i = 0; i < 4; i++)
            cache[i] = new_cache[i];
        chunk_x = x;
        chunk_y = y;
        resolve_lock = false;
    }
    int* get_chunk(int x, int y)
    {
    start:
        int dx = x - chunk_x;
        int dy = y - chunk_y;
        if(dx < 0 || dx > 1 || dy < 0 || dy > 1)
            if(resolve_lock)
                return NULL;
            else
            {
                move_cache(x, y);
                goto start;
            }
        int*& ans = cache[dx * 2 + dy];
        if(ans == NULL)
            ans = raw_get_chunk(x, y);
        return ans;
    }
public:
    int& get(int x, int y);
};

int& Storage::get(int x, int y)
{
    return get_chunk(div(x, WIDTH), div(y, HEIGHT))[mod(y, HEIGHT) * WIDTH + mod(x, WIDTH)];
}

Storage& new_storage()
{
    return *new Storage;
}
