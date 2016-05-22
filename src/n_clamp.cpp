/** 
    Copyright (c) 2016 Ryan Porter - arrayNodes
    You may use, distribute, or modify this code under the terms of the MIT license.
*/

#include <algorithm>

#include "n_clamp.h"

#include <maya/MDataHandle.h>
#include <maya/MDoubleArray.h>
#include <maya/MFnDoubleArrayData.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MPlug.h>
#include <maya/MPxNode.h>

using namespace std;

MObject ClampArrayNode::aInput;
MObject ClampArrayNode::aMin;
MObject ClampArrayNode::aMax;
MObject ClampArrayNode::aOutput;

void* ClampArrayNode::creator()
{
    return new ClampArrayNode();
}

MStatus ClampArrayNode::initialize()
{
    MStatus status;

    MFnTypedAttribute T;
    MFnNumericAttribute N;

    aInput = T.create("input", "i", MFnData::kDoubleArray);
    T.setKeyable(false);
    T.setStorable(true);
    T.setWritable(true);

    aMin = N.create("min", "mn", MFnNumericData::kDouble);
    N.setKeyable(true);
    N.setStorable(true);
    N.setWritable(true);
    N.setDefault(0.0);

    aMax = N.create("max", "max", MFnNumericData::kDouble);
    N.setKeyable(true);
    N.setStorable(true);
    N.setWritable(true);
    N.setDefault(1.0);

    aOutput = T.create("output", "o", MFnData::kDoubleArray);
    T.setKeyable(false);
    T.setChannelBox(false);
    T.setWritable(false);
    T.setStorable(false);

    addAttribute(aInput);
    addAttribute(aMin);
    addAttribute(aMax);
    addAttribute(aOutput);

    attributeAffects(aInput, aOutput);
    attributeAffects(aMin, aOutput);
    attributeAffects(aMax, aOutput);

    return MS::kSuccess;
}

void ClampArrayNode::postConstructor()
{
    this->setExistWithoutOutConnections(true);
}

MStatus ClampArrayNode::compute(const MPlug& plug, MDataBlock& data)
{
    if (plug != aOutput)
        return MS::kUnknownParameter;

    MStatus status;

    double mn = data.inputValue(aMin).asDouble();
    double mx = data.inputValue(aMax).asDouble();

    MDataHandle inputHandle = data.inputValue(aInput);
    MFnDoubleArrayData inputArrayData(inputHandle.data());
    MDoubleArray inputArray = inputArrayData.array();

    int numValues = inputArrayData.length();

    MDoubleArray outputArray(numValues);

    double value;

    for (int i = 0; i < numValues; i++)
    {
        value = inputArray[i];
        value = max(mn, min(value, mx));
        outputArray.set(value, i);
    }

    MDataHandle outputHandle = data.outputValue(aOutput);

    MFnDoubleArrayData outputArrayData;
    MObject outputData = outputArrayData.create(outputArray);

    outputHandle.setMObject(outputData);
    outputHandle.setClean();

    return MS::kSuccess;
}