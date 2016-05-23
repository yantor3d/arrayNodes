/*
    Copyright (c) 2016 Ryan Porter
*/

/**
    This node accumulates the values in the input arrays to a function and outputs the results.

    ## Attributes
        <table>
            <tr><th> Attribute Name <th> Short Name <th> Attribute Type
            <tr><td> input          <td> i          <td> doubleArray
            <tr><td colspan = "3"> List of input values that will be used in the calculations.
            <tr><td> operation      <td> op          <td> enu,
            <tr><td colspan = "3"> The operation that will be applied to the `input` values. 
                @param "No Operation"   No calculations will be performed
                @param Sum              Each output will be the sum of the input values.
                @param Difference       Each output will be the difference between the input values.
                @param Average          Each output will be the average of the input values.
                @param Product          Each output will be the product of the input values.
                @param Quotient         Each output will be the quotient of the input values.
                @param Expontent        Each output will be the expontent of the input values.
            <tr><td> elementwise    <td> ew         <td> enum
            <tr><td colspan = "3"> 
                If `True`, the output value at a given index will be calculated using the values at that index in the input arrays.
                Otherwise, the output value at a given index will be calculate using the values of the input array at that index.
            <tr><td> output         <td> o         <td> doubleArray
            <tr><td colspan = "3"> The normalized values.
        </table>
*/

#ifndef n_arrayMultiOp_H
#define n_arrayMultiOp_H

#include <vector>

#include <maya/MDoubleArray.h>
#include <maya/MDataBlock.h>
#include <maya/MPlug.h>
#include <maya/MPxNode.h>
#include <maya/MString.h>
#include <maya/MTypeId.h>

class ArrayMultiOperatorNode : public MPxNode
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
    static MObject          aElementwise;
    static MObject          aOutput;

    static bool             sortByLength(const MDoubleArray &lhs, const MDoubleArray &rhs) { return lhs.length() > rhs.length(); }
};

#endif