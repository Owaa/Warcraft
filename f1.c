#define BUFFER_OFFSET(i) ((char *)NULL + (i))
#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h> 
#include <math.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <time.h> 
#include <assert.h>
 
#include "head.h"

GLUquadricObj *quadAtmosphere;

int mode = 0;
int cursorX,cursorY;
int rotate = 0 ;
int chrono =0;
int denre_bois = 1500 ;
int denre_food = 2500;

int bonus_vie = 0;
int bonus_denre = 0;
int bonus_degat = 0;

int nb_perso = 0;
int nb_bati = 0;
int nb_monstre = 0; 
int id_roi ;
int id_obj ;

int cible_perso = 0;
int cible_monstre = -1;
FILE * Map;

test paysan;
test paysan2;


void 
reshape (int w, int h) { 
  
  glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
  glMatrixMode (GL_PROJECTION); 
  glLoadIdentity (); 
  gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 0.01, FIN * 3); 
  glMatrixMode(GL_MODELVIEW); 

}


void 
init(void) {


 
  int i = 0 , j = 0;
  int c =0 ;
  glClearColor (0.0, 0.0, 0.0, 0.0); 
  glEnable(GL_DEPTH_TEST);
  glShadeModel (GL_SMOOTH); 

  
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  //  glLightfv(GL_LIGHT0,  GL_POSITION, pos);
  
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT1);
 
  //  glEnable(GL_COLOR_MATERIAL);
 
  GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat mat_shininess[] = { 50.0 };
  GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
  
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
  glLightfv(GL_LIGHT1, GL_POSITION, light_position);
  /* _______________ Creation de la map a partir du fichier passe en paramettre _______*/
  while( (c = fgetc(Map  ))!= EOF){

    // Si sa depasse on ne prend pas en compte    
    if( j >TAILLE_MAP_X ) continue ;
    if( i >TAILLE_MAP_Y ) continue ;
   
    switch (c){
    case 10 :
      i++;
      j = 0;
      continue ;
      break;

    case  's' :
      cree_perso(j*TAILLE_CARRE, i * TAILLE_CARRE , 2 , 300);

      tab[j][i].type =   tab[j-1][i].type;
      j++ ;
      continue ;
      break;


    case  'r' :

      id_roi = nb_perso;
      cree_perso(j*TAILLE_CARRE, i * TAILLE_CARRE , 3 , 500);
     
      tab[j][i].type =   tab[j-1][i].type;
      j++ ;
      continue ;
      break;
   
    case  'm' :
      cree_monstre(j*TAILLE_CARRE, i * TAILLE_CARRE , 1 , 400);
      tab[j][i].type =   tab[j-1][i].type;
      j++ ;
      continue ;
      break;
	
 

    case  'p' :
      cree_perso(j*TAILLE_CARRE, i * TAILLE_CARRE , 1 , 200);
      tab[j][i].type =   tab[j-1][i].type;
      j++ ;
      continue ;
      break;

    case  'c' :
      cree_bati(j*TAILLE_CARRE, i * TAILLE_CARRE , 2 , 200);
      tab[j][i].type =   tab[j-1][i].type;
      j++ ;
      continue ;
      break;

    case  'g' :
      cree_bati(j*TAILLE_CARRE, i * TAILLE_CARRE , 1 , 200);
      tab[j][i].type =   tab[j-1][i].type;
      j++ ;
      continue ;
      break;
     

    }
   
  
    tab[j][i].type = c - 48;
    j++;
   

  }
  fclose(Map) ;

  /* _____________ Chargement des image et Texture _______________*/

  Image *image1;
  
  image1 = (Image *) malloc(sizeof(Image));
  if (image1 == NULL) {
    printf("Probleme d'allocation d'espace memoire\n");
  }
  
 
  if (!ImageLoad("herb.bmp", image1)) {
    printf("Impossible d'ouvrir ce fichier\n");
  }        

  glGenTextures(1, &id_tex_herbe);
  glBindTexture(GL_TEXTURE_2D, id_tex_herbe); 
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, 3, image1->sizeX, image1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image1->data);
  


  if (!ImageLoad("sol.bmp", image1)) {
    printf("Impossible d'ouvrir ce fichier\n");
  }        

  glGenTextures(1, &id_tex_sol);
  glBindTexture(GL_TEXTURE_2D, id_tex_sol); 
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, 3, image1->sizeX, image1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image1->data);






  if (!ImageLoad("eau.bmp", image1)) {
    printf("Impossible d'ouvrir ce fichier\n");
  }        

  glGenTextures(1, &id_tex_eau);
  glBindTexture(GL_TEXTURE_2D, id_tex_eau); 
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, 3, image1->sizeX, image1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image1->data);


  if (!ImageLoad("8.bmp", image1)) {
    printf("Impossible d'ouvrir ce fichier\n");
  }        

  glGenTextures(1, &id_tex_mur);
  glBindTexture(GL_TEXTURE_2D, id_tex_mur); 
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, 3, image1->sizeX, image1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image1->data);

  if (!ImageLoad("9.bmp", image1)) {
    printf("Impossible d'ouvrir ce fichier\n");
  }        

  glGenTextures(1, &id_tex_brique);
  glBindTexture(GL_TEXTURE_2D, id_tex_brique); 
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, 3, image1->sizeX, image1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image1->data);

 if (!ImageLoad("6.bmp", image1)) {
    printf("Impossible d'ouvrir ce fichier\n");
  }        

  glGenTextures(1, &id_tex_obj);
  glBindTexture(GL_TEXTURE_2D, id_tex_obj); 
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, 3, image1->sizeX, image1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image1->data);

 if (!ImageLoad("courone.bmp", image1)) {
    printf("Impossible d'ouvrir ce fichier\n");
  }        

  glGenTextures(1, &id_tex_courone);
  glBindTexture(GL_TEXTURE_2D, id_tex_courone); 
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, 3, image1->sizeX, image1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image1->data);

  
  
  if (!ImageLoad("fantome.bmp", image1)) {
    printf("Impossible d'ouvrir ce fichier\n");
  }        

  quadAtmosphere=gluNewQuadric();
  gluQuadricNormals(quadAtmosphere, GLU_SMOOTH);
  gluQuadricTexture(quadAtmosphere, GL_TRUE);

  glGenTextures(1, &id_tex_monstre);
  glBindTexture(GL_TEXTURE_2D, id_tex_monstre); 
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, 3, image1->sizeX, image1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image1->data);

  

  free(image1->data);
  free(image1);
  /* ____________________________________________________________ */
  /* ___________________   Chargemment VBO ______________________ */

  GLfloat herbe[] = {
    0.0 , 0.0 , 0.0,
    0.0 , 0.0 , TAILLE_CARRE,
    TAILLE_CARRE , 0.0 , TAILLE_CARRE,
    TAILLE_CARRE , 0.0 , 0.0,

   

    0.0 , 0.0,
    0.0 , 1.0,
    1.0 , 1.0,
    1.0 , 0.0,
  
  
    0.0 ,1.0 ,0.0, // nomale en plus y
    0.0 ,1.0 ,0.0, // nomale en plus y
    0.0 ,1.0 ,0.0, // nomale en plus y
    0.0 ,1.0 ,0.0, // nomale en plus y

  };
 

  glGenBuffers(1,&id_herbe);
  glBindBuffer(GL_ARRAY_BUFFER,id_herbe);
  glBufferData(GL_ARRAY_BUFFER, (12 + 8+ 12) *sizeof(GLfloat), herbe, GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER,0);
 
  GLfloat rect[] = {
    0.0 , 0.0 , 0.0,
    0.0 , 0.0 , TAILLE_CARRE ,
    TAILLE_CARRE/2 , 0.0 , TAILLE_CARRE,
    TAILLE_CARRE /2, 0.0 , 0.0,


    0.0 , 0.0,
    0.0 , 1.0,
    1.0 , 1.0,
    1.0 , 0.0,
  
  
    0.0 ,1.0 ,0.0, // nomale en plus y
    0.0 ,1.0 ,0.0, // nomale en plus y
    0.0 ,1.0 ,0.0, // nomale en plus y
    0.0 ,1.0 ,0.0, // nomale en plus y

  };
 

  glGenBuffers(1,&id_rect);
  glBindBuffer(GL_ARRAY_BUFFER,id_rect);
  glBufferData(GL_ARRAY_BUFFER, ( 12 + 8+ 12) *sizeof(GLfloat), rect, GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER,0);

  for( i = 0; i< nb_perso ; i++ ) {
      
    tab_perso[i].denre_type  =0;
    tab_perso[i].denre  =  0; 
  }


  

  GLfloat cube[]={


    0.0 , TAILLE_CARRE , TAILLE_CARRE , // Face Avant
    TAILLE_CARRE , TAILLE_CARRE , TAILLE_CARRE , 
    TAILLE_CARRE , 0.0 , TAILLE_CARRE , 
    0.0 , 0.0 , TAILLE_CARRE 
		  
    , 0.0 , TAILLE_CARRE , 0.0// Face Arriere
    , TAILLE_CARRE , TAILLE_CARRE , 0.0
    , TAILLE_CARRE , 0.0 , 0.0
    , 0.0 , 0.0 , 0.0
	
    , 0.0 , TAILLE_CARRE , 0.0// Face Haut
    , TAILLE_CARRE , TAILLE_CARRE , 0.0
    , TAILLE_CARRE , TAILLE_CARRE , TAILLE_CARRE 
    , 0.0 , TAILLE_CARRE , TAILLE_CARRE 
		  
    , 0.0 , 0.0 , 0.0 // Face bas
    , TAILLE_CARRE , 0.0 , 0.0 
    , TAILLE_CARRE , 0.0 , TAILLE_CARRE
    , 0.0 , 0.0 , TAILLE_CARRE 
	
    , 0.0 , TAILLE_CARRE ,TAILLE_CARRE //Face droite
    , 0.0 , TAILLE_CARRE , 0.0 
    , 0.0 , 0.0 , 0.0
    , 0.0 , 0.0 , TAILLE_CARRE
		 
    , TAILLE_CARRE , TAILLE_CARRE , TAILLE_CARRE // face gauche
    , TAILLE_CARRE , TAILLE_CARRE , 0.0
    , TAILLE_CARRE , 0.0 , 0.0
    , TAILLE_CARRE , 0.0 , TAILLE_CARRE,

		    
    0.0,  1.0 , 0.0 ,
    0.0 , 1.0 , 0.0 ,
    0.0 , 1.0 , 0.0 ,
    0.0 , 1.0 , 0.0 ,

    0.0 , 1.0 , 0.0 ,
    0.0 , 1.0 , 0.0 ,
    0.0 , 1.0 , 0.0 ,
    0.0 , 1.0 , 0.0 ,

    0.0 ,1.0 ,0.0, // nomale en plus y
    0.0 ,1.0 ,0.0, // nomale en plus y
    0.0 ,1.0 ,0.0, // nomale en plus y
    0.0 ,1.0 ,0.0, // nomale en plus y

    0.0 ,1.0 ,0.0, // nomale en moin y
    0.0 ,1.0 ,0.0, // nomale en moin y
    0.0 ,1.0 ,0.0, // nomale en moin y
    0.0 ,1.0 ,0.0, // nomale en moin y


    0.0,  1.0 , 0.0 ,
    0.0 , 1.0 , 0.0 ,
    0.0 , 1.0 , 0.0 ,
    0.0 , 1.0 , 0.0 ,

    0.0 , 1.0 , 0.0 ,
    0.0 , 1.0 , 0.0 ,
    0.0 , 1.0 , 0.0 ,
    0.0 , 1.0 , 0.0 ,
		   

    0.0 , 0.0,
    0.0 , 1.0,
    1.0 , 1.0,
    1.0 , 0.0,

    0.0 , 0.0,
    0.0 , 1.0,
    1.0 , 1.0,
    1.0 , 0.0,

    0.0 , 0.0,
    0.0 , 1.0,
    1.0 , 1.0,
    1.0 , 0.0,

    0.0 , 0.0,
    0.0 , 1.0,
    1.0 , 1.0,
    1.0 , 0.0,

    0.0 , 0.0,
    0.0 , 1.0,
    1.0 , 1.0,
    1.0 , 0.0,

    0.0 , 0.0,
    0.0 , 1.0,
    1.0 , 1.0,
    1.0 , 0.0


		  
  };

  glGenBuffers(1, &id_perso5);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_perso5);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, 192* sizeof(GL_UNSIGNED_INT), cube, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  GLfloat batimment[]={


    0.0             , TAILLE_CARRE * 8 , TAILLE_CARRE *6, // Face Avant
    TAILLE_CARRE *3 , TAILLE_CARRE * 8 , TAILLE_CARRE *6, 
    TAILLE_CARRE *3 , 0.0              , TAILLE_CARRE *6, 
    0.0             , 0.0              , TAILLE_CARRE *6,
		  
    0.0             , TAILLE_CARRE * 8 , 0.0           ,  // Face Arriere
    TAILLE_CARRE *3 , TAILLE_CARRE * 8 , 0.0           ,
    TAILLE_CARRE *3 , 0.0              , 0.0           ,
    0.0             , 0.0              , 0.0           ,
	
    0.0             , TAILLE_CARRE *8   , 0.0           ,    // Face Haut
    TAILLE_CARRE *3 , TAILLE_CARRE *8   , 0.0           ,
    TAILLE_CARRE *3 , TAILLE_CARRE *8  , TAILLE_CARRE *6 ,
    0.0             , TAILLE_CARRE *8  , TAILLE_CARRE *6 , 
		  
    0.0             , 0.0              , 0.0           ,    // Face bas
    TAILLE_CARRE*3  , 0.0              , 0.0           , 
    TAILLE_CARRE*3  , 0.0              , TAILLE_CARRE *6 , 
    0.0             , 0.0              , TAILLE_CARRE *6 ,
	
    0.0             , TAILLE_CARRE *8   ,TAILLE_CARRE  *6 , //Face droite
    0.0             , TAILLE_CARRE *8  , 0.0           ,
    0.0             , 0.0              , 0.0           ,
    0.0             , 0.0              , TAILLE_CARRE *6 ,
		 
    TAILLE_CARRE *3 , TAILLE_CARRE *8   , TAILLE_CARRE *6 ,     // face gauche
    TAILLE_CARRE* 3 , TAILLE_CARRE *8   , 0.0           ,
    TAILLE_CARRE *3 , 0.0               , 0.0           ,
    TAILLE_CARRE *3 , 0.0               , TAILLE_CARRE  *6,

    0.0,  1.0 , 0.0 ,
    0.0 , 1.0 , 0.0 ,
    0.0 , 1.0 , 0.0 ,
    0.0 , 1.0 , 0.0 ,

    0.0 , 1.0 , 0.0 ,
    0.0 , 1.0 , 0.0 ,
    0.0 , 1.0 , 0.0 ,
    0.0 , 1.0 , 0.0 ,

    0.0 ,1.0 ,0.0, // nomale en plus y
    0.0 ,1.0 ,0.0, // nomale en plus y
    0.0 ,1.0 ,0.0, // nomale en plus y
    0.0 ,1.0 ,0.0, // nomale en plus y

    0.0 ,1.0 ,0.0, // nomale en moin y
    0.0 ,1.0 ,0.0, // nomale en moin y
    0.0 ,1.0 ,0.0, // nomale en moin y
    0.0 ,1.0 ,0.0, // nomale en moin y


    0.0,  1.0 , 0.0 ,
    0.0 , 1.0 , 0.0 ,
    0.0 , 1.0 , 0.0 ,
    0.0 , 1.0 , 0.0 ,

    0.0 , 1.0 , 0.0 ,
    0.0 , 1.0 , 0.0 ,
    0.0 , 1.0 , 0.0 ,
    0.0 , 1.0 , 0.0 ,
      
		   
		   

    0.0 , 0.0,
    0.0 , 1.0,
    1.0 , 1.0,
    1.0 , 0.0,

    0.0 , 0.0,
    0.0 , 1.0,
    1.0 , 1.0,
    1.0 , 0.0,

    0.0 , 0.0,
    0.0 , 1.0,
    1.0 , 1.0,
    1.0 , 0.0,

    0.0 , 0.0,
    0.0 , 1.0,
    1.0 , 1.0,
    1.0 , 0.0,

    0.0 , 0.0,
    0.0 , 1.0,
    1.0 , 1.0,
    1.0 , 0.0,

    0.0 , 0.0,
    0.0 , 1.0,
    1.0 , 1.0,
    1.0 , 0.0


		  
  };

  glGenBuffers(1, &id_perso6);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_perso6);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, 192* sizeof(GL_UNSIGNED_INT), batimment, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  GLfloat bati[]={


    0.0             , TAILLE_CARRE * 3 , TAILLE_CARRE *6, // Face Avant
    TAILLE_CARRE *8 , TAILLE_CARRE * 3 , TAILLE_CARRE *6, 
    TAILLE_CARRE *8 , 0.0              , TAILLE_CARRE *6, 
    0.0             , 0.0              , TAILLE_CARRE *6,
		  
    0.0             , TAILLE_CARRE * 3 , 0.0           ,  // Face Arriere
    TAILLE_CARRE *8 , TAILLE_CARRE * 3 , 0.0           ,
    TAILLE_CARRE *8 , 0.0              , 0.0           ,
    0.0             , 0.0              , 0.0           ,
	
    0.0             , TAILLE_CARRE *3  , 0.0           ,    // Face Haut
    TAILLE_CARRE *8 , TAILLE_CARRE *3   , 0.0           ,
    TAILLE_CARRE *8 , TAILLE_CARRE *3  , TAILLE_CARRE *6 ,
    0.0             , TAILLE_CARRE *3  , TAILLE_CARRE *6 , 
		  
    0.0             , 0.0              , 0.0           ,    // Face bas
    TAILLE_CARRE*8 , 0.0              , 0.0           , 
    TAILLE_CARRE*8  , 0.0              , TAILLE_CARRE *6 , 
    0.0             , 0.0              , TAILLE_CARRE *6 ,
	
    0.0             , TAILLE_CARRE *3   ,TAILLE_CARRE  *6 , //Face droite
    0.0             , TAILLE_CARRE *3  , 0.0           ,
    0.0             , 0.0              , 0.0           ,
    0.0             , 0.0              , TAILLE_CARRE *6 ,
		 
    TAILLE_CARRE *8 , TAILLE_CARRE *3   , TAILLE_CARRE *6 ,     // face gauche
    TAILLE_CARRE* 8 , TAILLE_CARRE *3   , 0.0           ,
    TAILLE_CARRE *8 , 0.0               , 0.0           ,
    TAILLE_CARRE *8 , 0.0               , TAILLE_CARRE  *6,

    0.0,  1.0 , 0.0 ,
    0.0 , 1.0 , 0.0 ,
    0.0 , 1.0 , 0.0 ,
    0.0 , 1.0 , 0.0 ,

    0.0 , 1.0 , 0.0 ,
    0.0 , 1.0 , 0.0 ,
    0.0 , 1.0 , 0.0 ,
    0.0 , 1.0 , 0.0 ,

    0.0 ,1.0 ,0.0, // nomale en plus y
    0.0 ,1.0 ,0.0, // nomale en plus y
    0.0 ,1.0 ,0.0, // nomale en plus y
    0.0 ,1.0 ,0.0, // nomale en plus y

    0.0 ,1.0 ,0.0, // nomale en moin y
    0.0 ,1.0 ,0.0, // nomale en moin y
    0.0 ,1.0 ,0.0, // nomale en moin y
    0.0 ,1.0 ,0.0, // nomale en moin y


    0.0,  1.0 , 0.0 ,
    0.0 , 1.0 , 0.0 ,
    0.0 , 1.0 , 0.0 ,
    0.0 , 1.0 , 0.0 ,

    0.0 , 1.0 , 0.0 ,
    0.0 , 1.0 , 0.0 ,
    0.0 , 1.0 , 0.0 ,
    0.0 , 1.0 , 0.0 ,
      
		   
		   

    0.0 , 0.0,
    0.0 , 1.0,
    1.0 , 1.0,
    1.0 , 0.0,

    0.0 , 0.0,
    0.0 , 1.0,
    1.0 , 1.0,
    1.0 , 0.0,

    0.0 , 0.0,
    0.0 , 1.0,
    1.0 , 1.0,
    1.0 , 0.0,

    0.0 , 0.0,
    0.0 , 1.0,
    1.0 , 1.0,
    1.0 , 0.0,

    0.0 , 0.0,
    0.0 , 1.0,
    1.0 , 1.0,
    1.0 , 0.0,

    0.0 , 0.0,
    0.0 , 1.0,
    1.0 , 1.0,
    1.0 , 0.0


		  
  };

  glGenBuffers(1, &id_perso7);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_perso7);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, 192* sizeof(GL_UNSIGNED_INT), bati, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);





}


