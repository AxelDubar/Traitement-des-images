// test_couleur.cpp : Seuille une image couleur 

#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille, nR, nG, nB, SRMax,SRMin, SGMax,SGMin, SBMax,SBMin;
  
  if (argc != 9) 
     {
       printf("Usage: ImageIn.ppm ImageOut.ppm SeuilRMin SeuilRMax SeuilGMin SeuilGMax SeuilBMin SeuilBMax \n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgEcrite);
   sscanf (argv[3],"%d",&SRMin);
   sscanf (argv[4],"%d",&SRMax);
   sscanf (argv[5],"%d",&SGMin);
   sscanf (argv[6],"%d",&SGMax);
   sscanf (argv[7],"%d",&SBMin);
   sscanf (argv[8],"%d",&SBMax);

   OCTET *ImgIn, *ImgOut;
   
   lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   int nTaille3 = nTaille * 3;
   allocation_tableau(ImgIn, OCTET, nTaille3);
   lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgOut, OCTET, nTaille3);
	
   for (int i=0; i < nTaille3; i+=3)
     {
       nR = ImgIn[i];
       nG = ImgIn[i+1];
       nB = ImgIn[i+2];
       if (nR < SRMin) ImgOut[i]=SRMin; 
       else if(nR > SRMax) ImgOut[i]=SRMax;
       else ImgOut[i]=nR;

       if (nG < SGMin) ImgOut[i+1]=SGMin;
       else if (nG > SGMax) ImgOut[i+1]=SGMax;
       else ImgOut[i+1]=nG;

       if (nB < SBMin) ImgOut[i+2]=SBMin;
       else if(nB > SBMax) ImgOut[i+2]=SBMax;
       else ImgOut[i+2]=nB;
     }

   ecrire_image_ppm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn);
   return 1;
}
