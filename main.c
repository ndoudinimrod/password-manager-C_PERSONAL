#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#define MAX 10
#include<time.h>
#include <unistd.h>
///#include <windows.h>


#if defined WIN32
#define CLEAN_SCREEN "cls"
#elif defined __linux
#define CLEAN_SCREEN "clear"
#endif

#if defined WIN32
#define directory "dir /w"
#elif defined __linux
#define directory "ls"
#endif

void cls (void)
{
   system(CLEAN_SCREEN);
}

void ls (void)
{
   system(directory);
}

 char emplacement[100];
FILE* fichier = NULL;
FILE* creation_fichier() {

	 FILE* fichier = NULL;


    fichier = fopen("mdp.txt", "r+");


    if (fichier == NULL)

    {

         fichier = fopen("mdp.txt", "w+");

        printf("Le fichier mdp a ete cree\n");

    }

    return fichier;

}

void demandeFichier(){

        int fin;
        int choix;
        //int i;
        fin=0;

while(!fin) {


        printf("QUE SOUHAITEZ VOUS REALISER ??\n\n");
        printf("\n1) OUVRIR UNE APPLICATION \n ");
        printf("\n2) RETOUR AU MENU \n\n");
        scanf("%d", &choix);
        switch(choix){
            case 1:

                  fiche();

                  break;
            case 2:
                cls();

                break;
            default:
                  printf("Choix impossible \n \n");

                  break;
    }
}

}
void fiche(){





    ls();
    printf("ECRIVEZ LE CHEMIN DU FICHIER.TXT QUE VOUS SOUHAITEZ EXECUTER \n");
    printf("\n\n  CHEMIN D'ACCES :  \n\n");
    scanf("%s", emplacement);

    while (emplacement=="mdp.txt" || emplacement=="main.c")
    {
            cls();
            printf("\n\n  Vous n'avez pas LE DROIT DE MODIFIER CE FICHIER \n\n\n");
            ls();
            printf("\n\n  CHEMIN D'ACCES :  \n\n");
            scanf("%s", emplacement);



    }

    fichier = fopen(emplacement, "r+");

    if (fichier != NULL){
        printf("\n \n FICHIER TROUVE ET CHARGE\n\n");
        fclose(fichier);
        system(emplacement);
    }
    else{
        printf(" \n \n FICHIER INTROUVABLE !!! \n VEUILLEZ RESSAYER \n\n");
    }

    fclose(fichier);
    cls();
}





void chemin(){

    system("dir /w");
    printf("\n\n[*]Ecrivez le chemin d'acces du fichier que vous souhaitez ouvrir (en mettant des doubles antislash comme separateur pour les chemin d'acces absolu) \n");
    printf("\n\n[+]Chemin d'acces: \n");
    char interdit1[]="main.c";
    char interdit2[]="MAIN.c";
    char interdit3[]="mdp.txt";
    char interdit4[]="MDP.txt";
     char interdit5[]="data.txt";
      char interdit6[]="DATA.txt";


    scanf("%s", emplacement);

     while ( strcmp(emplacement,interdit1) == 0 || strcmp(emplacement,interdit2) == 0 || strcmp(emplacement,interdit3) == 0 || strcmp(emplacement,interdit4) == 0 || strcmp(emplacement,interdit5) == 0 || strcmp(emplacement,interdit6) == 0 )
    {
            cls();
            printf("\n\n  Vous n'avez pas LE DROIT DE MODIFIER CE FICHIER \n\n\n");
            ls();
            printf("\n\n  CHEMIN D'ACCES :  \n\n");
            scanf("%s", emplacement);



    }


    cls();
    fichier = fopen(emplacement, "r+");

    if (fichier != NULL){
        printf("[*]Fichier charge avec succes\n\n");
    }else{
        cls();
        printf("[!]Fichier introuvable\n\n");
        chemin();
    }

    fclose(fichier);
}


void Crypt(char mdp[]){

    unsigned char caractere[1000];
    int caractereActuel;
    int n; //Incr�mentation (caract�re fichier)
    int j; //Incr�mentation (caract�re cl�)
    int longPass; //Longueur de la cl�
    longPass = strlen(mdp);


    for(n=0;n<1000;n++){
        caractere[n] = 0;
    }
    n=0;
    j=0;

                                        /* CHIFFREMENT */

    printf("[*]Le chiffrement debute\n\n");
    fichier = fopen(emplacement, "r");
    char line [1000 ];

     while(caractereActuel != EOF){
            caractereActuel = fgetc(fichier); // On lit le caract�re (1 octet)
            if(caractereActuel > 31){
            caractereActuel += (mdp[j]-64);
            caractere[n] = caractereActuel; // On enregistre dans un tableau
            n++;
            j = (j+1)%longPass; //Caract�re suivant de la cl�
            }
        }

    fclose(fichier);


                                        /* REECRITURE */

    fichier = fopen(emplacement, "w+"); //Ecriture (avec suppression)
    for(n=0;n<1000;n++){
        if(caractere[n] != 0){
       fputc(caractere[n], fichier); //On ecrit chaque caract�re
       }
    }
    fclose(fichier);


    printf("\n\n\n[*]Chiffrement termine \n");
    system(emplacement);
}