void DessineId ( int id , int id_tex){
  // dessine la map | Charge un carre et plaqu la texture herbe | eau | sol
  glColor3f(1.0, 1.0, 1.0);
  glEnable(GL_TEXTURE_2D);
  
  glBindTexture(GL_TEXTURE_2D,id_tex);  
  glBindBuffer(GL_ARRAY_BUFFER,id);

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);

  glVertexPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(0));
  glTexCoordPointer(2, GL_FLOAT, 0, BUFFER_OFFSET(12 *sizeof(GLfloat)));
  glNormalPointer(GL_FLOAT, 0, BUFFER_OFFSET( (12+8 )*sizeof(GL_FLOAT)));

  glDrawArrays(GL_QUADS,0,4);

  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_TEXTURE_2D);
  glDisableClientState(GL_NORMAL_ARRAY);


  glBindTexture(GL_TEXTURE_2D,0 );  
  glBindBuffer(GL_ARRAY_BUFFER,0);
  glDisable(GL_TEXTURE_2D);
}
/* ___________________________________________________ */
/* __________________ Partie dessin __________________ */
/* ___________________________________________________ */
void
dessineBati(){

  int i ;

  // Activation de la texture
  glEnable(GL_TEXTURE_2D);




  for(i = 0; i < nb_bati ; i++){
  // Si pas visible affiche pas
    if( camX -tab_bati[i].x  > 500  ||  camX -tab_bati[i].x  < -450 ) continue ;
    if( camZ -tab_bati[i].z  > 500  ||  camX -tab_bati[i].x  < -450) continue ;
    // Bind le buffer vertex ->  Casern | garnison
    if(tab_bati[i].type == 2){
      glBindTexture(GL_TEXTURE_2D, id_tex_mur);
      glBindBuffer(GL_ARRAY_BUFFER,id_perso7);
    }
    else{
      glBindTexture(GL_TEXTURE_2D, id_tex_brique);
      glBindBuffer(GL_ARRAY_BUFFER,id_perso6);
    }

  // Activation des vertex
  glEnableClientState( GL_VERTEX_ARRAY );
  glVertexPointer( 3,GL_FLOAT , 0,  BUFFER_OFFSET(0) );
  // Activation des Normales
  glEnableClientState( GL_NORMAL_ARRAY );
  glNormalPointer(GL_FLOAT, 0 , BUFFER_OFFSET(72*sizeof (GLfloat)));
  // Activation de la texture
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  glTexCoordPointer(2, GL_FLOAT, 0, BUFFER_OFFSET(  144*sizeof (GLfloat)  ));

  
    glPushMatrix(); 
    glTranslatef ( tab_bati[i].x  , 2, tab_bati[i].z); 
  
    glDrawArrays(GL_QUADS, 0, 24);

    glPopMatrix(); 


  }
  // Desactivation
 
  glDisableClientState( GL_VERTEX_ARRAY );
  glDisableClientState(GL_NORMAL_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);

  glBindTexture(GL_TEXTURE_2D, 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glDisable(GL_TEXTURE_2D);
}

void
dessineMonstre(){
  int i ;

  glBindTexture(GL_TEXTURE_2D, id_tex_monstre);
  glEnable(GL_TEXTURE_2D);

  for(i = 0; i < nb_monstre ; i++){
    glColor3f(1.0 , 1.0 , 1.0);
    if(  tab_monstre[i].vie <= 0 ) continue; // Si mort ne pas l'afficher
    // Si pas visible affiche pas
    if( camX -tab_monstre[i].x  > 500  ||  camX -tab_monstre[i].x  < -500 ) continue ;
    if( camZ -tab_monstre[i].z  > 500  ||  camX -tab_monstre[i].x  < -500) continue ;

    glPushMatrix();
    glTranslatef ( tab_monstre[i].x   ,1, tab_monstre[i].z); 

    glRotatef(30,1.0 ,0.0 ,0.0);

    glRotatef(160,0.0 ,1.0 ,1.0);
    // Afiche le monstre plus ou moin grand selon sa vie
    gluSphere(quadAtmosphere,tab_monstre[i].vie/10, 16, 16);     
    glPopMatrix();
  }

  glBindTexture(GL_TEXTURE_2D, 0);
  glDisable(GL_TEXTURE_2D);
}


void
dessinePerso(){


  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, id_tex_monstre);

  glBindBuffer(GL_ARRAY_BUFFER,id_perso5);

  glEnableClientState( GL_VERTEX_ARRAY );
  glVertexPointer( 3,GL_FLOAT , 0,  BUFFER_OFFSET(0) );


  glEnableClientState( GL_NORMAL_ARRAY );
  glNormalPointer(GL_FLOAT, 0 , BUFFER_OFFSET(72*sizeof (GLfloat)));

  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  glTexCoordPointer(2, GL_FLOAT, 0, BUFFER_OFFSET(  144*sizeof (GLfloat)  ));

  int i;

  for(i = 0; i < nb_perso ; i++){
    if( tab_perso[i].vie <= 0) continue ;


     if( camX -tab_perso[i].x  > 500  ||  camX -tab_perso[i].x  < -500 ) continue ;
     if( camZ -tab_perso[i].z  > 500  ||  camX -tab_perso[i].x  < -500) continue ;

    glColor3f(1,1,1);
    glPushMatrix();
    
    glTranslatef ( tab_perso[i].x   ,1, tab_perso[i].z); 
    if(  tab_perso[i].type == 2)  glRotatef(45 ,0.0 ,1.0 ,0.0);
    // Petite "animation" selon l'action du perssonage
    if(tab_perso[i].farm == 1 && tab_perso[i].type == 1 && tab_perso[i].denre < MAX_DENRE )
      glRotatef(rotate ,0.0 ,1.0 ,0.0);
    // S il se bat il tourne autour de l'enemie
    if(tab_perso[i].farm == 2 && tab_perso[i].type == 2) {
      glRotatef(rotate ,0.0 ,1.0 ,0.0);
      glTranslatef ( 45,0,0);
    }
    if( tab_perso[i].type == 3)
      glBindTexture(GL_TEXTURE_2D,  id_tex_courone);
    
    else  glBindTexture(GL_TEXTURE_2D,  id_tex_monstre);


  
    glDrawArrays(GL_QUADS, 0, 24);


    glPopMatrix(); 
   
  }

  glDisableClientState( GL_VERTEX_ARRAY );
  glDisableClientState(GL_NORMAL_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);

  glBindTexture(GL_TEXTURE_2D, 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glDisable(GL_TEXTURE_2D);
}



void
afficheFarm(void){


  int a;
	for ( a = 0 ; a+499< denre_bois ; a += 500 ){

	  glPushMatrix();
	  glTranslatef (1000 - (a/15 ), 2 , -20);   
	  DessineId(id_rect ,id_tex_sol );
	  glPopMatrix(); 

	}
	for ( a = 0 ; a< denre_food ; a += 500 ){

	  glPushMatrix();
	  glTranslatef (1000- (a/15 ),5, -60);
	  DessineId(id_rect ,id_tex_eau );
	  glPopMatrix(); 
	  

	}
	// Vie du perso cible
	glPushMatrix();
	glTranslatef (1050 , 2 , 1050);

	glLineWidth(25); 
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);

	glNormal3f( 0.0 , 1.0 , 1.0);
	glVertex3f(-150, 0, 0);
	glNormal3f( 0.0 , 1.0 , 1.0);
	glVertex3f( -tab_perso[cible_perso].vie -150, 0.0, 0.0);

	glEnd();
	glPopMatrix();

    
	
}
void
afficheMap(void){


  int i , j;
  int n = 0;
  // Affiche tout ce qui est visible dans un "Rayon" de Visible
  for(i = (int)(camX / TAILLE_CARRE) - VISIBLE/2; i< (int)(camX / TAILLE_CARRE) + VISIBLE/2; i++){
    for(j = (int)(camZ / TAILLE_CARRE) - VISIBLE/2 ; j< (int)(camZ/ TAILLE_CARRE) + VISIBLE/2; j++){
       
      glPushMatrix();
      glTranslatef ( TAILLE_CARRE*i  ,0, TAILLE_CARRE *j ); 

      // Affiche un rectangle pour chaque 500 de farm et la ligne de vie du persso cible
      if (n ==0 ){	afficheFarm();  	n = 1;     }

      switch(tab[i][j].type) {
      case 1:
	DessineId(id_herbe , id_tex_herbe); break;
      case 2:
	DessineId(id_herbe ,id_tex_eau); break;
      case 3:
	DessineId(id_herbe ,id_tex_sol ); break;
      case 4:
	DessineId(id_herbe ,id_tex_herbe ); break; // A modifier
      case 5:
	DessineId(id_herbe ,id_tex_obj ); break; // A modifier
     
      }
      glPopMatrix();   

    }
 
  }




}




