// histo_gre.cpp : Affiche histo

#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
  char cNomImgLue[250];
  int nH, nW, nTaille;
  
  if (argc != 2) 
     {
       printf("Usage: ImageIn.pgm\n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;

   OCTET *ImgIn;
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   allocation_tableau(ImgIn, OCTET, nTaille);
   lire_image_pgm(cNomImgLue, ImgIn, nH * nW);

   int histoVal[256];
   int repartition[256];
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
        repartition[i]=100*((double)nTot/(double)nTaille);
    }
    for(int i=0;i<256;i++){
      printf("%d %d\n",i,repartition[i]);
    }

    free(ImgIn);
    return 1;
}
