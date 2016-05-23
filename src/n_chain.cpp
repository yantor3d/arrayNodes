/** Copyright (c) 2016 Ryan Porter - arrayNodes
    You may use, distribute, or modify this code under the terms of the MIT license.
*/

#include <vector>

#include "n_chain.h"

#include <maya/MArrayDataHandle.h>
#include <maya/MDataHandle.h>
#include <maya/MDoubleArray.h>
#include <maya/MFnDoubleArrayData.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MPlug.h>
#include <maya/MPxNode.h>

using namespace std; 

MObject ChainArraysNode::aInput;
MObject ChainArraysNode::aOutput;

void* ChainArraysNode::creator()
{
    return new ChainArraysNode();
}

MStatus ChainArraysNode::initialize()
{
    MStatus status;

    MFnTypedAttribute T;

    aInput = T.create("input", "i", MFnData::kDoubleArray);
    T.setKeyable(false);
    T.setStorable(true);
    T.setWritable(true);
    T.setArray(true);

    aOutput = T.create("output", "o", MFnData::kDoubleArray);
    T.setKeyable(false);
    T.setChannelBox(false);
    T.setWritable(false);
    T.setStorable(false);

    addAttribute(aInput);
    addAttribute(aOutput);

    attributeAffects(aInput, aOutput);

    return MS::kSuccess;
}

void ChainArraysNode::postConstructor()
{
    this->setExistWithoutOutConnections(true);
}

MStatus ChainArraysNode::compute(const MPlug& plug, MDataBlock& data)
{
    if (plug != aOutput)
        return MS::kUnknownParameter;

    MStatus status;

    MArrayDataHandle inputArrayHandle = data.inputArrayValue(aInput);
    int numInputs = inputArrayHandle.elementCount();
    int outputSize = 0;

    vector<MDoubleArray> inputData = vector<MDoubleArray>(numInputs);

    for (int i = 0; i < numInputs; i++)
    {
        MDataHandle inputHandle = inputArrayHandle.inputValue();
        MFnDoubleArrayData data(inputHandle.data(), &status);
        data.copyTo(inputData[i]);

        outputSize += data.length();

        if (!inputArrayHandle.next()) break;
    }

    MDoubleArray outputArray(outputSize);

    int index = 0;
    for (int i = 0; i < numInputs; i++)
    {
        outputSize = inputData[i].length();

        for (int j = 0; j < outputSize; j++)
        {
            outputArray[index] = inputData[i][j];
            index++;
        }
    }

    MDataHandle outputHandle = data.outputValue(aOutput);
    MFnDoubleArrayData output;
    MObject outputData = output.create(outputArray);

    outputHandle.setMObject(outputData);
    outputHandle.setClean();

    return MS::kSuccess;
}