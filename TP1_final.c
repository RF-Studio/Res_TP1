#include <stdio.h>
#include <string.h>

typedef struct
{
    char nom[20],
        prenom[20];
    int age;
} FICHE ;

// prototypes
FICHE saisie_clavier();
void affiche(FICHE * ptrf);
void saisir(FILE * fichier);
void lire(FILE * fichier);
void rechercher(char * str_user, FILE * fichier);
void AlphaTrie(FILE * fAT);

// Programme principal
void main(){
    // déclaration des variables
    char nom_fichier_travail[100]; // chemin et nom du fichier de travail
    FILE * flux_fichier_travail; // flux vers le fichier de travail
    int choix; // choix de l'utilisateur
    char recherche[20]; // nom à rechercher

    // Saisie au clavier du nom du fichier de travail
    printf("Donner le nom du fichier de travail : ");
    scanf("%s", nom_fichier_travail);

    do
    {
        // Affichier le menu à l'écran
        printf("MENU :\n   1 : Saisie d'une fiche\n   2 : Lecture et affichage du fichier\n   3 : Recherche d'une fiche\n   4 : Trie v.1\n   5 : Quitter\n\n");
        // Saisir le choix de l'utilisateur
        scanf("%d", &choix);

        switch (choix)
        {
        case 1: // Saisie d'une fiche (nom, prénom, âge) au clavier et ajout en fin de fichier de travail
            // ouvrir le fichier de travail
            flux_fichier_travail = fopen(nom_fichier_travail, "a+");
            // SI l'ouverture a échoué, afficher un message et terminer le programme
            if (flux_fichier_travail==NULL)
            {
                printf("Erreur lors de l'ouverture du fichier de travail.");
                return;
            }
            // Saisir et enregistrer une fiche dans le fichier de travail avec la fonction saisir
            saisir(flux_fichier_travail);
            // fermer le fichier de travail
            fclose(flux_fichier_travail);
            break;
        
        case 2: // afficher à l'écran toutes les fiches sauvegardées dans le fichier de travail
            // ouvrir le fichier de travail
            flux_fichier_travail = fopen(nom_fichier_travail, "r");
            // SI l'ouverture a échoué, afficher un message et terminer le programme
            if (flux_fichier_travail==NULL)
            {
                printf("Erreur lors de l'ouverture du fichier de travail.");
                return;
            }
            // afficher les fiches stockées dans le fichier travail avec la fonction lire
            lire(flux_fichier_travail);
            // fermer le fichier de travail
            fclose(flux_fichier_travail);
            break;
        
        case 3: // permet de rechercher une fiche à partir des premières lettres du nom
            // ouvrir le fichier de travail
            flux_fichier_travail = fopen(nom_fichier_travail, "r");
            // SI l'ouverture a échoué, afficher un message et terminer le programme
            if (flux_fichier_travail==NULL)
            {
                printf("Erreur lors de l'ouverture du fichier de travail.");
                return;
            }
            printf("Entrer les premieres lettres du Nom que vous recherchez : ");
            scanf("%s", recherche);
            rechercher(recherche, flux_fichier_travail);
            //fermer le fichier de travail
            fclose(flux_fichier_travail);
            break;
        case 4: // Fonction de trie des fiches
            // ouvrir le fichier de travail en mode lecture
            flux_fichier_travail = fopen(nom_fichier_travail, "r+");
            // SI l'ouverture a échoué, afficher un message et terminer le programme
            if (flux_fichier_travail==NULL)
            {
                printf("Erreur lors de l'ouverture du fichier de travail.");
                return;
            }
            AlphaTrie(flux_fichier_travail);
            // fermer le fichier de travail et tampon
            fclose(flux_fichier_travail);
            break;

        default:
            break;
        }
    } while (choix != 5);
    
}

// Instructions de la fonction saisie_clavier
FICHE saisie_clavier(){
    // saisir au clavier la valeur d'une variable de type FICHE et la retourne
    // au programme appelant
    // Déclaration des variables
    FICHE f; // fiche saisie et retournée
    printf("Nom : ");
    scanf("%s", f.nom);
    printf("Prenom : ");
    scanf("%s", f.prenom);
    printf("Age : ");
    scanf("%d", &f.age);
    return f;
}

// Instructions de la fonction affiche
void affiche(FICHE * ptrf){
    // affiche à l'écran les valeurs de tous les champs de la fiche pointés par ptrf
    printf("FICHE :\n Nom : %s\n Prenom : %s\n Age : %d\n\n", ptrf->nom, ptrf->prenom, ptrf->age);
}

