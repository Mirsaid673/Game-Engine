#pragma once

#include "Attrib.h"
#include <initializer_list>

class VertexLayout
{
public:
    Attrib attribs[(u8)Attrib::Location::MAX];

private:
    u8 count = 0;

public:
    VertexLayout() = default;
    VertexLayout(std::initializer_list<Attrib> attribs_list);

    VertexLayout &add(const Attrib &attrib);
    VertexLayout &add(Attrib::Location l,
                      u8 comp_count = 3,
                      DataType t = DataType::FLOAT,
                      bool norm = false);

    u8 getCount() const { return count; }

public:
    using iterator = Attrib *;
    using const_iterator = const Attrib *;

    iterator begin() { return &attribs[0]; }
    iterator end() { return &attribs[count]; }

    const_iterator begin() const { return cbegin(); }
    const_iterator end() const { return cend(); }

    const_iterator cbegin() const { return &attribs[0]; }
    const_iterator cend() const { return &attribs[count]; }
};