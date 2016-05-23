/*
    Copyright (c) 2016 Ryan Porter
*/

/**
    This node constructs an array from the indices of the multi-index input. 

    ## Attributes
    <table>
        <tr><th> Attribute Name <th> Short Name <th> Attribute Type
        <tr><td> input          <td> i          <td> double[]
        <tr><td colspan = "3"> 
            The individual values that will be used to construct the `output` array. 
            The logical indices of the input values are preserved - missing indices will be filled in with 0.0.
        <tr><td> size           <td> s         <td> int
        <tr><td colspan = "3"> 
            The size of the output array. If there are too few inputs, the remaining indices will be filled in with 0.0.
        <tr><td> output         <td> o         <td> doubleArray
        <tr><td colspan = "3"> An array constructed from the `input` values.
    </table>
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