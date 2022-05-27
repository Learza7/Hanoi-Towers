#include "headers.h"
#include "jeu.h"

/** ---------- LES TOURS DE HANOÏ version 2.0 ---------- **/



void jeu()
{
    SDL_DisplayMode mode;
    /**SDL_GetDesktopDisplayMode(0,&mode);   **/
    mode.h=1050;
    mode.w=1680;          /** récupère la résolution de l'écran **/
    int FenH=mode.h*0.8, FenW=mode.w*0.8;           /** ma fenêtre occupera 80% de l'écran **/

    SDL_Window* pWindow = NULL;
    SDL_Renderer* pRenderer = NULL;
    pWindow = SDL_CreateWindow("Les Tours de Hanoï",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,FenW,FenH,NULL);      /** création de la Fenêtre **/
    pRenderer = SDL_CreateRenderer(pWindow,-1,NULL);


    SDL_Color Noir={0,0,0};                 /** couleur noire **/
    SDL_Color Blanc={255,255,255};          /** couleur blanche **/

    TTF_Font *police = NULL;                /** initialisation de la police **/

    /** initialisation des surfaces **/
    SDL_Surface *surftitre1 = 0, *surftitre2 = 0, *surfJouer = 0, *surfJouerS = 0, *surfOptions = 0, *surfOptionsS = 0, *surfnom=0, *surfnbdisc = 0, *surfSleep=0,*surfrain = 0,*surfcasepas = 0,*surfdroite = 0, *surfcase = 0,*surffle = 0,*surfgauche = 0,*surffond = 0, *surftuto, *surftutoS;

    /** initialisation des textures **/
    SDL_Texture *titre1 = 0,*titre2 = 0,*Jouer = 0,*JouerS = 0, *Options = 0,*OptionsS = 0,*nom=0,*nbdisc = 0,*Sleep = 0,*Rain = 0,*casepas=0,*fle=0,*casec=0,*droite = 0,*gauche = 0,*fond = 0,*tuto,*tutoS;

    /** initialisation des positions **/
    SDL_Rect postitre1,postitre2,positionJouer,positionOptions,posnom,positionnbdisc,positionsleep,positionrain,poscase,positiondroite1,positiondroite2,poscroix,positiongauche1,positiongauche2,pilier1a,pilier1b,pilier2a,pilier2b,pilier3a,pilier3b,positiontuto;

            /************/
            /****MENU****/
            /************/

    /** ---------- TITRE DU MENU ---------- **/
    police = TTF_OpenFont("resources/Rubik.ttf", 95);           /** ouverture de la police en taille 95 **/

    /** 1ere partie du titre **/
    surftitre1 = TTF_RenderText_Blended(police ,"LES TOURS DE", Blanc);     /** création de la surface **/
    titre1= SDL_CreateTextureFromSurface(pRenderer,surftitre1);             /** surface -> texture **/
    SDL_FreeSurface(surftitre1);                                            /** libération de la surface (+ de RAM) **/
    SDL_QueryTexture(titre1,NULL,NULL,&postitre1.w,&postitre1.h);           /** récupération de la taille de la texture **/

    /** 2nde partie du titre **/
    surftitre2 = TTF_RenderUTF8_Blended(police ,"HANOÏ", Blanc);
    titre2= SDL_CreateTextureFromSurface(pRenderer,surftitre2);
    SDL_FreeSurface(surftitre2);
    SDL_QueryTexture(titre2,NULL,NULL,&postitre2.w,&postitre2.h);

    /** définition des positions du titre **/
    postitre1.x=FenW*0.5-postitre1.w/2;                                     /** abcisse **/
    postitre1.y=FenH*0.05;                                                  /** ordonnée **/
    postitre2.x=((postitre1.x+postitre1.x+postitre1.w)/2)-postitre2.w/2;
    postitre2.y=postitre1.y+postitre1.h+15;


    /** ---------- BOUTON JOUER ---------- **/
    police = TTF_OpenFont("resources/Rubik33.ttf", 85);                       /** taille 75 **/

    surfJouer = TTF_RenderText_Blended(police, "JOUER", Noir);              /** texte noir **/
    surfJouerS = TTF_RenderText_Blended(police, "JOUER", Blanc);            /** texte blanc pour quand le curseur passe dessus **/

    Jouer = SDL_CreateTextureFromSurface(pRenderer,surfJouer);              /** surface -> texture **/
    JouerS = SDL_CreateTextureFromSurface(pRenderer,surfJouerS);
    SDL_FreeSurface(surfJouer);                                             /** libération **/
    SDL_FreeSurface(surfJouerS);

    SDL_QueryTexture(Jouer,NULL,NULL,&positionJouer.w,&positionJouer.h);

    /** ---------- BOUTON TUTORIEL ---------- **/
    police = TTF_OpenFont("resources/Rubik33.ttf", 45);                       /** taille 65 **/

    surftuto = TTF_RenderText_Blended(police, "Solution", Noir);
    surftutoS = TTF_RenderText_Blended(police, "Solution", Blanc);

    tuto = SDL_CreateTextureFromSurface(pRenderer,surftuto);
    tutoS = SDL_CreateTextureFromSurface(pRenderer,surftutoS);
    SDL_FreeSurface(surftuto);
    SDL_FreeSurface(surftutoS);

    SDL_QueryTexture(tuto,NULL,NULL,&positiontuto.w,&positiontuto.h);

    /** ---------- BOUTON OPTIONS ---------- **/
    police = TTF_OpenFont("resources/Rubik33.ttf", 45);                       /** taille 55 **/

    surfOptions = TTF_RenderText_Blended(police, "options", Noir);
    surfOptionsS = TTF_RenderText_Blended(police, "options", Blanc);

    Options = SDL_CreateTextureFromSurface(pRenderer,surfOptions);
    OptionsS = SDL_CreateTextureFromSurface(pRenderer,surfOptionsS);
    SDL_FreeSurface(surfOptions);
    SDL_FreeSurface(surfOptionsS);

    SDL_QueryTexture(Options,NULL,NULL,&positionOptions.w,&positionOptions.h);

    /** ---------- AUTEUR ---------- **/
    police = TTF_OpenFont("resources/Roboto.ttf", 20);                      /** taille 20 **/

    surfnom = TTF_RenderUTF8_Blended(police, "©auteur",Blanc);

    nom = SDL_CreateTextureFromSurface(pRenderer,surfnom);
    SDL_FreeSurface(surfnom);

    SDL_QueryTexture(nom,NULL,NULL,&posnom.w,&posnom.h);
    posnom.y=FenH-posnom.h;
    posnom.x=0;


            /***************/
            /****OPTIONS****/
            /***************/

    police = TTF_OpenFont("resources/Rubik22.ttf", 35);                     /** taille 35 **/

    /** ---------- NOMBRE DE DISQUES ---------- **/

    surfnbdisc = TTF_RenderText_Blended(police, "Nombre de disques : ", Blanc);

    nbdisc = SDL_CreateTextureFromSurface(pRenderer,surfnbdisc);
    SDL_FreeSurface(surfnbdisc);

    SDL_QueryTexture(nbdisc,NULL,NULL,&positionnbdisc.w,&positionnbdisc.h);

    /** ---------- DÉLAI ---------- **/

    surfSleep = TTF_RenderUTF8_Blended(police, "Délai (en ms) : ", Blanc);

    Sleep = SDL_CreateTextureFromSurface(pRenderer,surfSleep);
    SDL_FreeSurface(surfSleep);

    SDL_QueryTexture(Sleep,NULL,NULL,&positionsleep.w,&positionsleep.h);

    /** ---------- RAINBOW ---------- **/

    surfrain = TTF_RenderText_Blended(police, "Rainbow : ", Blanc);

    Rain = SDL_CreateTextureFromSurface(pRenderer,surfrain);
    SDL_FreeSurface(surfrain);

    SDL_QueryTexture(Rain,NULL,NULL,&positionrain.w,&positionrain.h);

    /** ---------- CASE À COCHER ---------- **/

    /** case non cochée **/
    surfcasepas = IMG_Load("resources/pascoche.png");                   /** chargement de l'image de la case non cohée **/

    casepas = SDL_CreateTextureFromSurface(pRenderer,surfcasepas);
    SDL_FreeSurface(surfcasepas);

    /** case cochée **/
    surfcase = IMG_Load("resources/coche.png");                         /** chargement de l'image de la case cochée **/

    casec = SDL_CreateTextureFromSurface(pRenderer,surfcase);
    SDL_FreeSurface(surfcase);

    /** ---------- FLÈCHE RETOUR ---------- **/

    surffle = IMG_Load("resources/fleche.png");

    fle = SDL_CreateTextureFromSurface(pRenderer,surffle);
    SDL_FreeSurface(surffle);

    poscroix.x=5;                   /** position de la flèche retour **/
    poscroix.y=5;
    poscroix.h=FenH/15;             /** taille de la flèche (de l'image) **/
    poscroix.w=poscroix.h;

    /** ---------- FLÈCHES ---------- **/

    /** flèche vers la gauche **/
    surfdroite = TTF_RenderText_Blended(police, "<-", Blanc);

    droite = SDL_CreateTextureFromSurface(pRenderer,surfdroite);
    SDL_FreeSurface(surfdroite);

    SDL_QueryTexture(droite,NULL,NULL,&positiondroite1.w,&positiondroite1.h);
    SDL_QueryTexture(droite,NULL,NULL,&positiondroite2.w,&positiondroite2.h);

    /** flèche vers la droite **/
    surfgauche = TTF_RenderText_Blended(police, "->", Blanc);

    gauche = SDL_CreateTextureFromSurface(pRenderer,surfgauche);
    SDL_FreeSurface(surfgauche);

    SDL_QueryTexture(gauche,NULL,NULL,&positiongauche1.w,&positiongauche1.h);
    SDL_QueryTexture(gauche,NULL,NULL,&positiongauche2.w,&positiongauche2.h);

            /***************/
            /****GLOBAL*****/
            /***************/

    /** ---------- IMAGE DE FOND ---------- **/
    surffond = IMG_Load("resources/fond.png");

    fond = SDL_CreateTextureFromSurface(pRenderer,surffond);
    SDL_FreeSurface(surffond);

    /** ---------- COMPTEUR ---------- **/
    TTF_Font *policecompt=0;                                    /** initialisation de la police **/
    policecompt=TTF_OpenFont("resources/Roboto.ttf", 45);       /** ouverture de la police en 45 **/

    /** ---------- INITIALISATION DES VARIABLES ---------- **/
    int Parite=1,A=8, B=0, C=0, quit=0, FS=0, clic=0, passage=0, ecran=1,ran=1,pause=0,forw=0,decalage = 0,hauteur = 0,lache=0,sauvegarde=0,base=0;
    /** ---------- INTIALISATION DES TABLEAUX (UN PAR PILIER) ---------- **/
    int *pilier1=NULL, *pilier2=NULL, *pilier3=NULL;


    /** tableaux des valeurs possibles pour le nb de disques (dis) et du délai (sle) **/
    int dis[22]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,32,64}, sle[13]={0,10,20,30,50,100,200,500,1000,2000,3000,5000,10000};
    /** indice des valeurs possibles par défaut (8 disques, 50ms) **/
    int indis=7,indsle=4;
    /** init des  variables nb total d'étapes et nb d'étapes **/
    long nbmax,tour=0;

    /** Affichage du Menu (déclaration plus bas) **/
    Menu(pRenderer,fond,Jouer,Options,&positionJouer,&positionOptions,titre1,titre2,&postitre1,&postitre2,nom,&posnom,FenH,FenW,tuto,&positiontuto);
    /** Initialisation Jouer (voir plus bas) **/
    Init(&pilier1,&pilier2,&pilier3,dis[indis],FenH,FenW,&decalage,&hauteur,&pilier1a,&pilier1b,&pilier2a,&pilier2b,&pilier3a,&pilier3b,&nbmax,&tour);

    /** variable évènement **/
    SDL_Event event;

    while (quit==0)         /** boucle principale (rupture = fin du programme) **/
    {
        while (SDL_PollEvent(&event))   /** Gestions des évènement **/
        {
            switch(event.type)
            {
                case SDL_QUIT:      /** clic sur la croix = quitter **/
                        quit=1;
                        break;
                case SDL_KEYDOWN:     /** touche du clavier enfoncée **/
                        switch(event.key.keysym.sym)
                        {
                        case  SDLK_ESCAPE:      /** ECHAP = quitter **/
                            quit=1;
                            break;


                        case SDLK_RIGHT:        /** flèche droite = avancer d'une étape **/
                            forw=1;
                            break;

                        case SDLK_RETURN:       /** Entrée = retour au menu **/
                            if (ecran==2 || ecran==3 || ecran==4)   /** uniquement si écran actuel est jeu, options ou solution **/
                            {
                                ecran=1;
                                if (FS==0)
                                {Menu(pRenderer,fond,Jouer,Options,&positionJouer,&positionOptions,titre1,titre2,&postitre1,&postitre2,nom,&posnom,FenH,FenW,tuto,&positiontuto);}
                                else {Menu(pRenderer,fond,Jouer,Options,&positionJouer,&positionOptions,titre1,titre2,&postitre1,&postitre2,nom,&posnom,mode.h,mode.w,tuto,&positiontuto);}
                            }
                            break;

                        case SDLK_SPACE:        /** ESPACE = pause **/
                            if (pause==0)       /** si pas pause, alors pause **/
                            {
                                pause++;
                            }
                            else{pause--;}      /** si pause, alors pas pause **/
                            break;

                        case SDLK_F11:          /** F11 = fenètre -> plein écran ou plein écran -> fenètre **/
                            if (FS==1 && ecran==1)  /** si dans menu **/
                            {
                                FS=0;
                                SDL_SetWindowFullscreen(pWindow,0);

                                Menu(pRenderer,fond,Jouer,Options,&positionJouer,&positionOptions,titre1,titre2,&postitre1,&postitre2,nom,&posnom,FenH,FenW,tuto,&positiontuto);
                            }
                            else if (FS==0 && ecran==1)
                                {
                                FS=1;
                                SDL_SetWindowFullscreen(pWindow,SDL_WINDOW_FULLSCREEN_DESKTOP);
                                Menu(pRenderer,fond,Jouer,Options,&positionJouer,&positionOptions,titre1,titre2,&postitre1,&postitre2,nom,&posnom,mode.h,mode.w,tuto,&positiontuto);
                            }

                            if (ecran==2)           /** si dans options **/
                            {
                                if (FS==0)
                                {
                                    FS=1;
                                    SDL_SetWindowFullscreen(pWindow,SDL_WINDOW_FULLSCREEN_DESKTOP);
                                    affOptions(pRenderer,fond,nbdisc,Sleep,&positionnbdisc,&positionsleep,droite,gauche,&positiondroite1,&positiondroite2,&positiongauche1,&positiongauche2,police,sle[indsle],dis[indis],mode.h,mode.w,Rain,ran,&positionrain,casepas,casec,&poscase,&poscroix,fle);
                                }
                            else {  FS=0;
                                    SDL_SetWindowFullscreen(pWindow,0);
                                    affOptions(pRenderer,fond,nbdisc,Sleep,&positionnbdisc,&positionsleep,droite,gauche,&positiondroite1,&positiondroite2,&positiongauche1,&positiongauche2,police,sle[indsle],dis[indis],FenH,FenW,Rain,ran,&positionrain,casepas,casec,&poscase,&poscroix,fle);
                                }
                            }
                            break;

                        default:
                            break;
                        }
                case SDL_MOUSEBUTTONDOWN:   /** si clic **/
                    clic=1;
                    break;
                case SDL_MOUSEBUTTONUP:
                    lache=1;
                    break;

                case SDL_MOUSEMOTION:       /** si mouvement de souris **/
                                            /** si souris passe sur un des boutons du menu alors afficher le texte
                                                en blanc et si elle quitte un bouton alors afficher texte en noir**/
                    if (event.motion.x>positionJouer.x && event.motion.x<(positionJouer.x+positionJouer.w) && event.motion.y>positionJouer.y && event.motion.y<(positionJouer.y + positionJouer.h -15) && ecran==1)
                    {
                        if (passage==0)
                        {
                            passage=1;
                            if (FS==0)
                                {Menu(pRenderer,fond,JouerS,Options,&positionJouer,&positionOptions,titre1,titre2,&postitre1,&postitre2,nom,&posnom,FenH,FenW,tuto,&positiontuto);}
                                else {Menu(pRenderer,fond,JouerS,Options,&positionJouer,&positionOptions,titre1,titre2,&postitre1,&postitre2,nom,&posnom,mode.h,mode.w,tuto,&positiontuto);}

                        }

                    }
                    else if (event.motion.x>positionOptions.x && event.motion.x<(positionOptions.x+positionOptions.w) && event.motion.y>(positionOptions.y)&& event.motion.y<(positionOptions.y + positionOptions.h) && ecran==1)
                    {
                        if (passage==0)
                        {
                            passage=1;
                            if (FS==0)
                                {Menu(pRenderer,fond,Jouer,OptionsS,&positionJouer,&positionOptions,titre1,titre2,&postitre1,&postitre2,nom,&posnom,FenH,FenW,tuto,&positiontuto);}
                                else {Menu(pRenderer,fond,Jouer,OptionsS,&positionJouer,&positionOptions,titre1,titre2,&postitre1,&postitre2,nom,&posnom,mode.h,mode.w,tuto,&positiontuto);}   }
                    }
                    else if (event.motion.x>positiontuto.x && event.motion.x<(positiontuto.x+positiontuto.w) && event.motion.y>(positiontuto.y)&& event.motion.y<(positiontuto.y + positiontuto.h) && ecran==1)
                    {
                        if (passage==0)
                        {
                            passage=1;
                            if (FS==0)
                                {Menu(pRenderer,fond,Jouer,Options,&positionJouer,&positionOptions,titre1,titre2,&postitre1,&postitre2,nom,&posnom,FenH,FenW,tutoS,&positiontuto);}
                                else {Menu(pRenderer,fond,Jouer,Options,&positionJouer,&positionOptions,titre1,titre2,&postitre1,&postitre2,nom,&posnom,mode.h,mode.w,tutoS,&positiontuto);}   }
                    }
                    else if (ecran ==1){
                        if (passage==1)
                        {
                            passage=0;
                            if (FS==0)
                                {Menu(pRenderer,fond,Jouer,Options,&positionJouer,&positionOptions,titre1,titre2,&postitre1,&postitre2,nom,&posnom,FenH,FenW,tuto,&positiontuto);}
                                else {Menu(pRenderer,fond,Jouer,Options,&positionJouer,&positionOptions,titre1,titre2,&postitre1,&postitre2,nom,&posnom,mode.h,mode.w,tuto,&positiontuto);} }
                    }

                    break;

            }

        }

        if (ecran ==1 && clic ==1) /** si clic dans menu **/
        {                          /** si clic sur solution **/

            if (event.motion.x>positiontuto.x && event.motion.x<(positiontuto.x+positiontuto.w) && event.motion.y>(positiontuto.y)&& event.motion.y<(positiontuto.y + positiontuto.h) && ecran==1)
                     {
                        ecran=3;
                        clic=0;
                         if (dis[indis]%2==1)   /** si nb de disques est impair, alors variable Parite=0 sinon Parite=1 **/
                            {
                                Parite=0;
                            }
                        if (FS==0)
                        {
                            Init(&pilier1,&pilier2,&pilier3,dis[indis],FenH,FenW,&decalage,&hauteur,&pilier1a,&pilier1b,&pilier2a,&pilier2b,&pilier3a,&pilier3b,&nbmax,&tour);

                        }
                        else{Init(&pilier1,&pilier2,&pilier3,dis[indis],mode.h,mode.w,&decalage,&hauteur,&pilier1a,&pilier1b,&pilier2a,&pilier2b,&pilier3a,&pilier3b,&nbmax,&tour);}
                    }
                                /** si clic sur options **/
                    else if (event.motion.x>positionOptions.x && event.motion.x<(positionOptions.x+positionOptions.w) && event.motion.y>(positionOptions.y)&& event.motion.y<(positionOptions.y + positionOptions.h) && ecran==1)
                    {

                        ecran=2;
                        clic=0;
                        if (FS==0)
                        {
                        affOptions(pRenderer,fond,nbdisc,Sleep,&positionnbdisc,&positionsleep,droite,gauche,&positiondroite1,&positiondroite2,&positiongauche1,&positiongauche2,police,sle[indsle],dis[indis],FenH,FenW,Rain,ran,&positionrain,casepas,casec,&poscase,&poscroix,fle);
                        }
                        else{affOptions(pRenderer,fond,nbdisc,Sleep,&positionnbdisc,&positionsleep,droite,gauche,&positiondroite1,&positiondroite2,&positiongauche1,&positiongauche2,police,sle[indsle],dis[indis],mode.h,mode.w,Rain,ran,&positionrain,casepas,casec,&poscase,&poscroix,fle);}
                    }
                                /** si clic sur jouer **/
                    if (event.motion.x>positionJouer.x && event.motion.x<(positionJouer.x+positionJouer.w) && event.motion.y>positionJouer.y && event.motion.y<(positionJouer.y + positionJouer.h -15) && ecran==1)

                    {
                        ecran=4;
                        if (FS==0)
                        {Init(&pilier1,&pilier2,&pilier3,dis[indis],FenH,FenW,&decalage,&hauteur,&pilier1a,&pilier1b,&pilier2a,&pilier2b,&pilier3a,&pilier3b,&nbmax,&tour);}
                        else {Init(&pilier1,&pilier2,&pilier3,dis[indis],mode.h,mode.w,&decalage,&hauteur,&pilier1a,&pilier1b,&pilier2a,&pilier2b,&pilier3a,&pilier3b,&nbmax,&tour);
}

                        clic=0;
                    }
                            /** si clic sur rien **/
                    else {clic=0;}

        }
        if (ecran==2)       /** si dans options **/
        {
            if (clic==1)
            {               /** si clic si clic sur flèche gauche du nb de disques **/
                if(ecran==2 && event.motion.x>positiondroite1.x && event.motion.x<(positiondroite1.x+positiondroite1.w) && event.motion.y>positiondroite1.y && event.motion.y<(positiondroite1.y+positiondroite1.h))
                {
                    if(indis==0)
                    {
                        indis=21;
                    }
                    else{indis--;}
                }           /** si clic si clic sur flèche gauche du délai **/
            else if(ecran==2 && event.motion.x>positiondroite2.x && event.motion.x<(positiondroite2.x+positiondroite2.w) && event.motion.y>positiondroite2.y && event.motion.y<(positiondroite2.y+positiondroite2.h))
                {
                    if(indsle==0)
                    {
                        indsle=12;
                    }
                    else{indsle--;}

                }           /** si clic si clic sur flèche droite du nb de disques **/
            else if(ecran==2 && event.motion.x>positiongauche1.x && event.motion.x<(positiongauche1.x+positiongauche1.w) && event.motion.y>positiongauche1.y && event.motion.y<(positiongauche1.y+positiongauche1.h))
                {
                    if(indis==21)
                    {
                        indis=0;
                    }
                    else{indis++;}

                }           /** si clic si clic sur flèche droite du délai **/
            else if(ecran==2 && event.motion.x>positiongauche2.x && event.motion.x<(positiongauche2.x+positiongauche2.w) && event.motion.y>positiongauche2.y && event.motion.y<(positiongauche2.y+positiongauche2.h))
                {
                    if(indsle==12)
                    {
                        indsle=0;
                    }
                    else{indsle++;}

                }           /** si clic sur la case à cocher (rainbow) **/
            else if(ecran==2 && event.motion.x>poscase.x && event.motion.x<(poscase.x+poscase.w) && event.motion.y>poscase.y && event.motion.y<(poscase.y+poscase.h))
                {
                    if(ran==1)
                    {
                        ran=0;
                    }
                    else{ran++;}

                }           /** si clic si clic sur flèche retour **/
            else if (ecran==2 && event.motion.x>poscroix.x && event.motion.x<(poscroix.x+poscroix.w) && event.motion.y>poscroix.y && event.motion.y<(poscroix.y+poscroix.h))
                {
                    ecran=1;
                    if (FS==0)
                                {Menu(pRenderer,fond,Jouer,Options,&positionJouer,&positionOptions,titre1,titre2,&postitre1,&postitre2,nom,&posnom,FenH,FenW,tuto,&positiontuto);}
                                else {Menu(pRenderer,fond,Jouer,Options,&positionJouer,&positionOptions,titre1,titre2,&postitre1,&postitre2,nom,&posnom,mode.h,mode.w,tuto,&positiontuto);}
                    clic=0;
                    continue;
                }
                clic=0;
                if (FS==0)
                        {
                        affOptions(pRenderer,fond,nbdisc,Sleep,&positionnbdisc,&positionsleep,droite,gauche,&positiondroite1,&positiondroite2,&positiongauche1,&positiongauche2,police,sle[indsle],dis[indis],FenH,FenW,Rain,ran,&positionrain,casepas,casec,&poscase,&poscroix,fle);
                        }
                        else{affOptions(pRenderer,fond,nbdisc,Sleep,&positionnbdisc,&positionsleep,droite,gauche,&positiondroite1,&positiondroite2,&positiongauche1,&positiongauche2,police,sle[indsle],dis[indis],mode.h,mode.w,Rain,ran,&positionrain,casepas,casec,&poscase,&poscroix,fle);}

                        }

        }
        if (ecran==3)       /** si TUTORIEL **/
        {                   /** si clic sur flèche retour **/
            if(clic==1 && event.motion.x>5 && event.motion.x<(5+poscroix.w) && event.motion.y>5 && event.motion.y<(5+poscroix.h))
                    {
                        ecran=1;
                        if (FS==0)
                                {Menu(pRenderer,fond,Jouer,Options,&positionJouer,&positionOptions,titre1,titre2,&postitre1,&postitre2,nom,&posnom,FenH,FenW,tuto,&positiontuto);}
                                else {Menu(pRenderer,fond,Jouer,Options,&positionJouer,&positionOptions,titre1,titre2,&postitre1,&postitre2,nom,&posnom,mode.h,mode.w,tuto,&positiontuto);}
                                clic=0;
                                continue;
                    }
            clic=0;

            if (FS==1)
            {
                tableauToDisque(pilier1,pilier2,pilier3,pRenderer,dis[indis],pWindow,mode.h,mode.w,fond,decalage,hauteur,ran,pilier1a,pilier1b,pilier2a,pilier2b,pilier3a,pilier3b,nbmax,policecompt,tour,fle,&poscroix);
                }
           else{tableauToDisque(pilier1,pilier2,pilier3,pRenderer,dis[indis],pWindow,FenH,FenW,fond,decalage,hauteur,ran,pilier1a,pilier1b,pilier2a,pilier2b,pilier3a,pilier3b,nbmax,policecompt,tour,fle,&poscroix);}

            if (pause==0 || forw==1)    /** si pas pause ou si ordre d'avancer d'une étape (flèche droite) **/
            {
                if (sle[indsle]!=0 && pause==0)     /** application du délai si non nul **/
                    {
                        SDL_Delay(sle[indsle]);
                    }
                    if (pilier3[dis[indis]]==dis[indis]) /** si jeu fini **/
                    {
                        continue;                        /** arrêt **/
                    }

                    tour++;                              /** incrémentation du compteur de tour **/

                /** pour chaque tableau (pilier), je récupère l'indice du plus haut disque (voir déclaration) **/
                A=MaxTableau(dis[indis], pilier1);
                B=MaxTableau(dis[indis], pilier2);
                C=MaxTableau(dis[indis], pilier3);

                    if (Parite)     /** si nb disque pair **/
                    {
                        switch(tour%3)
                        {
                        case 1:             /** si numéro de l'étape modulo 3 = 1, alors échange de disque entre pilier A et pilier B **/
                            if (pilier1[A]>pilier2[B])  /** si A possède le plus petit disque **/
                            {
                                pilier2[B+1]=pilier1[A];
                                pilier1[A]=0;
                            }
                            else{                       /** si B possède le plus petit **/
                                pilier1[A+1]=pilier2[B];
                                pilier2[B]=0;
                            }
                            break;

                        case 2:             /** si num mod 3 = 2, échange entre A et C **/
                            if (pilier1[A]>pilier3[C])
                            {
                                pilier3[C+1]=pilier1[A];
                                pilier1[A]=0;
                            }
                            else{
                                pilier1[A+1]=pilier3[C];
                                pilier3[C]=0;
                            }
                            break;

                        case 0:             /** si num mod 3 = 0, échange entre B et C **/
                            if (pilier3[C]>pilier2[B])
                            {
                                pilier2[B+1]=pilier3[C];
                                pilier3[C]=0;
                            }
                            else{
                                pilier3[C+1]=pilier2[B];
                                pilier2[B]=0;
                            }
                            break;
                        }
                    }
                    else{                           /** si nb disque impair **/
                            switch(tour%3)
                            {
                                case 2:             /** si num étape mod 3 = 2, échange A et B **/
                                    if (pilier1[A]>pilier2[B])
                                    {
                                        pilier2[B+1]=pilier1[A];
                                        pilier1[A]=0;
                                    }
                                    else{
                                        pilier1[A+1]=pilier2[B];
                                        pilier2[B]=0;
                                    }
                                    break;

                                case 1:             /** si num étape mod 3 = 1, échange A et C **/
                                    if (pilier1[A]>pilier3[C])
                                    {
                                        pilier3[C+1]=pilier1[A];
                                        pilier1[A]=0;
                                    }
                                    else{
                                        pilier1[A+1]=pilier3[C];
                                        pilier3[C]=0;
                                    }
                                    break;

                                case 0:             /** si num étape mod 3 = 0, échange C et B **/
                                    if (pilier3[C]>pilier2[B])
                                    {
                                        pilier2[B+1]=pilier3[C];
                                        pilier3[C]=0;
                                    }
                                    else{
                                        pilier3[C+1]=pilier2[B];
                                        pilier2[B]=0;
                                    }
                                    break;
                                }

                            }
                if (forw==1) /** si ordre d'avancer (fleche droite), alors ordre de stopper **/
                {
                   forw=0;
                }

            }
        }
        if (ecran==4) /** jouer manuellement **/
        {
            A=MaxTableau(dis[indis], pilier1);
            B=MaxTableau(dis[indis], pilier2);
            C=MaxTableau(dis[indis], pilier3);
            if (FS==1)  /** affichage **/
            {
                tableauToDisque(pilier1,pilier2,pilier3,pRenderer,dis[indis],pWindow,mode.h,mode.w,fond,decalage,hauteur,ran,pilier1a,pilier1b,pilier2a,pilier2b,pilier3a,pilier3b,nbmax,policecompt,tour,fle,&poscroix);
                }
           else{tableauToDisque(pilier1,pilier2,pilier3,pRenderer,dis[indis],pWindow,FenH,FenW,fond,decalage,hauteur,ran,pilier1a,pilier1b,pilier2a,pilier2b,pilier3a,pilier3b,nbmax,policecompt,tour,fle,&poscroix);}
            if (clic==1) /** si clic **/
            {       /** pilier A **/
                if (event.motion.x>pilier1b.x && event.motion.x<(pilier1b.x+pilier1b.w) && event.motion.y>pilier1a.y && A!=0)
                    {
                        sauvegarde=pilier1[A];
                        pilier1[A]=0;
                        base=1;
                    }
                    /** pilier B **/
                else if (event.motion.x>pilier2b.x && event.motion.x<(pilier2b.x+pilier2b.w) && event.motion.y>pilier2a.y && B!=0)
                    {
                        sauvegarde=pilier2[B];
                        pilier2[B]=0;
                        base=2;
                    }
                    /** pilier C **/
                else if (event.motion.x>pilier3b.x && event.motion.x<(pilier3b.x+pilier3b.w) && event.motion.y>pilier3a.y && C!=0)
                    {
                        sauvegarde=pilier3[C];
                        pilier3[C]=0;
                        base=3;
                    }
                    /** si fleche retour **/
                if(event.motion.x>5 && event.motion.x<(5+poscroix.w) && event.motion.y>5 && event.motion.y<(5+poscroix.h))
                    {
                        ecran=1;
                        if (FS==0)
                                {Menu(pRenderer,fond,Jouer,Options,&positionJouer,&positionOptions,titre1,titre2,&postitre1,&postitre2,nom,&posnom,FenH,FenW,tuto,&positiontuto);}
                                else {Menu(pRenderer,fond,Jouer,Options,&positionJouer,&positionOptions,titre1,titre2,&postitre1,&postitre2,nom,&posnom,mode.h,mode.w,tuto,&positiontuto);}
                                clic=0;
                                continue;

                    }

                    clic=0;
            }
            if (sauvegarde !=0)    /** si clic sur un disque **/
            {   /** affiche disque sur le curseur **/
                if (FS==0)
                {
                afficherDisqueCurseur(pRenderer,sauvegarde,ran,dis[indis],event.motion.x,event.motion.y,hauteur,decalage,FenW);
                }
                else {afficherDisqueCurseur(pRenderer,sauvegarde,ran,dis[indis],event.motion.x,event.motion.y,hauteur,decalage,mode.w);}

                SDL_RenderPresent(pRenderer);
                SDL_Delay(20);      /** délai (pour éviter le clignotement **/
                if (lache==1)       /** si relachement du bouton **/
                {                   /** si sur pilier A **/
                    if (event.motion.x>pilier1b.x && event.motion.x<(pilier1b.x+pilier1b.w) && event.motion.y>pilier1a.y && pilier1[A]<sauvegarde && base!=1)
                    {
                        pilier1[A+1]=sauvegarde;    /** ajoute le disque au pilier **/
                        tour++;         /** incrémente le compteur d'étapes **/
                    }
                                /** de même avec le pilier B **/
                    else if (event.motion.x>pilier2b.x && event.motion.x<(pilier2b.x+pilier2b.w) && event.motion.y>pilier2a.y && pilier2[B]<sauvegarde && base!=2)
                    {
                        pilier2[B+1]=sauvegarde;
                        tour++;
                    }
                                     /** pilier C **/
                    else if (event.motion.x>pilier3b.x && event.motion.x<(pilier3b.x+pilier3b.w) && event.motion.y>pilier3a.y && pilier3[C]<sauvegarde && base!=3)
                    {
                        pilier3[C+1]=sauvegarde;
                        tour++;
                    }
                    else {  /** si sur aucun pilier, je le remets sur son pilier d'origine (base) **/
                        switch (base)
                        {
                        case 1: pilier1[A+1]=sauvegarde;
                                break;
                        case 2: pilier2[B+1]=sauvegarde;
                                break;
                        case 3: pilier3[C+1]=sauvegarde;
                                break;
                        }
                        }
                    sauvegarde=0;   /** puis je réinitialise mes variables **/
                    lache=0;
                    base=0;
                }
            }
            else {  /** si clic sur un pilier vide **/
                    lache=0;
            }
        }

   }

    /** ---------- FIN DU PROGRAMME --------- **/

    /** libération de la RAM allouée dynamiquement pour chaque tableau (pilier) **/
    free(pilier1);
    free(pilier2);
    free(pilier3);

    /** Destruction des textures, des polices et de la fenêtre **/
    SDL_DestroyTexture(titre1);
    SDL_DestroyTexture(titre2);
    SDL_DestroyTexture(Jouer);
    SDL_DestroyTexture(JouerS);
    SDL_DestroyTexture(Options);
    SDL_DestroyTexture(OptionsS);
    SDL_DestroyTexture(nbdisc);
    SDL_DestroyTexture(Sleep);
    SDL_DestroyTexture(Rain);
    SDL_DestroyTexture(casepas);
    SDL_DestroyTexture(fle);
    SDL_DestroyTexture(casec);
    SDL_DestroyTexture(droite);
    SDL_DestroyTexture(gauche);
    SDL_DestroyTexture(nom);
    SDL_DestroyTexture(fond);
    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);
    TTF_CloseFont(policecompt);
    TTF_CloseFont(police);


}


    /**  fonction pour afficher les options **/
