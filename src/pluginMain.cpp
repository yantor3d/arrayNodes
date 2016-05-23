/**
    Copyright (c) 2016 Ryan Porter
*/

/*
    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

/**
    @mainpage Array Nodes

    @author: Ryan Porter
    @version: 1.0.0

    @sa https://github.com/yantor3d

    ## Description
        A set of nodes for performing calculates on sets of values in a single 
        node rather than in dozens or hundreds of nodes. This allows for the 
        construction of a more compact node graph that won't get bogged down by 
        tens or hundreds of identical sub-graphs.

    ## Nodes
        - <a href="class_array_constructor_node.html">arrayCtor</a>
        - <a href="class_array_iterator_node.html">arrayIter</a>
        - <a href="class_array_multi_operator_node.html">arrayMultiOp</a>
        - <a href="class_array_scalar_operation_node.html">arrayScalarOp</a>
        - <a href="class_chain_arrays_node.html">chainArray</a>
        - <a href="class_clamp_array_node.html">clampArray</a>
        - <a href="class_modify_array_node.html">modifyArray</a>
        - <a href="class_normalize_array_node.html">normalizeArray</a>
        - <a href="class_reduce_array_node.html">reduceArray</a>
        - <a href="class_remap_array_values_node.html">remapArrayValues</a>
        - <a href="class_slice_array_node.html">sliceArray</a>

    ## Commands
        - n/a
*/

#include "n_chain.h"
#include "n_clamp.h"
#include "n_ctor.h"
#include "n_iter.h"
#include "n_modify.h"
#include "n_multi.h"
#include "n_normalize.h"
#include "n_remap.h"
#include "n_scalar.h"
#include "n_slice.h"

#include <maya/MFnPlugin.h>
#include <maya/MTypeId.h>
#include <maya/MString.h>

const char* kAUTHOR = "Ryan Porter";
const char* kVERSION = "1.0.0";
const char* kREQUIRED_API_VERSION = "Any";

MTypeId ArrayConstructorNode::kNODE_ID = 0x00126b00;
MString ArrayConstructorNode::kNODE_NAME = "arrayCtor";

MTypeId ArrayIteratorNode::kNODE_ID = 0x00126b01;
MString ArrayIteratorNode::kNODE_NAME = "arrayIter";

MTypeId ArrayMultiOperatorNode::kNODE_ID = 0x00126b02;
MString ArrayMultiOperatorNode::kNODE_NAME = "arrayMultiOp";

MTypeId ArrayScalarOperationNode::kNODE_ID = 0x00126b03;
MString ArrayScalarOperationNode::kNODE_NAME = "arrayScalarOp";

MTypeId ModifyArrayNode::kNODE_ID = 0x00126b04;
MString ModifyArrayNode::kNODE_NAME = "modifyArray";

MTypeId NormalizeArrayNode::kNODE_ID = 0x00126b05;
MString NormalizeArrayNode::kNODE_NAME = "normalizeArray";

MTypeId RemapArrayValuesNode::kNODE_ID = 0x00126b06;
MString RemapArrayValuesNode::kNODE_NAME = "remapArrayValues";

MTypeId ClampArrayNode::kNODE_ID = 0x00126b07;
MString ClampArrayNode::kNODE_NAME = "clampArray";

MTypeId SliceArrayNode::kNODE_ID = 0x00126b08;
MString SliceArrayNode::kNODE_NAME = "sliceArray";

MTypeId ChainArraysNode::kNODE_ID = 0x00126b09;
MString ChainArraysNode::kNODE_NAME = "chainArrays";

#define REGISTER_NODE(NODE)                    \
    status = fnPlugin.registerNode(            \
        NODE::kNODE_NAME,                    \
        NODE::kNODE_ID,                        \
        NODE::creator,                        \
        NODE::initialize                    \
    );                                        \
    CHECK_MSTATUS_AND_RETURN_IT(status);    \

#define DEREGISTER_NODE(NODE)                \
    status = fnPlugin.deregisterNode(        \
        NODE::kNODE_ID                        \
    );                                        \
    CHECK_MSTATUS_AND_RETURN_IT(status);    \

MStatus initializePlugin(MObject obj)
{
    MStatus status;
    MFnPlugin fnPlugin(obj, kAUTHOR, kVERSION, kREQUIRED_API_VERSION);

    REGISTER_NODE(ArrayConstructorNode);
    REGISTER_NODE(ArrayMultiOperatorNode);
    REGISTER_NODE(ArrayIteratorNode);
    REGISTER_NODE(ArrayScalarOperationNode);
    REGISTER_NODE(ModifyArrayNode);
    REGISTER_NODE(ChainArraysNode);
    REGISTER_NODE(ClampArrayNode);
    REGISTER_NODE(NormalizeArrayNode);
    REGISTER_NODE(RemapArrayValuesNode);
    REGISTER_NODE(SliceArrayNode);

    return MS::kSuccess;
}

MStatus uninitializePlugin(MObject obj)
{
    MStatus status;
    MFnPlugin fnPlugin(obj, kAUTHOR, kVERSION, kREQUIRED_API_VERSION);

    DEREGISTER_NODE(ArrayConstructorNode);
    DEREGISTER_NODE(ArrayMultiOperatorNode);
    DEREGISTER_NODE(ArrayIteratorNode);
    DEREGISTER_NODE(ArrayScalarOperationNode);
    DEREGISTER_NODE(ModifyArrayNode);
    DEREGISTER_NODE(ChainArraysNode);
    DEREGISTER_NODE(ClampArrayNode);
    DEREGISTER_NODE(NormalizeArrayNode);
    DEREGISTER_NODE(RemapArrayValuesNode);
    DEREGISTER_NODE(SliceArrayNode);

    return MS::kSuccess;
}