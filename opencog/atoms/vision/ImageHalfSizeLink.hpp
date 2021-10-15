/*
 * opencog/atoms/vision/ImageHalfSizeLink.hpp
 *
 * Copyright (C) 2021 Adrian Borucki
 * All Rights Reserved
 * SPDX-License-Identifier: AGPL-3.0-or-later
 */

#ifndef _OPENCOG_IMAGE_HALF_SIZE_LINK_H
#define _OPENCOG_IMAGE_HALF_SIZE_LINK_H

#include <opencog/atoms/core/FunctionLink.h>
#include <opencog/atoms/vision/atom_types.h>

namespace opencog {
/** \addtogroup grp_atomspace
 *  @{
 */

/**
 * The ImageHalfSizeLink implements ...
 */
class ImageHalfSizeLink : public FunctionLink {
  protected:
    void init();

  public:
    ImageHalfSizeLink(HandleSeq, Type = IMAGE_HALF_SIZE_LINK);
    ~ImageHalfSizeLink() override = default;

    ImageHalfSizeLink(const ImageHalfSizeLink&) = delete;
    ImageHalfSizeLink& operator=(const ImageHalfSizeLink&) = delete;

    static Handle factory(const Handle&);

    ValuePtr execute(AtomSpace*, bool = false) override;
};

using ImageHalfSizeLinkPtr = std::shared_ptr<ImageHalfSizeLink>;

static inline ImageHalfSizeLinkPtr ImageHalfSizeLinkCast(AtomPtr a) {
    return std::dynamic_pointer_cast<ImageHalfSizeLink>(a);
}

static inline ImageHalfSizeLinkPtr ImageHalfSizeLinkCast(const Handle& h) {
    AtomPtr a(h);
    return std::dynamic_pointer_cast<ImageHalfSizeLink>(a);
}

template <typename... Args>
static constexpr auto createImageHalfSizeLink(Args&&... args) {
    return std::make_shared<ImageHalfSizeLink>(args...);
}

/** @}*/
} // namespace opencog

#endif // _OPENCOG_IMAGE_HALF_SIZE_LINK_H