void affOptions(SDL_Renderer *pRenderer,SDL_Texture *Fond,SDL_Texture *nbdisc, SDL_Texture *Sleep, SDL_Rect *positionsnbdisc, SDL_Rect *positionssleep,SDL_Texture *droite,SDL_Texture *gauche, SDL_Rect *posdroite1,SDL_Rect *posdroite2, SDL_Rect *posgauche1, SDL_Rect *posgauche2,TTF_Font *police, int slee,int dis, int h,int w,SDL_Texture *rain,int ran,SDL_Rect *posrain,SDL_Texture *casepas,SDL_Texture *casec,SDL_Rect *poscase,SDL_Rect *poscroix,SDL_Texture *fle)
{
    /** position des flèches droites **/
    posdroite2->x=w*0.65;
    posdroite2->y=h*0.5;
    posdroite1->x=w*0.65;
    posdroite1->y=h*0.4;
    /** positions des flèches droites **/
    posgauche1->x=w*0.80;
    posgauche1->y=h*0.4;
    posgauche2->x=w*0.80;
    posgauche2->y=h*0.5;
    /** position du nombre de disques **/
    positionsnbdisc->x=w*0.15;
    positionsnbdisc->y=h*0.4;
    /** position du délai **/
    positionssleep->x=w*0.15;
    positionssleep->y=h*0.5;
    /** position du rainbow **/
    posrain->x=w*0.15;
    posrain->y=h*0.6;
    /** position de la case **/
    poscase->w=posrain->h*1.2;
    poscase->h=poscase->w;
    poscase->x=((posdroite1->x+posgauche1->x+posdroite1->w)/2)-(poscase->w)/2;
    poscase->y=((2*posrain->y+posrain->h)/2)-poscase->h/2;

    /** collage des textures sur la fenêtre **/
    SDL_RenderCopy(pRenderer, Fond, NULL,NULL);
    SDL_RenderCopy(pRenderer, nbdisc, NULL, positionsnbdisc);
    SDL_RenderCopy(pRenderer, Sleep, NULL, positionssleep);
    SDL_RenderCopy(pRenderer,droite,NULL,posdroite1);
    SDL_RenderCopy(pRenderer,droite,NULL,posdroite2);
    SDL_RenderCopy(pRenderer,gauche,NULL,posgauche1);
    SDL_RenderCopy(pRenderer,gauche,NULL,posgauche2);
    SDL_RenderCopy(pRenderer,rain,NULL,posrain);
    SDL_RenderCopy(pRenderer,fle, NULL, poscroix);

    /** si case cochée **/
    if (ran==1)
    {
        SDL_RenderCopy(pRenderer,casec, NULL, poscase);
    }
    else{
            SDL_RenderCopy(pRenderer,casepas, NULL, poscase);
        }

    char str1[10];      /** chaîne de caractère contenant la valeur du délai **/
    sprintf(str1, "%d", slee);
    char str2[10];      /** chaîne de caractère contenant la valeur du délai **/
    sprintf(str2, "%d", dis);

    SDL_Color Noir={255,255,255};

    /** nombre de disques **/
    SDL_Surface *surfnb = 0;
    surfnb = TTF_RenderText_Blended(police,str2, Noir);

    SDL_Texture *disc = 0;
    disc = SDL_CreateTextureFromSurface(pRenderer,surfnb);
    SDL_FreeSurface(surfnb);

    SDL_Rect posdisc;
    SDL_QueryTexture(disc,NULL,NULL,&posdisc.w,&posdisc.h);
    posdisc.x=((posdroite2->x+posgauche2->x+posgauche1->w))/2-posdisc.w/2;
    posdisc.y=h*0.4;

    /** délai **/
    SDL_Surface *surfsle = 0;
    surfsle = TTF_RenderText_Blended(police,str1, Noir);

    SDL_Texture *sleee = 0;
    sleee = SDL_CreateTextureFromSurface(pRenderer,surfsle);
    SDL_FreeSurface(surfsle);

    SDL_Rect posslee;
    SDL_QueryTexture(sleee,NULL,NULL,&posslee.w,&posslee.h);
    posslee.x=((posdroite1->x+posgauche1->x+posdroite1->w)/2)-posslee.w/2;
    posslee.y=h*0.5;

    /** collage des valeurs **/
    SDL_RenderCopy(pRenderer,sleee,NULL,&posslee);
    SDL_RenderCopy(pRenderer,disc,NULL,&posdisc);

    /** actualisation de la fenêtre **/
    SDL_RenderPresent(pRenderer);

}


    /** fontion qui initialise avant le jeu (piliers, paramètres d'affichage, compteur, etc..) **/