/* __________ Fct pour le picking __________*/
void
dessinePaysan2(){

  int i , j;
  glBindBuffer(GL_ARRAY_BUFFER,id_herbe);
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(0));

  for(i = (int)(camX / TAILLE_CARRE) - VISIBLE/2; i< (int)(camX / TAILLE_CARRE) + VISIBLE/2; i++){
    for(j = (int)(camZ / TAILLE_CARRE) - VISIBLE/2 ; j< (int)(camZ/ TAILLE_CARRE) + VISIBLE/2; j++){
      /*
       Chaque case est colorier avec r = sa position x g = pos z b = 0
       Dans le picking si je clique sur un pixel avec b = 0 
       alors j'ai cliquer sur la map et je conais son x et z grace au r et g

       Les perso sont colorier r = 30 g = 30 b = leur identifiant
       Les monstres sont colorier r = 60 g = 60 b = leur identifiant
       Les batimentssont colorier r = 90 g = 90 b = leur identifiant
      */
      glPushMatrix();
      glTranslatef ( TAILLE_CARRE*i  ,2, TAILLE_CARRE *j ); 

      glColor3ub(i,j,0);

      glDrawArrays(GL_QUADS,0,4);      
      glPopMatrix(); 
     
    }
    int i;


    for(i = 0; i < nb_perso ; i++){
    
      glColor3ub(30,30,i);
      if( tab_perso[i].vie <= 0) continue ;

      glPushMatrix();
      glTranslatef ( tab_perso[i].x  ,2, tab_perso[i].z);
      glDrawArrays(GL_QUADS,0,4);      
      glPopMatrix(); 


    }
    
    for(i = 0; i < nb_bati ; i++){
      int h  , l , p  ;
      glColor3ub(60,60,i);
      // dessine une caserne | garnison
      if( tab_bati[i].type == 1) {	l = 3 ; h = 8 ; p = 6 ;  }
                        else     {	l = 8 ; h = 3 ; p = 6 ;  }

      glBegin(GL_QUADS);
    

      glVertex3f( tab_bati[i].x,           TAILLE_CARRE* h     ,              tab_bati[i].z );
      glVertex3f(tab_bati[i].x,                TAILLE_CARRE* h  ,              TAILLE_CARRE*p +   tab_bati[i].z );
      glVertex3f(TAILLE_CARRE *l +tab_bati[i].x,  0 ,             TAILLE_CARRE*p +  tab_bati[i].z  );
      glVertex3f(TAILLE_CARRE *l + tab_bati[i].x,  0 ,            tab_bati[i].z    );

      glEnd(); 
    
    }
 
    for(i = 0; i < nb_monstre ; i++){
      if( tab_monstre[i].vie <= 0) continue ;

      glColor3ub(90,90,i);
      glPushMatrix();
      glTranslatef ( tab_monstre[i].x   ,1, tab_monstre[i].z); 
      glutSolidSphere(tab_monstre[i].vie/10,16,16);

      glPopMatrix();
    }


  }

  glDisableClientState(GL_VERTEX_ARRAY);
  glBindBuffer(GL_ARRAY_BUFFER,0);

}


