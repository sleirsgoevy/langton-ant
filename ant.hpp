struct tick
{
    int x;
    int y;
    int new_value;
    int new_direction;
};

class Ant
{
public:
    void tick(struct tick&);
    void walk(int, int, int, int, void(*)(void*, int, int, int), void*);
};

Ant* new_ant(const char* program);