void decrypt(char mdp[]){

    unsigned char caractere[1000];
    int caractereActuel;
    int n; //Incr�mentation (caract�re fichier)
    int j; //Incr�mentation (caract�re cl�)
    int longPass; //Longueur de la cl�


    longPass = strlen(mdp);
    for(n=0;n<1000;n++){
        caractere[n] = 0;
    }
    n=0;
    j=0;




                                        /* DECHIFFREMENT */

    printf("Le dechiffrement debute...\n\n");
    fichier = fopen(emplacement, "r+");

     while(caractereActuel != EOF){
            caractereActuel = fgetc(fichier); // On lit le caract�re (1 octet)
            if(caractereActuel > 31){
            caractereActuel -= (mdp[j]-64);
            caractere[n] = caractereActuel; // On enregistre dans un tableau
            n++;
            j = (j+1)%longPass; //Caract�re suivant de la cl�
            }
        }
    fclose(fichier);


                                        /* REECRITURE */

    fichier = fopen(emplacement, "w+"); //Ecriture (avec suppression)
    for(n=0;n<1000;n++){
        if(caractere[n] != 0){
       fputc(caractere[n], fichier); //On ecrit chaque caract�re
       }
    }
    fclose(fichier);


    printf("\n\n\nDechiffrement termine...\n");
    system(emplacement);
}


void cryptage()      // ENTRER DU MOT DE PASSE
{

        int choix;
        char mdp[100];
        int i;
        int fin;
        fin =0;

        for(i=0;i<20;i++){
            mdp[i] = 0;
        }




        chemin();
        while(!fin) {

        printf(" \n QUE SOUHAITEZ VOUS FAIRE ?? \n\n");
        printf("\n1) CHIFFRER \n");
        printf("\n2) DECHIFFRE \n");
         printf("\n3) OUVRIR UNE APPLICATION  \n");
        printf("\n4) RETOUR AU MENU  \n\n");
        scanf("%d", &choix);
        switch(choix){
            case 1:
                  printf("Rentrez un mot de passe (20 caracteres maximum) (souvenez vous en bien !) : ");


                  scanf("%s",mdp);



                                     FILE* base = NULL;

                                    base = fopen("DATA.txt", "a+");
                                    if (base != NULL)    {

                                        fprintf(base,"%s \n",mdp);



                                        fclose(base);
                                        }






                  while(i < 20){
                        mdp[i] = toupper(mdp[i]); //Mettre cl� en majuscule
                        i++;
                  }
                  Crypt(mdp);
                  break;
            case 2:
                  printf("Rentrez le mot de passe : ");
                  scanf("%s", mdp);
                  while(i < 20){
                        mdp[i] = toupper(mdp[i]); //Mettre cl� en majuscule
                        i++;
                  }
                  decrypt(mdp);
                  break;
            case 3:
                fiche();
                break;
            case 4:
                cls();
                return 0;
            default:
                  printf("Choix impossible");
                  break;
    }
}
}


typedef struct Element Element;
struct Element
{
    char *nombre;
    Element *suivant;
};

typedef struct File File;
struct File
{
    Element *premier;
};

void recup_mdp()
{ // R�CUPERE LES MOTS DE PASSE DANS LE FICHIER
 //   Element *nouveau = malloc(sizeof(*nouveau));
//	nouveau->nombre = 0;
//	nouveau->suivant= NULL;
//    Element *elementActuel = file->premier;
    FILE* fichier = fopen("mdp.txt","r");
char mot[1000];


/*((*/fgets(mot,1000,fichier);//)) //!= EOF )
    //{
        //if ((fgets(elementActuel->nombre,1000,fichier)) == " ") {
        //     fseek(fichier, 1, SEEK_CUR);
       // }
       // printf("%s", elementActuel->nombre);
        //elementActuel = elementActuel->suivant;
        //}
        printf("Les mots de passes sont : %s\n",mot);
    }







void stocker_mdp(File *file, char *nvNombre) //STOCKE LES MOTS DE PASSE DANS UNE LISTE CHA�N�E
{

    Element *nouveau = malloc(sizeof(*nouveau));
    if (file == NULL || nouveau == NULL)
    {
        exit(EXIT_FAILURE);
    }

    nouveau->nombre = nvNombre;
    nouveau->suivant = NULL;

    if (file->premier != NULL) /* La file n'est pas vide */
    {
        /* On se positionne � la fin de la file */
        Element *elementActuel = file->premier;

        while (elementActuel->suivant != NULL)
        {

            elementActuel = elementActuel->suivant;
        }

        elementActuel->suivant = nouveau;
    }
    else /* La file est vide, notre �l�ment est le premier */
    {
        file->premier = nouveau;
    }
}


