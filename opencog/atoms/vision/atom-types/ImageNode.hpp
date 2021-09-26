/*
 * opencog/spacetime/octomap/OctoMapNode.h
 *
 * Copyright (C) 2018 Hanson Robotics
 * All Rights Reserved
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

#ifndef _OPENCOG_OCTOMAP_NODE_H
#define _OPENCOG_OCTOMAP_NODE_H
#include <memory>

#include <opencog/atoms/base/Node.h>

#include <opencv2/core/mat.hpp>

namespace opencog
{
/** \addtogroup grp_vision
 *  @{
 */

// ImageNode holds image data from a given path.
// It is used to open an image via OpenCV.

// using TimeOctomapPtr = std::shared_ptr<TimeOctomap<Handle>>;

class ImageNode : public Node
{
public:
    ImageNode(Type t, const std::string&);
    // ImageNode(const std::string&, TimeOctomapPtr);
    virtual ~ImageNode();

    static Handle factory(const Handle&);
};

// typedef std::shared_ptr<ImageNode> OctoMapNodePtr;

/** @}*/
}

#endif // _OPENCOG_OCTOMAP_NODE_H
