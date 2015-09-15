GLUquadricObj *quadAtmosphere;

/* La structure pour stocker l'image lue */
typedef struct {
    unsigned long sizeX;
    unsigned long sizeY;
    char *data;
} Image;

#ifndef _INCL_GUARD
#define _INCL_GUARD


static int r = 1;
#define FIN 500.0
#define MAX_DENRE 500
#define TAILLE_CARRE 20.0
#define VITESSE_MARCHE_PAYSAN 20.0
#define VITESSE_CAMERA 20
#define TAILLE_MAP_X 100
#define TAILLE_MAP_Y 100
#define VISIBLE 50
#define ZOOM 1000


struct test{
  int x , y,z , type;
  int nx , nz;
  int vie;
  int denre;
  int denre_type;
  int farm ;
  int cible ;
};

struct bati{
  int x,y , z , type;

  int vie;
};

typedef struct bati bati;
typedef struct test test;
bati tab_bati[255] ;
test tab_perso[255] ;
test tab_monstre[255] ;

static GLuint id_herbe , id_rect,id_tex_herbe,id_tex_mur,id_tex_obj, id_tex_courone ,id_tex_monstre, id_tex_brique, id_perso5, id_perso6,id_perso7,  id_tex_sol,id_tex_eau;
static GLfloat camX  = ( TAILLE_MAP_X * TAILLE_CARRE) /2 , camY = 10.0, camZ =( TAILLE_MAP_Y * TAILLE_CARRE) /2   ;
static GLfloat  sourisX  ,  sourisY ;
 test tab[TAILLE_MAP_X ][TAILLE_MAP_Y] ;


#endif

void reshape (int w, int h);
void init(void);

void cree_monstre(int x , int y , int type, int vie);
void cree_perso(int x , int y , int type, int vie);
void cree_bati (int x , int z ,int type , int vie);

void DessineId ( int id , int id_tex);
void dessineBati();
void dessineMonstre();
void dessinePerso();
void afficheFarm(void);
void afficheMap(void);
void dessinePaysan2();
void mouse ( int x, int y );
void mouseStuff(int button, int state, int x, int y);
void specialkeyboard (int key, int x, int y) ;
void cree_perso (int x , int z ,int type , int vie);
void keyboard (unsigned char key, int x, int y);
void cree_monstre (int x , int z ,int type , int vie);
void cree_bati (int x , int z ,int type , int vie);
void deplacePerso(void);
void deplaceMonstre ();
void farme(void) ;
void idle (void);
void DessineRepere(void);
void processPick ();
void display(void ) ;
int main(int argc, char** argv);
