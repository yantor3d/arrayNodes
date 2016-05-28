/*
    Copyright (c) 2016 Ryan Porter
*/

/**
    This node applies an accumulating function to the values of the input array and outputs a single value.

    ## Attributes
        <table>
            <tr><th> Attribute Name <th> Short Name <th> Attribute Type
            <tr><td> input          <td> i          <td> doubleArray
            <tr><td colspan = "3"> Input values that will be reduced to a single value.
            <tr><td> operation      <td> op          <td> enum
            <tr><td colspan = "3"> The operation that will be applied to the `input` values.
                @param "No Operation"   Output will be 0.0.
                @param Sum              Output will be the first value plus the remaining values.
                @param Difference       Output will be the first value minus the remaining values.
                @param Average          Output will be the average of the input values.
                @param Product          Output will be the first value times the remaining values.
                @param Quotient         Output will be the first value divided by the remaining values.    
                @param Exponent         Output will be the first value raised to the remaining values.
                @param Min              Output will be the smallest value.
                @param Max              Output will be the largest value.
                @param Length           Output will be the number of values.
            <tr><td> output         <td> o         <td> double
            <tr><td colspan = "3"> The result of the operation.
        </table>
*/

#ifndef n_reduceArray_H
#define n_reduceArray_H

#include <maya/MDataBlock.h>
#include <maya/MPlug.h>
#include <maya/MPxNode.h>
#include <maya/MString.h>
#include <maya/MTypeId.h>

class ReduceArrayNode : public MPxNode
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
    static MObject          aOutput;
};

#endif