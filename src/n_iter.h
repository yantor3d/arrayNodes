/*
     Copyright (c) 2016 Ryan Porter
*/

/**
    This node sets the values of each index in the input array to the index of the multi-index output.

    ## Attributes
        <table>
            <tr><th> Attribute Name <th> Short Name <th> Attribute Type
            <tr><td> input          <td> i          <td> doubleArray
            <tr><td colspan = "3"> The values that will be unpacked to individual outputs.
            <tr><td> output         <td> o         <td> double[]
            <tr><td colspan = "3"> The individual values of the `input` array.
        </table>  
*/

#ifndef n_iterArray_H
#define n_iterArray_H

#include <maya/MDataBlock.h>
#include <maya/MPlug.h>
#include <maya/MPxNode.h>
#include <maya/MString.h>
#include <maya/MTypeId.h>

class ArrayIteratorNode : public MPxNode
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