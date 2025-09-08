#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/**
* NOM : Seydina Bocoum
* CODE PERMANENT: BOCS92260401
*/

#define TAILLE_BUFFER 4096          // Taille maximale du buffer pour la lecture de lignes dans les fichiers
#define MAX_LIGNES 31127           // Nombre maximal de lignes à lire (non utilisé ici mais pourrait servir pour des contrôles)
#define LONG_NOM_PAYS 50           // Taille maximale pour le nom d'un pays
#define LONG_CODE_PAYS 10          // Taille maximale pour le code d'un pays
#define LONG_NOM_VILLE 100         // Taille maximale pour le nom d'une ville
#define FORMAT_TITRE  "%-s\t%-27s\t%-46s\t%-s\n"   // Format de titre pour l'affichage (aligné)
#define FORMAT_COLONNES "%ld\t%-30s\t%-40s\t%ld\n" // Format des colonnes pour les villes et pays (aligné)
#define MANUEL_LIGNE_1 "\nUsage: ./geonames <NUMBER OF CITIES>\n"
#define MANUEL_LIGNE_2 "\nDisplay a table of the n most populous cities on stdout."
#define MANUEL_LIGNE_3 "\nThe number of cities must not exceed 5000.\n"
#define MANUEL_LIGNE_4 "\nIf no argument is provided, the program prints this help and exit.\n"
#define MANUEL_LIGNE_5 "\nProgram parameters :\n"
#define MANUEL_LIGNE_6 "\n  NUMBER OF CITIES : number of cities to display\n"
#define NOMBRE_ARGUMENT_INVALIDE  "nombre arguments invalide"
#define MAUVAIS_NOMBRE_VILLES  "nombre de ville invalide" 
#define ARGUMENT_INVALIDE  "type argument invalide"


typedef struct Pays {
    char nom[LONG_NOM_PAYS];       // Nom du pays
    char code[LONG_CODE_PAYS];     // Code du pays
} PAYS;

typedef struct Ville {
    char nom[LONG_NOM_VILLE];      // Nom de la ville
    long population;               // Population de la ville
    PAYS pays;                     // Pays auquel appartient la ville
} VILLE;



/**
 * Fonction principale qui gère l'argument utilisateur et affiche les résultats.
 * Cette fonction vérifie le nombre d'arguments, traite l'argument utilisateur,
 * et affiche les informations sur les villes triées par population.
 * 
 * @param argc Le nombre d'arguments passés au programme.
 * @param argv Le tableau des arguments passés au programme.
 * 
 * @return Un code de sortie indiquant le succès (0) ou l'échec (1) de l'exécution.
 * 
 */
void lireLignesEntree(char *argument, int *nombreLignes);

/**
 * Ces prototypes déclarent les fonctions qui sont définies plus bas dans 
 * le fichier. Elles incluent des fonctions pour charger les données des 
 * pays et des villes, ainsi que pour trier et afficher les informations 
 * relatives aux villes. 
 */

 /**
 *  Compte le nombre de lignes dans un fichier.
 * 
 * Cette fonction ouvre un fichier spécifié par son nom, lit chaque ligne, 
 * et compte le nombre total de lignes présentes dans le fichier. 
 * 
 * @param nomfichier Le nom du fichier à traiter. 
 * 
 * @return Le nombre total de lignes dans le fichier. 
 * 
 */
long compterNombreLignes(char *nomfichier);
/**
 * Vérifie le nombre d'arguments dans l'entrée utilisateur.
 * Cette fonction analyse une chaîne de caractères donnée par l'utilisateur
 * et vérifie si elle contient exactement un seul argument .
 * Si plus d'un argument est détecté, un message d'erreur
 * est affiché par la fonction `manuelUtilisateur`, et le programme se termine.
 *
 * @param entreeUtilisateur La chaîne de caractères entrée par l'utilisateur
 *                          à vérifier. Elle doit être suffisamment longue pour
 *                          contenir un argument valide et un éventuel espace.
 *
 * @note Cette fonction utilise `strtok` pour diviser la chaîne en fonction
 *       des espaces. Si la chaîne contient plus d'un mot, une erreur est
 *       signalée.
 *
 * @return void
 */
void verifierNombreArgument(char *entreeUtilisateur);
/** 
 * Permute deux villes dans le tableau.
 *
 * Cette fonction échange les valeurs des deux villes pointées par les pointeurs fournis. 
 * Elle est utilisée pour réorganiser les villes lors du tri.
 *
 * @param a Pointeur vers la première ville à permuter.
 * @param b Pointeur vers la deuxième ville à permuter.
 * 
 * @note Les villes doivent être valides et les pointeurs ne doivent pas être nuls.
 */
