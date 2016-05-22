/**
    Copyright (c) 2016 Ryan Porter - arrayNodes
    You may use, distribute, or modify this code under the terms of the MIT license.
*/

/**
    arrayScalarOp

    @author: Ryan Porter
    @version: 1.0.0
    @description:
        This node calculates a binary operation between each value in the
        input array and the scalar value and outputs the results.

    @attributes
        input (i) - doubleArray

        operation (op) - enum
            Operation controls the function applied by this node. 
            The operations are: No operation, add, subtract, multiply, divide, power

        argumentOrder (ao) - enum
            Determines if the scalar is the left or right side argument. 
            Argument order only matters for subtraction, division, and exponentiation.

        output (o) - doubleArray
*/

#ifndef n_arrayScalarOp_H
#define n_arrayScalarOp_H

#include <maya/MDataBlock.h>
#include <maya/MPlug.h>
#include <maya/MPxNode.h>
#include <maya/MString.h>
#include <maya/MTypeId.h>

class ArrayScalarOperationNode : public MPxNode
{
public:
    virtual MStatus         compute(const MPlug& plug, MDataBlock& data);
    virtual void            postConstructor();
    static  void*           creator();
    static  MStatus         initialize();

public:
    static MTypeId          kNODE_ID;
    static MString          kNODE_NAME;

    static MObject          aInput;
    static MObject          aScalar;
    static MObject          aOperation;
    static MObject          aOrder;
    static MObject          aOutput;
};

#endif