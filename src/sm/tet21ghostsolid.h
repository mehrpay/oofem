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

#ifndef TET21GHOSTSOLID_H
#define TET21GHOSTSOLID_H

#include "nlstructuralelement.h"
#include "floatmatrix.h"

#define _IFT_tet21ghostsolid_Name "tet21ghostsolid"

namespace oofem {
class FEI3dTetQuad;
class FEI3dTetLin;

class tet21ghostsolid : public NLStructuralElement
{
private:
    FloatMatrix Dghost;
    bool computeItransform;
    FloatMatrix Itransform;

    void giveUnknownData(FloatArray &u_prev, FloatArray &u, FloatArray &inc, TimeStep *tStep);

public:
    tet21ghostsolid(int n, Domain *d);

    virtual FEInterpolation *giveInterpolation() const;
    virtual void giveDofManDofIDMask(int inode, IntArray &answer) const;
    virtual const char *giveInputRecordName() const { return _IFT_tet21ghostsolid_Name; }
    virtual int computeNumberOfDofs() { return 70; }
    virtual MaterialMode giveMaterialMode() { return _3dMat; }
    virtual void computeStiffnessMatrix(FloatMatrix &answer, MatResponseMode rMode, TimeStep *tStep);
    virtual void computeNumericStiffnessMatrix(FloatMatrix &answer, MatResponseMode rMode, TimeStep *tStep);
    virtual void giveInternalForcesVector(FloatArray &answer, TimeStep *tStep, int useUpdatedGpRecord = 0);
    virtual void giveInternalForcesVectorGivenSolution(FloatArray &answer, TimeStep *tStep, int useUpdatedGpRecord, FloatArray &SolutionVector);
    virtual void computeLoadVector(FloatArray &answer, Load *load, CharType type, ValueModeType mode, TimeStep *tStep);
    virtual void computeDeformationGradientVector(FloatArray &answer, GaussPoint *gp, TimeStep *tStep, FloatArray &u);
    virtual int giveIPValue(FloatArray &answer, GaussPoint *gp, InternalStateType type, TimeStep *tStep);
    virtual double computeVolumeAround(GaussPoint *gp);
    virtual bool giveRowTransformationMatrix(FloatMatrix &Itransform, TimeStep *tStep);
    virtual const char *giveClassName() const { return "tet21ghostsolid"; }

protected:
    static FEI3dTetQuad interpolation;
    static FEI3dTetLin interpolation_lin;

    virtual void computeBmatrixAt(GaussPoint *, FloatMatrix &, int = 1, int = ALL_STRAINS);
    virtual void computeBHmatrixAt(GaussPoint *, FloatMatrix &);
    virtual void computeGaussPoints();

    /// Ordering of momentum balance equations in element. Used to assemble the element stiffness
    static IntArray momentum_ordering;
    /// Ordering of conservation equations in element. Used to assemble the element stiffness
    static IntArray conservation_ordering;
    /// Ordering of ghost displacements equations
    static IntArray ghostdisplacement_ordering;

};

}
#endif // TET21GHOSTSOLID_H
