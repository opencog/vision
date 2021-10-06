/*
 * opencog/atoms/vision/atom-types/ImageNode.hpp
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License v3 as
 * published by the Free Software Foundation and including the
 * exceptions at http://opencog.org/wiki/Licenses
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public
 * License along with this program; if not, write to:
 * Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef _OPENCOG_IMAGE_NODE_H
#define _OPENCOG_IMAGE_NODE_H

#include <memory>

#include <opencog/atoms/base/Node.h>

#include <opencv2/core/mat.hpp>

namespace opencog {
/** \addtogroup grp_atomspace
 *  @{
 */

// ImageNode holds image data from a given path.
// It is used to open an image via OpenCV.
class ImageNode : public Node {
  private:
    cv::Mat _image;

  public:
    ImageNode(Type t, const std::string&);
    ~ImageNode() override = default;

    static Handle factory(const Handle&);

    const cv::Mat& image() const;
};

using ImageNodePtr = std::shared_ptr<ImageNode>;

static inline ImageNodePtr ImageNodeCast(const Handle& h) {
    return std::dynamic_pointer_cast<ImageNode>(h);
}

static inline ImageNodePtr ImageNodeCast(AtomPtr a) {
    return std::dynamic_pointer_cast<ImageNode>(a);
}

#define createImageNode std::make_shared<ImageNode>

/** @}*/
} // namespace opencog

#endif // _OPENCOG_IMAGE_NODE_H
