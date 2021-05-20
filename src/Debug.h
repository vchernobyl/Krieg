#include "Math.h"

#include <vector>
#include <utility>

class Debug {
public:
    static void Draw(class Renderer* renderer);
    static void DrawRect(const Rectangle& rect);
    static void DrawLine(const Vector2& start, const Vector2& end);
private:
    static std::vector<Rectangle> rects;
    static std::vector<std::pair<Vector2, Vector2> > lines;
};