/* ___________________________________________________ */
/* _____________ Partie control interaction __________ */
/* ___________________________________________________ */
void 
mouse ( int x, int y ){
  

  sourisX = x;
  sourisY = y;
 
}

void mouseStuff(int button, int state, int x, int y) {

	if (button != GLUT_LEFT_BUTTON || state != GLUT_DOWN)
		return;
	
	cursorX = x;
	cursorY = y;
	mode = 1;
	

}

void 
specialkeyboard (int key, int x, int y) { 
  // Deplace la camera grace au fleche du clavier
  // Test si on depasse de la map et application des changement
  switch (key)	{ 
  case GLUT_KEY_UP :  
    if( (camZ/ TAILLE_CARRE) + VISIBLE/2 < TAILLE_MAP_X)
      camZ +=  VITESSE_CAMERA;
    break;
  case GLUT_KEY_DOWN :
    if( (camZ/ TAILLE_CARRE) - VISIBLE/2 >=0)
    camZ -=  VITESSE_CAMERA; 
    break;
    
  case GLUT_KEY_LEFT :
    if ((camX / TAILLE_CARRE) + VISIBLE/2 < TAILLE_MAP_Y)
      camX +=  VITESSE_CAMERA;
  break;
  case GLUT_KEY_RIGHT :
 if ((camX / TAILLE_CARRE) - VISIBLE/2 >= 0)
       camX -=  VITESSE_CAMERA;
    break;
  }

  glutPostRedisplay();
}

