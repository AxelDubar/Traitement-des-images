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

   int histoVal[256];
   double repartition[256];
   for(int i=0;i<256;i++){
     histoVal[i]=0;
   }   
   for (int i=0; i < nH; i++){
     for (int j=0; j < nW; j++)
      {
         histoVal[ImgIn[i*nW+j]]++;
      }
    }
    int nTot=0;
    for(int i=0;i<256;i++){
        nTot+=histoVal[i];
        repartition[i]=((double)nTot/(double)nTaille);
    }
    int Fa[256];
    for(int i=0;i<256;i++){
        Fa[i]=255*repartition[i];
        printf("%d %d\n",i,Fa[i]);
    }
    for (int i=0; i < nH; i++){
        for (int j=0; j < nW; j++)
        {
        int val=ImgIn[i*nW+j];
        
        ImgOut[i*nW+j]=Fa[val];
        }
    }
    ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
    free(ImgIn);
    return 1;
}