void permuter(VILLE *a, VILLE *b);
/** 
 * Trie un tableau de villes par leur population en utilisant l'algorithme de tri rapide (quicksort).
 *
 * Cette fonction utilise la méthode de partitionnement pour trier les villes. 
 * Les villes sont triées en fonction de leur population en ordre croissant.
 *
 * @param tab Tableau de villes à trier.
 * @param first Index de la première ville dans le tableau à considérer.
 * @param last Index de la dernière ville dans le tableau à considérer.
 * 
 * @note Si `first` est supérieur ou égal à `last`, la fonction ne fait rien.
 */
void triRapid(VILLE tab[], int first, int last);
/** 
 * Trouve la correspondance entre une ville et son pays dans le tableau des pays.
 *
 * Cette fonction parcourt le tableau des pays pour associer le nom du pays à la ville 
 * correspondante, en se basant sur le code du pays.
 *
 * @param indiceVille Indice de la ville dans le tableau des villes à traiter.
 * 
 * @note Cette fonction ne retourne rien mais modifie le tableau des villes.
 */
void trouverCorrespondance(int indiceVille, VILLE tableauDesVilles[], PAYS tableauPays[]);

/** 
 * Isoler le code du pays d'une ligne de fichier.
 *
 * Cette fonction parcourt une ligne de texte et extrait le code du pays, 
 * qui est supposé se trouver à un emplacement spécifique.
 *
 * @param buffer Ligne de texte à traiter.
 * @param codeDuPays pour stocker le code du pays extrait
 * @note Les champs dans le fichier sont séparés par des tabulations.
 */
void isolerCodeDuPays(char* buffer , char *codeDuPays);
/** 
 * Isoler le code et le nom du pays d'une ligne de fichier.
 *
 * Cette fonction extrait le code du pays et le nom du pays d'une ligne de texte 
 * séparée par des tabulations.
 *
 * @param ligneCopie Ligne de texte à traiter.
 * @param code Buffer pour stocker le code du pays.
 * @param pays Buffer pour stocker le nom du pays.
 * 
 * @note La fonction suppose que les champs sont séparés par des tabulations.
 */
void cherchercode(char *ligneCopie, char *code, char *pays);
/**
 *  Traite le fichier des pays et remplit le tableau des pays.
 * 
 * Cette fonction lit le fichier ligne par ligne, ignore les (50) premières 
 * lignes, puis extrait et stocke les codes et noms des pays dans un tableau 
 * de structures de type PAYS. 
 * 
 * @param file Pointeur vers le fichier à traiter.
 * @param tableauPays Tableau de structures de type PAYS où les codes et noms 
 *        des pays seront stockés.
 * 
 * @see cherchercode
 */
void isolerCodeEtPays(FILE *file, PAYS tableauPays[]);
/**
 * Ouvre le fichier "countryInfo.txt" et charge les données des pays.
 * 
 * Cette fonction tente d'ouvrir le fichier contenant les informations sur les 
 * pays. Si l'ouverture réussit, elle appelle une fonction pour extraire les 
 * données  (codes et noms des pays) et les stocker dans le tableau 
 * fourni.
 * 
 * @param tableauPays Tableau de structures de type PAYS où les informations 
 *        sur les pays seront stockées.
 * 
 * @return 0 si l'opération réussit, 1 si l'ouverture du fichier échoue.
 * 
 * @note En cas d'échec à ouvrir le fichier, un message d'erreur est affiché
 *       à l'utilisateur.
 * 
 * @see isolerCodeEtPays
 */
int ouvrirCountry(PAYS tableauPays[]);
/**
 *  Ouvre le fichier "cities15000.txt" et traite les lignes.
 * 
 * Cette fonction ouvre le fichier contenant la liste des villes et s'assure que 
 * les informations sur les pays sont traitées en premier. Elle lit ensuite les 
 * lignes du fichier des villes et appelle la fonction appropriée pour 
 * copier les données dans le tableau des villes.
 * 
 * @param tableauDesVilles Tableau de structures de type VILLE où les 
 *        informations des villes seront stockées.
 * @param tableauPays Tableau de structures de type PAYS contenant les 
 *        informations sur les pays, nécessaire pour associer les villes à 
 *        leurs pays respectifs.
 * 
 * @note Si le fichier des villes ne peut pas être ouvert, un message d'erreur 
 *       est affiché à l'utilisateur.
 * 
 * @see ouvrirCountry
 * @see copierLignesFichier
 */