void cree_perso (int x , int z ,int type , int vie){


  tab_perso[nb_perso].type = type;
  tab_perso[nb_perso].x = tab_perso[nb_perso].nx = x; 
  tab_perso[nb_perso].y = 0 ;
  tab_perso[nb_perso].z = tab_perso[nb_perso].nz = z;

 
  tab_perso[nb_perso].vie = vie +bonus_vie;

  nb_perso++;



}

void 
keyboard (unsigned char key, int x, int y) { 
  if(  paysan.nx < 3 || paysan.nz < 3 ) return; ;
  switch (key)	{ 
    
  case 27:
    exit(0);
    break;
  case 'r':
    r *= -1;
    break;
  case 'p':
    if(nb_perso < 255 && denre_food >= 500)
      cree_perso (paysan.nx ,paysan.nz ,1 ,200);
    else  printf("\nVous avez atteint le max perso possible\n");
    denre_food-= 500;
    break;
    
  case'g':
    if( denre_bois >= 1000){
      cree_bati(paysan.nx ,paysan.nz , 1 , 1000);
      denre_bois-= 1000;
  bonus_denre += 10;
    }
    break;

  case'c':
    if( denre_bois >= 1000){
      cree_bati(paysan.nx ,paysan.nz , 2 , 1000);
      denre_bois-= 1000;
      bonus_degat += 5;
      bonus_vie += 50;
    }
    
    break;

  case'x':
    if(nb_perso < 255 && denre_food >= 500)
      cree_perso (paysan.nx ,paysan.nz ,2 ,200);

    denre_food-= 500;
  
    break;

  case'm':
    if(nb_monstre < 255 )
      cree_monstre (paysan.nx ,paysan.nz ,2 ,200);

  
    break;


  }
  glutPostRedisplay();

}
/* ___________________________________________________ */
/* _____________ Partie Creation des obgets __________ */
/* ___________________________________________________ */

 void cree_monstre (int x , int z ,int type , int vie){

 tab_monstre[nb_monstre].type = type;
 tab_monstre[nb_monstre].x = tab_monstre[nb_monstre].nx = x;
 tab_monstre[nb_monstre].z = tab_monstre[nb_monstre].nz = z;
 
 if(type == 4){
   tab_monstre[nb_monstre].nx = tab_perso[id_roi].x ;
tab_monstre[nb_monstre].nz = tab_perso[id_roi].z ;
}
 tab_monstre[nb_monstre].vie = vie ;
 tab_monstre[nb_monstre].cible = -1;
tab_monstre[nb_monstre].farm = 0;
 nb_monstre++;



}
void cree_bati (int x , int z ,int type , int vie){
  tab_bati[nb_bati].type = type;
  tab_bati[nb_bati].x = x;
  tab_bati[nb_bati].z = z;
 tab_bati[nb_bati].vie = vie;
  nb_bati++;

}

