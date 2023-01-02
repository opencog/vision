#ifndef _OPENCOG_IMAGE_VALUE_H_
#define _OPENCOG_IMAGE_VALUE_H_

#include <typeindex>

#include <opencog/atoms/atom_types/atom_types.h>
#include <opencog/atoms/value/Value.h>
#include <opencog/atoms/value/ValueFactory.h>
#include <opencog/atomspace/AtomSpace.h>

#include <opencv2/core/mat.hpp>

namespace opencog {
/** \addtogroup grp_atomspace
 *  @{
 */

// ImageValue holds image data (OpenCV data type).
// It is used for storing results of operating on images.
class ImageValue : public Value {
  private:
    cv::Mat _image;

  protected:
    void update() const;
    bool image_equal(const cv::Mat&, const cv::Mat&) const;

  public:
    /**
     * @param image an OpenCV `Mat` instance that contains the image pixel
     * array.
     */
    ImageValue(cv::Mat image);
    ~ImageValue() override = default;

    virtual ValuePtr value_at_index(size_t) const { return nullptr; }

    bool operator==(const Value& other) const override;

    std::string to_string(const std::string& indent = "") const override;

    const cv::Mat& image() const;
};

using ImageValuePtr = std::shared_ptr<ImageValue>;

static inline ImageValuePtr ImageValueCast(const ValuePtr& a) {
    return std::dynamic_pointer_cast<ImageValue>(a);
}

template <typename... Args>
static inline ImageValuePtr createImageValue(Args&&... args) {
    return std::make_shared<ImageValue>(args...);
}

/** @}*/
} // namespace opencog
#endif
