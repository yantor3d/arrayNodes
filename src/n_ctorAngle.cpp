/**
    Copyright (c) 2016 Ryan Porter - arrayNodes
    You may use, distribute, or modify this code under the terms of the MIT license.
*/

#include "n_ctorAngle.h"

#include <maya/MAngle.h>
#include <maya/MDataBlock.h>
#include <maya/MDoubleArray.h>
#include <maya/MFnDoubleArrayData.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MFnUnitAttribute.h>
#include <maya/MPlug.h>
#include <maya/MPxNode.h>
#include <maya/MString.h>
#include <maya/MTypeId.h>

MObject ArrayAngleConstructorNode::aSize;
MObject ArrayAngleConstructorNode::aInput;
MObject ArrayAngleConstructorNode::aOutput;

void* ArrayAngleConstructorNode::creator()
{
    return new ArrayAngleConstructorNode();
}

MStatus ArrayAngleConstructorNode::initialize()
{
    MStatus status;

    MFnNumericAttribute N;
    MFnTypedAttribute T;
    MFnUnitAttribute U;

    aSize = N.create("size", "size", MFnNumericData::kInt, 8.0, &status);
    N.setKeyable(true);
    N.setStorable(true);
    N.setWritable(true);
    N.setDefault(8);

    aInput = U.create("input", "i", MFnUnitAttribute::kAngle, 0.0, &status);
    U.setKeyable(false);
    U.setStorable(true);
    U.setWritable(true);
    U.setArray(true);

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

void ArrayAngleConstructorNode::postConstructor()
{
    this->setExistWithoutOutConnections(true);
}

MStatus ArrayAngleConstructorNode::compute(const MPlug& plug, MDataBlock& data)
{
    if (plug != aOutput)
        return MS::kUnknownParameter;

    MStatus status;

    int index;

    MArrayDataHandle inputArrayHandle = data.inputArrayValue(aInput);
    int inputSize = inputArrayHandle.elementCount();
    int outputSize = data.inputValue(aSize).asInt();

    MDoubleArray outputArray(outputSize);

    MAngle::Unit uiUnit = MAngle::uiUnit();

    for (int i = 0; i < inputSize; i++)
    {
        index = inputArrayHandle.elementIndex();

        if (index >= outputSize) break;

        if (uiUnit == MAngle::kRadians)
        { 
            outputArray[index] = inputArrayHandle.inputValue().asAngle().asRadians();
        } else {
            outputArray[index] = inputArrayHandle.inputValue().asAngle().asDegrees();
        }

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