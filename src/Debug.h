#include "Math.h"
#include <vector>

class Debug {
public:
    static void Draw(class Renderer* renderer);
    static void DrawRect(const Rect& rect);
private:
    static std::vector<Rect> rects;
};
