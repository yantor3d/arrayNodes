/**
    Copyright (c) 2016 Ryan Porter - arrayNodes
    You may use, distribute, or modify this code under the terms of the MIT license.
*/

#include <vector>

#include "n_slice.h"

#include <maya/MDataHandle.h>
#include <maya/MDoubleArray.h>
#include <maya/MFnDoubleArrayData.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MGlobal.h>
#include <maya/MPlug.h>
#include <maya/MPxNode.h>

using namespace std;

MObject SliceArrayNode::aInput;
MObject SliceArrayNode::aStartIndex;
MObject SliceArrayNode::aStopIndex;
MObject SliceArrayNode::aStepSize;
MObject SliceArrayNode::aOutput;

void* SliceArrayNode::creator()
{
    return new SliceArrayNode();
}

MStatus SliceArrayNode::initialize()
{
    MStatus status;

    MFnTypedAttribute T;
    MFnNumericAttribute N;

    aInput = T.create("input", "i", MFnData::kDoubleArray);
    T.setKeyable(false);
    T.setStorable(true);
    T.setWritable(true);

    aStartIndex = N.create("start", "st", MFnNumericData::kInt);
    N.setKeyable(true);
    N.setStorable(true);
    N.setWritable(true);

    aStopIndex = N.create("stop", "sp", MFnNumericData::kInt, -1);
    N.setKeyable(true);
    N.setStorable(true);
    N.setWritable(true);
    N.setDefault(-1);

    aStepSize = N.create("step", "ss", MFnNumericData::kInt, 1);
    N.setKeyable(true);
    N.setStorable(true);
    N.setWritable(true);
    N.setDefault(1);

    aOutput = T.create("output", "o", MFnData::kDoubleArray);
    T.setKeyable(false);
    T.setChannelBox(false);
    T.setWritable(false);
    T.setStorable(false);

    addAttribute(aInput);
    addAttribute(aStartIndex);
    addAttribute(aStopIndex);
    addAttribute(aStepSize);
    addAttribute(aOutput);

    attributeAffects(aInput, aOutput);
    attributeAffects(aStartIndex, aOutput);
    attributeAffects(aStopIndex, aOutput);
    attributeAffects(aStepSize, aOutput);

    return MS::kSuccess;
}

void SliceArrayNode::postConstructor()
{
    this->setExistWithoutOutConnections(true);
}

MStatus SliceArrayNode::compute(const MPlug& plug, MDataBlock& data)
{
    MStatus status;

    int start = data.inputValue(aStartIndex).asInt();
    int stop = data.inputValue(aStopIndex).asInt();
    int step = data.inputValue(aStepSize).asInt();

    if (step == 0)
    {
        MGlobal::displayWarning(this->name() + " - slice step size cannot be zero.");
        return MS::kInvalidParameter;
    }

    MDataHandle inputHandle = data.inputValue(aInput);
    MFnDoubleArrayData inputArrayData(inputHandle.data());

    int numInputs = inputArrayData.length();

    vector<int> slice = vector<int>();

    start = start >= 0 ? start : numInputs - start;
    stop = stop >= 0 ? stop : numInputs - stop;

    int index = start;

    while ((step > 0) ? (index < stop) : (index > stop))
    {
        if (index >= 0 && index < numInputs)
            slice.push_back(index);

        index += step;
    }

    int outputSize = int(slice.size());
    MDoubleArray outputArray(outputSize);

    for (int i = 0; i < outputSize; i++)
    {
        outputArray.set(inputArrayData[slice[i]], i);
    }

    MFnDoubleArrayData outputArrayData;
    MObject outputData = outputArrayData.create(outputArray);

    MDataHandle outputHandle = data.outputValue(aOutput);
    outputHandle.setMObject(outputData);
    outputHandle.setClean();

    return MS::kSuccess;
}