/*
 * opencog/atoms/vision/ImageBlurLink.cpp
 *
 * Copyright (C) 2021 Adrian Borucki
 * All Rights Reserved
 * SPDX-License-Identifier: AGPL-3.0-or-later
 */

#include "ImageBlurLink.hpp"

#include <opencog/atoms/base/ClassServer.h>

using namespace opencog;

ImageBlurLink::ImageBlurLink(const Handle& a, const Handle& b) :
    FunctionLink({a, b}, IMAGE_BLUR_LINK) {
    init();
}

ImageBlurLink::ImageBlurLink(const HandleSeq&& oset, Type t) :
    FunctionLink(std::move(oset), t) {
    init();
}

void ImageBlurLink::init() {

    Type tscope = get_type();
    if (not nameserver().isA(tscope, IMAGE_BLUR_LINK))
        throw InvalidParamException(TRACE_INFO, "Expecting a ImageBlurLink");
}

ValuePtr ImageBlurLink::kons(AtomSpace* as,
                        bool silent,
                        const ValuePtr& fi,
                        const ValuePtr& fj) const {}

DEFINE_LINK_FACTORY(ImageBlurLink, IMAGE_BLUR_LINK)
