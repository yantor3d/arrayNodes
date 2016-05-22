/**
    Copyright (c) 2016 Ryan Porter - arrayNodes
    You may use, distribute, or modify this code under the terms of the MIT license.
*/

/**
    clampArray

    @author: Ryan Porter
    @version: 1.0.0
    @description:
    This node keeps the values of the input array within a specified range. 

    @attributes
        input (i) - doubleArray

        min (imn) - double
            Values in Output will not be smaller than this value.

        max (imx) - double
            Values in Output will not be larger than this value.

        output (o) - doubleArray

*/

#ifndef n_clampArray_H
#define n_clampArray_H

#include <maya/MDataBlock.h>
#include <maya/MPlug.h>
#include <maya/MPxNode.h>
#include <maya/MString.h>
#include <maya/MTypeId.h>

class ClampArrayNode : public MPxNode
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
    static MObject          aMin;
    static MObject          aMax;
    static MObject          aOutput;
};

#endif