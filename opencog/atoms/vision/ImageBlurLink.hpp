/*
 * opencog/atoms/vision/ImageBlurLink.hpp
 *
 * Copyright (C) 2021 Adrian Borucki
 * All Rights Reserved
 * SPDX-License-Identifier: AGPL-3.0-or-later
 */

#ifndef _OPENCOG_IMAGE_BLUR_LINK_H
#define _OPENCOG_IMAGE_BLUR_LINK_H

#include <opencog/atoms/core/FunctionLink.h>
#include <opencog/atoms/vision/atom_types.h>

namespace opencog {
/** \addtogroup grp_atomspace
 *  @{
 */

/**
 * The ImageBlurLink implements ...
 */
class ImageBlurLink : public FunctionLink {
  protected:
    void init();

  public:
    ImageBlurLink(HandleSeq, Type = IMAGE_BLUR_LINK);
    ~ImageBlurLink() override = default;

    ImageBlurLink(const ImageBlurLink&) = delete;
    ImageBlurLink& operator=(const ImageBlurLink&) = delete;

    static Handle factory(const Handle&);

    virtual bool is_executable() const { return true; }
    virtual ValuePtr execute(AtomSpace*, bool = false);
};

using ImageBlurLinkPtr = std::shared_ptr<ImageBlurLink>;

static inline ImageBlurLinkPtr ImageBlurLinkCast(AtomPtr a) {
    return std::dynamic_pointer_cast<ImageBlurLink>(a);
}

static inline ImageBlurLinkPtr ImageBlurLinkCast(const Handle& h) {
    AtomPtr a(h);
    return std::dynamic_pointer_cast<ImageBlurLink>(a);
}

template <typename... Args>
static constexpr auto createImageBlurLink(Args&&... args) {
    return std::make_shared<ImageBlurLink>(args...);
}

/** @}*/
} // namespace opencog

#endif // _OPENCOG_IMAGE_BLUR_LINK_H
