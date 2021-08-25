#pragma once

#include "Math.h"

class Shape {
public:
    virtual void Draw() = 0;
};

class Line : public Shape {
public:
    Line(const Vector2& start, const Vector2& end);
    void Draw() override;
private:
    Vector2 start;
    Vector2 end;
};
