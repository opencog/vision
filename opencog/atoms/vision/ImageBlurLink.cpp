/*
 * opencog/atoms/vision/ImageBlurLink.cpp
 *
 * Copyright (C) 2021 Adrian Borucki
 * All Rights Reserved
 * SPDX-License-Identifier: AGPL-3.0-or-later
 */

#include "ImageBlurLink.hpp"
#include "ImageNode.hpp"
#include "ImageValue.hpp"

#include <memory>
#include <opencog/atoms/base/ClassServer.h>
#include <opencog/atoms/core/NumberNode.h>
#include <opencog/atoms/value/Value.h>
#include <opencv2/core/types.hpp>
#include <opencv2/imgproc.hpp>

using namespace opencog;

ImageBlurLink::ImageBlurLink(const HandleSeq&& oset, Type t) :
    FunctionLink(std::move(oset), t) {
    init();
}

void ImageBlurLink::init() {
    Type tscope = get_type();
    if (not nameserver().isA(tscope, IMAGE_BLUR_LINK))
        throw InvalidParamException(TRACE_INFO, "Expecting an ImageBlurLink.");

    if (getOutgoingSet().size() != 1)
        throw InvalidParamException(TRACE_INFO,
                                    "Wrong number of arguments, expecting 1.");
}

ValuePtr ImageBlurLink::execute(AtomSpace* atomspace, bool silent) {
    const Handle& arg1 = getOutgoingSet().at(0);
    Type arg1_type = arg1.const_atom_ptr()->get_type();
    if (!(arg1_type == IMAGE_NODE || arg1_type == IMAGE_VALUE))
        throw InvalidParamException(TRACE_INFO,
                                    "Wrong argument type on position 1, "
                                    "expecting ImageNode or ImageValue.");

    const Handle& arg2 = getOutgoingSet().at(1);
    Type arg2_type = arg2.const_atom_ptr()->get_type();
    if (arg2_type != NUMBER_NODE)
        throw InvalidParamException(
            TRACE_INFO,
            "Wrong argument type on position 2, expecting NumberNode.");

    auto img_np = ImageNodeCast(arg1);
    auto img_vp = ImageValueCast(arg1);
    const cv::Mat& input =
        img_np != nullptr ? img_np->image() : img_vp->image();
    const int ksize = std::stoi(NumberNodeCast(arg2)->get_name());

    cv::Mat output;
    cv::blur(input, output, cv::Size(ksize, ksize));

    ImageValuePtr ivp = createImageValue(output);
    return std::dynamic_pointer_cast<Value>(ivp);
}

DEFINE_LINK_FACTORY(ImageBlurLink, IMAGE_BLUR_LINK)
