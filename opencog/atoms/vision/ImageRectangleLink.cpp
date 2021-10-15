/*
 * opencog/atoms/vision/ImageRectangleLink.cpp
 *
 * Copyright (C) 2021 Adrian Borucki
 * All Rights Reserved
 * SPDX-License-Identifier: AGPL-3.0-or-later
 */

#include "ImageRectangleLink.hpp"
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

ImageRectangleLink::ImageRectangleLink(HandleSeq oset, Type t) :
    FunctionLink(std::move(oset), t) {
    init();
}

void ImageRectangleLink::init() {
    Type tscope = get_type();
    if (not nameserver().isA(tscope, IMAGE_RECTANGLE_LINK))
        throw InvalidParamException(TRACE_INFO,
                                    "Expecting an ImageRectangleLink.");

    if (getOutgoingSet().size() != 4)
        throw InvalidParamException(TRACE_INFO,
                                    "Wrong number of arguments, expecting 4.");
}

ValuePtr ImageRectangleLink::execute(AtomSpace* atomspace, bool silent) {
    // -- type check --
    const Handle& arg1 = getOutgoingSet().at(0));
    Type arg1_type = arg1.const_atom_ptr()->get_type();
    if (not nameserver().isA(arg1_type, NUMBER_NODE))
        throw InvalidParamException(
            TRACE_INFO,
            "Wrong argument type on position 1, expecting NumberNode.");

    const Handle& arg2 = getOutgoingSet().at(1);
    Type arg2_type = arg2.const_atom_ptr()->get_type();
    if (not nameserver().isA(arg2_type, NUMBER_NODE))
        throw InvalidParamException(
            TRACE_INFO,
            "Wrong argument type on position 2, expecting NumberNode.");

    const Handle& arg3 = getOutgoingSet().at(2);
    Type arg3_type = arg3.const_atom_ptr()->get_type();
    if (not nameserver().isA(arg3_type, NUMBER_NODE))
        throw InvalidParamException(
            TRACE_INFO,
            "Wrong argument type on position 3, expecting NumberNode.");

    const Handle& arg4 = getOutgoingSet().at(3);
    Type arg4_type = arg4.const_atom_ptr()->get_type();
    if (not nameserver().isA(arg4_type, NUMBER_NODE))
        throw InvalidParamException(
            TRACE_INFO,
            "Wrong argument type on position 4, expecting NumberNode.");

    // -- argument processing --
    int x = std::stoi(NumberNodeCast(arg1)->get_name());
    int y = std::stoi(NumberNodeCast(arg2)->get_name());
    int width = std::stoi(NumberNodeCast(arg3)->get_name());
    int height = std::stoi(NumberNodeCast(arg4)->get_name());

    // -- procedure execution --
    cv::Rect2i rect(x, y, width, height);

    // TODO: figure out if this is needed.

    return createImageValue(rect);
}

DEFINE_LINK_FACTORY(ImageRectangleLink, IMAGE_RECTANGLE_LINK)