void ouvrirCities(VILLE tableauDesVilles[], PAYS tableauPays[]);
/** 
 * Affiche l'usage correct du programme et un message d'erreur.
 *
 * Cette fonction affiche un message d'erreur et des instructions sur la manière 
 * d'utiliser le programme.
 *
 * @param message Message d'erreur à afficher.
 * 
 * @note Cette fonction n'a pas de valeur de retour et ne modifie aucun état.
 */
void manuelUtilisateur(char* message);
/**
 * Fonction pour isoler le nom de la ville dans une ligne.
 * 
 * Cette fonction utilise un délimiteur pour séparer les champs dans une chaîne 
 * de caractères et renvoie le nom de la ville extrait du deuxième champ.
 * 
 * @param lignesCopie La chaîne contenant les informations de la ville, 
 *                    avec les champs séparés par des tabulations.
 * @return Un pointeur vers le nom de la ville extrait.
 */
const char* isolerVille(char* lignesCopie);
/**
 * Fonction pour inverser une chaîne de caractères.
 * 
 * Cette fonction prend une chaîne de caractères et l'inverse en modifiant
 * la chaîne d'origine. 
 * 
 * @param chaine La chaîne de caractères à inverser. La chaîne est modifiée
 *               en place.
 */
void renverserChaine(char *chaine);
/**
 * Fonction pour isoler la population dans une ligne.
 * 
 * Cette fonction extrait la population d'une chaîne de caractères qui contient 
 * les informations de la ville, en utilisant un délimiteur pour séparer les champs.
 * Elle inverse d'abord la chaîne pour rechercher à partir de la fin et renvoie 
 * la population comme une chaîne de caractères.
 * 
 * @param lignesCopie La chaîne contenant les informations de la ville, 
 *                    avec les champs séparés par des tabulations.
 * @param population  pour stocker la population extraite
 *
 * @return Un pointeur vers la chaîne contenant la population extraite.
 */
const char* isolerPopulation(char* lignesCopie, char *population );
/**
 * Copie les lignes d'un fichier dans le tableau des villes.
 * Cette fonction lit un fichier ligne par ligne, extrait les informations 
 * de chaque ligne (nom de la ville, population, code du pays) et les 
 * copie dans un tableau de structures représentant des villes. 
 * Avant de commencer à traiter les villes, elle charge d'abord les 
 * informations sur les pays en appelant la fonction `ouvrirCountry`.
 * 
 * @param file Pointeur vers le fichier à lire. Ce fichier doit contenir
 *        les informations sur les villes formatées de manière appropriée.
 * @param tableauDesVilles Tableau de structures de type VILLE où les 
 *        informations des villes seront copiées.
 * @param tableauPays Tableau de structures de type PAYS contenant les 
 *        informations sur les pays, utilisé pour associer le nom du pays
 *        à chaque ville.
 * 
 * @note Cette fonction utilise plusieurs chaînes temporaires pour 
 *       extraire et traiter les données de chaque ligne lue. 
 *       Elle trie également le tableau des villes par population après
 *       avoir copié toutes les données.
 * 
 * @see ouvrirCountry
 * @see isolerVille
 * @see isolerPopulation
 * @see isolerCodeDuPays
 * @see trouverCorrespondance
 * @see triRapid
 */
void copierLignesFichier(FILE *file, VILLE tableauDesVilles[], PAYS tableauPays[]);
/**
 * Vérifie la validité de l'argument passé et lance le traitement des villes.
 * Cette fonction valide l'argument fourni par l'utilisateur pour s'assurer qu'il
 * s'agit d'un nombre entier positif dans une plage spécifiée. Si l'argument est
 * valide, elle ouvre les fichiers nécessaires et démarre le traitement des données 
 * des villes. En cas d'argument invalide, un message d'erreur est affiché.
 * 
 * @param entreeUtilisateur Pointeur vers une chaîne de caractères contenant l'argument
 *        fourni par l'utilisateur représentant le nombre de villes à traiter.
 * @param tableauDesVilles Tableau de structures de type VILLE contenant les informations
 *        sur les villes.
 * @param tableauPays Tableau de structures de type PAYS contenant les informations
 *        sur les pays.
 * 
 * @see ouvrirCities
 * @see manuelUtilisateur
 */
