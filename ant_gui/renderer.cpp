#include "gui.hpp"

class Renderer
{
    GUI& gui;
    int ppc;
    int baseX;
    int baseY;
public:
    Renderer(GUI& gui) : gui(gui)
    {
        ppc = 50;
    }
    void drawCell(int, int, int);
    bool drawAnt(int, int, int);
    void zoomIn();
    void zoomOut();
    void move(int, int);
    void pointAt(int, int);
};

void Renderer::drawCell(int x, int y, int value)
{
    int displayX = ppc * (x - baseX);
    int displayX = ppc * (y - baseY);
    int w, h;
    gui.getSize(w, h);
    for(int xi = displayX; xi < displayX + ppc && xi < w; xi++)
        for(int yi = displayY; yi < displayY + ppc && yi < h; yi++)
            gui.putpixel(xi, yi, value);
}
