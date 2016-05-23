/**
    Copyright (c) 2016 Ryan Porter - arrayNodes
    You may use, distribute, or modify this code under the terms of the MIT license.
*/

#include <algorithm>
#include <vector>

#include "n_modify.h"

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

MObject ModifyArrayNode::aInput;
MObject ModifyArrayNode::aOperation;
MObject ModifyArrayNode::aReverse;
MObject ModifyArrayNode::aOutput;

const short kNO_OP = 0;
const short kSORT = 1;
const short kABS = 2;
const short kREFLECT_LEFT = 3;
const short kREFLECT_RIGHT = 4;

void* ModifyArrayNode::creator()
{
    return new ModifyArrayNode();
}

MStatus ModifyArrayNode::initialize()
{
    MStatus status;

    MFnTypedAttribute T;
    MFnNumericAttribute N;
    MFnEnumAttribute E;

    aInput = T.create("input", "i", MFnData::kDoubleArray);
    T.setKeyable(false);
    T.setChannelBox(false);
    T.setStorable(true);
    T.setWritable(true);

    aOperation = E.create("operation", "operation");
    E.addField("No Operation", kNO_OP);
    E.addField("Sort", kSORT);
    E.addField("Absolute Value", kABS);
    E.addField("Reflect Left", kREFLECT_LEFT);
    E.addField("Reflect Righ", kREFLECT_RIGHT);
    E.setDefault(kNO_OP);
    E.setKeyable(true);
    E.setStorable(true);
    E.setWritable(true);

    aReverse = N.create("reverse", "rev", MFnNumericData::kBoolean);
    N.setKeyable(true);
    N.setChannelBox(true);
    N.setStorable(true);
    N.setWritable(true);

    aOutput = T.create("output", "o", MFnData::kDoubleArray);
    T.setKeyable(false);
    T.setChannelBox(false);
    T.setWritable(false);
    T.setStorable(false);

    addAttribute(aOperation);
    addAttribute(aInput);
    addAttribute(aReverse);
    addAttribute(aOutput);

    attributeAffects(aOperation, aOutput);
    attributeAffects(aInput, aOutput);
    attributeAffects(aReverse, aOutput);

    return MS::kSuccess;
}

void ModifyArrayNode::postConstructor()
{
    this->setExistWithoutOutConnections(true);
}

MStatus ModifyArrayNode::compute(const MPlug& plug, MDataBlock& data)
{
    if (plug != aOutput)
        return MS::kUnknownParameter;

    MStatus status;

    MFnDoubleArrayData inputArray(data.inputValue(aInput).data());

    short op = data.inputValue(aOperation).asShort();
    bool reverse = data.inputValue(aReverse).asBool();

    int inputSize = int(inputArray.length());
    int outputSize = 0;

    switch (op)
    {
        case kREFLECT_LEFT:
        case kREFLECT_RIGHT:
            outputSize = max(0, inputSize * 2 - 1);
            break;
        default:
            outputSize = inputSize;
        break;
    }

    std::vector<double> values = std::vector<double>(outputSize);
    MDoubleArray outputArray(outputSize);

    int index = 0;

    switch (op)
    {
        case kNO_OP:
            for (int i = 0; i < outputSize; i++)
                values[i] = inputArray[i];
        break;
        case kSORT:
            for (int i = 0; i < outputSize; i++)
                values[i] = inputArray[i];

            std::sort(values.begin(), values.end());
        break;

        case kABS:
            for (int i = 0; i < outputSize; i++)
                values[i] = abs(inputArray[i]);
        break;

        case kREFLECT_LEFT:            
            for (int i = inputSize - 1; i > 0; i--)                
            {
                values[index] = inputArray[i];
                index++;
            }

            for (int i = 0; i < inputSize; i++)
            {
                values[index] = inputArray[i];
                index++;
            }
        break;

        case kREFLECT_RIGHT:
            for (int i = 0; i < inputSize - 1; i++)
            {
                values[index] = inputArray[i];
                index++;
            }

            for (int i = inputSize - 1; i >= 0; i--)
            {
                values[index] = inputArray[i];
                index++;
            }
        break;
    }

    for (int i = 0; i < outputSize; i++)
    {
        index = reverse ? outputSize - i - 1 : i;
        outputArray[i] = values[index];
    }
        
    
    MDataHandle outputHandle = data.outputValue(this->aOutput);
    MFnDoubleArrayData output;
    MObject outputData = output.create(outputArray);

    outputHandle.setMObject(outputData);
    outputHandle.setClean();

    return MS::kSuccess;
}