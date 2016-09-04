/**
Copyright (c) 2016 Ryan Porter - arrayNodes
You may use, distribute, or modify this code under the terms of the MIT license.
*/

/*-----------------------------------------------------------------------------
arrayAngleIter
Sets each value in an input doubleArray to an index in the output attribute as 
a doubleAngle so that values can be passed to attributes that expected angles 
without a unitConversion node.

Input Attributes
    - input (doubleArray)

Output Attributes
    - output (doubleAngle[])
-----------------------------------------------------------------------------*/

#include "n_iterAngle.h"

#include <maya/MAngle.h>
#include <maya/MFnDoubleArrayData.h>
#include <maya/MArrayDataBuilder.h>
#include <maya/MArrayDataHandle.h>
#include <maya/MDataHandle.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MFnUnitAttribute.h>
#include <maya/MPlug.h>
#include <maya/MPxNode.h>

MObject ArrayAngleIteratorNode::aInput;
MObject ArrayAngleIteratorNode::aOutput;

void* ArrayAngleIteratorNode::creator()
{
    return new ArrayAngleIteratorNode();
}

MStatus ArrayAngleIteratorNode::initialize()
{
    MStatus status;

    MFnTypedAttribute T;
    MFnNumericAttribute N;
    MFnUnitAttribute U;

    aInput = T.create("input", "i", MFnData::kDoubleArray);
    T.setKeyable(false);
    T.setStorable(true);
    T.setWritable(true);

    aOutput = U.create("output", "o", MFnUnitAttribute::kAngle);
    U.setKeyable(false);
    U.setChannelBox(false);
    U.setWritable(false);
    U.setStorable(false);
    U.setArray(true);
    U.setUsesArrayDataBuilder(true);

    addAttribute(aInput);
    addAttribute(aOutput);

    attributeAffects(aInput, aOutput);

    return MS::kSuccess;
}

void ArrayAngleIteratorNode::postConstructor()
{
    this->setExistWithoutOutConnections(true);
}

MStatus ArrayAngleIteratorNode::compute(const MPlug& plug, MDataBlock& data)
{
    if (plug != aOutput && plug.parent() != aOutput)
        return MS::kUnknownParameter;

    MFnDoubleArrayData inputData(data.inputValue(aInput).data());

    MArrayDataHandle outputHandle = data.outputValue(aOutput);
    MArrayDataBuilder outputData = outputHandle.builder();

    int size = inputData.length();

    MAngle::Unit uiUnit = MAngle::uiUnit();

    for (int i = 0; i < size; i++)
    {
        MDataHandle outHandle = outputData.addElement(i);
        outHandle.setMAngle(MAngle(inputData[i], uiUnit));
    }

    outputHandle.set(outputData);
    outputHandle.setAllClean();

    return MS::kSuccess;
}