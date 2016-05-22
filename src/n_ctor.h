/**
    Copyright (c) 2016 Ryan Porter - arrayNodes
    You may use, distribute, or modify this code under the terms of the MIT license.
*/

/**
    arrayCtor

    @author: Ryan Porter
    @version: 1.0.0
    @description:
        Thise node constructs an array from the indices of the multi-index 
        input. The logical indices of the input values are preserved.

    @attributes
        - input (i)           doubleArray
        - size (s)            int
        - output (o)          doubleArray
*/

#ifndef n_arrayCtor_H
#define n_arrayCtor_H

#include <maya/MDataBlock.h>
#include <maya/MPlug.h>
#include <maya/MPxNode.h>
#include <maya/MString.h>
#include <maya/MTypeId.h>

class ArrayConstructorNode : public MPxNode
{
public:
    virtual MStatus         compute(const MPlug& plug, MDataBlock& data);
    virtual void            postConstructor();
    static  void*           creator();
    static  MStatus         initialize();

public:
    static MTypeId          kNODE_ID;
    static MString          kNODE_NAME;

    static MObject        aSize;
    static MObject        aInput;
    static MObject        aOutput;
};

#endif