void Init(int **pilier1, int **pilier2, int **pilier3, int N, int h, int w, int *decalage, int *hauteur,SDL_Rect *pilier1a,SDL_Rect *pilier1b,SDL_Rect *pilier2a,SDL_Rect *pilier2b,SDL_Rect *pilier3a,SDL_Rect *pilier3b,long *nbmax,long *tour)
{
    /** allocation dynamique des tableaux (piliers) **/
    *pilier1 = malloc(sizeof(int)*(N+1));
    *pilier2 = malloc(sizeof(int)*(N+1));
    *pilier3 = malloc(sizeof(int)*(N+1));
    int i=0;
    for (i=0; i<(N+1); i++)     /** boucle pour attribuer les valeurs intiales aux tableaux **/
    {
        (*pilier1)[i]=i;
        (*pilier2)[i]=0;
        (*pilier3)[i]=0;
    }

    /** paramètres d'affichages (hauteur, décalage entre chaque disque) **/
    switch(N)
{
case 1:*decalage=41*w/1120;*hauteur=51*h/630;break;
case 2:*decalage=61*w/1120;*hauteur=51*h/630;break;
case 3:*decalage=61*w/1120;*hauteur=51*h/630;break;
case 4:*decalage=41*w/1120;*hauteur=51*h/630;break;
case 5:*decalage=41*w/1120;*hauteur=51*h/630;break;
case 6:*decalage=31*w/1120;*hauteur=46*h/630;break;

case 7:*decalage=31*w/1120;*hauteur=46*h/630;break;

case 8:*decalage=25*w/1120;*hauteur=41*h/630;break;
case 9:*decalage=24*w/1120;*hauteur=41*h/630;break;
default:break;
}
if (N>=10)
{
    *decalage=((w/8)+2.4*N)/(N-1);
    *hauteur=(h-h/4)/N;
}

    /** défition de la taille et de la positions des piliers pour l'affichage **/
    pilier1a->h=h-h/20;
    pilier1a->w=h/40;
    pilier1a->y=pilier1a->w*5;
    pilier1a->x=w/6 - pilier1a->w/2;
    pilier2a->h=pilier1a->h;
    pilier2a->w=pilier1a->w;
    pilier2a->y=pilier1a->y;
    pilier2a->x=w/2 - pilier2a->w/2;
    pilier3a->h=pilier1a->h;
    pilier3a->w=pilier1a->w;
    pilier3a->y=pilier1a->y;
    pilier3a->x=(w*5)/6 - pilier3a->w/2;
    pilier1b->w=w/4;
    pilier1b->h=h/40;
    pilier1b->y=h-pilier1b->h;
    pilier1b->x=w/6 - pilier1b->w/2;
    pilier2b->w=pilier1b->w;
    pilier2b->h=pilier1b->h;
    pilier2b->y=pilier1b->y;
    pilier2b->x=w/2 - pilier2b->w/2;
    pilier3b->w=pilier1b->w;
    pilier3b->h=pilier1b->h;
    pilier3b->y=pilier1b->y;
    pilier3b->x=(w*5)/6 - pilier3b->w/2;


    *nbmax=pow(2,N)-1;  /** calcul nombre max d'étape **/
    *tour=0;            /** initialisation du compteur **/

}

    /** fonction qui affiche un disque **/