/* ___________________________________________________ */
/* _____________ Partie deplacements des obgets __________ */
/* ___________________________________________________ */


void
deplacePerso(void){

  int i;
  // int i2, x , y , z , ecart;
  // int lateral ;
  for( i = 0; i< nb_perso ; i++ ) {
 
    

    // Si possiton actuelle != de la possition voulue je deplace mon perso
    if(tab_perso[i] .x != tab_perso[i].nx)
      tab_perso[i].x += tab_perso[i].x > tab_perso[i].nx? -VITESSE_MARCHE_PAYSAN : VITESSE_MARCHE_PAYSAN;    
    
    if(tab_perso[i].z != tab_perso[i].nz)
      tab_perso[i].z += tab_perso[i].z >tab_perso[i].nz? -VITESSE_MARCHE_PAYSAN : VITESSE_MARCHE_PAYSAN;
    

      /* ________________ Colision seullement entre personnage__________
	 Si colisiont activer je ne peut plus entre dans le if de ma fct farme
	 fonction qui a chaque seconde regarde qui est en train de ce batre ou couper du bois 
	 et applique les modification nessesaire.
	 A regler 

    */
    /*  
       lateral = (tab_perso[i].x - tab_perso[i].nx ) != 0  ? 1 : 2 ;

   for(i2 = i+1 ; i2 < nb_perso ; i2++ ) {
     
  	x = 	tab_perso[i].x - tab_perso[i2].x ;
        y = 	tab_perso[i].y- tab_perso[i2].y  ;
        z = 	tab_perso[i].z- tab_perso[i2].z ;
       	ecart = sqrt(  (x*x) + (y*y) + (z*z) );

	if ( ecart < TAILLE_CARRE){
	  i2 = i;
	  if(lateral == 2)
	  tab_perso[i].x -= TAILLE_CARRE;
	  else
	     tab_perso[i].z -= TAILLE_CARRE;
	
	  }
    
    }
    */


    if(tab[ (int)( tab_perso[id_roi].x /TAILLE_CARRE)][(int) (tab_perso[id_roi].z /TAILLE_CARRE )].type == 5){
      printf("Vous avez gagnez\n");
      exit(0);
    }
    if (tab_perso[i].type == 1 ){ // Pour les paysans

      if(tab_perso[i].z == tab_perso[i].nz &&   tab_perso[i].x == tab_perso[i].nx &&   tab_perso[i].denre_type < 0) {
	// Si je ne bouge pas et que je suis en mode "defarme" depose mes denree selon leur type
     
	switch(  tab_perso[i].denre_type ){
	case -2 :
	  denre_food +=	 tab_perso[i].denre ;  break;
	case -3:
	  denre_bois += tab_perso[i].denre ;  break ;
     
	}

	tab_perso[i].denre = 0;
	tab_perso[i].denre_type = 0;
	continue ;
      }
      // Si je vais sur de l'eau ou dans la foret je m'arrete et passe en mode farm

      switch( tab[ (int)( tab_perso[i].x /TAILLE_CARRE)][(int) (tab_perso[i].z /TAILLE_CARRE )].type){

      case 2 :
	tab_perso[i].nx = tab_perso[i].x;
	tab_perso[i].nz = tab_perso[i].z;
	tab_perso[i].denre_type  = 2;
	tab_perso[i].farm = 1;
	break;
   
      case 3 :
	tab_perso[i].nx = tab_perso[i].x;
	tab_perso[i].nz = tab_perso[i].z;
	tab_perso[i].denre_type  = 3;
	tab_perso[i].farm = 1;
	break;



      default :
	tab_perso[i].farm = 0;
	break;
      }
    }

    if (tab_perso[i].type == 2 ){ // Pour les soldats
      if(tab_perso[i].z  == tab_monstre[tab_perso[i].cible].z  &&    tab_perso[i].x  == tab_monstre[tab_perso[i].cible].x &&   tab_perso[i].farm == 1) {
	// Si je ne bouge pas et que je suis en mode "attaque" == 1  passe en mode combat == 2
	tab_perso[i].farm = 2 ;

	continue ;
      }
    }

 }
 
}


