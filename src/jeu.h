#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED

void affOptions(SDL_Renderer *pRenderer,SDL_Texture *Fond,SDL_Texture *nbdisc, SDL_Texture *Sleep, SDL_Rect *positionsnbdisc, SDL_Rect *positionssleep,SDL_Texture *droite,SDL_Texture *gauche, SDL_Rect *posdroite1,SDL_Rect *posdroite2, SDL_Rect *posgauche1, SDL_Rect *posgauche2,TTF_Font *police, int slee,int dis, int h,int w,SDL_Texture *rain,int ran,SDL_Rect *posrain,SDL_Texture *casepas,SDL_Texture *casec,SDL_Rect *poscase,SDL_Rect *poscroix,SDL_Texture *fle);


void Init(int **pilier1, int **pilier2, int **pilier3, int N, int h, int w, int *decalage, int *hauteur,SDL_Rect *pilier1a,SDL_Rect *pilier1b,SDL_Rect *pilier2a,SDL_Rect *pilier2b,SDL_Rect *pilier3a,SDL_Rect *pilier3b,long *nbmax,long *tour);
void afficherDisque(SDL_Renderer *renderer,int pilier, int index, int couleur, int h, int w,int hauteur, int decalage,int rainbow, int N);
void tableauToDisque(int *pilier1, int *pilier2,int  *pilier3,SDL_Renderer *renderer, int N, SDL_Window *window, int h, int w, SDL_Texture  *fond,int decalage,int hauteur,int rainbow,SDL_Rect pilier1a,SDL_Rect pilier1b,SDL_Rect pilier2a,SDL_Rect pilier2b,SDL_Rect pilier3a,SDL_Rect pilier3b,long nbmax,TTF_Font *policecompt,long tour,SDL_Texture *croix,SDL_Rect *poscroix);
void Menu(SDL_Renderer *pRenderer,SDL_Texture *Fond,SDL_Texture *Jouer, SDL_Texture *Options, SDL_Rect *posJouer, SDL_Rect *posOptions,SDL_Texture *titre1,SDL_Texture *titre2, SDL_Rect *postitre1,SDL_Rect *postitre2,SDL_Texture *nom, SDL_Rect *posnom,int h, int w,SDL_Texture *tuto,SDL_Rect *postuto);
int MaxTableau(int NB, int *tableau);
void afficherDisqueCurseur(SDL_Renderer *renderer,int couleur,int rainbow,int N,int x, int y, int hauteur, int decalage,int w);


#endif
