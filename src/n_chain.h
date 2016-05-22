/* Copyright (c) 2016 Ryan Porter - arrayNodes
* You may use, distribute, or modify this code under the terms of the MIT license.
*/

/**
    chainArrays

    @author: Ryan Porter
    @version: 1.0.0
    @description:
        This node concatenates the input arrays and outputs a single array.

    @attributes
        input (i) - doubleArray[]
        output (o) - doubleArray
*/

#ifndef n_chainArrays_H
#define n_chainArrays_H

#include <maya/MDataBlock.h>
#include <maya/MPlug.h>
#include <maya/MPxNode.h>
#include <maya/MString.h>
#include <maya/MTypeId.h>

class ChainArraysNode : public MPxNode
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
    static MObject          aOutput;
};

#endif