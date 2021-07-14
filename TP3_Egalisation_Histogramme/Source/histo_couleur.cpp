// test_couleur.cpp : Seuille une image couleur 

#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
  char cNomImgLue[250];
  int nH, nW, nTaille, nR, nG, nB;
  
  if (argc != 2) 
     {
       printf("Usage: ImageIn.ppm\n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;

   OCTET *ImgIn;
   
   lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   int nTaille3 = nTaille * 3;
   allocation_tableau(ImgIn, OCTET, nTaille3);
   lire_image_ppm(cNomImgLue, ImgIn, nH * nW);

   int histoValR[256],histoValG[256],histoValB[256];
   for(int i=0;i<256;i++){
       histoValR[i]=0;
       histoValG[i]=0;
       histoValB[i]=0;
   }
	
   for (int i=0; i < nTaille3; i+=3)
     {
       nR = ImgIn[i];
       nG = ImgIn[i+1];
       nB = ImgIn[i+2];
       histoValR[nR]++;
       histoValG[nG]++;
       histoValB[nB]++;
     }

   for(int i=0;i<256;i++){
       printf("%d %d %d %d\n",i,histoValR[i],histoValG[i],histoValB[i]);
   }

   free(ImgIn);
   return 1;
}