void deplaceMonstre (){

  int i;
  //  int i2 ,x , y , z , ecart;

  for( i = 0; i< nb_monstre ; i++ ) {
    
    // Si possiton actuelle != de la possition voulue je deplace mon monstre
    if(tab_monstre[i].x != tab_monstre[i].nx)
      tab_monstre[i].x += tab_monstre[i].x > tab_monstre[i].nx? -VITESSE_MARCHE_PAYSAN : VITESSE_MARCHE_PAYSAN;    
    
    if(tab_monstre[i].z != tab_monstre[i].nz)
      tab_monstre[i].z += tab_monstre[i].z >tab_monstre[i].nz? -VITESSE_MARCHE_PAYSAN : VITESSE_MARCHE_PAYSAN;

    /*
 //Pour deplace mes monstre  mais sa fait trop laguer || a tester sur un ordi plus puissant
  if(tab_monstre[ i ].farm == 0){
    
	switch( rand() % 10) {

	case 0 :
	  tab_monstre[i].nx -= TAILLE_CARRE;
	  tab_monstre[i].nz -=  TAILLE_CARRE *2;

	  break;
	case 1 :
	  tab_monstre[i].nx += TAILLE_CARRE;
	  tab_monstre[i].nz +=  TAILLE_CARRE *2;
	

	  break;
	case 2 :
	  tab_monstre[i].nx += TAILLE_CARRE *3;
	  tab_monstre[i].nz +=  TAILLE_CARRE ;

	  break;

	case 4 :
	  tab_monstre[i].nx += TAILLE_CARRE *3;
	  tab_monstre[i].nz +=  TAILLE_CARRE ;

	  break;
		 
	}
   
	}*/
  }  

}

/* _________ Fonction de controle des activites Farm | combats etc _______ */
int compteur = 0;
void farme(void) {


  clock_t cp;
  int tps_init, tps_crt, dtps = 0;
  int x,y,z,ecart ;
  // Je lance le chrono
 
  if(chrono == 0)  {
    cp = clock () ;
    tps_init =(int)cp;
    chrono =1;
  }

  tps_crt = (int) clock();
  dtps = tps_crt - tps_init;
  // si dtps depasse une sec, check tous les perso farm combat | monstre combat agression

  if(dtps >1000000){

    chrono =0;
    int i ,i2;
    for( i = 0; i< nb_perso ; i++ ) {
      if(  tab_perso[i].vie <= 0) continue;

      if( tab_perso[i].denre >= MAX_DENRE &&  tab_perso[i].type == 1 ) continue ;
      // plus 20 de farm toute les sec
    
      if(  tab_perso[i].farm > 0 )// Si en mode farm
	tab_perso[i].denre += 20 + bonus_denre; 
     
      if( tab_perso[i].type == 2 && tab_perso[i].farm == 2){ // Pour les soldat en mode combat
	if(	tab_monstre[  tab_perso[i].cible ].cible == -1) {// Si le monstre que je suis en train de cibler ne cible perssone
	  tab_monstre[  tab_perso[i].cible ].cible = i; //  Il me cible
	  tab_monstre[  tab_perso[i].cible ].farm =2;
	}
	if( 	tab_monstre[  tab_perso[i].cible ].vie > 0) // Si il n'est pas deja mort
	  tab_monstre[  tab_perso[i].cible ].vie -= (20+ bonus_degat ); // Je lui enleve 20 pv
	else {
	  tab_perso[i].cible = -1; // Sinon je ne cible plus personne
	  tab_perso[i].farm = 0; //  Et passe en mode inactif
	  tab_monstre[ tab_perso[i].cible ].cible = -1 ;
	}
	  
      }


    }
   
  

    for( i = 0; i< nb_monstre ; i++ ) {
      if(  tab_monstre[i].vie <= 0) continue;

      if(  tab_monstre[i].farm == 2 &&	tab_perso[  tab_monstre[i].cible ].vie > 0) // Si je cible qqun et qu'il n'est pas mort
	tab_perso[  tab_monstre[i].cible ].vie -= 20; // je lui enleve 5 pv
      else {
	tab_monstre[i].cible = -1;
	tab_monstre[i].farm = 0;
      }	  
      // Agression
      for( i2 = 0; i2< nb_perso ; i2++ ) {
	if(  tab_perso[i2].vie <= 0 ) continue;
	// check si proche d'un personage
	x = 	tab_monstre[i].x - tab_perso[i2].x ;
        y = 	tab_monstre[i].y- tab_perso[i2].y  ;
        z = 	tab_monstre[i].z- tab_perso[i2].z ;
	ecart = sqrt(  (x*x) + (y*y) + (z*z) );
	// si ecart < 50 je combat
	if ( ecart < 50 && tab_monstre[ i ].cible == -1){

	  if(	tab_perso[  i2 ].farm != 2){ // Si le monstre que je suis en train de cibler ne cible perssone
	    tab_perso[  i2 ].cible = i; //  Il me cible
	    tab_perso[  i2 ].farm = 2;
	  }
	  tab_monstre[ i ].farm = 2 ;
	  tab_monstre[ i ].cible = i2 ;
	  break;
	}
	// si ecart <200 j'attaque | me raproche de la cible
	else if ( ecart < 200 && tab_monstre[ i ].cible == -1 ){
	  tab_monstre[i].nx =tab_perso[i2].x ;
	  tab_monstre[i].nz =tab_perso[i2].z ;
	  tab_monstre[ i ].cible = i2 ;
	  tab_monstre[ i ].farm = 1 ;
	  break ;
	}
	// si personne autour je fait rien
	else {
	 
	   tab_monstre[ i ].cible = -1 ;
	}

      }

 
    
      compteur ++;

      if(compteur > 2000){
	// Fair un random pour pop les monstre sur la map aleatoirement
      
	cree_monstre ((rand() %TAILLE_MAP_X) * TAILLE_CARRE , (rand() %TAILLE_MAP_Y)  * TAILLE_CARRE  ,4 ,200);

	compteur =0;

      }

    }
    




  }
}


