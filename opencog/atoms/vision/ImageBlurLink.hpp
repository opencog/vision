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

    virtual ValuePtr
    kons(AtomSpace*, bool, const ValuePtr&, const ValuePtr&) const;

public:
    ImageBlurLink(const Handle&, const Handle&);
    ImageBlurLink(const HandleSeq&&, Type = IMAGE_BLUR_LINK);

    ImageBlurLink(const ImageBlurLink&) = delete;
    ImageBlurLink& operator=(const ImageBlurLink&) = delete;

    static Handle factory(const Handle&);
};

typedef std::shared_ptr<ImageBlurLink> ImageBlurLinkPtr;
static inline ImageBlurLinkPtr ImageBlurLinkCast(const Handle& h) {
    AtomPtr a(h);
    return std::dynamic_pointer_cast<ImageBlurLink>(a);
}
static inline ImageBlurLinkPtr ImageBlurLinkCast(AtomPtr a) {
    return std::dynamic_pointer_cast<ImageBlurLink>(a);
}

#define createImageBlurLink std::make_shared<ImageBlurLink>

/** @}*/
} // namespace opencog

#endif // _OPENCOG_IMAGE_BLUR_LINK_H
