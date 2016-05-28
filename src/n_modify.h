/*
    Copyright (c) 2016 Ryan Porter
*/

/**
    This node applies a function to the input array and outputs the result.

    ## Attributes
        <table>
            <tr><th> Attribute Name <th> Short Name <th> Attribute Type
            <tr><td> input          <td> i          <td> doubleArray
            <tr><td colspan = "3"> List of input values that will be normalized. The sum of normalized values is always 1.0.
            <tr><td> operation      <td> op          <td> enum
            <tr><td colspan = "3"> The operation that will be applied to the `input` values.
                @param "No Operation"   Output will be identical to the input.
                @param Sort             Output will contain all the values of the input, sorted by value.
                @param "Reflect Left"   Output will be the input reflected across the first value.
                                        \n For example: : [0, 1, 2, 3, 4] -> [4, 3, 2, 1, 0, 1, 2, 3, 4]
                @param "Reflect Right"  Output will be the input reflected across the last value.
                                        \n For example: [0, 1, 2, 3, 4] -> [0, 1, 2, 3, 4, 3, 2, 1, 0]
            <tr><td> reverse        <td> rev         <td> bool
            <tr><td colspan = "3">
                If `True`, the values will be output in reverse order.
            <tr><td> output         <td> o         <td> doubleArray
            <tr><td colspan = "3"> The result of the operation.
        </table>
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
    virtual void            postConstructor();
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