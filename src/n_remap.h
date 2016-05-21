/**
    Copyright (c) 2016 Ryan Porter - arrayNodes
    You may use, distribute, or modify this code under the terms of the MIT license.
*/

/**
    remapArrayValues

    @author: Ryan Porter
    @version: 1.0.0
    @description:
        This node remaps the values of the input array using a gradient.

    @attributes
        input (i) - doubleArray

        inputMin (imn) - double
            This determines the value which maps to the left of the gradient.
        inputMax (imx) - double
            This determines the value which maps to the right of the gradient.

        outputMin (omn) - double
            This determines the output value at the bottom of the gradient.

        outputMax (omx) - double
            This determines the output value at the top of the gradient.

        values (vl) - ramp attribute
            Defines a range of values used to remap the values of the input array. 

        output (o) - double
*/

#ifndef n_remapArrayValues_H
#define n_remapArrayValues_H

#include <maya/MDataBlock.h>
#include <maya/MPlug.h>
#include <maya/MPxNode.h>
#include <maya/MString.h>
#include <maya/MTypeId.h>

class RemapArrayValuesNode : public MPxNode
{
public:
    virtual MStatus         compute(const MPlug& plug, MDataBlock& data);
    virtual void            postConstructor();
    virtual MStatus         setInitialRampValues();

    static  void*           creator();
    static  MStatus         initialize();
    static float            remapValue(float inValue, float inputMin, float inputMax, float outputMin = 0.0, float outputMax = 1.0);

public:
    static MTypeId          kNODE_ID;
    static MString          kNODE_NAME;

    static MObject          aInput;
    static MObject          aInputMin;
    static MObject          aInputMax;
    static MObject          aOutputMin;
    static MObject          aOutputMax;
    static MObject          aRamp;
    static MObject          aOutput;

};

#endif