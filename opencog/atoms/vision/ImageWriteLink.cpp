/*
 * opencog/atoms/vision/ImageWriteLink.cpp
 *
 * Copyright (C) 2021 Adrian Borucki
 * All Rights Reserved
 * SPDX-License-Identifier: AGPL-3.0-or-later
 */

#include "ImageWriteLink.hpp"
#include "ImageNode.hpp"
#include "ImageValue.hpp"

#include <memory>
#include <opencog/atoms/base/ClassServer.h>
#include <opencog/atoms/atom_types/atom_types.h>
#include <opencog/atoms/base/Node.h>
#include <opencog/atoms/value/Value.h>
#include <opencog/atoms/flow/ValueOfLink.h>
#include <opencog/atoms/truthvalue/SimpleTruthValue.h>
#include <opencv2/core/types.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

using namespace opencog;

ImageWriteLink::ImageWriteLink(HandleSeq oset, Type t) :
    FunctionLink(std::move(oset), t) {
    init();
}

void ImageWriteLink::init() {
    Type tscope = get_type();
    if (not nameserver().isA(tscope, IMAGE_WRITE_LINK))
        throw InvalidParamException(TRACE_INFO, "Expecting an ImageWriteLink.");

    if (getOutgoingSet().size() != 2)
        throw InvalidParamException(TRACE_INFO,
                                    "Wrong number of arguments, expecting 2.");
}

ValuePtr ImageWriteLink::execute(AtomSpace* atomspace, bool silent) {
    const Handle& arg1 = getOutgoingSet().at(0);
    Type arg1_type = arg1.const_atom_ptr()->get_type();
    if (not(nameserver().isA(arg1_type, IMAGE_NODE) or
            nameserver().isA(arg1_type, VALUE_OF_LINK)))
        throw InvalidParamException(TRACE_INFO,
                                    "Wrong argument type on position 1, "
                                    "expecting ImageNode or ValueOfLink.");

    const Handle& arg2 = getOutgoingSet().at(1);
    Type arg2_type = arg2.const_atom_ptr()->get_type();
    if (not nameserver().isA(arg2_type,
                             CONCEPT_NODE)) // TODO: accept StringValue as well.
        throw InvalidParamException(TRACE_INFO,
                                    "Wrong argument type on position 2, "
                                    "expecting ConceptNode or ValueOfLink.");

    ImageValuePtr img_vp = nullptr;
    auto img_np = ImageNodeCast(arg1);
    auto img_vof = ValueOfLinkCast(arg1);
    if (img_vof != nullptr)
        img_vp = ImageValueCast(img_vof->execute(atomspace, silent));
    
    if (img_np == nullptr and img_vp == nullptr)
        return std::make_shared<SimpleTruthValue>(0, 1);

    const cv::Mat& image =
        img_np != nullptr ? img_np->image() : img_vp->image();
    const std::string& filepath = NodeCast(arg2)->get_name();

    cv::imwrite(filepath, image);

    return std::make_shared<SimpleTruthValue>(1, 1);
}

DEFINE_LINK_FACTORY(ImageWriteLink, IMAGE_WRITE_LINK)
