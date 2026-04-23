# Maze

## Concept
**Maze** est un projet. Randomized Depth-First Search. L'objectif de ce mini-projet est de concevoir un générateur de labyrinthes. Il permettra de mettre en pratique les notions d'arbres vues précédemment, et de développer des algorithmes plus complexes.

## Structure des Fichiers
Le projet est organisé comme suit :

- **src/** : Répertoire contenant les fichiers source du projet.
  - **main.c** : Point d'entrée du programme, responsable de l'initialisation, de la génération et de la résolution du Labyrinthe.
  - **rdfs_generator.c** : Contient les fonctions pour initialiser et générer le Labyrinthe,  et pour l'afficher.
  - **resolver_breadthfirstsearch.c** : Contient toutes les fonctions relatives à l'algorithme Breadth First Search (BFS).
  - **resolver_djikstra.c** : ...
  - **resolver_a.c** : ...
  - **rdfs_generator.h**, **resolver_breadthfirstsearch.h**, **resolver_djikstra.h**, **resolver_a.h** : Headerfiles définissant les structures (`Cell`, `Grid`, `Position`), les macros, les prototypes des fonctions, et incluant les bibliothèques nécessaires.

- **Makefile** : Simplifie la compilation du projet.
- **.gitignore** : ...
- **README.md** : Ce fichier, décrivant le projet, sa structure, et les instructions d'exécution.

## Prérequis
- Un compilateur C (ex. : `gcc`).
- Un système compatible POSIX (Linux, macOS, ou Windows avec WSL/MinGW).
- La bibliothèque standard C. (voir Notes pour installation)

## Instructions pour lancer le programme
1. **Cloner le dépôt** :
   ```bash
   git clone https://github.com/JeanComeC/Maze.git
   cd Maze
   ```

2. **Compiler le programme** :
   Avec le `Makefile` :
   ```bash
   make
   ```

3. **Lancer le programme** :
   Exécutez le binaire généré, en s'assurant de mettre les dimensions :
   ```bash
   ./maze.exe HEIGHT WIDTH
   ```

## Notes
- Assurez-vous que `HEIGHT` et `WIDTH` soient correctement mis au lancement et qu'ils ne dépassent pas les capacités de votre machine. Vous pouvez modifier les macros `SIZE_HEIGHT_MAX` et `SIZE_WIDTH_MAX` prévues à cet effet.
- Si vous n'avez pas fait les mises à jour, faites-les, avant de compiler le programme, avec la commande :
   ```bash
   sudo apt update && sudo apt upgrade && sudo apt autoremove && sudo apt clean
   ```
- Le programme se termine lorsque l'algorithme choisit par l'utilisateur a fini de résoudre le Labyrinthe.