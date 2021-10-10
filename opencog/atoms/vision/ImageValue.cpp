#include "ImageValue.hpp"

#include <opencog/atoms/base/ClassServer.h>
#include <opencog/atoms/value/ValueFactory.h>
#include <opencog/atoms/vision/atom_types.h>
#include <opencog/util/exceptions.h>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

using namespace opencog;

void ImageValue::update() const {}

bool ImageValue::image_equal(const cv::Mat& im_left,
                             const cv::Mat& im_right) const {
    if (im_left.empty() && im_right.empty())
        return true;

    if (im_left.cols != im_right.cols || im_left.rows != im_right.rows ||
        im_left.dims != im_right.dims)
        return false;

    cv::Mat diff;
    cv::Mat diff1color;
    cv::compare(im_left, im_right, diff, cv::CMP_NE);

    cv::cvtColor(diff, diff1color, cv::COLOR_BGRA2GRAY, 1);
    int nz = cv::countNonZero(diff1color);

    return nz == 0;
}

ImageValue::ImageValue(cv::Mat image) :
    Value(IMAGE_VALUE), _image(std::move(image)) {}

bool ImageValue::operator==(const Value& other) const {
    if (IMAGE_VALUE != other.get_type())
        return false;

    auto other_image = dynamic_cast<const ImageValue&>(other)._image;
    return image_equal(_image, other_image);
}

std::string ImageValue::to_string(const std::string& indent) const {
    update();
    std::string rv = indent + "(" + nameserver().getTypeName(_type);
    rv += " <image array>";
    rv += ")\n";

    return rv;
}

const cv::Mat& ImageValue::image() const { return _image; }

// Adds factory when the library is loaded.
DEFINE_VALUE_FACTORY(IMAGE_VALUE, createImageValue, cv::Mat)
