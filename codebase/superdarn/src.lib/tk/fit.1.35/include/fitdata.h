/* fitdata.h
   ========== 
   Author: R.J.Barnes
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




#ifndef _FITDATA_H
#define _FITDATA_H

#ifndef _FITBLK_H
#include "fitblk.h"
#endif

struct FitData {
  struct {
    int major;
    int minor;
  } revision;
  struct FitNoise noise;
  struct FitRange *rng;
  struct FitRange *xrng;
  struct FitElv  *elv;
};

/*Data used to calculate elevation angles and errors*/
struct elevation_data {
    double interfer_x;
    double interfer_y;
    double interfer_z;

    int tfreq;
    int maxbeam;
    int bmnum;

    double phidiff;
    double bmsep;
    double tdiff;

};

/* struct that contains function points to methods/algorithms 
 * that the fitacf algorithm may use. This allow flexbility and minimal 
 * implementation to add a new algorithm in for any possible fitting 
 * algorithm. The elevation data structure also allows a set struct 
 * that elevation algorithms must accept makeing so developers being consistent 
 * with input values.
 * example) elevation angles: elevation, elev_goose, or elevation_v2
 * future might be power and phase calculations :) */
struct fitacf_functions {
    double (*elevation_method)(struct elevation_data*, double);
    double (*elevation_error_method)(struct elevation_data*, double, double);
    
};



struct FitData *FitMake();
void FitFree(struct FitData *ptr);
int FitSetRng(struct FitData *ptr,int nrang);
int FitSetXrng(struct FitData *ptr,int nrang);
int FitSetElv(struct FitData *ptr,int nrang);

void *FitFlatten(struct FitData *ptr,int nrang,size_t *size);
int FitExpand(struct FitData *ptr,int nrang,void *buffer);

#endif
