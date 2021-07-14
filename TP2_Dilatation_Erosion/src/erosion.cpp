// seuil_auto.cpp : Seuille une image en niveau de gris automatiquement

#include <stdio.h>
#include "image_ppm.h"

void erosion(OCTET *ImgIn,OCTET *ImgOut,int nH, int nW){

	for (int j=0; j < nW; j++)//i=0 et i=nH-1
	{
	  if(ImgIn[j]==255){//i=0
	  	if(j<nW-1){
	   	ImgOut[j+1]=255;//i=0
	   	ImgOut[nW+j+1]=255;


	    }
	    if(j>0){
	   		ImgOut[nW+j+1]=255;//i=0
	   		ImgOut[j-1]=255;//i=0
	    }
	   	ImgOut[nW+j]=255;//i=0
	   }

	   if(ImgIn[(nH-1)*nW+j]==255){//i=nh-1

	   	if(j<nW-1){
	   		ImgOut[(nH-1)*nW+j+1]=255;
			ImgOut[(nH-2)*nW+j+1]=255;
		}
		if(j>0){
			ImgOut[(nH-1)*nW+j-1]=255;
			ImgOut[(nH-2)*nW+j-1]=255;
		}
		ImgOut[(nH-2)*nW+j]=255;
	   }
	}

	for (int i=0; i < nH; i++)//j=0 et j=nW-1
	{
	  if(ImgIn[i*nW]==255){//j=0
	  	if(i<nH-1){
	   		ImgOut[(i+1)*nW]=255;
	   		ImgOut[(i+1)*nW+1]=255;
	    }
	    if(i>0){
	   		ImgOut[(i-1)*nW]=255;
	   		ImgOut[(i-1)*nW+1]=255;
	    }
	   	ImgOut[i*nW+1]=255;
	   }

	   if(ImgIn[(i+1)*nW+nW-1]==255){//j=nW-1

	   	if(i<nH-1){
	   		ImgOut[(i+1)*nW+nW-1]=255;
	   		ImgOut[(i+1)*nW+nW-2]=255;
	    }
	    if(i>0){
	   		ImgOut[(i-1)*nW+nW-1]=255;
	   		ImgOut[(i-1)*nW+nW-2]=255;
	    }
	   	ImgOut[i*nW+nW-2]=255;
	   }
	}

   for (int i=1; i < nH-1; i++)
     for (int j=1; j < nW-1; j++)
     {
       if(ImgIn[i*nW+j]==255){
       	ImgOut[i*nW+j+1]=255;
       	ImgOut[i*nW+j-1]=255;
       	ImgOut[(i-1)*nW+j]=255;
       	ImgOut[(i-1)*nW+j+1]=255;
       	ImgOut[(i-1)*nW+j-1]=255;
       	ImgOut[(i+1)*nW+j]=255;
       	ImgOut[(i+1)*nW+j+1]=255;
       	ImgOut[(i+1)*nW+j-1]=255;
       }
     }
}