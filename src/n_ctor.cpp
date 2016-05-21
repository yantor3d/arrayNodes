/**
    Copyright (c) 2016 Ryan Porter - arrayNodes
    You may use, distribute, or modify this code under the terms of the MIT license.
*/

#include "n_ctor.h"

#include <maya/MDataBlock.h>
#include <maya/MDoubleArray.h>
#include <maya/MFnDoubleArrayData.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MPlug.h>
#include <maya/MPxNode.h>
#include <maya/MString.h>
#include <maya/MTypeId.h>

MObject ArrayConstructorNode::aSize;
MObject ArrayConstructorNode::aInput;
MObject ArrayConstructorNode::aOutput;

void* ArrayConstructorNode::creator()
{
    return new ArrayConstructorNode();
}

MStatus ArrayConstructorNode::initialize()
{
    MStatus status;

    MFnNumericAttribute N;
    MFnTypedAttribute T;

    aSize = N.create("size", "size", MFnNumericData::kInt, 8.0, &status);
    N.setKeyable(true);
    N.setStorable(true);
    N.setWritable(true);
    N.setDefault(8);

    aInput = N.create("input", "i", MFnNumericData::kDouble, 0.0, &status);
    N.setKeyable(false);
    N.setStorable(true);
    N.setWritable(true);
    N.setArray(true);

    aOutput = T.create("output", "o", MFnData::kDoubleArray, &status);
    T.setKeyable(false);
    T.setChannelBox(false);
    T.setWritable(false);
    T.setStorable(false);

    addAttribute(aSize);
    addAttribute(aInput);
    addAttribute(aOutput);

    attributeAffects(aSize, aOutput);
    attributeAffects(aInput, aOutput);

    return MS::kSuccess;
}

MStatus ArrayConstructorNode::compute(const MPlug& plug, MDataBlock& data)
{
    if (plug != aOutput)
        return MS::kUnknownParameter;

    MStatus status;

    int index;

    MArrayDataHandle inputArrayHandle = data.inputArrayValue(aInput);
    int inputSize = inputArrayHandle.elementCount();
    int outputSize = data.inputValue(aSize).asInt();

    MDoubleArray outputArray(outputSize);

    for (int i = 0; i < inputSize; i++)
    {
        index = inputArrayHandle.elementIndex();

        if (index >= outputSize) break;

        outputArray[index] = inputArrayHandle.inputValue().asDouble();

        if (!inputArrayHandle.next()) break;
    }

    MFnDoubleArrayData outputArrayData;
    MObject outputData = outputArrayData.create(outputArray, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);

    MDataHandle outputHandle = data.outputValue(aOutput);
    outputHandle.setMObject(outputData);
    outputHandle.setClean();

    return MS::kSuccess;
}