void afficherDisque(SDL_Renderer *renderer,int pilier, int index, int couleur, int h, int w,int hauteur, int decalage,int rainbow, int N)
{


    if (couleur!=0)    /** si disque à afficher **/
    {

    if (rainbow==0)         /** si couleurs classiques **/
    {
    switch (couleur%6)
    {


    case 0:
        SDL_SetRenderDrawColor(renderer,255,111,111,SDL_ALPHA_OPAQUE);
        break; // ROUGE
    case 1:
        SDL_SetRenderDrawColor(renderer,255,255,111,SDL_ALPHA_OPAQUE);
        break; // BLEU
    case 2:
        SDL_SetRenderDrawColor(renderer,111,255,111,SDL_ALPHA_OPAQUE);
        break; // VERT
    case 3:
        SDL_SetRenderDrawColor(renderer,111,255,255,SDL_ALPHA_OPAQUE);
        break; // ORANGE
    case 4:
        SDL_SetRenderDrawColor(renderer,111,111,255,SDL_ALPHA_OPAQUE);
        break;// TURQUOISE
    case 5:
        SDL_SetRenderDrawColor(renderer,255,111,255,SDL_ALPHA_OPAQUE);
        break;  // VIOLET
    }
    }
    else{           /** si RAINBOW (ﾉ>ω<)ﾉ :｡･:*:･ﾟ’★,｡･:*:･ﾟ’☆ **/
        int avance;
        avance = (255*5)/N;    /** attribution de la couleur en fonction de la valeur du disque **/
        if (avance*(N-couleur)<255)
        {
            SDL_SetRenderDrawColor(renderer,255,(avance*(N-couleur))%255,0,SDL_ALPHA_OPAQUE);
        }
        else if (avance*(N-couleur)<510)
        {
            SDL_SetRenderDrawColor(renderer,255-(avance*(N-couleur))%255,255,0,SDL_ALPHA_OPAQUE);
        }
        else if (avance*(N-couleur)<765)
        {
            SDL_SetRenderDrawColor(renderer,0,255,(avance*(N-couleur))%255,SDL_ALPHA_OPAQUE);
        }
        else if (avance*(N-couleur)<1020)
        {
            SDL_SetRenderDrawColor(renderer,0,255-(avance*(N-couleur))%255,255,SDL_ALPHA_OPAQUE);
        }
        else if (avance*(N-couleur)<1275)
        {
             SDL_SetRenderDrawColor(renderer,(avance*(N-couleur))%255,0,255,SDL_ALPHA_OPAQUE);
        }
    }

    SDL_Rect Disque;            /** position et taille du disque **/
    Disque.h=hauteur;
    Disque.w=w/4 -((couleur)*decalage);
    Disque.x = ((2*pilier-1)*w/6) - Disque.w/2;
    Disque.y=h-(index*Disque.h)-h/40;

    SDL_RenderFillRect(renderer, &Disque);      /** colorie la surface du disque **/

    SDL_SetRenderDrawColor(renderer,0,0,0,SDL_ALPHA_OPAQUE);    /** couleur noire **/
    SDL_RenderDrawRect(renderer, &Disque);                      /** trace le rectangle du disque (contour noir) **/
    }


}

    /** fonction qui affiche l'étape en cours à partir des tableaux **/
