// histo_gre.cpp : Affiche histo

#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
  char cNomImgModele[250],cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille,nHMod, nWMod, nTailleMod;
  
  if (argc != 4) 
     {
       printf("Usage: ImageModele.pgm ImageIn.pgm ImageOut.pgm\n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgModele) ;
   sscanf (argv[2],"%s",cNomImgLue) ;
   sscanf (argv[3],"%s",cNomImgEcrite) ;

   OCTET *ImgIn, *ImgModele,*ImgOut;
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
   allocation_tableau(ImgIn, OCTET, nTaille);
   lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgModele, &nHMod, &nWMod);
   nTailleMod = nHMod * nWMod;
   allocation_tableau(ImgModele, OCTET, nTailleMod);
   lire_image_pgm(cNomImgModele, ImgModele, nHMod * nWMod);
   
   allocation_tableau(ImgOut, OCTET, nTaille);

   int histoVal[256];
   double repartition[256];
   for(int i=0;i<256;i++){
     histoVal[i]=0;
   }   
   for (int i=0; i < nH; i++){
     for (int j=0; j < nW; j++)
      {
         histoVal[ImgModele[i*nW+j]]++;
      }
    }
    int nTot=0;
    for(int i=0;i<256;i++){
        nTot+=histoVal[i];
        repartition[i]=((double)nTot/(double)nTaille);
    }
    int Fa[256];
    int FaInv[256];
    for(int i=0;i<256;i++){
        Fa[i]=255*repartition[i];
        FaInv[i]=-1;
    }
    for(int i=0;i<256;i++){
        FaInv[Fa[i]]=i;
        printf("%d %d %d\n",i,FaInv[i],Fa[i]);
    }
    
    for (int i=0; i < nH; i++){
        for (int j=0; j < nW; j++)
        {
        int val=ImgIn[i*nW+j];
        
        ImgOut[i*nW+j]=FaInv[val];
        }
    }
    ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
    free(ImgIn);
    return 1;
}
