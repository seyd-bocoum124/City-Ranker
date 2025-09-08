# Travail pratique 1


# nbinaire.c

## Description

Le programme **nbinaire.c** permet de convertir un nombre entier en sa representation binaire. Il prend un argument au momemnt de son excecution, verifie sa validite, puis genere la representation binaire du nombre entier fourni.

Si l'argument n'est pas valide (par exemple, s'il ne s'agit pas d'un entier ou si le nombre est en dehors de l intervalle [0;1000]), le programme affichera un message d'erreur et s'arretera.

## Usage

Le programme se compile et s'execute comme suit :

### Compilation

```bash
gcc -o nbinaire nbinaire.c
```

### Execution

Pour executer le programme, utilisez la commande suivante :

```bash
./nbinaire <NOMBRE_ENTIER>
```

Le parametre `<NOMBRE_ENTIER>` doit etre un nombre entier compris entre 0 et 1000. Si aucun argument ou un argument invalide est fourni, le programme affichera un message d'erreur.

### Exemples d'execution

- Pour convertir le nombre 10 en binaire :

```bash
./nbinaire 10
```

Cela produira une sortie comme celle-ci :

```
1010
```

- Si un argument non valide est fourni (par exemple, une chaine de caracteres), le programme affichera un message d'erreur :

```bash
./nbinaire abc
```

```
error: The argument must be an integer between 0 and 1000
```

## Fonctions principales

Le programme utilise plusieurs fonctions pour effectuer ses taches :

- `verifierValiditeArg()` : Verifie si l'argument fourni est un entier valide entre 0 et 1000.
- `determinerBinaire()` : Genere la representation binaire d'un entier.
- `genererBinaire()` : Genere le binaire a partir du reste d'une division.
- `formaterCodeBinaire()` : Inverse la chaine binaire pour obtenir la representation correcte.

## Gestion des erreurs

Le programme gere les erreurs suivantes :

1. Si aucun argument ou plus d'un argument est fourni, un message "error: Exactly one argument must be provided" est affiche.
2. Si l'argument n'est pas un entier ou si l'entier est en dehors de [0; 1000], le message "error: The argument must be an integer between 0 and 1000" sera affiche.

## Conclusion

Nbinaire est un outil simple pour convertir des nombres entiers en binaire. Il verifie la validite des entrees et fournit des messages d'erreur clairs en cas de mauvaise utilisation.




# mystery.c

## Description

Le programme **mystery.c** permet de traiter une chaine de caracteres fournie par l'utilisateur. Il supprime les espaces superflus au debut et a la fin. Si la chaine depasse une longueur maximale definie (4086 caracteres), le programme affiche un message d'erreur et termine l'execution.

## Usage

Le programme se compile et s'execute comme suit :

### Compilation

```bash
gcc -o mystery mystery.c
```

### Execution

Pour executer le programme, utilisez la commande suivante :

```bash
./mystery
```

Le programme attendra que vous saisissiez une chaine de caracteres, puis supprimera les espaces au debut et a la fin de cette chaine. Si la chaine depasse la longueur maximale autorisee, un message d'erreur s'affichera.

### Exemples d'execution

- Pour supprimer les espaces d'une chaine saisie :

```bash
./mystery
```

Apres avoir saisi une chaine comme `  Bonjour le monde  ` et appuye sur Entree, le programme affichera :

```
Chaine apres suppression des espaces: 'Bonjour le monde'
```

- Si la chaine depasse 4086 caracteres, le programme affichera un message d'erreur :

```bash
Erreur: La chaine d'entree depasse la taille maximale autorisee (4086 caracteres)
```

## Fonctions principales

Le programme utilise plusieurs fonctions pour realiser ces operations :

- `verifier_taille_argument()` : Verifie si la chaine entree par l'utilisateur depasse la taille maximale autorisee.
- `supprimer_les_espaces()` : Supprime les espaces au debut et a la fin de la chaine.
- `supprimer_espaces_debut()` : Supprime les espaces au debut de la chaine.
- `supprimer_espaces_fin()` : Supprime les espaces a la fin de la chaine.

## Gestion des erreurs

Le programme gere les erreurs suivantes :

1. Si la chaine entree par l'utilisateur est vide, un message d'erreur "Erreur: La chaine entree est vide" sera affiche.
2. Si la chaine depasse la longueur maximale, le message "Erreur: La chaine d'entree depasse la taille maximale autorisee" sera affiche.

## Conclusion

Ce programme fournit une methode simple pour traiter les chaines de caracteres en supprimant les espaces inutiles et en gerant les erreurs de longueur excessive.



# geonames.c

## Description

Le programme **geonames.c** permet d afficher les n villes les plus peuplees dans l ordre du plus peuple au moins peuple. Il utilise des structures pour représenter les villes et les pays, et trie ces villes par population pour les afficher dans une table formatee.

Le programme prend un parametre en entree: le nombre de villes qu on veut afficher. Si aucun parametre n'est fourni ou si le nombre de villes est invalide, le programme affichera un message d'aide.

## Usage

Le programme se compile et s'execute comme suit :

### Compilation

```bash
gcc -o geonames geonames.c
```

### Execution

Pour exécuter le programme, utilisez la commande suivante :

```bash
./geonames <NOMBRE_DE_VILLES>
```

Le paramètre `<NOMBRE_DE_VILLES>` doit etre un nombre entier compris entre 1 et 5000. Si aucun argument n'est fourni ou que l argument fourni est invalide , le programme affichera un message d'aide décrivant son usage.

### Exemples d'execution

- Pour afficher les 10 villes les plus peuplees :

```bash
./geonames 10
```

Cela produira une sortie comme celle-ci :

```
Rang	Nom                        	Pays                                      	Population
----	---                        	----                                        ----------
1	Shanghai                      	China                                   	22315474
2	Beijing                       	China                                   	18960744
3	Shenzhen                      	China                                   	17494398
4	Guangzhou                     	China                                   	16096724
5	Kinshasa                      	Democratic Republic of the Congo        	16000000
6	Lagos                         	Nigeria                                 	15388000
7	Haselbachtal                  	Germany                                 	14625220
8	Chengdu                       	China                                   	13568357
9	Mumbai                        	India                                   	12691836
10	São Paulo                    	Brazil                                  	12400232

...
```

- Si le nombre de villes ou  le nombre n est pas compris entre 1 et 5000, un message d'erreur ou d'aide sera affiche :

```bash
./geonames
```

```
Usage: ./geonames <NOMBRE DE VILLES>
Affiche une table des n villes les plus peuplées sur stdout.
Le nombre de villes ne doit pas dépasser 5000.
```

## Structures utilisees

Le programme utilise deux structures principales :

- `PAYS` : represente un pays avec un nom et un code.
- `VILLE` : represente une ville avec un nom, une population et un pays auquel elle appartient.

```c
typedef struct Pays {
    char nom[50];       // Nom du pays
    char code[10];      // Code du pays
} PAYS;

typedef struct Ville {
    char nom[100];      // Nom de la ville
    long population;    // Population de la ville
    PAYS pays;          // Pays auquel appartient la ville
} VILLE;
```

## Gestion des erreurs

Le programme gere plusieurs erreurs possibles :

1. Si le nombre d'arguments est incorrect, un message "nombre arguments invalide" sera affiche.
2. Si le nombre de villes specifie est superieur à 5000, le message "nombre de ville invalide" s'affichera.

## Conclusion

Geonames est un programe qui trie es villes les plus peuple du monde dans l ordre et les affiches avec leur rang, nom, pays et population. Pour parvenir a ce resultat il suffit de de lui fournir le nombre de ville qu l on veut qu il affiche. Toutefois le nombre de ville doit etre compris entre 1  et 5000, dans le cas contraire un message d erreur s affiche suivi du mode d emploi du programme. 



# motzkin.c

## Description

Le programme **motzkin.c** permet de dessiner un chemin de Motzkin en fonction d'une serie d'etapes fournies par l'utilisateur. Les chemins sont generes en format SVG, et les etapes sont des deplacements  vers la droite, vers le haut ou vers le bas. Le programme verifie que le chemin respecte certaines contraintes et genere un message d'erreur si elles ne sont pas respecter.

## Usage

Le programme se compile et s'execute comme suit :

### Compilation

```bash
gcc -o motzkin motzkin.c
```

### Execution

Pour executer le programme, utilisez la commande suivante :

```bash
./motzkin <ETAPES>
```

Le parametre `<ETAPES>` est une sequence de lettres representant les etapes du chemin de Motzkin :

- `r` ou `R` : pas vers la droite (1,0)
- `u` ou `U` : pas montant (1,1)
- `d` ou `D` : pas descendant (1,-1)

### Exemples d'execution

- Pour dessiner un chemin de Motzkin simple :

```bash
./motzkin ruurdd
```

Cela generera un fichier SVG representant le chemin avec les etapes : droite, montant, montant, droite, descendant,descendant.

- Si une erreur se produit, par exemple si le chemin va en dessous de l'axe horizontal, un message d'erreur s'affichera :

```bash
error: the path cannot go below the horizontal axis
```

### Fonctions principales

Le programme utilise plusieurs fonctions pour realiser ces operations :

- `DessinerCheminMotzkin()` : Genere le chemin de Motzkin en fonction des etapes fournies.
- `verifierEtapes()` : Verifie la validite des etapes et s'assure qu'elles respectent les contraintes (pas de descente sous l'axe horizontal, largeur maximale de 40 ou la fin du chemin au dessus de l axe horizontal).
- `genererSVG()` : Genere un fichier SVG contenant le chemin dessine.

## Gestion des erreurs

Le programme gere les erreurs suivantes :

1. Si le nombre d'arguments est incorrect, un message "error: wrong number of arguments" sera affiche.
2. Si une etape non reconnue est fournie, le message "error: unrecognized step" sera affiche.
3. Si le chemin depasse les limites (descend sous l'axe horizontal ou est trop large), des messages d'erreur appropries seront affiches.

## Conclusion

Ce programme fournit un moyen de dessiner des chemins de Motzkin en SVG en fonction d'instructions simples. Il est utile pour visualiser ces chemins tout en verifiant les contraintes imposees par les regles du chemin de Motzkin.
