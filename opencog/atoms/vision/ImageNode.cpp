/*
 * opencog/atoms/vision/ImageNode.cpp
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

#include "ImageNode.hpp"

#include <mutex>

#include <opencog/atoms/atom_types/NameServer.h>
#include <opencog/atoms/vision/atom_types.h>
#include <opencog/util/Logger.h>

#include <opencv2/imgcodecs.hpp>

using namespace opencog;

ImageNode::ImageNode(Type t, const std::string& filename) :
    Node(t, filename), _image(cv::imread(filename)) {}

const cv::Mat& ImageNode::image() const { return _image; }

// Add factory.
DEFINE_NODE_FACTORY(ImageNode, IMAGE_NODE)
