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
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef symmetrybarrier_h
#define symmetrybarrier_h

#include "nonlocalbarrier.h"
#include "domain.h"
#include "floatarray.h"
#include "floatmatrix.h"

///@name Input fields for SymmetryBarrier
//@{
#define _IFT_SymmetryBarrier_Name "symmetrybarrier"
#define _IFT_SymmetryBarrier_origin "origin"
#define _IFT_SymmetryBarrier_normals "normals"
#define _IFT_SymmetryBarrier_activemask "activemask"
//@}

namespace oofem {
/**
 * Implementation of symmetry nonlocal barrier.
 * It allows to specify up to three planes (orthogonal ones) of symmetry
 * It then modifies the integration weights of source points to take into account
 * symmetry of the averaged field.
 */
class SymmetryBarrier : public NonlocalBarrier
{
protected:
    FloatArray origin;
    FloatArray normals;
    IntArray mask;
    FloatMatrix lcs;

public:
    /**
     * Constructor. Creates an element with number n belonging to domain aDomain.
     * @param n Element's number
     * @param d Pointer to the domain to which element belongs.
     */
    SymmetryBarrier(int n, Domain *d);
    /// Destructor.
    virtual ~SymmetryBarrier();

    virtual void applyConstraint(const FloatArray &c1, const FloatArray &c2, double &weight,
                                 bool &shieldFlag, NonlocalMaterialExtensionInterface *nei);
    virtual double calculateMinimumDistanceFromBoundary(const FloatArray &coords, double maxPossibleDistance) { return maxPossibleDistance; }
    virtual IRResultType initializeFrom(InputRecord *ir);

    virtual const char *giveClassName() const { return "SymmetryBarrier"; }
    virtual classType giveClassID() const { return SymmetryBarrierClass; }
};
} // end namespace oofem
#endif // symmetrybarrier_h
