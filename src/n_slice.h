/**
    Copyright (c) 2016 Ryan Porter - arrayNodes
    You may use, distribute, or modify this code under the terms of the MIT license.
*/

/**
    sliceArray

    @author: Ryan Porter
    @version: 1.0.0
    @description:
        This node creates an output array from a slice of the input array.
        
        The slice behaves the same as it does in Python.

    @attributes
        input (i) - doubleArray

        start (st) - int
            Index in the input array from which to start the slice. If start is negative,
            the slice will start that many indices from the end of the input array.

        stop (sp) - int
            Index in the input array at which to end the slice. If stop is negative, the
            slice will end that many indices from end of the input array.

        step (ss) - int
            Stride of each step of the slice. If step is 1, every index from
            start to stop will be returned. Step may not be 0.

        output (o) - doubleArray
*/

#ifndef n_sliceArray_H
#define n_sliceArray_H

#include <maya/MDataBlock.h>
#include <maya/MPlug.h>
#include <maya/MPxNode.h>
#include <maya/MString.h>
#include <maya/MTypeId.h>

class SliceArrayNode : public MPxNode
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
    static MObject          aStartIndex;
    static MObject          aStopIndex;
    static MObject          aStepSize;
    static MObject          aOutput;
};

#endif