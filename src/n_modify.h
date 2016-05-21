/**
    Copyright (c) 2016 Ryan Porter - arrayNodes
    You may use, distribute, or modify this code under the terms of the MIT license.
*/

/**
    modifyArray

    @author: Ryan Porter
    @version: 1.0.0
    @description:
        This node applies a function to the input array and outputs the result.

    @attributes
        input (i) - doubleArray
            
        operation (op) - enum
            Operation controls the function applied by this node. The settings are:
                No Operation: Output is set to equal Input.

                Sort: Output is set to equal the sorted values of Input.

                Reflect Left: Output is set to the values of Input reflected across the first value.
                              For example: [0, 1, 2, 3, 4] -> [4, 3, 2, 1, 0, 1, 2, 3, 4]

                Reflect Right: Output is set to the values of Input reflected across the last value.
                               For example: [0, 1, 2, 3, 4] -> [0, 1, 2, 3, 4, 3, 2, 1, 0]

        reverse (rev) - boolean
            If True, Output is set in reversed order.

        output (o) - doubleArray
*/

#ifndef n_modifyArray_H
#define n_modifyArray_H

#include <maya/MDataBlock.h>
#include <maya/MPlug.h>
#include <maya/MPxNode.h>
#include <maya/MString.h>
#include <maya/MTypeId.h>

class ModifyArrayNode : public MPxNode
{
public:
    virtual MStatus         compute(const MPlug& plug, MDataBlock& data);
    static  void*           creator();
    static  MStatus         initialize();

public:
    static MTypeId          kNODE_ID;
    static MString          kNODE_NAME;

    static MObject          aInput;
    static MObject          aOperation;
    static MObject          aReverse;
    static MObject          aOutput;
};

#endif