/**
    Copyright (c) 2016 Ryan Porter - arrayNodes
    You may use, distribute, or modify this code under the terms of the MIT license.
*/
/*-----------------------------------------------------------------------------
arrayIter
Sets each value in an input doubleArray to an index in the output attribute
so that values can be passed to nodes that do not operate on doubleArray objects.

Input Attributes
    - input (doubleArray)

Output Attributes
    - output (double[])
-----------------------------------------------------------------------------*/

#include "n_iter.h"

#include <maya/MFnDoubleArrayData.h>
#include <maya/MArrayDataBuilder.h>
#include <maya/MArrayDataHandle.h>
#include <maya/MDataHandle.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MPlug.h>
#include <maya/MPxNode.h>

MObject ArrayIteratorNode::aInput;
MObject ArrayIteratorNode::aOutput;

void* ArrayIteratorNode::creator()
{
    return new ArrayIteratorNode();
}

MStatus ArrayIteratorNode::initialize()
{
    MStatus status;

    MFnTypedAttribute T;
    MFnNumericAttribute N;

    aInput = T.create("input", "i", MFnData::kDoubleArray); 
    T.setKeyable(false);
    T.setStorable(true);
    T.setWritable(true);

    aOutput = N.create("output", "o", MFnNumericData::kDouble);
    N.setKeyable(false);
    N.setChannelBox(false);
    N.setWritable(false);
    N.setStorable(false);
    N.setArray(true);
    N.setUsesArrayDataBuilder(true);

    addAttribute(aInput);
    addAttribute(aOutput);

    attributeAffects(aInput, aOutput);

    return MS::kSuccess;
}

MStatus ArrayIteratorNode::compute(const MPlug& plug, MDataBlock& data)
{
    if (plug != aOutput && plug.parent() != aOutput)
        return MS::kUnknownParameter;

    MFnDoubleArrayData inputData(data.inputValue(aInput).data());

    MArrayDataHandle outputHandle = data.outputValue(aOutput);
    MArrayDataBuilder outputData = outputHandle.builder();

    int size = inputData.length();

    for (int i = 0; i < size; i++)
    {
        MDataHandle outHandle = outputData.addElement(i);
        outHandle.setDouble(inputData[i]);
    }

    outputHandle.set(outputData);
    outputHandle.setAllClean();

    return MS::kSuccess;
}