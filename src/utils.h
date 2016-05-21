/* Copyright (c) 2016 Ryan Porter - arrayNodes
* You may use, distribute, or modify this code under the terms of the MIT license.
*/

#ifndef n_arrayNodeUtils_H
#define n_arrayNodeUtils_H

const short kNO_OP = 0;
const short kSUM = 1;
const short kDIFFERENCE = 2;
const short kAVERAGE = 3;
const short kPRODUCT = 4;
const short kQUOTIENT = 5;
const short kEXPONENT = 6;
const short kMIN = 7;
const short kMAX = 8;

#include <maya/MStatus.h>
#include <maya/MPxNode.h>

double    computeOutput(double &lhs, double &rhs, short &operation, MStatus &status);
void      reportComputeError(MPxNode *node, short &operation);
#endif