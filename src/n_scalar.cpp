/**
    Copyright (c) 2016 Ryan Porter - arrayNodes
    You may use, distribute, or modify this code under the terms of the MIT license.
*/

/*-----------------------------------------------------------------------------
arrayScalarOp
Performs an arithmetic operation on for each value of the input array with the
value and a scalar value as the parameters. There is an option to toggle the
order of the parameters - f(element, scalar) or f(scalar, element)

Operations
    - Add
    - Subtract
    - Multiply
    - Divide
    - Power

Input Attributes
    - input (doubleArray)
    - scalar (double)
    - order (enum)
    - operation (enum)

Output Attributes
    - output (doubleArray)
-----------------------------------------------------------------------------*/

#include "n_scalar.h"
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

MObject ArrayScalarOperationNode::aInput;
MObject ArrayScalarOperationNode::aScalar;
MObject ArrayScalarOperationNode::aOperation;
MObject ArrayScalarOperationNode::aOrder;
MObject ArrayScalarOperationNode::aOutput;

const short ELEMENT_SCALAR = 0;
const short SCALAR_ELEMENT = 1;

#define ALMOST_ZERO 1e-5

void* ArrayScalarOperationNode::creator()
{
    return new ArrayScalarOperationNode();
}

MStatus ArrayScalarOperationNode::initialize()
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

    aScalar = N.create("scalar", "s", MFnNumericData::kDouble);
    N.setKeyable(true);
    N.setChannelBox(true);
    N.setStorable(true);
    N.setWritable(true);

    aOutput = T.create("output", "o", MFnData::kDoubleArray);
    T.setKeyable(false);
    T.setChannelBox(false);
    T.setWritable(false);
    T.setStorable(false);

    aOperation = E.create("operation", "operation");
    E.addField("No Operation", kNO_OP);
    E.addField("Sum", kSUM);
    E.addField("Difference", kDIFFERENCE),
    E.addField("Product", kPRODUCT);
    E.addField("Quotient", kQUOTIENT);
    E.addField("Exponent", kEXPONENT);
    E.setKeyable(true);
    E.setStorable(true);
    E.setWritable(true);

    aOrder = E.create("argumentOrder", "ao");
    E.addField("Element First", 0);
    E.addField("Scalar First", 1);
    E.setKeyable(true);
    E.setStorable(true);
    E.setWritable(true);

    addAttribute(aOperation);
    addAttribute(aOrder);
    addAttribute(aInput);
    addAttribute(aScalar);
    addAttribute(aOutput);

    attributeAffects(aOperation, aOutput);
    attributeAffects(aOrder, aOutput);
    attributeAffects(aInput, aOutput);
    attributeAffects(aScalar, aOutput);

    return MS::kSuccess;
}

MStatus ArrayScalarOperationNode::compute(const MPlug& plug, MDataBlock& data)
{
    MStatus status;

    MDataHandle inputHandle = data.inputValue(aInput, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);

    MFnDoubleArrayData input(inputHandle.data());
    double scalar = data.inputValue(aScalar).asDouble();
    short operation = data.inputValue(aOperation).asShort();
    bool order = data.inputValue(aOrder).asShort() == ELEMENT_SCALAR;

    double output;
    double lhs;
    double rhs;

    int size = input.length();
    MDoubleArray outputArray(size);

    for (int i = 0; i < size; i++)
    {
        lhs = order ? input[i] : scalar;
        rhs = order ? scalar : input[i];

        output = computeOutput(lhs, rhs, operation, status);

        if (!status) { reportComputeError(this, operation); }

        outputArray.set(output, i);
    }

    MDataHandle outputHandle = data.outputValue(this->aOutput);
    MFnDoubleArrayData outputArrayData;
    MObject outputData = outputArrayData.create(outputArray);

    outputHandle.setMObject(outputData);
    outputHandle.setClean();

    return MS::kSuccess;
}