/*
    Copyright (c) 2016 Ryan Porter
*/

/**
    This node calculates a binary operation between each value in the input array and the scalar value and outputs the results.

    ## attributes
        <table>
            <tr><th> Attribute Name <th> Short Name <th> Attribute Type
            <tr><td> input          <td> i          <td> doubleArray  
            <tr><td colspan="3"> Input values that will be applied to the operation with the `scalar` value.
            <tr><td> scalar         <td> s          <td> double
            <tr><td colspan="3"> The scalar value that will be applied to the operation with each value of `input`.
            <tr><td> operation      <td> op         <td> enum
            <tr><td colspan="3"> The operation that will be applied to the `input` values. 
                @param "No Operation" Each output will be the same as the input
                @param Add            Each output will be the sum of the input and the scalar.
                @param Subtract       Each output will be the difference between the input and the scalar.
                @param Multiply       Each output will be the product of the input and the scalar.
                @param Divide         Each output will be the quotient of the input and the scalar.
                @param Power          Each output will be the expontent of the input and the scalar.      
            <tr><td> argumentOrder  <td> op         <td> enum     
            <tr><td colspan="3"> The order in which the arguments will be passed to the operation.
                @param "Element First" Each element in the `input` array is the left hand operand.
                @param "Scalar First"  The `scalar` value is the left hand operand.
            <tr><td> output         <td> op         <td> doubleArray
            <tr><td colspan="3"> The result of the calculations.
        </table>
*/

#ifndef n_arrayScalarOp_H
#define n_arrayScalarOp_H

#include <maya/MDataBlock.h>
#include <maya/MPlug.h>
#include <maya/MPxNode.h>
#include <maya/MString.h>
#include <maya/MTypeId.h>

class ArrayScalarOperationNode : public MPxNode
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
    static MObject          aScalar;
    static MObject          aOperation;
    static MObject          aOrder;
    static MObject          aOutput;
};

#endif