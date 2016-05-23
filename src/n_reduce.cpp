/**
    Copyright (c) 2016 Ryan Porter - arrayNodes
    You may use, distribute, or modify this code under the terms of the MIT license.
*/

#include <algorithm>

#include "n_reduce.h"
#include "utils.h"

#include <maya/MDataBlock.h>
#include <maya/MDataHandle.h>
#include <maya/MDoubleArray.h>
#include <maya/MFnDoubleArrayData.h>
#include <maya/MFnEnumAttribute.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MGlobal.h>
#include <maya/MPlug.h>
#include <maya/MPxNode.h>

using namespace std;

MObject ReduceArrayNode::aInput;
MObject ReduceArrayNode::aOperation;
MObject ReduceArrayNode::aOutput;

const short kLENGTH = 9;

void* ReduceArrayNode::creator()
{
    return new ReduceArrayNode();
}

MStatus ReduceArrayNode::initialize()
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

    aOutput = N.create("output", "o", MFnNumericData::kDouble, 0.0);
    T.setKeyable(false);
    T.setChannelBox(false);
    T.setWritable(true);
    T.setStorable(true);

    aOperation = E.create("operation", "operation");
    E.addField("No Operation", kNO_OP);
    E.addField("Sum", kSUM);
    E.addField("Difference", kDIFFERENCE);
    E.addField("Average", kAVERAGE);
    E.addField("Product", kPRODUCT);
    E.addField("Quotient", kQUOTIENT);
    E.addField("Exponent", kEXPONENT);
    E.addField("Minimum", kMIN);
    E.addField("Maximum", kMAX);
    E.addField("Length", kLENGTH);
    E.setKeyable(true);
    E.setStorable(true);
    E.setWritable(true);

    addAttribute(aOperation);
    addAttribute(aInput);
    addAttribute(aOutput);

    attributeAffects(aOperation, aOutput);
    attributeAffects(aInput, aOutput);

    return MS::kSuccess;
}

void ReduceArrayNode::postConstructor()
{
    this->setExistWithoutOutConnections(true);
}

MStatus ReduceArrayNode::compute(const MPlug& plug, MDataBlock& data)
{
    if (plug != aOutput)
        return MS::kUnknownParameter;

    MStatus status;

    MDataHandle inputHandle = data.inputValue(aInput, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);

    MFnDoubleArrayData inputArrayData(inputHandle.data());
    MDoubleArray inputArray = inputArrayData.array();
    int numInputs = inputArray.length();

    short operation = data.inputValue(aOperation).asShort();

    double output = numInputs > 0 ? inputArray[0] : 0.0;

    if (operation == kLENGTH)
    {
        output = double(numInputs);
    } else {
        for (int i = 1; i < numInputs; i++)
        {
            output = computeOutput(output, inputArray[i], operation, status);

            if (!status)
            {
                reportComputeError(this, operation);
                break;
            }
        }
    }

    MDataHandle outputHandle = data.outputValue(this->aOutput);
    outputHandle.setDouble(output);
    outputHandle.setClean();

    return MS::kSuccess;
}