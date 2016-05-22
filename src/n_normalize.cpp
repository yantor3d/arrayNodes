/**
    Copyright (c) 2016 Ryan Porter - arrayNodes
    You may use, distribute, or modify this code under the terms of the MIT license.
*/

#include "n_normalize.h"

#include <vector>
#include <algorithm>
#include <iterator>
#include <numeric>

#include <maya/MArrayDataBuilder.h>
#include <maya/MDataBlock.h>
#include <maya/MDataHandle.h>
#include <maya/MDoubleArray.h>
#include <maya/MFnDoubleArrayData.h>
#include <maya/MFnEnumAttribute.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MPlug.h>
#include <maya/MPxNode.h>

using namespace std;

MObject NormalizeArrayNode::aInput;
MObject NormalizeArrayNode::aElementwise;
MObject NormalizeArrayNode::aOutput;

#define TOLERANCE 1e-5

void* NormalizeArrayNode::creator()
{
    return new NormalizeArrayNode();
}

MStatus NormalizeArrayNode::initialize()
{
    MStatus status;

    MFnTypedAttribute T;
    MFnNumericAttribute N;

    aInput = T.create("input", "i", MFnData::kDoubleArray);
    T.setKeyable(false);
    T.setChannelBox(false);
    T.setStorable(true);
    T.setWritable(true);
    T.setArray(true);

    aElementwise = N.create("elementwise", "ew", MFnNumericData::kBoolean, 1.0);
    N.setKeyable(true);
    N.setChannelBox(true);
    N.setStorable(true);
    N.setWritable(true);

    aOutput = T.create("output", "o", MFnData::kDoubleArray);
    T.setKeyable(false);
    T.setChannelBox(false);
    T.setWritable(false);
    T.setStorable(false);
    T.setArray(true);
    T.setUsesArrayDataBuilder(true);

    addAttribute(aInput);
    addAttribute(aElementwise);
    addAttribute(aOutput);

    attributeAffects(aInput, aOutput);
    attributeAffects(aElementwise, aOutput);

    return MS::kSuccess;
}

void NormalizeArrayNode::postConstructor()
{
    this->setExistWithoutOutConnections(true);
}

MStatus NormalizeArrayNode::compute(const MPlug& plug, MDataBlock& data)
{
    MStatus status;

    MArrayDataHandle inputArrayHandle = data.inputValue(aInput, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);

    int numElements = inputArrayHandle.elementCount();
    bool elementwise = data.inputValue(aElementwise).asBool();

    vector<int> sizes = vector<int>(numElements);
    vector<int> indices = vector<int>(numElements);
    vector<MDoubleArray> inputs = vector<MDoubleArray>(numElements);

    for (int i = 0; i < numElements; i++)
    {
        MDataHandle inputHnd = inputArrayHandle.inputValue(&status);
        CHECK_MSTATUS_AND_RETURN_IT(status);

        MFnDoubleArrayData inputArrayData(inputHnd.data());
        MDoubleArray inputArray = inputArrayData.array(&status);

        inputs[i] = status ? inputArray : MDoubleArray();
        sizes[i] = int(inputArray.length());
        indices[i] = inputArrayHandle.elementIndex();

        if (!inputArrayHandle.next()) continue;
    }

    int numOutputs = elementwise ? *max_element(sizes.begin(), sizes.end()) : numElements;

    MArrayDataHandle outputHandle = data.outputValue(aOutput, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    
    vector<double> sumsOfWeights = vector<double>(numOutputs);
        
    for (int e = 0; e < numElements; e++)
    {
        for (int i = 0; i < sizes[e]; i++)
        {
            sumsOfWeights[elementwise ? i : e] += inputs[e][i];
        }
    }

    for (int i = 0; i < numOutputs; i++)
    {
        sumsOfWeights[i] = abs(sumsOfWeights[i]) < TOLERANCE ? 0.0 : 1.0 / sumsOfWeights[i];
    }

    vector<MDoubleArray> outputs = vector<MDoubleArray>(numElements);

    for (int i = 0; i < numElements; i++)
    {
        outputs[i] = MDoubleArray(elementwise ? numOutputs : sizes[i]);
    }

    for (int e = 0; e < numElements; e++)
    {
        for (int i = 0; i < sizes[e]; i++)
        {
            outputs[e][i] = inputs[e][i] * sumsOfWeights[elementwise ? i : e];
        }
    }

    MArrayDataBuilder outputData = outputHandle.builder(&status);
    MFnDoubleArrayData outputArrayData;
    CHECK_MSTATUS_AND_RETURN_IT(status);

    for (int i = 0; i < numElements; i++)
    {
        MDataHandle outputHnd = outputData.addElement(indices[i], &status);
        CHECK_MSTATUS_AND_RETURN_IT(status);

        MObject data = outputArrayData.create(outputs[i], &status);
        CHECK_MSTATUS_AND_RETURN_IT(status);

        outputHnd.setMObject(data);
    }

    outputHandle.set(outputData);
    outputHandle.setAllClean();

    return MS::kSuccess;
}