void tableauToDisque(int *pilier1, int *pilier2,int  *pilier3,SDL_Renderer *renderer, int N, SDL_Window *window, int h, int w, SDL_Texture  *fond,int decalage,int hauteur,int rainbow,SDL_Rect pilier1a,SDL_Rect pilier1b,SDL_Rect pilier2a,SDL_Rect pilier2b,SDL_Rect pilier3a,SDL_Rect pilier3b,long nbmax,TTF_Font *policecompt,long tour,SDL_Texture *croix,SDL_Rect *poscroix)

{
    /** fond **/
    SDL_RenderCopy(renderer, fond, NULL,NULL);

    /** ---------- COLLAGE DES PILIERS ---------- **/

    SDL_SetRenderDrawColor(renderer, 230,110,50, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &pilier2a);
    SDL_RenderFillRect(renderer, &pilier1a);
    SDL_RenderFillRect(renderer, &pilier3a);

    SDL_SetRenderDrawColor(renderer,0,0,0,SDL_ALPHA_OPAQUE);
    SDL_RenderDrawRect(renderer, &pilier1a);
    SDL_RenderDrawRect(renderer, &pilier2a);
    SDL_RenderDrawRect(renderer, &pilier3a);

    SDL_SetRenderDrawColor(renderer, 230,110,50, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &pilier3b);
    SDL_RenderFillRect(renderer, &pilier1b);
    SDL_RenderFillRect(renderer, &pilier2b);

    SDL_SetRenderDrawColor(renderer,0,0,0,SDL_ALPHA_OPAQUE);
    SDL_RenderDrawRect(renderer, &pilier3b);
    SDL_RenderDrawRect(renderer, &pilier2b);
    SDL_RenderDrawRect(renderer, &pilier1b);

    int i=0;
    for (i=1; i<=N; i++)    /** pour chaque valeur des tableaux, j'affiche le disque correspondant (fonction précédente)**/
    {
        afficherDisque(renderer, 1, i, pilier1[i],h,w,hauteur,decalage,rainbow,N);
        afficherDisque(renderer, 2, i, pilier2[i],h,w,hauteur,decalage,rainbow,N);
        afficherDisque(renderer, 3, i, pilier3[i],h,w,hauteur,decalage,rainbow,N);
    }

    SDL_Color Noir={255,255,255};

    /** COMPTEUR  **/
    char compteur[100];
    sprintf(compteur, "%lu", tour);     /** conversion du numéro de l'étape en cours en une chaîne de caractère **/
    strcat(compteur, "/");              /** ajout du slash à la chaîne **/
    char maxi[50];
    if (N==64)
    {
        strcat(compteur,"18446744073709551615");
    }
    else if(N==32)
    {
        strcat(compteur,"4294967295");
    }
    else{
        sprintf(maxi,"%lu",nbmax);      /** ajout du nombre max d'étape (2^N - 1) **/
        strcat(compteur, maxi);
    }

    SDL_Surface *compt=TTF_RenderText_Blended(policecompt,compteur,Noir);   /** surface du compteur **/
    SDL_Texture *comp=SDL_CreateTextureFromSurface(renderer,compt);         /** texture du compteur **/

    SDL_Rect poscompt;                                                      /** position **/
    SDL_QueryTexture(comp,NULL,NULL,&poscompt.w,&poscompt.h);
    poscompt.y=0;
    poscompt.x=w-poscompt.w-10;

    SDL_RenderCopy(renderer,comp,NULL,&poscompt);           /** collage **/

    SDL_FreeSurface(compt);                                 /** libération de la RAM **/
    SDL_DestroyTexture(comp);

    SDL_RenderCopy(renderer,croix,NULL,poscroix);           /** collage de la flèche retour **/

    SDL_RenderPresent(renderer);                            /** actualisation de la fenêtre **/

}

    /** fonction qui affiche le menu **/