// Instructions de la fonction saisir
void saisir(FILE * fichier){
    // Saisir une fiche au clavier et l'enregistre dans le flux fichier
    // déclaration des variables
    FICHE f2; // fiche saisie et enregistrée

    // saisie de la fiche f2 au clavier avec la fonction saisie_clavier
    f2 = saisie_clavier();
    // écriture de la fiche f2 dans le flux fichier avec la fonction fwrite
    fwrite(&f2, 1, sizeof f2, fichier);
}

// Instructions de la fonction lire
void lire(FILE * fichier){
    // lit toutes les fiches contenues dans le flux fichier et les affiche à l'écran
    // Déclaration des variables
    FICHE f3; // fiche lue et affichée

    do
    {
        // lire la valeur d'une fiche dans le flux fichier et la stocker dans f3 avec la fonction fread
        fread(&f3, sizeof f3, 1, fichier);
        // SI la lecture a réussi
        if (ferror(fichier) == 0 && feof(fichier) == 0) 
        {
            // affichier la ficher f3 à l'écran avec la fonction affiche
            affiche(&f3);
        }
    } while (feof(fichier) == 0);
}

// Instruction de la fonction  recherche
void rechercher(char * str_user, FILE * fichier){
    // Permet de rechercher une fiche à partir des premières lettres du nom
    int c, choix, match=0; // taux de match
    FICHE buffer; // fiche buffer pour récupérer le nom dans le fichier de travail
    
    do
    {
        fread(&buffer, sizeof buffer, 1, fichier); // lecture fichier de travail
        // si lecture OK
        if (ferror(fichier) == 0 && feof(fichier) == 0)
        {
            c = strncmp(str_user, buffer.nom, strlen(str_user));
            if (c==0)
            {
                match++;
                affiche(&buffer);
                printf("\nVoulez-vous poursuivre la recherche ?\n   1 : OUI\n   2 : NON\n");
                scanf("%d", &choix);
                if (choix == 2)
                {
                    return;
                }
                
            }
            
        }
        
    } while (feof(fichier) == 0);
    if (match==0)
    {
        printf("\nAucune fiche ne correspond a votre recherche !\n\n");
        return;
    }
    else
    {
        printf("\nIl n'y a pas d'autres fiches a afficher...\n\n");
        return;
    }
}

void AlphaTrie(FILE * fAT){
    /* ATTENTION, cette méthode présente un bug si jamais on n'adopte pas les mêmes formats (majuscule minuscule) pour les noms et prénom (ex de format : NOM, Prénom) */
    FICHE buffer; // fiche tampon
    FICHE Tbuffer[100]; // tableau de fiche
    int i=0, j=0, flag=-1, nbF=0, k=0;

    // Copie des fiches dans le Tableau buffer -- TEST OK --
    do
    {
        fread(&buffer, sizeof buffer, 1, fAT); // lecture des fiches dans le fichier de travail
        // Si lecture OK
        if (feof(fAT)==0 && ferror(fAT)==0)
        {
            Tbuffer[nbF]=buffer; // copie de la fiche dans le tableau
            nbF++;
        }
        
    } while (feof(fAT)==0); // Tant que la fin du fichier n'est pas atteinte

    // Déplacer la tête de lecture du stream en début de fichier
    rewind(fAT);
    
    // Trie par itération -- TEST OK --
    for (size_t i = 0; i < nbF; i++)
    {
        for (size_t j = 0; j < nbF; j++)
        {
            if (strcmp(Tbuffer[i].nom, Tbuffer[j].nom) < 0) // Test si le nom de la fichie i et de la fiche j si sont dans le désordre
            {
                // interverti 2 lignes
                buffer = Tbuffer[i];
                Tbuffer[i] = Tbuffer[j];
                Tbuffer[j] = buffer;
            }
            else if (strcmp(Tbuffer[i].nom, Tbuffer[j].nom) == 0) // Test si le nom de la fiche i et de la fiche j sont égaux
            {
                if (strcmp(Tbuffer[i].prenom, Tbuffer[j].prenom) < 0) // Test si le prénom de la fichie i et de la fiche j si sont dans le désordre
                {
                    // interverti 2 lignes
                    buffer = Tbuffer[i];
                    Tbuffer[i] = Tbuffer[j];
                    Tbuffer[j] = buffer;
                }
                
            }
            
            
        }
        
    }
    

   // Copie dans le fichier de travail -- TEST OK --
   for (size_t k = 0; k < nbF; k++)
   {
       buffer = Tbuffer[k];
       fwrite(&buffer, 1, sizeof buffer, fAT);
   }
}
