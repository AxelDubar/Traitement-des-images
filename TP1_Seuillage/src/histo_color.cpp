// histo_couleur.cpp : Affiche l'histogramme d'une image en couleur
#include <stdio.h>
#include "../header/image_ppm.h"

int main(int argc, char* argv[])
{
  char cNomImgLue[250];
  int indiceValR[256];
  int indiceValG[256];
  int indiceValB[256];
  int nH, nW, nTaille;
  if (argc != 2) 
     {
       printf("Usage: ImageIn.pgm\n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;

   OCTET *ImgIn;
   
   lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   allocation_tableau(ImgIn, OCTET, nTaille*3);
   lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
   printf("# Histo de l'image\n");
   for(int i=0;i<256;i++){
    indiceValR[i]=0;
    indiceValG[i]=0;
    indiceValB[i]=0;
   }
   int nR,nG,nB;
   for (int i=0; i < nTaille*3; i+=3)
    {
      nR = ImgIn[i];
      nG = ImgIn[i+1];
      nB = ImgIn[i+2];
      indiceValR[nR]++;
      indiceValG[nG]++;
      indiceValB[nB]++;
    }
   for(int i=0;i<256;i++){
     printf("%d %d %d %d\n",i,indiceValR[i],indiceValG[i],indiceValB[i]);
   } 
   free(ImgIn);
   return 1;
}