void Menu(SDL_Renderer *pRenderer,SDL_Texture *Fond,SDL_Texture *Jouer, SDL_Texture *Options, SDL_Rect *posJouer, SDL_Rect *posOptions,SDL_Texture *titre1,SDL_Texture *titre2, SDL_Rect *postitre1,SDL_Rect *postitre2,SDL_Texture *nom, SDL_Rect *posnom,int h, int w,SDL_Texture *tuto,SDL_Rect *postuto)
{

    posOptions->x=w*0.6;                     /** redéfinition des positions des éléments **/
    posOptions->y=h*0.68;
    postuto->x=w*0.6;
    postuto->y=h*0.61;
    posJouer->x=w*0.6;
    posJouer->y=h*0.5;
    postitre1->x=w*0.5-postitre1->w/2;
    postitre1->y=h*0.05;
    postitre2->y=postitre1->y+postitre1->h+15;
    postitre2->x=((postitre1->x+postitre1->x+postitre1->w)/2)-postitre2->w/2;
    posnom->y=h-posnom->h;
    SDL_RenderCopy(pRenderer, Fond, NULL,NULL);             /** fond **/
    SDL_RenderCopy(pRenderer, Jouer, NULL, posJouer);       /** bouton jouer **/
    SDL_RenderCopy(pRenderer, tuto, NULL, postuto);         /** bouton solution **/
    SDL_RenderCopy(pRenderer, Options, NULL, posOptions);   /** bouton options **/
    SDL_RenderCopy(pRenderer,titre1,NULL,postitre1);        /** 1ere partie du titre **/
    SDL_RenderCopy(pRenderer,titre2,NULL,postitre2);        /** 2nde partie du titre **/
    SDL_RenderCopy(pRenderer,nom,NULL,posnom);              /** auteur **/
    SDL_RenderPresent(pRenderer);                           /** actualisation **/
}

    /** fonction qui renvoie l'indice de la première valeur non nulle en partant de la fin (facilement compréhensible)**/
