/* DataMapRead.c
   ==============
   Author: R.J.Barnes */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#include "rtypes.h"
#include "dmap.h"



int main(int argc,char *argv[]) {

 

  struct DataMap *ptr=NULL;
  struct DataMapScalar *s;
  struct DataMapArray *a;
  char **tmp;

  int fid;
  int c;
  int x,n;


  fid=open(argv[1],O_RDONLY,0);
 
  if (fid==-1) {
    fprintf(stderr,"File not found.\n");
    exit (-1);
  }



 while ((ptr=DataMapRead(fid)) !=NULL) {
    fprintf(stdout,"scalars:\n");
    for (c=0;c<ptr->snum;c++) {
      s=ptr->scl[c];
      switch (s->type) {
        case DATACHAR:
        fprintf(stdout,"\tchar");
        break;
        case DATASHORT:
        fprintf(stdout,"\tshort");
        break;
        case DATAINT:
        fprintf(stdout,"\tint");
        break;
        case DATAFLOAT:
        fprintf(stdout,"\tfloat");
        break;
        case DATADOUBLE:
        fprintf(stdout,"\tdouble");
        break;
        case DATASTRING:
        fprintf(stdout,"\tstring");
        break;
      }
      fprintf(stdout,"\t%c%s%c",'"',s->name,'"');
      fprintf(stdout," = ");
      switch (s->type) {
        case DATACHAR:
        fprintf(stdout,"%d",*(s->data.cptr));
        break;
        case DATASHORT:
        fprintf(stdout,"%d",*(s->data.sptr));
        break;
        case DATAINT:
        fprintf(stdout,"%d",*(s->data.lptr));
        break;
        case DATAFLOAT:
        fprintf(stdout,"%g",*(s->data.fptr));
        break;
        case DATADOUBLE:
        fprintf(stdout,"%g",*(s->data.dptr));
        break;
        case DATASTRING:
	tmp=(char **) s->data.vptr;
        fprintf(stdout,"%c%s%c",'"',*tmp,'"');
        break;
      }
      fprintf(stdout,"\n");
    }
    fprintf(stdout,"arrays:\n");
    for (c=0;c<ptr->anum;c++) {
      a=ptr->arr[c];
      switch (a->type) {
        case DATACHAR:
        fprintf(stdout,"\tchar");
        break;
        case DATASHORT:
        fprintf(stdout,"\tshort");
        break;
        case DATAINT:
        fprintf(stdout,"\tint");
        break;
        case DATAFLOAT:
        fprintf(stdout,"\tfloat");
        break;
        case DATADOUBLE:
        fprintf(stdout,"\tdouble");
        break;
        case DATASTRING:
        fprintf(stdout,"\tstring");
        break;
      }
      fprintf(stdout,"\t%c%s%c",'"',a->name,'"');
      fprintf(stdout," ");
      for (x=0;x<a->dim;x++) fprintf(stdout,"[%d]",a->rng[a->dim-1-x]);
    
      fprintf(stdout,"=");
      n=1;
      for (x=0;x<a->dim;x++) n=a->rng[x]*n;
      for (x=0;x<n;x++) {
        if (x % a->rng[0]==0) fprintf(stdout,"\n\t\t");
        else if (x !=0) fprintf(stdout,",\t");
        switch (a->type) {
        case DATACHAR:
          fprintf(stdout,"%d",a->data.cptr[x]);
          break;
        case DATASHORT:
          fprintf(stdout,"%d",a->data.sptr[x]);
          break;
        case DATAINT:
          fprintf(stdout,"%d",a->data.lptr[x]);
          break;
        case DATAFLOAT:
          fprintf(stdout,"%g",a->data.fptr[x]);
          break;
        case DATADOUBLE:
          fprintf(stdout,"%g",a->data.dptr[x]);
          break;	    
        case DATASTRING:
          tmp=(char **) a->data.vptr;
          fprintf(stdout,"%c%s%c",'"',tmp[x],'"');
          break;
	    
        }  
        fprintf(stdout,"\n");
      } 
    }  
    DataMapFree(ptr);

  }
  close(fid);
  return 0;

}
