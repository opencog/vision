/*
 * opencog/atoms/vision/ImageRectangleLink.hpp
 *
 * Copyright (C) 2021 Adrian Borucki
 * All Rights Reserved
 * SPDX-License-Identifier: AGPL-3.0-or-later
 */

#ifndef _OPENCOG_IMAGE_RECTANGLE_LINK_H
#define _OPENCOG_IMAGE_RECTANGLE_LINK_H

#include <opencog/atoms/core/FunctionLink.h>
#include <opencog/atoms/vision/atom_types.h>

namespace opencog {
/** \addtogroup grp_atomspace
 *  @{
 */

/**
 * The ImageRectangleLink implements ...
 */
class ImageRectangleLink : public FunctionLink {
  protected:
    void init();

  public:
    ImageRectangleLink(HandleSeq, Type = IMAGE_RECTANGLE_LINK);
    ~ImageRectangleLink() override = default;

    ImageRectangleLink(const ImageRectangleLink&) = delete;
    ImageRectangleLink& operator=(const ImageRectangleLink&) = delete;

    static Handle factory(const Handle&);

    ValuePtr execute(AtomSpace*, bool = false) override;
};

using ImageRectangleLinkPtr = std::shared_ptr<ImageRectangleLink>;

static inline ImageRectangleLinkPtr ImageRectangleLinkCast(AtomPtr a) {
    return std::dynamic_pointer_cast<ImageRectangleLink>(a);
}

static inline ImageRectangleLinkPtr ImageRectangleLinkCast(const Handle& h) {
    AtomPtr a(h);
    return std::dynamic_pointer_cast<ImageRectangleLink>(a);
}

template <typename... Args>
static constexpr auto createImageRectangleLink(Args&&... args) {
    return std::make_shared<ImageRectangleLink>(args...);
}

/** @}*/
} // namespace opencog

#endif // _OPENCOG_IMAGE_RECTANGLE_LINK_H
