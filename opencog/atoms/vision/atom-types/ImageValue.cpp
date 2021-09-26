#include "ImageValue.hpp"

#include <opencog/util/exceptions.h>
#include <opencog/atoms/base/ClassServer.h>
#include <opencog/atoms/value/ValueFactory.h>

using namespace opencog;


void ImageValue::update() const
{
    // auto it = (_om->get_locations_of_atom(_item)).rbegin(); //We need the last.
    // _value = {it->x(), it->y(), it->z()};
}

ImageValue::ImageValue(const HandleSeq& hseq) : FloatValue(IMAGE_VALUE)
{

    if( hseq.size() != 2) {
        throw InvalidParamException(TRACE_INFO, 
                "Required 2 arguments. Provided %d.", hseq.size());
    }

    _item = hseq[0];
    // _octo_node = hseq[1];
    // _om = OctoMapNodeCast(_octo_node)->get_map();
}

bool ImageValue::operator==(const Value& other) const
{
    if (IMAGE_VALUE != other.get_type()) return false;

    const ImageValue* fov = (const ImageValue*) &other;

    // if (_octo_node == fov->_octo_node) return true;

    return false;
}

std::string ImageValue::to_string(const std::string& indent) const
{
    update(); // Update values
    std::string rv = indent + "(" + nameserver().getTypeName(_type);
    rv += ("\n " + _item->to_short_string() + " ");
    // rv += (_octo_node->to_short_string() + " (");
    for (double v : _value) {
        char buf[40];
        snprintf(buf, 40, "%.17g", v);
        rv += std::string(" ") + buf;
    }
    rv += ")\n)\n";

    return rv;
}

// Adds factory when the library is loaded.
DEFINE_VALUE_FACTORY(IMAGE_VALUE, createOctoValue, HandleSeq)
