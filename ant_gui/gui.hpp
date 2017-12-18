class GUI
{
public:
    void getSize(int&, int&);
    void putpixel(int, int, int);
    void flip();
    void wait();
    int getKey();
    void getMouse(int&, int&, int&);
};

GUI* new_gui(const char*);
