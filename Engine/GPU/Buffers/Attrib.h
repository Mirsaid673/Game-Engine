#pragma once

#include "Core.h"
#include "Enums.h"

struct Attrib
{
public:
    enum Location : u8
    {
        POSITION = 0,
        NORMAL = 1,
        TANGENT = 2,
        BITANGENT = 3,
        WEIGHT = 4,
        COLOR0 = 5,
        COLOR1 = 6,
        COLOR2 = 7,
        COLOR3 = 8,
        TEX_COORD0 = 9,
        TEX_COORD1 = 10,
        TEX_COORD2 = 11,
        TEX_COORD3 = 12,
        MAX,
    };

private:
    Location location;
    DataType data_type;
    u8 component_count;

    bool normalized = false;

public:
    Attrib() = default;
    Attrib(Location l, u8 comp_count = 3,
           DataType t = DataType::FLOAT,
           bool norm = false) : location(l),
                                component_count(comp_count),
                                data_type{t},
                                normalized(norm) {}

public:
    Location getLocation() const { return location; }
    DataType getDataType() const { return data_type; }
    u8 getCount() const { return component_count; }
    bool getNormalized() const { return normalized; }
    u8 getSize() const
    {
        static const u8 sizes[(u8)DataType::COUNT] =
            {
                1, // byte
                1, // unsigned byte
                2, // short
                2, // unsigned short
                4, // int
                4, // unsigned int
                4, // float
            };
        return getCount() * sizes[(u8)data_type];
    }

    friend class VertexLayout;
};
