/*
    Copyright (c) 2016 Ryan Porter
*/

/**
    This node clamps the values of the input array within a specified range. 

    ## Attributes
    <table>
        <tr><th> Attribute Name <th> Short Name <th> Attribute Type
        <tr><td> input          <td> i          <td> doubleArray
        <tr><td colspan = "3"> Input values.
        <tr><td> min            <td> mn         <td> double
        <tr><td colspan = "3"> Values in `output` will not be less than this value.
        <tr><td> max            <td> mn         <td> double
        <tr><td colspan = "3"> Values in `output` will not be greater than this value.
        <tr><td> output         <td> o         <td> doubleArray
        <tr><td colspan = "3"> Output values.
    </table>
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