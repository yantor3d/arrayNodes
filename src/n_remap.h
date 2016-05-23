/*
    Copyright (c) 2016 Ryan Porter
*/

/**
    This node remaps the values of the input array using a gradient.

    ## Attributes
    <table>
        <tr><th> Attribute Name <th> Short Name <th> Attribute Type
        <tr><td> input          <td> i          <td> doubleArray[]
        <tr><td colspan = "3"> Values to be remapped.
        <tr><td> inputMin       <td> imn        <td> double
        <tr><td colspan = "3"> This determines the value which maps to the left of the gradient.
        <tr><td> inputMax       <td> imx        <td> double
        <tr><td colspan = "3"> This determines the value which maps to the right of the gradient.
        <tr><td> outputMin      <td> omn        <td> double
        <tr><td colspan = "3"> This determines the output value at the bottom of the gradient.
        <tr><td> outputMax      <td> omx        <td> double
        <tr><td colspan = "3"> This determines the output value at the top of the gradient.
        <tr><td> values         <td> vl          <td> ramp attribute
        <tr><td colspan = "3"> Defines a range of values used to remap the values of the input array.
        <tr><td> output         <td> o         <td> doubleArray
        <tr><td colspan = "3"> The remapped values.
    </table>
*/

#ifndef n_remapArrayValues_H
#define n_remapArrayValues_H

#include <maya/MDataBlock.h>
#include <maya/MPlug.h>
#include <maya/MPxNode.h>
#include <maya/MString.h>
#include <maya/MTypeId.h>

class RemapArrayValuesNode : public MPxNode
{
public:
    virtual MStatus         compute(const MPlug& plug, MDataBlock& data);
    virtual void            postConstructor();
    virtual MStatus         setInitialRampValues();

    static  void*           creator();
    static  MStatus         initialize();
    static float            remapValue(float inValue, float inputMin, float inputMax, float outputMin = 0.0, float outputMax = 1.0);

public:
    static MTypeId          kNODE_ID;
    static MString          kNODE_NAME;

    static MObject          aInput;
    static MObject          aInputMin;
    static MObject          aInputMax;
    static MObject          aOutputMin;
    static MObject          aOutputMax;
    static MObject          aRamp;
    static MObject          aOutput;

};

#endif