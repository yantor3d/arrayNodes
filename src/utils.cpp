/**
    Copyright (c) 2016 Ryan Porter - arrayNodes
    You may use, distribute, or modify this code under the terms of the MIT license.
*/

#include <algorithm>
#include <cmath>
#include <cfloat>

#include "utils.h"

#include <maya/MStatus.h>
#include <maya/MPxNode.h>
#include <maya/MGlobal.h>

#define ALMOST_ZERO 1e-5

using namespace std;

double computeOutput(double &lhs, double &rhs, short &operation, MStatus &status)
{
    double result = 0.0;

    switch (operation)
    {
        case kNO_OP: 
            result = lhs;
        break;

        case kSUM:            
            result = lhs + rhs; 
        break;

        case kDIFFERENCE:    
            result = lhs - rhs; 
        break;

        case kAVERAGE:        
            result = lhs + rhs; 
        break;

        case kPRODUCT:        
            result = lhs * rhs; 
        break;

        case kQUOTIENT:
            if (abs(rhs) < ALMOST_ZERO)
            {
                result = DBL_MAX;
                status = MS::kFailure;
            } else {
                result = lhs / rhs;
            }
        break;

        case kEXPONENT:
            if (rhs > 0.0 && rhs < 1.0 && lhs < 0.0)
            {
                result = NAN;
                status = MS::kFailure;
            } else {
                result = pow(lhs, rhs);
            }
        break;

        case kMIN:
            result = min(lhs, rhs);
        break;

        case kMAX:
            result = max(lhs, rhs);
        break;
    }

    return result;
}

void reportComputeError(MPxNode *node, short &operation)
{
    switch (operation)
    {
        case kQUOTIENT:
            MGlobal::displayWarning(node->name() + " - basicExpression has encountered a divide by zero. Result is unpredictable.");
        break;
        case kEXPONENT:
            MGlobal::displayWarning(node->name() + " - negative number cannot be raised to a fractional power.");
        break;
    }
}
