/*
 * opencog/atoms/vision/ImageFilter2DLink.cpp
 *
 * Copyright (C) 2021 Adrian Borucki
 * All Rights Reserved
 * SPDX-License-Identifier: AGPL-3.0-or-later
 */

#include "ImageFilter2DLink.hpp"
#include "ImageNode.hpp"
#include "ImageValue.hpp"

#include <memory>
#include <opencog/atoms/base/ClassServer.h>
#include <opencog/atoms/core/NumberNode.h>
#include <opencog/atoms/flow/ValueOfLink.h>
#include <opencog/atoms/value/Value.h>
#include <opencv2/core/types.hpp>
#include <opencv2/imgproc.hpp>

using namespace opencog;

ImageFilter2DLink::ImageFilter2DLink(HandleSeq oset, Type t) :
    FunctionLink(std::move(oset), t) {
    init();
}

void ImageFilter2DLink::init() {
    Type tscope = get_type();
    if (not nameserver().isA(tscope, IMAGE_FILTER_TWO_D_LINK))
        throw InvalidParamException(TRACE_INFO,
                                    "Expecting an ImageFilter2DLink.");

    if (getOutgoingSet().size() != 3)
        throw InvalidParamException(TRACE_INFO,
                                    "Wrong number of arguments, expecting 3.");
}

ValuePtr ImageFilter2DLink::execute(AtomSpace* atomspace, bool silent) {
    // -- type check --
    const Handle& arg1 = getOutgoingSet().at(0);
    Type arg1_type = arg1.const_atom_ptr()->get_type();
    if (not(nameserver().isA(arg1_type, IMAGE_NODE) or
            nameserver().isA(arg1_type, VALUE_OF_LINK)))
        throw InvalidParamException(TRACE_INFO,
                                    "Wrong argument type on position 1, "
                                    "expecting ImageNode or ValueOf.");

    const Handle& arg2 = getOutgoingSet().at(1);
    Type arg2_type = arg2.const_atom_ptr()->get_type();
    if (not nameserver().isA(arg2_type, NUMBER_NODE))
        throw InvalidParamException(
            TRACE_INFO,
            "Wrong argument type on position 2, expecting NumberNode.");

    const Handle& arg3 = getOutgoingSet().at(2);
    Type arg3_type = arg3.const_atom_ptr()->get_type();
    if (not(nameserver().isA(arg3_type, IMAGE_NODE) or
            nameserver().isA(arg3_type, VALUE_OF_LINK)))
        throw InvalidParamException(TRACE_INFO,
                                    "Wrong argument type on position 3, "
                                    "expecting ImageNode or ValueOf.");

    // -- argument processing --
    // arg-1: input image
    ImageValuePtr img_vp = nullptr;
    auto img_atm = ImageNodeCast(arg1);
    auto img_vof = ValueOfLinkCast(arg1);
    if (img_vof != nullptr)
        img_vp = ImageValueCast(img_vof->execute(atomspace, silent));

    if (img_atm == nullptr and img_vp == nullptr)
        throw InvalidParamException(
            TRACE_INFO, "Invalid arguments: could not get valid input.");

    // arg-3: kernel
    ImageValuePtr kernel_vp = nullptr;
    auto kernel_atm = ImageNodeCast(arg1);
    auto kernel_vof = ValueOfLinkCast(arg1);
    if (kernel_vof != nullptr)
        kernel_vp = ImageValueCast(kernel_vof->execute(atomspace, silent));

    if (kernel_atm == nullptr and kernel_vp == nullptr)
        throw InvalidParamException(
            TRACE_INFO, "Invalid arguments: could not get valid input.");

    // -- procedure execution --
    const cv::Mat& input =
        img_atm != nullptr ? img_atm->image() : img_vp->image();
    int ddepth = std::stoi(NumberNodeCast(arg2)->get_name());

    cv::Mat output;
    cv::filter2D(input, output, ddepth, kernel_vp->image());

    return createImageValue(output);
}

DEFINE_LINK_FACTORY(ImageFilter2DLink, IMAGE_FILTER_TWO_D_LINK)
