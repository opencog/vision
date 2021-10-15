/*
 * opencog/atoms/vision/ImageWriteLink.hpp
 *
 * Copyright (C) 2021 Adrian Borucki
 * All Rights Reserved
 * SPDX-License-Identifier: AGPL-3.0-or-later
 */

#ifndef _OPENCOG_IMAGE_WRITE_LINK_H
#define _OPENCOG_IMAGE_WRITE_LINK_H

#include <opencog/atoms/core/FunctionLink.h>
#include <opencog/atoms/vision/atom_types.h>

namespace opencog {
/** \addtogroup grp_atomspace
 *  @{
 */

/**
 * The ImageWriteLink implements OpenCV `imwrite` operation.
 * 
 * signature: ImageWrite <Image or ValueOf[ImageValue]> <Concept or ValueOf[StringValue]>
 */
class ImageWriteLink : public FunctionLink {
  protected:
    void init();

  public:
    ImageWriteLink(HandleSeq, Type = IMAGE_WRITE_LINK);
    ~ImageWriteLink() override = default;

    ImageWriteLink(const ImageWriteLink&) = delete;
    ImageWriteLink& operator=(const ImageWriteLink&) = delete;

    static Handle factory(const Handle&);

    /**
     * Save a given image to a given location
     *
     * Returns STV 1 1 on success and STV 0 1 on failure.
     */
    ValuePtr execute(AtomSpace*, bool = false) override;
};

using ImageWriteLinkPtr = std::shared_ptr<ImageWriteLink>;

static inline ImageWriteLinkPtr ImageWriteLinkCast(AtomPtr a) {
    return std::dynamic_pointer_cast<ImageWriteLink>(a);
}

static inline ImageWriteLinkPtr ImageWriteLinkCast(const Handle& h) {
    AtomPtr a(h);
    return std::dynamic_pointer_cast<ImageWriteLink>(a);
}

template <typename... Args>
static constexpr auto createImageWriteLink(Args&&... args) {
    return std::make_shared<ImageWriteLink>(args...);
}

/** @}*/
} // namespace opencog

#endif // _OPENCOG_IMAGE_WRITE_LINK_H
