/**
    Copyright (c) 2016 Ryan Porter - arrayNodes
    You may use, distribute, or modify this code under the terms of the MIT license.
*/

#include <vector>
#include <algorithm>

#include "n_multi.h"
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

MObject ArrayMultiOperatorNode::aInput;
MObject ArrayMultiOperatorNode::aOperation;
MObject ArrayMultiOperatorNode::aElementwise; 
MObject ArrayMultiOperatorNode::aOutput;

void* ArrayMultiOperatorNode::creator()
{
    return new ArrayMultiOperatorNode();
}

MStatus ArrayMultiOperatorNode::initialize()
{
    MStatus status;

    MFnEnumAttribute E;
    MFnNumericAttribute N;
    MFnTypedAttribute T;

    aInput = T.create("input", "i", MFnData::kDoubleArray);
    T.setKeyable(false);
    T.setChannelBox(false);
    T.setStorable(true);
    T.setWritable(true);
    T.setArray(true);

    aOperation = E.create("operation", "operation");
    E.addField("No Operation", kNO_OP);
    E.addField("Sum", kSUM);
    E.addField("Difference", kDIFFERENCE);
    E.addField("Average", kAVERAGE);
    E.addField("Product", kPRODUCT);
    E.addField("Quotient", kQUOTIENT);
    E.addField("Exponent", kEXPONENT);
    E.setDefault(kSUM);
    E.setKeyable(true);
    E.setStorable(true);
    E.setWritable(true);

    aElementwise = N.create("elementwise", "ew", MFnNumericData::kBoolean);
    N.setDefault(true);
    N.setKeyable(true);
    N.setStorable(true);
    N.setWritable(true);

    aOutput = T.create("output", "o", MFnData::kDoubleArray);
    T.setKeyable(false);
    T.setChannelBox(false);
    T.setWritable(false);
    T.setStorable(false);

    addAttribute(aInput);
    addAttribute(aOperation);
    addAttribute(aElementwise);
    addAttribute(aOutput);

    attributeAffects(aOperation, aOutput);
    attributeAffects(aElementwise, aOutput);
    attributeAffects(aInput, aOutput);

    return MS::kSuccess;
}

void ArrayMultiOperatorNode::postConstructor()
{
    this->setExistWithoutOutConnections(true);
}

MStatus ArrayMultiOperatorNode::compute(const MPlug& plug, MDataBlock& data)
{
    if (plug != aOutput)
        return MS::kUnknownParameter;

    MStatus status;

    MArrayDataHandle inputArrayHandle = data.inputValue(aInput);
    
    short operation = data.inputValue(aOperation).asShort();
    bool elementwise = data.inputValue(aElementwise).asBool();

    int numInputs = inputArrayHandle.elementCount();
    
    vector<int> sizes = vector<int>(numInputs);
    vector<MDoubleArray> inputArrays = vector<MDoubleArray>(numInputs);
    
    int numOutputs = 0;

    for (int i = 0; i < numInputs; i++)
    {
        MDataHandle inputHandle = inputArrayHandle.inputValue();
        MFnDoubleArrayData inputArrayData(inputHandle.data());
        MDoubleArray inputArray = inputArrayData.array();
        
        numOutputs = max(int(inputArray.length()), numOutputs);

        inputArrays[i] = inputArray;

        if (!inputArrayHandle.next()) break;
    }

    numOutputs = elementwise ? numOutputs : numInputs;
    sort(inputArrays.begin(), inputArrays.end(), sortByLength);

    for (int i = 0; i < numInputs; i++)
    {
        sizes[i] = inputArrays[i].length();
    }

    MDoubleArray outputArray(numOutputs);
    double value = 0.0;

    if (elementwise)
    {
        for (int i = 0; i < numOutputs; i++)
        {
            value = 0.0;
            status = MS::kSuccess;

            if (int(inputArrays[0].length()) > i) { 
                value = inputArrays[0][i];

                for (int j = 1; j < numInputs; j++)
                {
                    if (i >= sizes[j]) { break; }

                    value = computeOutput(value, inputArrays[j][i], operation, status);

                    if (!status) {
                        reportComputeError(this, operation);
                        break;
                    }
                }
            }

            outputArray.set(value, i);
        }
    } else {
        for (int i = 0; i < numInputs; i++)
        {
            value = sizes[i] > 0 ? inputArrays[i][0] : 0.0;
            status = MS::kSuccess;

            for (int j = 1; j < sizes[i]; j++)
            {
                value = computeOutput(value, inputArrays[i][j], operation, status);

                if (!status)
                {
                    reportComputeError(this, operation);
                    break;
                }
            }

            outputArray.set(value, i);
        }
    }

    MFnDoubleArrayData outputArrayData;
    MObject outputData = outputArrayData.create(outputArray);

    MDataHandle outputHandle = data.outputValue(aOutput);
    outputHandle.setMObject(outputData);
    outputHandle.setClean();

    return MS::kSuccess;
}