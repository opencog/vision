/*
 * opencog/atoms/vision/ImageFilter2DLink.hpp
 *
 * Copyright (C) 2021 Adrian Borucki
 * All Rights Reserved
 * SPDX-License-Identifier: AGPL-3.0-or-later
 */

#ifndef _OPENCOG_IMAGE_FILTER_2D_LINK_H
#define _OPENCOG_IMAGE_FILTER_2D_LINK_H

#include <opencog/atoms/core/FunctionLink.h>
#include <opencog/atoms/vision/atom_types.h>

namespace opencog {
/** \addtogroup grp_atomspace
 *  @{
 */

/**
 * The ImageBlurLink implements ...
 */
class ImageFilter2DLink : public FunctionLink {
  protected:
    void init();

  public:
    ImageFilter2DLink(HandleSeq, Type = IMAGE_FILTER_TWO_D_LINK);
    ~ImageFilter2DLink() override = default;

    ImageFilter2DLink(const ImageFilter2DLink&) = delete;
    ImageFilter2DLink& operator=(const ImageFilter2DLink&) = delete;

    static Handle factory(const Handle&);

    ValuePtr execute(AtomSpace*, bool = false) override;
};

using ImageFilter2DLinkPtr = std::shared_ptr<ImageFilter2DLink>;

static inline ImageFilter2DLinkPtr ImageFilter2DLinkCast(AtomPtr a) {
    return std::dynamic_pointer_cast<ImageFilter2DLink>(a);
}

static inline ImageFilter2DLinkPtr ImageFilter2DLinkCast(const Handle& h) {
    AtomPtr a(h);
    return std::dynamic_pointer_cast<ImageFilter2DLink>(a);
}

template <typename... Args>
static constexpr auto createImageFilter2DLink(Args&&... args) {
    return std::make_shared<ImageFilter2DLink>(args...);
}

/** @}*/
} // namespace opencog

#endif // _OPENCOG_IMAGE_FILTER_2D_LINK_H
