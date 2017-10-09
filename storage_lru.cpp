#include <map>
#include <unordered_map>
#include <list>
#include <iostream>

using namespace std;

#define LRU_SIZE 1

class Storage
{
    unordered_map<long long, int*> slow_map;
    unordered_map<long long, int*> fast_map;
    list<long long> fast_keys;
    void drop_key()
    {
        if(fast_keys.size() < LRU_SIZE)
            return;
        long long key = fast_keys.front();
        fast_keys.pop_front();
        slow_map[key] = fast_map[key];
        fast_map.erase(fast_map.find(key));
    }
    int* get_by_key(long long key)
    {
        int* ans;
        if(fast_map.find(key) == fast_map.end())
        {
            drop_key();
            fast_keys.push_back(key);
            if(slow_map.find(key) == slow_map.end())
            {
                ans = fast_map[key] = new int;
                ans[0] = 0;
            }
            else
                ans = fast_map[key] = slow_map[key];
        }
        else
            ans = fast_map[key];
        return ans;
    }
public:
    int& get(int x, int y);
};

int& Storage::get(int x, int y)
{
    long long key = (((long long)x) << 32) | (unsigned int)y;
    return *get_by_key(key);
}

Storage& new_storage()
{
    return *new Storage;
}
