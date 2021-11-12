#pragma once

#include <string>

class Font {
public:
    Font();
    ~Font();
    bool Load(const std::string& fileName);
    void Unload();
};