void stocker_mdp2(File *file){

    fichier = fopen("mdp.txt", "r+");
    Element *nouveau = malloc(sizeof(*nouveau));


     Element *elementActuel = file->premier;

        while (elementActuel->suivant != NULL)
        {
            fprintf(fichier, " %s ", elementActuel->nombre);
            elementActuel = elementActuel->suivant;
        }
        fprintf(fichier, "%s ",elementActuel->nombre);
       fclose(fichier);
    }
void ajouter_mdp(File *file){

    fichier = fopen("mdp.txt", "a");
    Element *nouveau = malloc(sizeof(*nouveau));
    fseek(fichier, 1, SEEK_END);


     Element *elementActuel = file->premier;

        while (elementActuel->suivant != NULL)
        {
            fprintf(fichier, "%s ", elementActuel->nombre);
            elementActuel = elementActuel->suivant;
        }
        fprintf(fichier, "%s ",elementActuel->nombre);
       fclose(fichier);
    }

File *initialiser()
{
    File *file = malloc(sizeof(*file));
    file->premier = NULL;

    return file;
}


void crypt_txt(char mdp[]){

    unsigned char caractere[1000];
    int caractereActuel;
    int n; //Incr�mentation (caract�re fichier)
    int j; //Incr�mentation (caract�re cl�)
    int longPass; //Longueur de la cl�
    longPass = strlen(mdp);

    for(n=0;n<1000;n++){
        caractere[n] = 0;
    }
    n=0;
    j=0;

                                        /* CHIFFREMENT */

  //  printf("[*]Le chiffrement debute\n\n");
    fichier = fopen("mdp.txt", "r");

     while(caractereActuel != EOF){
            caractereActuel = fgetc(fichier); // On lit le caract�re (1 octet)
            if(caractereActuel > 31){
            caractereActuel += (mdp[j]-64);
            caractere[n] = caractereActuel; // On enregistre dans un tableau
            n++;
            j = (j+1)%longPass; //Caract�re suivant de la cl�
            }
        }
    fclose(fichier);


                                        /* REECRITURE */

    fichier = fopen("mdp.txt", "w+"); //Ecriture (avec suppression)
    for(n=0;n<1000;n++){
        if(caractere[n] != 0){
       fputc(caractere[n], fichier); //On ecrit chaque caract�re
       }
    }
    fclose(fichier);


   // printf("\n\n\n[*]Chiffrement termine \n");

}


void decrypt_txt(char mdp[]){

    unsigned char caractere[1000];
    int caractereActuel;
    int n; //Incr�mentation (caract�re fichier)
    int j; //Incr�mentation (caract�re cl�)
    int longPass; //Longueur de la cl�

    longPass = strlen(mdp);
    for(n=0;n<1000;n++){
        caractere[n] = 0;
    }
    n=0;
    j=0;




                                        /* DECHIFFREMENT */

  //  printf("[*]Le dechiffrement debute\n\n");
    fichier = fopen("mdp.txt", "r");

     while(caractereActuel != EOF){
            caractereActuel = fgetc(fichier); // On lit le caract�re (1 octet)
            if(caractereActuel > 31){
            caractereActuel -= (mdp[j]-64);
            caractere[n] = caractereActuel; // On enregistre dans un tableau
            n++;
            j = (j+1)%longPass; //Caract�re suivant de la cl�
            }
        }
    fclose(fichier);


                                        /* REECRITURE */

    fichier = fopen("mdp.txt", "w+"); //Ecriture (avec suppression)
    for(n=0;n<1000;n++){
        if(caractere[n] != 0){
       fputc(caractere[n], fichier); //On ecrit chaque caract�re
       }
    }
    fclose(fichier);


   // printf("\n\n\n[*]Dechiffrement termine \n ");

}



