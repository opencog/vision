#include "ImageValue.hpp"

#include <opencog/atoms/base/ClassServer.h>
#include <opencog/atoms/value/ValueFactory.h>
#include <opencog/atoms/vision/atom_types.h>
#include <opencog/util/exceptions.h>

using namespace opencog;

void ImageValue::update() const {}

ImageValue::ImageValue(const cv::Mat& image) : Value(IMAGE_VALUE) {
    _image = image;
}

bool ImageValue::operator==(const Value& other) const {
    if (IMAGE_VALUE != other.get_type())
        return false;

    auto other_image = dynamic_cast<const ImageValue&>(other)._image;
    return _image == other_image;
}

std::string ImageValue::to_string(const std::string& indent) const {
    update();
    std::string rv = indent + "(" + nameserver().getTypeName(_type);
    rv += "<image array>\n"; // TODO: pretty printing of image arrays.
    rv += ")\n";

    return rv;
}

// Adds factory when the library is loaded.
DEFINE_VALUE_FACTORY(IMAGE_VALUE, createImageValue, HandleSeq)
