#pragma once

namespace car
{

class PartBodyBase
{
public:
    PartBodyBase()
        : color(0)
    {
    };

public:
    size_t color;
};

} // namespace car