int cryptage2()      // MENU GESTIONNAIRE MOT DE PASSE
{

    int i;




        while(1) {
                      int choix;
        int nbr=0;
        char mdp[20];
        creation_fichier();

        File* maFile= initialiser();
        printf(" \n  QUE SOUHAITEZ-VOUS FAIRE ?? \n\n");
      //  printf("\n1) DEPOSER VOS MOTS DE PASSE ET CRYPTER LE FICHIER \n");
        printf("\n1) AFFICHER VOS SITES OU COMPTES \n");
        printf("\n2) AJOUTER VOS SITES OU COMPTES \n ");
        printf("\n3) RETOUR AU MENU  \n\n");
        scanf("%d", &choix);
        switch(choix){
            case 99:
                 for(i=0;i<20;i++){
            mdp[i] = 0;
        }
 i=0;
                  printf("Rentrez un mot de passe (20 caracteres maximum) (souvenez-vous en bien !) : ");
                  scanf("%s", mdp);

            stocker_mdp(maFile,mdp);

            printf("Combien de mots de passe a enregistrer ?\n");
                if(scanf("%d", &nbr)!= 1){
                    exit(-1);
                        }

                while(i < nbr){
                    printf("Veuillez entrer le mot de passe numero %d\n",(i+1));
                    char *mdp = malloc(20*sizeof(char));
                    scanf("%s", mdp);
                    stocker_mdp(maFile, mdp);

                    i++;

                        }

                    stocker_mdp2(maFile);

                  crypt_txt(mdp);

                  cls();

                  break;
            case 1:

                  printf("Rentrez le mot de passe : ");
                  char mdp[20];
                   for(i=0;i<20;i++){
            mdp[i] = 0;
        }

                  File* maFile2 = initialiser();
                  scanf("%s", mdp);
                  decrypt_txt(mdp);
                  recup_mdp(maFile2);
                  crypt_txt(mdp);
                  sleep(5);
                   cls();
                  break;
            case 2 :
                for(i=0;i<20;i++){
            mdp[i] = 0;
        }

        i = 0;
                //fichier = fopen("mdp.txt", "a");
                printf("Tapez votre mot de passe\n");
                scanf("%s", mdp);

                FILE* base = NULL;

                                    base = fopen("DATA.txt", "a+");
                                    if (base != NULL)    {

                                        fprintf(base,"%s \n",mdp);



                                        fclose(base);
                                        }



				File *maFile3 = initialiser();
				i=0;

printf("Combien de sites ou comptes voulez vous ajouter ?\n");

while (scanf("%d", &nbr)!= 1){
scanf("%d", &nbr);
}

while(i < nbr){
        printf("Veuillez entrer le site ou compte numero %d\n",(i+1));
        char *mdpajout = malloc(20*sizeof(char));
        scanf("%s", mdpajout);
        stocker_mdp(maFile3, mdpajout);

        i++;

            }
        decrypt_txt(mdp);
        ajouter_mdp(maFile3);
        crypt_txt(mdp);
                sleep(2);
                 cls();
                break;
            case 3:
               return 0;
            default:
                  printf("Choix impossible");
                  break;
    }
}
cryptage2();
}


void data ()
{
    FILE* fichier = NULL;
    int caractereActuel = 0;
    int TAILLE_MAX=1000;
    char chaine[1000] = ""; // Cha�ne vide de taille TAILLE_MAX


    fichier = fopen("data.txt", "r");

    if (fichier != NULL)
    {
        // Boucle de lecture des caract�res un � un
       /* do
        {
            caractereActuel = fgetc(fichier); // On lit le caract�re
            printf("%c", caractereActuel); // On l'affiche



        } while (caractereActuel != EOF); // On continue tant que fgetc n'a pas retourn� EOF (fin de fichier)
        */

        int ligne= 1;
       while (fgets(chaine, TAILLE_MAX, fichier) != NULL) // On lit le fichier tant qu'on ne re�oit pas d'erreur (NULL)
        {

            printf("\n ligne %d :  ",ligne);
            printf("%s", chaine); // On affiche la cha�ne qu'on vient de lire

                  File* maFile2 = initialiser();
                  decrypt_txt(chaine);
                  recup_mdp(maFile2);
                  crypt_txt(chaine);
                  sleep(5);
                   cls();






            ligne++;

        }


        fclose(fichier);
    }

    return 0;
}


int main()
{


        int choix;
        int fin ;
        fin = 0;
while (!fin)

{
        printf(" \n \n \n ******* Hello world, welcome in CODEC GENERATOR *******\n");

        printf("\n xx xx xx xx xx xx xx xx MENU xx xx xx xx xx xx xx xx \n \n ");

        printf("\n  1) CREATION D'UN GESTIONNAIRE DE MOT DE PASSE  \n ");
        printf("\n  2) CRYPTER UN FICHIER  \n\n\n\n");
        printf("\n  3) QUITTER  \n\n\n\n");
        scanf("%d", &choix);                        //MENU PRICIPAL
        switch(choix){

                                                //////////// CODEC MANAGER  ///////////////
            case  1:
                    cls();
                    cryptage2();
                    cls();
                    break;
            default:
                  printf("\n \n Choix impossible !!!");
                  break;
            case 2:
                cls();
                cryptage();
                    break;
             case 99:
                cls();
                data();
                    break;

            case 3:
                return 0;





                }
}
    }
