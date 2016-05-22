/**
    Copyright (c) 2016 Ryan Porter - arrayNodes
    You may use, distribute, or modify this code under the terms of the MIT license.
*/

/**
    arrayMultiOp

    @author: Ryan Porter
    @version: 1.0.0
    @description:
        This node accumulates the values in the input arrays to a function, 
        and outputs the results.

    @attributes
        input (i) - doubleArray[]

        operation (op) - enum
            Operation controls the function applied by this node.
            The operations are: 
                No Operation
                Sum
                Difference
                Average
                Product
                Quotient
                Exponent

        elementwise (ew) - boolean
            If True, Output will be the length of the largest input array.
            Each index of Output will be calculated using the values in that
            index of each Input.

        output (o) - doubleArray
*/

#ifndef n_arrayMultiOp_H
#define n_arrayMultiOp_H

#include <vector>

#include <maya/MDoubleArray.h>
#include <maya/MDataBlock.h>
#include <maya/MPlug.h>
#include <maya/MPxNode.h>
#include <maya/MString.h>
#include <maya/MTypeId.h>

using namespace std;

class ArrayMultiOperatorNode : public MPxNode
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
    static MObject          aOperation;
    static MObject          aElementwise;
    static MObject          aOutput;

    static bool             sortByLength(const MDoubleArray &lhs, const MDoubleArray &rhs) { return lhs.length() > rhs.length(); }
};

#endif