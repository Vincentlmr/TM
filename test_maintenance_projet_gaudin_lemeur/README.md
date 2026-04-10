        Yohann Gaudin, Vincent Le Meur 2024
        Mini-Projet Test & Maintenance IS4 2024

1. Sujet
  =======

Créer un programme qui lit un fichier et calcule la fréquence de chaque mot dans un fichier.

2. Réalisation
  =============

Pour ce projet, nous avons implémenté plusieurs fonctionnalités :

  - Un même mot avec ou sans majuscule est considéré comme le même mot par le programme.

  - Un mot adjacent à la ponctuation est compté sans les signes de ponctuation par le programme.

  - Le programme sort comme résultat dans un fichier texte une liste de mots énumérés par ordre décroissant de fréquence. En cas d'égalité de fréquence, les mots sont triés par ordre alphabétique.

  - Le programme trie les mots d'un fichier texte d'entrée et écrit le résultat dans un fichier texte de sortie, le tout en ligne de commande.

  - Les mots vides fournis pour le projet sont exclus du comptage des mots.
  
  - Une barre de chargement est visible lors de la lecture du document texte d'entrée.
  
  - L'utilisateur peut choisir son fichier texte d'entrée et aussi de sortie sans avoir à modifier le code.


3. Programme
  ============

Le projet étant réalisé en langage C, nous avons décidé d'opter pour une structure de données de liste chaînée, car elle permet une insertion efficace et un allocation dynamique.

Pour ce faire, nous avons créé plusieurs fichiers :

  - Un fichier includes/struct.h qui contient la définition de la structure de données composée d'un maillon qui contient le mot ainsi que sa fréquence et le maillon suivant, ainsi qu'une liste qui contient le nombre total de mots de la liste ainsi que le maillon de tête de la liste.

  - Dans un fichier src/struct.c se trouvent les différentes fonctions que nous avons utilisées pour répondre au sujet : 
    * init_list_char : permet d'initialiser une liste.
    * ajout_liste : permet d'ajouter un mot à la liste qui correspond aux critères du sujet ou s'il est déjà présent dedans, d'augmenter sa fréquence.
    * tri_occ : permet de retourner un tableau contenant les mots triés dans l'ordre décroissant de fréquence et par ordre alphabétique, ainsi qu'un tableau avec les fréquences triées dans le même ordre.
    * clear_liste : permet de vider la liste pour éviter toute perte.

  - Un fichier main.c:qui prend en argument 2 fichiers texte et qui va écrire dans un fichier texte la liste des mots d'un texte contenu dans l'autre fichier texte triés par ordre décroissant de fréquence et par ordre alphabétique.

  - Un fichier test unit_tests.c où l'on retrouve les différents tests que l'on a effectués.
  
    * test_init: vérifie qu'une liste est bien initialisée avec un nombre de mot de 0.
    * test_array : vérifie que l'ajout d'un mot dans une liste fonctionne.
    * test_2mot_egaux : vérifie que le même mot ne s'ajoute pas 2 fois dans la liste.
    * test_ponctauation : vérifie que que si l'on ajoute un mot avec de la ponctuation collé au début ou à la fin, la liste reconnait le mot sans la ponctuation.
    * test_tri_freq : vérifie que la fonction de tri par fréquence fonctionne correctement.
    * test_tri_mot : vérifie que la fonctionn de tri des mots fonctionne correctement.
    * test_majuscule : vérifie que si l'on ajoute un mot avec une majuscule, la liste reconnait le mot sans la majuscule.
    * test_tri_odre_alpha : vérifie que la fonction de tri fonctionne correctement lorsque les fréquence de mots sont similaires.
    * test_clear_liste : vérifie que le nombre de mot d'une liste revien à 0 après avoir utilisé clear_liste, et vérifie que le tableau des mots ordonnés après tri_occ soit vide.
  
  - Un fichier MakeFile

On retrouve de plus, les fichiers textes que l'on peut utiliser dans le programme dans le dossier fichier_texte/

  - Les fichiers d'entré avec du texte
    * histoire_courte.txt
    * test.txt
    * shakspear.txt
    * blake.txt
    * frankenstein.txt
    
  - Le fichier d'écriture du résultat : fichier_sortie.txt
  
  - La liste des mots vides : liste_mot_vide.txt
  
  - La liste des caractères spéciaux: charactere_speciaux.txt
  
4. Compilation et execution
  ==========================
  
  Pour compiler le programme il faut se trouver dans le main dans la racine du git, puis lancer les commandes :
        - make clean
        - make main
        - make tests 
        - ./build/tri_comp fichier_texte/nomdocentrée.txt fichier_texte/nomdocsortie.txt : cela permet de tester le programme
        - ./build/tri_tests : cela permet de tester les différents tests

Avec nomdocentrée le document que vous voulez analyser qui correspon à un des fichiers texte contenu dans le dossier fichier_texte/ et nomdocsortie le document où les résultats seront insérés présent aussi dans le dossier fichier_texte/.

Il est également possible de faire un make coverage afin de voir si toutes les lignes du code et si toutes les fonctions sont testées. Ici, 4 lignes ne sont pas testées. Nous supposons que ce sont celles concernant l'affichage de la bar de chargement lors de la lecture du document texte d'entrée.


Sur la pipeline .gitlab-ci.yml, la fonction valgrind est utilisée sur le fichier texte blake.txt, car c'est le seul fichier de base qui n'est pas trop volumineux, et qui permet d'utiliser cette fonction.
