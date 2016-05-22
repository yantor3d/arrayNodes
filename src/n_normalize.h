/**
    Copyright (c) 2016 Ryan Porter - arrayNodes
    You may use, distribute, or modify this code under the terms of the MIT license.
*/

/**
    arrayScalarOp

    @author: Ryan Porter
    @version: 1.0.0
    @description:
        This node calculates the normalized value of each value in the input 
        arrays. Normalized values add up to 1.0. The normalization can be done
        by row or by column by toggling the elementwise attribute.

    @attributes
        input (i) - doubleArray[]

        elementwise (ew) - boolean
            If True, the values are normalized by column. Otherwise, the 
            values are normalized by row.

        output (o) - doubleArray[]
*/

#ifndef n_arrayNormalize_H
#define n_arrayNormalize_H

#include <maya/MDataBlock.h>
#include <maya/MPlug.h>
#include <maya/MPxNode.h>
#include <maya/MString.h>
#include <maya/MTypeId.h>

using namespace std;

class NormalizeArrayNode : public MPxNode
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
    static MObject          aElementwise;
    static MObject          aOutput;
};

#endif