int MaxTableau(int NB, int *tableau)
{
    int i=0;
    for (i=NB; i>0; i--)
    {
        if (tableau[i]!=0)
        {
            return i;
        }
    }

    return 0;
}

void afficherDisqueCurseur(SDL_Renderer *renderer,int couleur,int rainbow,int N,int x, int y, int hauteur, int decalage,int w)
{

    if (couleur!=0)    /** si disque à afficher **/
    {

    if (rainbow==0)         /** si couleurs classiques **/
    {
    switch (couleur%6)
    {


    case 0:
        SDL_SetRenderDrawColor(renderer,255,111,111,SDL_ALPHA_OPAQUE);
        break; // ROUGE
    case 1:
        SDL_SetRenderDrawColor(renderer,255,255,111,SDL_ALPHA_OPAQUE);
        break; // BLEU
    case 2:
        SDL_SetRenderDrawColor(renderer,111,255,111,SDL_ALPHA_OPAQUE);
        break; // VERT
    case 3:
        SDL_SetRenderDrawColor(renderer,111,255,255,SDL_ALPHA_OPAQUE);
        break; // ORANGE
    case 4:
        SDL_SetRenderDrawColor(renderer,111,111,255,SDL_ALPHA_OPAQUE);
        break;// TURQUOISE
    case 5:
        SDL_SetRenderDrawColor(renderer,255,111,255,SDL_ALPHA_OPAQUE);
        break;  // VIOLET
    }
    }
    else{           /** si RAINBOW (ﾉ>ω<)ﾉ :｡･:*:･ﾟ’★,｡･:*:･ﾟ’☆ **/
        int avance;
        avance = 255*5/N;    /** attribution de la couleur en fonction de la valeur du disque **/
        if (avance*(N-couleur)<255)
        {
            SDL_SetRenderDrawColor(renderer,255,(avance*(N-couleur))%255,0,SDL_ALPHA_OPAQUE);
        }
        else if (avance*(N-couleur)<510)
        {
            SDL_SetRenderDrawColor(renderer,255-(avance*(N-couleur))%255,255,0,SDL_ALPHA_OPAQUE);
        }
        else if (avance*(N-couleur)<765)
        {
            SDL_SetRenderDrawColor(renderer,0,255,(avance*(N-couleur))%255,SDL_ALPHA_OPAQUE);
        }
        else if (avance*(N-couleur)<1020)
        {
            SDL_SetRenderDrawColor(renderer,0,255-(avance*(N-couleur))%255,255,SDL_ALPHA_OPAQUE);
        }
        else if (avance*(N-couleur)<1275)
        {
             SDL_SetRenderDrawColor(renderer,(avance*(N-couleur))%255,0,255,SDL_ALPHA_OPAQUE);
        }
    }

    SDL_Rect Disque;            /** position et taille du disque **/
    Disque.h=hauteur;
    Disque.w=w/4 -((couleur)*decalage);
    Disque.x = x - Disque.w/2;
    Disque.y=  y - Disque.h/2;

    SDL_RenderFillRect(renderer, &Disque);      /** colorie la surface du disque **/

    SDL_SetRenderDrawColor(renderer,0,0,0,SDL_ALPHA_OPAQUE);    /** couleur noire **/
    SDL_RenderDrawRect(renderer, &Disque);                      /** trace le rectangle du disque (contour noir) **/
    }
}
/* DABROWSKI Rémi*/
