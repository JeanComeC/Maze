# Maze

## Concept
**Maze** est un projet implémentant un générateur de labyrinthes en C, basé sur l'algorithme Randomized Depth-First Search (RDFS). Le labyrinthe est représenté sous forme de grille de cellules reliées entre elles. Une fois généré, le labyrinthe peut être résolu par trois algorithmes au choix : BFS, Dijkstra, ou A*. Le programme s'exécute en ligne de commande en précisant les dimensions souhaitées.

## Structure des Fichiers
Le projet est organisé comme suit :

- **src/** : Répertoire contenant les fichiers source du projet.
  - **main.c** : Point d'entrée du programme, responsable de l'initialisation, de la génération et de la résolution du Labyrinthe.
  - **rdfs_generator.c** : Contient les fonctions pour initialiser et générer le Labyrinthe,  et pour l'afficher.
  - **resolver_breadthfirstsearch.c** : Contient toutes les fonctions relatives à l'algorithme Breadth First Search (BFS).
  - **resolver_djikstra.c** : Contient toutes les fonctions relatives à l'algorithme Djikstra.
  - **resolver_a.c** : Contient toutes les fonctions relatives à l'algorithme A*.
  - **rdfs_generator.h**, **resolver_breadthfirstsearch.h**, **resolver_djikstra.h**, **resolver_a.h** : Headerfiles définissant les structures (`Cell`, `Grid`, `Position`, ...), les macros, les prototypes des fonctions, et incluant les bibliothèques nécessaires.

- **Makefile** : Simplifie la compilation du projet.
- **.gitignore** : Liste les fichiers et dossiers à exclure du suivi Git, comme les fichiers compilés (.o, .exe) afin de ne pas les versionner.
- **README.md** : Ce fichier, décrivant le projet, sa structure, et les instructions d'exécution.

## Prérequis
- Un compilateur C (ex. : `gcc`).
- Un système compatible POSIX (Linux, macOS, ou Windows avec WSL/MinGW).
- La bibliothèque standard C. (voir Notes pour mises à jour).

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
- Arbitrairement, l'entrée du Labyrinthe se situe en bas à gauche, et la sortie en haut à droite.
- Le programme se termine lorsque l'algorithme choisit par l'utilisateur a fini de résoudre le Labyrinthe.
- Si vous n'avez pas fait les mises à jour, faites-les, avant de compiler le programme, avec la commande :
   ```bash
   sudo apt update && sudo apt upgrade && sudo apt autoremove && sudo apt clean
   ```
- Si vous voulez supprimer les fichiers compilés (.o, .exe) de votre machine, faites-le avec la commande :
   ```bash
   make clean
   ```
- Si vous voulez supprimer tout mon projet de votre machine, faites-le avec la commande :
   ```bash
   cd ..
   rm -rf Maze
   ```