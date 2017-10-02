#include <map>
#include <list>

using namespace std;

#define LRU_SIZE 100

class Storage
{
    map<long long, int> slow_map;
    map<long long, int> fast_map;
    list<long long> fast_keys;
    
