// profil_gris.cpp : Affiche le profil d'une image en niveau de gris

#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
  char cNomImgLue[250];
  int nH, nW, nTaille;
  int num;
  char LigneCol;
  if (argc != 4) 
     {
       printf("Usage: ImageIn.pgm L/C numLigne/numColonne\n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%c",&LigneCol) ;
   sscanf (argv[3],"%d",&num) ;

   OCTET *ImgIn;
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   allocation_tableau(ImgIn, OCTET, nTaille);
   lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
   printf("# Profil de l'image\n");
   if(LigneCol=='L'){
     for (int j=0; j < nH; j++){
   	  printf("%d %d\n",j,ImgIn[num*nW+j]);
     }
   }
   if(LigneCol=='C'){
     for (int i=0; i < nH; i++){
   	  printf("%d %d\n",i,ImgIn[i*nW+num]);
     }
   }
   free(ImgIn);
   return 1;
}