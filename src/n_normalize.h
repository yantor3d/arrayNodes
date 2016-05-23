/*
    Copyright (c) 2016 Ryan Porter
*/

/**
    This node calculates the normalized value of each value in the input arrays. 

    ## Attributes
        <table>
            <tr><th> Attribute Name <th> Short Name <th> Attribute Type
            <tr><td> input          <td> i          <td> doubleArray[]
            <tr><td colspan = "3"> List of input values that will be normalized. The sum of normalized values is always 1.0.
            <tr><td> elementwise    <td> ew          <td> bool
            <tr><td colspan = "3"> If True, the input values will be normalized by row. If False, the input values will be normalized by column.
            <tr><td> output         <td> o         <td> doubleArray[]
            <tr><td colspan = "3"> The normalized values.
        </table>
*/

#ifndef n_arrayNormalize_H
#define n_arrayNormalize_H

#include <maya/MDataBlock.h>
#include <maya/MPlug.h>
#include <maya/MPxNode.h>
#include <maya/MString.h>
#include <maya/MTypeId.h>

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