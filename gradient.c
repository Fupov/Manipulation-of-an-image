#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lodepng.h"

typedef struct
{
  unsigned int height;
  unsigned int width;
  unsigned char **rouge;
  unsigned char **bleu;
  unsigned char **vert;
  unsigned char **alpha;


}myimage;

int min(int tab[],int taille)
{
  int min = tab[0];
  for(int i=1;i<taille;i++)
  {
      if(min>tab[i])
      min = tab[i];
  }
  return min;
}

int max(int tab[],int taille)
{
  int max = tab[0];
  for(int i=1;i<taille;i++)
  {
      if(max<tab[i])
      max = tab[i];
  }
  return max;
}
myimage LireImage(const char *filename)
{
  myimage img;
  unsigned error;
  unsigned char *image = 0;
  unsigned int width, height;

  error = lodepng_decode32_file(&image, &width, &height, filename);
  if (error) {
    printf("error %u: %s\n", error, lodepng_error_text(error));
  }
  img.height = height;
  img.width = width;
    img.rouge= malloc(height*sizeof(unsigned char*));
    img.bleu= malloc(height*sizeof(unsigned char*));
    img.vert= malloc(height*sizeof(unsigned char*));
    img.alpha= malloc(height*sizeof(unsigned char*));
    int h=0;
  for(int i=0;i<height;i++)
  {
    img.rouge[i]= malloc(width*sizeof(unsigned char));
    img.vert[i]= malloc(width*sizeof(unsigned char));
    img.bleu[i]= malloc(width*sizeof(unsigned char));
    img.alpha[i]= malloc(width*sizeof(unsigned char));

      for(int j=0;j<width;j++) {
      img.rouge[i][j] = image[h];
      h++;
      img.vert[i][j] = image[h];
      h++;
      img.bleu[i][j] = image[h];
      h++;
      img.alpha[i][j] = image[h];
      h++;
      }
  }

  return img;
}

void EcrireImage(myimage im, char* nom_fichier)
{
    unsigned char *image;

    unsigned error;
    unsigned int width,height;
    width = im.width;
    height = im.height;
    image = malloc(height*width*4*sizeof(unsigned char));
    int M,m;
    int h=0;
    int tab[9];

  for( int i=0;i<height;i++)
  {
    for( int j=0;j<width;j++){

  
    if(i+1 < height && i-1>=0 && j+1<width && j-1 >=0){
        tab[0] = im.rouge[i][j];
        tab[1] = im.rouge[i][j+1];
        tab[2] = im.rouge[i][j-1];
        tab[3] = im.rouge[i+1][j];
        tab[4] = im.rouge[i+1][j+1];
        tab[5] = im.rouge[i+1][j-1];
        tab[6] = im.rouge[i-1][j];   
        tab[7] = im.rouge[i-1][j+1];
        tab[8] = im.rouge[i-1][j-1];
      
    M = max(tab,9);

    m = min(tab,9);

    int p = M-m;
     image[h] = p;
      h++;
      image[h] = p;
      h++;
      image[h] = p;
      h++;
      image[h] = im.alpha[i][j];
      h++;
    }
    else
    {
       image[h] = im.rouge[i][j];
      h++;
      image[h] = im.vert[i][j];
      h++;
      image[h] = im.bleu[i][j];
      h++;
      image[h] = im.alpha[i][j];
      h++;
    }

    }
  }
  
      
  error = lodepng_encode32_file(nom_fichier, image, width, height);
  if (error)
    printf("error %u: %s\n", error, lodepng_error_text(error));
}

void NoirEtBlanc(myimage im)
{

    unsigned int width,height;
    width = im.width;
    height = im.height;
    unsigned int noirblanc;
    for(int i=0;i<height;i++)
  {
    for(int j=0;j<width;j++) {
      noirblanc = (im.rouge[i][j]+im.bleu[i][j]+im.vert[i][j])/3 ;
      im.rouge[i][j] = noirblanc;
      im.bleu[i][j] = noirblanc;
      im.vert[i][j] = noirblanc;
    }
  }
  

}

int main(int argc, char *argv[])
{
  myimage img;
  if(argc < 3) 
	{
		printf("Veuillez entrer les param complet");
    return EXIT_FAILURE;
	} 

  img = LireImage(argv[1]);
  EcrireImage(img,argv[2]);
  return EXIT_SUCCESS;
}