void verifierArgument(char entreeUtilisateur[],VILLE tableauDesVilles[],PAYS tableauPays[]);

void copierLignesFichier(FILE *file,VILLE tableauDesVilles[],PAYS tableauPays[]);


long compterNombreLignes(char *nomfichier) {
    long compteur = 0;
    char buffer[TAILLE_BUFFER];
    FILE *fichier = fopen(nomfichier, "r"); 
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s\n", nomfichier);
        return -1; // Retourne -1 en cas d'erreur
    }
    while (fgets(buffer, TAILLE_BUFFER, fichier)) {
        compteur++;
    }
    fclose(fichier);
    return compteur;
}


void permuter(VILLE *a, VILLE *b) {
    VILLE temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void triRapide(VILLE tab[], int first, int last) {
    int pivot, i, j;
    if (first < last) {
        pivot = first;
        i = first;
        j = last;
        while (i < j) {
            while (tab[i].population <= tab[pivot].population && i < last) {
                i++;    // On cherche la première ville avec une population plus grande que le pivot
            }
            while (tab[j].population > tab[pivot].population) {
                j--;    // On cherche la première ville avec une population plus petite que le pivot
            }
            if (i < j) {
                permuter(&tab[i], &tab[j]);  // On échange les deux villes si elles sont mal ordonnées
            }
        }
        permuter(&tab[pivot], &tab[j]);  // On place le pivot au bon endroit
        triRapide(tab, first, j - 1);     // Tri des sous-tableaux gauche et droite
        triRapide(tab, j + 1, last);
    }
}


void trouverCorrespondance(int indiceVille,VILLE tableauDesVilles[],PAYS tableauPays[]){
   int trouve = 0;
    for(int i = 0; i < 253 ; i++){
        if(!strcmp(tableauDesVilles[indiceVille].pays.code, tableauPays[i].code)){
            strcpy(tableauDesVilles[indiceVille].pays.nom, tableauPays[i].nom);  // On associe le nom du pays à la ville
            trouve = 1;
        }
    }
    if (trouve == 0){
    tableauDesVilles[indiceVille].population = 0;
    }
}

void isolerCodeDuPays(char* buffer , char *codeDuPays){
    const char* delimitateur = "\t";  // Les champs sont séparés par des tabulations dans le fichier
    char *elementRecuperer;
    char elementPrecedent[5000];
    int decompte = 0;
    elementRecuperer = strtok(buffer ,delimitateur);  // On récupère le premier élément
    while(elementRecuperer != NULL && decompte < 9){
        strcpy(elementPrecedent, elementRecuperer);
        elementRecuperer = strtok(NULL, delimitateur); // On parcourt les éléments
        if(decompte == 7){
            strcpy(codeDuPays, elementRecuperer);      // Le code du pays est au 7e élément
            if(atol(elementRecuperer) != 0){           // Si ce n'est pas un nombre, on récupère l'élément précédent
                strcpy(codeDuPays, elementPrecedent);
            }
        }
        decompte++;
    }
}


void chercherCodeEtPays(char *ligneCopie, char *code, char *pays) {
    const char delimitateur[] = "\t";
    char *elementRecuperer;
    int decompte = 0;

    elementRecuperer = strtok(ligneCopie, delimitateur); // On récupère le code du pays
    if (elementRecuperer != NULL) {
        strcpy(code, elementRecuperer);
    }

    while (elementRecuperer != NULL && decompte < 4) {
        elementRecuperer = strtok(NULL, delimitateur); // On parcourt jusqu'à trouver le pays
        decompte++;
    }
    strcpy(pays, elementRecuperer);  // On copie le nom du pays
}


void isolerCodeEtPays(FILE *file , PAYS tableauPays[]) {
    char buffer[TAILLE_BUFFER];  // Buffer pour stocker chaque ligne
    char code[LONG_CODE_PAYS];
    char pays[LONG_NOM_PAYS];
    int compteur = 0;  // Compteur de lignes lues

    while (fgets(buffer, sizeof(buffer), file) != NULL) {  // Lecture ligne par ligne
        compteur++;
        if (buffer[0] == '#' || buffer[0] == '\0') {  // On ignore les lignes qui n ont pas de code de pays 
          continue;
          }
            chercherCodeEtPays(buffer, code, pays);
            strcpy(tableauPays[compteur].nom, pays);  // On copie le nom du pays
            strcpy(tableauPays[compteur].code, code); // On copie le code du pays
    }
}


int ouvrirCountry(PAYS tableauPays[]){
    FILE* fichierCountrie;
    fichierCountrie = fopen("countryInfo.txt", "r");  // Ouverture du fichier en lecture
    if (fichierCountrie == NULL) {
        printf("Impossible de charger le fichier countryInfo.txt\n");
        return 1;
    }

    isolerCodeEtPays(fichierCountrie , tableauPays);  // On isole les codes et noms des pays
    fclose(fichierCountrie);  // Fermeture du fichier
    return 0;
}

void ouvrirCities(VILLE tableauDesVilles[] , PAYS tableauPays[]) {
    FILE *fichierCountrie;
    ouvrirCountry(tableauPays);  // On commence par ouvrir et traiter le fichier des pays
    fichierCountrie = fopen("cities15000.txt", "r");  // Ouverture du fichier des villes
    if (fichierCountrie == NULL) {
        printf("Impossible de charger le fichier cities15000.txt\n");
    }
    copierLignesFichier(fichierCountrie,tableauDesVilles,tableauPays);  // Traitement des villes
    fclose(fichierCountrie); 
}


void manuelUtilisateur(char* message) {
    fprintf(stderr,"%s", message);
    fprintf(stderr,MANUEL_LIGNE_1);
    fprintf(stderr,MANUEL_LIGNE_2);
    fprintf(stderr,MANUEL_LIGNE_3);
    fprintf(stderr,MANUEL_LIGNE_4);
    fprintf(stderr,MANUEL_LIGNE_5);
    fprintf(stderr,MANUEL_LIGNE_6);
}

const char* isolerVille(char* lignesCopie) {
    const char delimitateur[] = "\t";
    char *elementRecuperer;
    int decompte = 0;

    elementRecuperer = strtok(lignesCopie, delimitateur);  // On récupère le premier champ
    while (elementRecuperer != NULL && decompte < 1) {
        elementRecuperer = strtok(NULL, delimitateur);  // Le deuxième champ est le nom de la ville
        decompte++;
    }

    return elementRecuperer;  
}

void renverserChaine(char *chaine) {
    int longueur = strlen(chaine);
    char temp;

    for (int i = 0; i < longueur / 2; i++) {
        temp = chaine[i];
        chaine[i] = chaine[longueur - i - 1];
        chaine[longueur - i - 1] = temp;
    }
}

const char* isolerPopulation(char* lignesCopie, char *population ) {
    const char delimitateur[] = "\t";
    char *elementRecuperer;
    int decompte = 0;
    renverserChaine(lignesCopie);  // On inverse la chaîne pour commencer la recherche à partir de la fin
    elementRecuperer = strtok(lignesCopie, delimitateur);  // On récupère le dernier champ
    while (elementRecuperer != NULL && decompte < 5) {
        if (decompte == 3){
            renverserChaine(elementRecuperer);  // On réinverser la chaîne pour la population
            strcpy(population, elementRecuperer);
            if(atol(elementRecuperer) < 15000){  // Si la population est inférieure à 15000, on la modifie
                elementRecuperer = strtok(NULL, delimitateur);
                renverserChaine(elementRecuperer);
                strcpy(population, elementRecuperer);
            }
        }
        elementRecuperer = strtok(NULL, delimitateur);  // On passe au champ suivant
        decompte++;
    }
    return elementRecuperer;  
}

void copierLignesFichier(FILE *file,VILLE tableauDesVilles[],PAYS tableauPays[]) {
    int compteurLignesLues = 0;
    char codeDuPays[31]; 
    char population[20];
    char chaineTemporaire[TAILLE_BUFFER];
    char chaineTemporaire2[TAILLE_BUFFER];
    char chaineTemporaire3[TAILLE_BUFFER];
    ouvrirCountry(tableauPays); //charge les pays avant de traiter les villes

    while (fgets(chaineTemporaire, TAILLE_BUFFER, file) != NULL) {
        strcpy(chaineTemporaire2, chaineTemporaire);
        strcpy(chaineTemporaire3, chaineTemporaire);
        strcpy(tableauDesVilles[compteurLignesLues].nom, isolerVille(chaineTemporaire));  // On isole et copie le nom de la ville
        isolerPopulation(chaineTemporaire2,population);  // On isole la population
        tableauDesVilles[compteurLignesLues].population = atol(population);  // Conversion de la population en long
        isolerCodeDuPays(chaineTemporaire3,codeDuPays);  // On isole le code du pays
        strcpy(tableauDesVilles[compteurLignesLues].pays.code, codeDuPays);  // On associe le code du pays à la ville
        trouverCorrespondance(compteurLignesLues,tableauDesVilles,tableauPays);  // On cherche le nom du pays correspondant
        compteurLignesLues++;
    }
    triRapide(tableauDesVilles, 0, compterNombreLignes("cities15000.txt"));  // On trie les villes par population
}


void verifierNombreArgument(char entreeUtilisateur[]){
    char verifierArgument[TAILLE_BUFFER] ;
    char *transition;
    char delimitateur[]=" ";
    strcpy(verifierArgument,entreeUtilisateur);
    transition = strtok(verifierArgument,delimitateur);
    transition = strtok(NULL,delimitateur);
   if(transition != NULL){
    manuelUtilisateur(NOMBRE_ARGUMENT_INVALIDE);  // Erreur si le nombre d'arguments est incorrect
    exit(1);
   }
}

void verifierArgument(char entreeUtilisateur[],VILLE tableauDesVilles[],PAYS tableauPays[]){
    int nombreDeLignes;
    char argument[TAILLE_BUFFER];
    strcpy(argument,entreeUtilisateur);
    verifierNombreArgument(entreeUtilisateur);
    if(argument[0] == '\0'){
    manuelUtilisateur(NOMBRE_ARGUMENT_INVALIDE);  // Erreur si le nombre d'arguments est incorrect
    exit(1);
   }
    for(int i = 0; i < strlen(argument); i++){
       if( argument[i] < 48 || argument[i] > 58){
          manuelUtilisateur(ARGUMENT_INVALIDE);  // Erreur si l'argument n'est pas un nombre
         exit(3);
       }
}
        nombreDeLignes = atoi(entreeUtilisateur);
        if(nombreDeLignes < 1 || nombreDeLignes > 5000){
            manuelUtilisateur(MAUVAIS_NOMBRE_VILLES);  // Erreur si le nombre est en dehors de la plage
            exit(2);
        } else {
            ouvrirCities(tableauDesVilles,tableauPays);  // On ouvre les fichiers et lance le traitement si l'argument est valide
        }
   
}


void lireLignesEntree(char *argument, int *nombreLignes) {
    char buffer[TAILLE_BUFFER];
    while (fgets(buffer, TAILLE_BUFFER, stdin) != NULL) {
        if (*nombreLignes == 0) {
            strcpy(argument, buffer);
        }
        (*nombreLignes)++;
    }
    if (*nombreLignes == 0) {
        manuelUtilisateur(NOMBRE_ARGUMENT_INVALIDE);
        exit(1);
    }
    argument[strlen(argument) - 1] = '\0'; // Supprime le saut de ligne à la fin
}


void verifierArguments(int argc, int nombreLignes) {
    if (argc != 1 || nombreLignes > 1) {
        manuelUtilisateur(NOMBRE_ARGUMENT_INVALIDE);
        exit(1);
    }
}


void afficherResultats(int nombreVillesVoulu, long tailleTableau, VILLE tableauDesVilles[]) {
    printf(FORMAT_TITRE, "Rang", "Nom", "Pays", "Population");
    printf(FORMAT_TITRE, "----", "---", "----", "----------");
    for (int i = tailleTableau; i > (tailleTableau - nombreVillesVoulu); i--) {
        printf(FORMAT_COLONNES, tailleTableau - i + 1, tableauDesVilles[i].nom, tableauDesVilles[i].pays.nom, tableauDesVilles[i].population);
    }
}

// Nouvelle fonction principale modulaire
int main(int argc, char *argv[]) {
    char argument[TAILLE_BUFFER];
    int nombreLignes = 0;

    // Lire les lignes d'entrée
    lireLignesEntree(argument, &nombreLignes);

    // Vérifier les arguments
    verifierArguments(argc, nombreLignes);

    // Initialisation des tableaux
    PAYS tableauPays[compterNombreLignes("countryInfo.txt")];
    VILLE tableauDesVilles[compterNombreLignes("cities15000.txt")];

    // Vérification et traitement de l'argument
    verifierArgument(argument, tableauDesVilles, tableauPays);

    long tailleTableau = compterNombreLignes("cities15000.txt");
    int nombreVillesVoulu = atoi(argument);

    // Afficher les résultats
    afficherResultats(nombreVillesVoulu, tailleTableau, tableauDesVilles);

    exit(0);
}

