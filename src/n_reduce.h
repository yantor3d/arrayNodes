/**
    Copyright (c) 2016 Ryan Porter - arrayNodes
    You may use, distribute, or modify this code under the terms of the MIT license.
*/

/**
    reduceArray

    @author: Ryan Porter
    @version: 1.0.0
    @description:
        This node applies an accumulating function to the values of the input
        array and outputs a single value.

    @attributes
        input (i) - doubleArray

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
                Min
                Max
                Length

        output (o) - double
*/

#ifndef n_reduceArray_H
#define n_reduceArray_H

#include <maya/MDataBlock.h>
#include <maya/MPlug.h>
#include <maya/MPxNode.h>
#include <maya/MString.h>
#include <maya/MTypeId.h>

class ReduceArrayNode : public MPxNode
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
    static MObject          aOutput;
};

#endif