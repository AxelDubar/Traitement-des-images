// seuil_auto.cpp : Seuille une image en niveau de gris automatiquement

#include <stdio.h>
#include "image_ppm.h"

void floutage(OCTET *ImgIn,OCTET *ImgOut,int nH, int nW,int nTaille){
    int tab_nR[nTaille],tab_nG[nTaille],tab_nB[nTaille];
    int newTab_nR[nTaille],newTab_nG[nTaille],newTab_nB[nTaille];
    int nR,nG,nB;
    int j=0;
    for(int i=0;i<nTaille*3;i+=3){
        tab_nR[j] = ImgIn[i];
        tab_nG[j] = ImgIn[i+1];
        tab_nB[j] = ImgIn[i+2];

        newTab_nR[j]=tab_nR[j];
        newTab_nG[j]=tab_nG[j];
        newTab_nB[j]=tab_nB[j];
        j++;
    }

/*
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
	}*/

   for (int i=1; i < nH-1; i++){
     for (int j=1; j < nW-1; j++)
     {
        newTab_nR[i*nW+j]=(int)((tab_nR[(i-1)*nW+j-1]+tab_nR[(i-1)*nW+j]+tab_nR[(i-1)*nW+j+1]+
                            tab_nR[i*nW+j-1]+tab_nR[i*nW+j]+tab_nR[i*nW+j+1]+
                            tab_nR[(i+1)*nW+j-1]+tab_nR[(i+1)*nW+j]+tab_nR[(i+1)*nW+j+1])/9.0);
        newTab_nG[i*nW+j]=(int)((tab_nG[(i-1)*nW+j-1]+tab_nG[(i-1)*nW+j]+tab_nG[(i-1)*nW+j+1]+
                            tab_nG[i*nW+j-1]+tab_nG[i*nW+j]+tab_nG[i*nW+j+1]+
                            tab_nG[(i+1)*nW+j-1]+tab_nG[(i+1)*nW+j]+tab_nG[(i+1)*nW+j+1])/9.0);
        newTab_nB[i*nW+j]=(int)((tab_nB[(i-1)*nW+j-1]+tab_nB[(i-1)*nW+j]+tab_nB[(i-1)*nW+j+1]+
                            tab_nB[i*nW+j-1]+tab_nB[i*nW+j]+tab_nB[i*nW+j+1]+
                            tab_nB[(i+1)*nW+j-1]+tab_nB[(i+1)*nW+j]+tab_nB[(i+1)*nW+j+1])/9.0);
       
     }
   }
   j=0;
   for(int i=0;i<nTaille*3;i+=3){
        ImgOut[i] = newTab_nR[j];
        ImgOut[i+1] = newTab_nG[j];
        ImgOut[i+2] = newTab_nB[j];
        j++;
    }

}

int main(int argc, char* argv[])
{
char cNomImgLue[250], cNomImgEcrite[250];
  int indiceVal[256];
  int nH, nW, nTaille, S;
  
  if (argc != 3) 
     {
       printf("Usage: ImageIn.ppm ImageOut.ppm \n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgEcrite);

   OCTET *ImgIn, *ImgOut;
   
   lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
    int nTaille3=nTaille*3;
   allocation_tableau(ImgIn, OCTET, nTaille3);
   lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgOut, OCTET, nTaille3);

   floutage(ImgIn,ImgOut,nH,nW,nTaille);




   ecrire_image_ppm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn);
   return 1;
}