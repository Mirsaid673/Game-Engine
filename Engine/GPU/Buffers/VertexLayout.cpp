#include "VertexLayout.h"

VertexLayout &VertexLayout::add(const Attrib& attrib)
{
    attribs[count] = attrib;
    count++;

    return *this;
}

VertexLayout &VertexLayout::add(Attrib::Location l, DataType t, u8 comp_count, bool norm)
{
    attribs[count].location = l;
    attribs[count].data_type = t;
    attribs[count].component_count = comp_count;
    attribs[count].normalized = norm;
    count++;
    return *this;
}

VertexLayout::VertexLayout(std::initializer_list<Attrib> attribs_list)
{
    for (auto attribute : attribs_list)
    {
        attribs[count] = attribute;
        count++;
    }
}