void 
idle (void){

 
  rotate = (rotate +20) % 360 ;
  deplaceMonstre ();
  deplacePerso();
  farme();

  if(tab_perso[id_roi].vie <= 0) {   
    printf("Vous avez perdu\n");
    exit(0);
  }
  glutPostRedisplay();

}

//inutile
void 
DessineRepere(void) {

 glBegin(GL_LINES);
  glColor3f (1.0, 0.0, 0.0); //Rouge
  glVertex3f(0,  0,  0);
  glVertex3f(5,  0,  0);// Ligne X
  glColor3f (0.0, 1.0, 0.0); // Vert
  glVertex3f(0,  0,  0);
  glVertex3f(0,  5,  0);// LIGNE Y
  glColor3f (0.0, 0.0, 1.0); // Bleu
  glVertex3f(0,  0,  0);
  glVertex3f(0,  0,  5); //Ligne Z
  glEnd();

 }



void
processPick (){
	GLint viewport[4];
	GLubyte pixel[3];

	glGetIntegerv(GL_VIEWPORT,viewport);

	glReadPixels(cursorX,viewport[3]-cursorY,1,1,GL_RGB,GL_UNSIGNED_BYTE,(void *)pixel);

	// Je selectione un monstre

	if (pixel[1] == 90 && pixel[0] ==90){



	paysan.nx = tab_monstre[ pixel[2]  ].x  ;
	paysan.nz = tab_monstre[ pixel[2]  ].z  ;
	cible_monstre =  pixel[2] ;

	if(tab_perso[cible_perso].type == 2 ) tab_perso[cible_perso].farm = 1;
	tab_perso[cible_perso].nx = paysan.nx;
	tab_perso[cible_perso].nz = paysan.nz;
	tab_perso[cible_perso].cible = cible_monstre;
	}
	// Je selectione un batiment 
	else if (pixel[1] == 60 && pixel[0] ==60){

	paysan.nx = tab_bati[ pixel[2]  ].x ;
	paysan.nz = tab_bati[ pixel[2]  ].z  -TAILLE_CARRE;


	tab_perso[cible_perso].nx = paysan.nx;
	tab_perso[cible_perso].nz = paysan.nz;
	// Si garnison passe en mode defarme
	if(	 tab_bati[ pixel[2]  ].type == 1)
	  tab_perso[cible_perso].denre_type *= -1  ;

	}
		// Je selectione un personage
	else if (pixel[1] == 30 && pixel[0] ==30)
	   cible_perso = pixel[2];
	  
	// Je clique sur la map
	else if ( pixel[2] == 0){
	paysan.nx =  pixel[0] *  TAILLE_CARRE;
	paysan.nz =  pixel[1] *  TAILLE_CARRE;
	
	tab_perso[cible_perso].nx = paysan.nx;
	tab_perso[cible_perso].nz = paysan.nz;
       	tab_perso[cible_perso].farm = 0;
       	tab_monstre[tab_perso[cible_perso].cible ].farm = -1;
	

	}

	
	
   
}


void
display(void ){
  glLoadIdentity (); 

  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  gluLookAt(camX, camY + ZOOM,  camZ, 
	    camX , camY - 50 , camZ + 100,  
  	    0.0 , 1.0 , 0.0 ); 

  glPushMatrix();
 
  glTranslatef ( 0  ,0, 130 ); // Centre la map a lecrant ( plus joli)

  if(r == -1)
    DessineRepere();

  if (mode == 1){
    glDisable(GL_LIGHTING);
    dessinePaysan2();
  }
  else{
    glEnable(GL_LIGHTING);
	  
    dessineMonstre();
    dessinePerso();
    dessineBati();
    afficheMap();
	  
  }

  if (mode == 1) {
    processPick();
    mode = 0;
  }
  else   
    glutSwapBuffers();

  glPopMatrix(); 


}


int 
main(int argc, char** argv) { 
  Map =  fopen ( argv[1] , "r");
  glutInit(&argc, argv); 
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 
  glutInitWindowSize (1000, 1000); 
  glutInitWindowPosition (100, 100); 
  glutCreateWindow ("Warcraft | lundi 24 mars| version 'final'"); 
  srand(time(NULL));
 
  init(); 

  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutIdleFunc(idle);
  glutKeyboardFunc(keyboard); 
  	glutMouseFunc(mouseStuff);

  glutSpecialFunc(specialkeyboard);
   glutPassiveMotionFunc(mouse);
 
  
  glutMainLoop(); 


  return 0; 
}


/*

 Pour cree un paysan - Apuyer sur la touche p | Il faut une unite de nouriture
pour cree un batiment - Apuyer sur la touche g | Il faut deux unite de bois





*/
