/*
    Copyright (c) 2016 Ryan Porter
*/

/**
    This node creates an output array from a slice of the input array.

    ## Attributes
    <table>
        <tr><th> Attribute Name <th> Short Name <th> Attribute Type
        <tr><td> input          <td> i          <td> doubleArray
        <tr><td colspan = "3"> Input array that will be sliced to produce the output.
        <tr><td> start          <td> st         <td> int
        <tr><td colspan = "3"> 
            Index in the input array from which to start the slice.  
            If start is negative, the slice will start that many indices from the end of the input array.
        <tr><td> stop           <td> sp         <td> int
        <tr><td colspan = "3"> 
            Index in the input array at which to end the slice. 
            If stop is negative, the slice will end that many indices from end of the input array.
        <tr><td> step           <td> ss         <td> int
        <tr><td colspan = "3"> 
            Stride of each step of the slice. 
            If step is 1, every index from start to stop will be returned. 
            Step may not be 0.
        <tr><td> output         <td> o         <td> doubleArray
        <tr><td colspan = "3"> An array containing the values sliced from the `input` array.
    </table>
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