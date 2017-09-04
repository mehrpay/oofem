/*
 *
 *                 #####    #####   ######  ######  ###   ###
 *               ##   ##  ##   ##  ##      ##      ## ### ##
 *              ##   ##  ##   ##  ####    ####    ##  #  ##
 *             ##   ##  ##   ##  ##      ##      ##     ##
 *            ##   ##  ##   ##  ##      ##      ##     ##
 *            #####    #####   ##      ######  ##     ##
 *
 *
 *             OOFEM : Object Oriented Finite Element Code
 *
 *               Copyright (C) 1993 - 2013   Borek Patzak
 *
 *
 *
 *       Czech Technical University, Faculty of Civil Engineering,
 *   Department of Structural Mechanics, 166 29 Prague, Czech Republic
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

//   *****************************************************************************
//   *** GENERAL 2D ELEMENT FOR FLUID DYNAMIC PROBLEMS SOLVED WITH PFEM METHOD ***
//   *****************************************************************************

#ifndef pfemelement2d_h
#define pfemelement2d_h


#include "pfemelement.h"
#include "femcmpnn.h"
#include "domain.h"
#include "floatmatrix.h"
#include "material.h"



#include "fei2dtrlin.h"

namespace oofem {
class TimeStep;
class Node;
class Material;
class GaussPoint;
class FloatMatrix;
class FloatArray;
class IntArray;

/**
 * This class is the implementation of general 2d element with arbitrary interpolation of velocity and pressure fields.
 * Should be used with PFEM solution algorithm.
 *
 * @author David Krybus
 */
class PFEMElement2d : public PFEMElement
{
protected:

public:
    /// Constructor
    PFEMElement2d(int n, Domain *d);
    /// Destructor
    ~PFEMElement2d();

    virtual double computeCriticalTimeStep(TimeStep *tStep) = 0;

    virtual const char *giveClassName() const { return "PFEMElement2d"; }
    virtual Element_Geometry_Type giveGeometryType() const { return EGT_triangle_1; }

    virtual void giveElementDofIDMask(IntArray &answer) const = 0;
    virtual void giveDofManDofIDMask(int inode, IntArray &answer) const = 0;
    virtual int computeNumberOfDofs() = 0;
    IRResultType initializeFrom(InputRecord *ir);
    virtual int checkConsistency();

    virtual Interface *giveInterface(InterfaceType) = 0;

    virtual Element *giveElement() { return this; }

#ifdef __OOFEG
    virtual int giveInternalStateAtNode(FloatArray &answer, InternalStateType type, InternalStateMode mode,
                                        int node, TimeStep *tStep) = 0;
    // Graphics output
    //virtual void drawYourself (oofegGraphicContext&);
    //virtual void drawRawGeometry(oofegGraphicContext &);
    //virtual void drawScalar(oofegGraphicContext &context);
    //virtual void drawDeformedGeometry(oofegGraphicContext&, UnknownType) {}
#endif

    virtual FEInterpolation *giveVelocityInterpolation() = 0;
    virtual FEInterpolation *givePressureInterpolation() = 0;

protected:
    virtual void computeGaussPoints() = 0;
    virtual void computeDeviatoricStress(FloatArray &answer, GaussPoint *gp, TimeStep *tStep) = 0;
    virtual void computeDeviatoricStressDivergence(FloatArray &answer, TimeStep *tStep) = 0;

    virtual void computeBMatrix(FloatMatrix &answer, GaussPoint *gp);
    virtual void computeStiffnessMatrix(FloatMatrix &answer, MatResponseMode mode, TimeStep *tStep); //K
    virtual void computePressureLaplacianMatrix(FloatMatrix &answer, TimeStep *tStep); //L
    virtual void computeDivergenceMatrix(FloatMatrix &answerx, TimeStep *tStep); //D
    virtual void computeGradientMatrix(FloatMatrix &answer, TimeStep *tStep); //G

    void computePrescribedRhsVector(FloatArray &answer, TimeStep *tStep, ValueModeType mode);

    /// Calculates the shape function matrix on an edge
    void computeEdgeNMatrixAt(FloatMatrix &answer, int iedge, GaussPoint *gp);
    /// Calculates the shape function vector on an edge
    void computeEgdeNVectorAt(FloatArray &answer, int iedge, GaussPoint *gp);
    /// Calculates the volume around an edge
    double computeEdgeVolumeAround(GaussPoint *gp, int iEdge);
    /// Gives the mapping for degrees of freedom on an edge
    void giveEdgeDofMapping(IntArray &answer, int iEdge) const;
};
} // end namespace oofem
#endif // pfemelement_2d_h
