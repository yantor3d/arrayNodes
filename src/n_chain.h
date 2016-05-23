/*
    Copyright (c) 2016 Ryan Porter
*/

/** 
    This node concatenates the input arrays and outputs a single array.

    ## Attributes
    <table>
        <tr><th> Attribute Name <th> Short Name <th> Attribute Type
        <tr><td> input          <td> i          <td> doubleArray[]
        <tr><td colspan = "3"> List of input arrays that will be chained together to produce the output.
        <tr><td> output         <td> o         <td> doubleArray
        <tr><td colspan = "3"> A single array containing all the values of the input arrays.
    </table>
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