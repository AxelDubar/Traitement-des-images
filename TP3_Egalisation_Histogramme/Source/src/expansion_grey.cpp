// histo_gre.cpp : Affiche histo

#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille, S;
  
  if (argc != 3) 
     {
       printf("Usage: ImageIn.pgm ImageOut.pgm\n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgEcrite) ;

   OCTET *ImgIn, *ImgOut;
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   allocation_tableau(ImgIn, OCTET, nTaille);
   lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgOut, OCTET, nTaille);
   
    int Vmin=0;
    int Vmax=255;
    int V0,V1;

   int histoVal[256];
   for(int i=0;i<256;i++){
     histoVal[i]=0;
   }
   for (int i=0; i < nH; i++){
     for (int j=0; j < nW; j++)
      {
         histoVal[ImgIn[i*nW+j]]++;
      }
   }
    V0=0;
    while (histoVal[V0]==0)
    {
        V0++;
    }
    V1=255;
    while (histoVal[V1]==0)
    {
        V1--;
    }

    double d=(Vmin*V1-Vmax*V0)/(V1-V0);
    double g=(Vmax-Vmin)/(V1-V0);

    printf("d=%lf, g=%lf\n",d,g);
    for (int i=0; i < nH; i++){
     for (int j=0; j < nW; j++)
      {
         ImgOut[i*nW+j]=g*ImgIn[i*nW+j]+d;
      }
   }

    
    ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
    free(ImgIn);
    return 1;
}
