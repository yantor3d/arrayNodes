/**
    Copyright (c) 2016 Ryan Porter - arrayNodes
    You may use, distribute, or modify this code under the terms of the MIT license.
*/

#include "n_remap.h"

#include <vector>
#include <cmath>
#include <cfloat>
#include <algorithm>

#include <maya/MDataBlock.h>
#include <maya/MDataHandle.h>
#include <maya/MDoubleArray.h>
#include <maya/MFnCompoundAttribute.h>
#include <maya/MFnDependencyNode.h>
#include <maya/MFloatArray.h>
#include <maya/MFnDoubleArrayData.h>
#include <maya/MFnEnumAttribute.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MIntArray.h>
#include <maya/MPlug.h>
#include <maya/MPxNode.h>
#include <maya/MRampAttribute.h>

using namespace std;

MObject RemapArrayValuesNode::aInput;
MObject RemapArrayValuesNode::aInputMin;
MObject RemapArrayValuesNode::aInputMax;
MObject RemapArrayValuesNode::aOutputMin;
MObject RemapArrayValuesNode::aOutputMax;
MObject RemapArrayValuesNode::aRamp;
MObject RemapArrayValuesNode::aOutput;

void* RemapArrayValuesNode::creator()
{
    return new RemapArrayValuesNode();
}

MStatus RemapArrayValuesNode::initialize()
{
    MStatus status;

    MFnCompoundAttribute C;
    MFnTypedAttribute T;
    MFnNumericAttribute N;
    MFnEnumAttribute E;

    aInput = T.create("input", "i", MFnData::kDoubleArray, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    T.setKeyable(false);
    T.setChannelBox(false);
    T.setStorable(true);
    T.setWritable(true);

    aInputMin = N.create("inputMin", "imn", MFnNumericData::kDouble, 0.0, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    N.setKeyable(true);
    N.setChannelBox(true);
    N.setStorable(true);
    N.setWritable(true);

    aInputMax = N.create("inputMax", "imx", MFnNumericData::kDouble, 0.0, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    N.setKeyable(true);
    N.setChannelBox(true);
    N.setStorable(true);
    N.setWritable(true);
    N.setDefault(1.0);

    aOutputMin = N.create("outputMin", "omn", MFnNumericData::kDouble, 0.0, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    N.setKeyable(true);
    N.setChannelBox(true);
    N.setStorable(true);
    N.setWritable(true);

    aOutputMax = N.create("outputMax", "omx", MFnNumericData::kDouble, 0.0, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    N.setKeyable(true);
    N.setChannelBox(true);
    N.setStorable(true);
    N.setWritable(true);
    N.setDefault(1.0);

    aRamp = MRampAttribute::createCurveRamp("values", "vl", &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);

    aOutput = T.create("output", "o", MFnData::kDoubleArray, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    T.setKeyable(false);
    T.setChannelBox(false);
    T.setWritable(false);
    T.setStorable(false);

    addAttribute(aInput);
    addAttribute(aInputMin);
    addAttribute(aInputMax);
    addAttribute(aOutputMin);
    addAttribute(aOutputMax);
    addAttribute(aRamp);
    addAttribute(aOutput);

    attributeAffects(aInput, aOutput);
    attributeAffects(aInputMin, aOutput);
    attributeAffects(aInputMax, aOutput);
    attributeAffects(aOutputMin, aOutput);
    attributeAffects(aOutputMax, aOutput);
    attributeAffects(aRamp, aOutput);

    return MS::kSuccess;
}

void RemapArrayValuesNode::postConstructor()
{
    this->setExistWithoutOutConnections(true);
    this->setInitialRampValues();
}

MStatus RemapArrayValuesNode::setInitialRampValues()
{
    MStatus status;

    MRampAttribute ramp(thisMObject(), aRamp);

    MFloatArray positions(1);
    positions.set(1.0, 0);

    MFloatArray values(1);
    values.set(1.0, 0);

    MIntArray interps(1);
    interps.set(1, 0);

    ramp.addEntries(positions, values, interps, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);

    return MS::kSuccess;
}

MStatus RemapArrayValuesNode::compute(const MPlug& plug, MDataBlock& data)
{
    if (plug != aOutput)
        return MS::kUnknownParameter;

    MStatus status;

    MFnDoubleArrayData input(data.inputValue(aInput).data());
    float inputMin = float(data.inputValue(aInputMin).asDouble());
    float inputMax = float(data.inputValue(aInputMax).asDouble());
    float outputMin = float(data.inputValue(aOutputMin).asDouble());
    float outputMax = float(data.inputValue(aOutputMax).asDouble());

    int size = input.length();
    MDoubleArray outputArray(size);
    
    MRampAttribute ramp(thisMObject(), aRamp, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);

    MFloatArray positions;
    MFloatArray values;
    MIntArray interps;
    MIntArray indices;

    ramp.getEntries(indices, positions, values, interps);

    int numIndices = indices.length();

    float inValue = 0.0;
    float outValue = 0.0;

    for (int i = 0; i < size; i++)
    {
        inValue = float(input[i]);
        
        inValue = remapValue(inValue, inputMin, inputMax);

        if (numIndices > 0)
        {
            ramp.getValueAtPosition(inValue, outValue, &status);
            CHECK_MSTATUS_AND_RETURN_IT(status);
        } else {
            outValue = inValue;
        }

        outValue = remapValue(outValue, 0.0, 1.0, outputMin, outputMax);

        outputArray.set(double(outValue), i);
    }

    MDataHandle outputHandle = data.outputValue(aOutput);
    MFnDoubleArrayData output;
    MObject outputData = output.create(outputArray);

    outputHandle.setMObject(outputData);
    outputHandle.setClean();

    return MS::kSuccess;
}

float RemapArrayValuesNode::remapValue(float inValue, float inputMin, float inputMax, float outputMin, float outputMax)
{
    float d = (inputMax - inputMin);
    float result = 0.0;

    if (abs(d) > FLT_EPSILON)
    {
        result = outputMin + ((inValue - inputMin) * (outputMax - outputMin) / d);
    } else {
        result = outputMin;
    }

    return result;
}
