/* solve.c
   ======= 
   Author:R.J.Barnes
*/


/*
 LICENSE AND DISCLAIMER
 
 Copyright (c) 2012 The Johns Hopkins University/Applied Physics Laboratory
 
 This file is part of the Radar Software Toolkit (RST).
 
 RST is free software: you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 any later version.
 
 RST is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with RST.  If not, see <http://www.gnu.org/licenses/>.
 
 
 
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/types.h>
#include "rtypes.h"
#include "rmath.h"
#include "rfile.h"
#include "griddata.h"
#include "cnvmap.h"
#include "cnvgrid.h"
#include "solvepotential.h"
#include "solvevelocity.h"
#include "solveefield.h"



int CnvMapSolve(struct CnvMapData *ptr,struct CnvGrid *gptr,
                float decyear,int old_aacgm) {

  if (gptr->type==0) return CnvMapSolvePotential(ptr,gptr);
  else if (gptr->type==2) return CnvMapSolveEfield(ptr,gptr);
  else return CnvMapSolveVelocity(ptr,gptr,decyear,old_aacgm);

}

