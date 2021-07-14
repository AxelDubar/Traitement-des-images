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

void dilatation(OCTET *ImgIn,OCTET *ImgOut,int nH, int nW){
	for (int j=0; j < nW; j++)//i=0 et i=nH-1
	{
	  if(ImgIn[j]==0){//i=0
	  	if(j<nW-1){
	   	ImgOut[j+1]=0;//i=0
	   	ImgOut[nW+j+1]=0;


	    }
	    if(j>0){
	   		ImgOut[nW+j+1]=0;
	   		ImgOut[j-1]=0;
	    }
	   	ImgOut[nW+j]=0;//i=0
	   }

	   if(ImgIn[(nH-1)*nW+j]==0){//i=nh-1

	   	if(j<nW-1){
	   		ImgOut[(nH-1)*nW+j+1]=0;
			ImgOut[(nH-2)*nW+j+1]=0;
		}
		if(j>0){
			ImgOut[(nH-1)*nW+j-1]=0;
			ImgOut[(nH-2)*nW+j-1]=0;
		}
		ImgOut[(nH-2)*nW+j]=0;
	   }
	}

	for (int i=0; i < nH; i++)//j=0 et j=nW-1
	{
	  if(ImgIn[i*nW]==0){//j=0
	  	if(i<nH-1){
	   		ImgOut[(i+1)*nW]=0;
	   		ImgOut[(i+1)*nW+1]=0;
	    }
	    if(i>0){
	   		ImgOut[(i-1)*nW]=0;
	   		ImgOut[(i-1)*nW+1]=0;
	    }
	   	ImgOut[i*nW+1]=0;
	   }

	   if(ImgIn[(i+1)*nW+nW-1]==0){//j=nW-1

	   	if(i<nH-1){
	   		ImgOut[(i+1)*nW+nW-1]=0;
	   		ImgOut[(i+1)*nW+nW-2]=0;
	    }
	    if(i>0){
	   		ImgOut[(i-1)*nW+nW-1]=0;
	   		ImgOut[(i-1)*nW+nW-2]=0;
	    }
	   	ImgOut[i*nW+nW-2]=0;
	   }
	}

   for (int i=1; i < nH-1; i++)
     for (int j=1; j < nW-1; j++)
     {
       if(ImgIn[i*nW+j]==0){
       	ImgOut[i*nW+j+1]=0;
       	ImgOut[i*nW+j-1]=0;
       	ImgOut[(i-1)*nW+j]=0;
       	ImgOut[(i-1)*nW+j+1]=0;
       	ImgOut[(i-1)*nW+j-1]=0;
       	ImgOut[(i+1)*nW+j]=0;
       	ImgOut[(i+1)*nW+j+1]=0;
       	ImgOut[(i+1)*nW+j-1]=0;
       }
     }
}

void fermeture(OCTET *ImgIn,OCTET *ImgOut,int nH, int nW, int taille){
	OCTET *ImgInter;
	allocation_tableau(ImgInter,OCTET,taille);
	for (int i=0; i < nH-1; i++)
     for (int j=0; j < nW-1; j++)
     {
     	ImgInter[i*nW+j]=ImgIn[i*nW+j];
     }
	dilatation(ImgIn,ImgInter,nH,nW);
	erosion(ImgInter,ImgOut,nH,nW);
}

void ouverture(OCTET *ImgIn,OCTET *ImgOut,int nH, int nW, int taille){
	OCTET *ImgInter;
	allocation_tableau(ImgInter,OCTET,taille);

	erosion(ImgIn,ImgInter,nH,nW);
	for (int i=0; i < nH-1; i++)
     for (int j=0; j < nW-1; j++)
     {
     	ImgOut[i*nW+j]=ImgInter[i*nW+j];
     }
	dilatation(ImgInter,ImgOut,nH,nW);
}

void difference(OCTET *ImgIn,OCTET *ImgOut,int nH, int nW, int taille){
	for (int i=0; i < nH-1; i++)
     for (int j=0; j < nW-1; j++)
     {
     	ImgOut[i*nW+j]=ImgIn[i*nW+j];
     }
	dilatation(ImgIn,ImgOut,nH,nW);
	for (int i=1; i < nH-1; i++)
     for (int j=1; j < nW-1; j++)
     {
       if(ImgIn[i*nW+j]==ImgOut[i*nW+j]){
       	ImgOut[i*nW+j]=255;
       }
     }
}

int main(int argc, char* argv[])
{
char cNomImgLue[250], cNomImgEcrite[250];
  int indiceVal[256];
  int nH, nW, nTaille, S;
  
  if (argc != 3) 
     {
       printf("Usage: ImageIn.pgm ImageOut.pgm \n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgEcrite);

   OCTET *ImgIn, *ImgOut;
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   allocation_tableau(ImgIn, OCTET, nTaille);
   lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgOut, OCTET, nTaille);
	
   for (int i=0; i < nH-1; i++)
     for (int j=0; j < nW-1; j++)
     {
     	ImgOut[i*nW+j]=ImgIn[i*nW+j];
     }

   dilatation(ImgIn,ImgOut,nH,nW);




   ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn);
   return 1;
}