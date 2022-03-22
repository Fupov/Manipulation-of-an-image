#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lodepng.h"

typedef struct
{
  unsigned int height;
  unsigned int width;
  unsigned char *rouge;
  unsigned char *bleu;
  unsigned char *vert;
  unsigned char *alpha;


}myimage;


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
    img.rouge= malloc(height*width*sizeof(unsigned char));
    img.bleu= malloc(height*width*sizeof(unsigned char));
    img.vert= malloc(height*width*sizeof(unsigned char));
    img.alpha= malloc(height*width*sizeof(unsigned char));
    int h=0;
  for(int i=0;i<(height*width);i++)
  {
      img.rouge[i] = image[h];
      h++;
      img.vert[i] = image[h];
      h++;
      img.bleu[i] = image[h];
      h++;
      img.alpha[i] = image[h];
      h++;
        
  }

  return img;
}
void EcrireImage(myimage im, char* nom_fichier)
{
    unsigned char *image;
    unsigned error;
    unsigned int width,height;
    int h = 0;
    width = im.width;
    height = im.height;
    image = malloc(height*width*4*sizeof(unsigned char));
    for(int i=0;i<(height*width);i++)
  {
      image[h] = im.rouge[i];
      h++;
      image[h] = im.vert[i];
      h++;
      image[h] = im.bleu[i];
      h++;
      image[h] = im.alpha[i];
      h++;

  }
   error = lodepng_encode32_file(nom_fichier, image, width, height);
  if (error)
    printf("error %u: %s\n", error, lodepng_error_text(error));
}


void EcrireImagedemiBN(myimage im,myimage im1, char* nom_fichier)
{
    unsigned char *image;
    unsigned error;
    unsigned int width,height;
    unsigned int noirblanc;

    int h = 0;
    width = im.width;
    height = im.height;
    image = malloc(height*width*4*sizeof(unsigned char));
    int number=0, upper=25, lower = -25;
    for(int i=0;i<(height*width);i++)
  {
      if(im1.rouge[i] == 255 && im1.vert[i] == 255 && im1.bleu[i] == 255 )
      {
    noirblanc = (im.rouge[i]+im.bleu[i]+im.vert[i])/3 ;
    do{
    number = (rand() % (upper - lower + 1)) + lower;
    } while (number+noirblanc<0 || number+noirblanc > 255);

        image[h] = noirblanc+number;
      h++;
      image[h] = noirblanc+number;
      h++;
      image[h] = noirblanc+number;
      h++;
      image[h] = im.alpha[i];
      h++;
      }
      else
      {
      image[h] = im.rouge[i];
      h++;
      image[h] = im.vert[i];
      h++;
      image[h] = im.bleu[i];
      h++;
      image[h] = im.alpha[i];
      h++;
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
    for(int i=0;i<(height*width);i++)
  {
      noirblanc = (im.rouge[i]+im.bleu[i]+im.vert[i])/3 ;
      im.rouge[i] = noirblanc;
      im.bleu[i] = noirblanc;
      im.vert[i] = noirblanc;
     
  }
  

}

int main(int argc, char *argv[])
{
  myimage img;
  myimage img1;
  if(argc < 3) 
	{
		printf("Veuillez entrer les param complet");
    return EXIT_FAILURE;
	} 

  img = LireImage(argv[1]);
  img1 = LireImage(argv[2]);
  //NoirEtBlanc(img);
  EcrireImagedemiBN(img,img1,argv[3]);
  return EXIT_SUCCESS;
}