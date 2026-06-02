# ♟ Jeu d'Échecs en C++ / Qt

Un jeu d'échecs complet développé en **C++** avec une interface graphique **Qt**, réalisé dans le cadre d'un projet de 2ème année à l'ESISA.

---

## 🎮 Fonctionnalités

- ✅ **Joueur vs Joueur** — Deux joueurs sur le même écran
- ✅ **Joueur vs IA** — Affrontez une intelligence artificielle
- ✅ **Interface graphique Qt** — Plateau interactif avec clics souris
- ✅ **Validation complète** — Tous les mouvements sont vérifiés selon les règles officielles
- ✅ **Détection d'échec / mat / pat** — Fin de partie automatique
- ✅ **Promotion du pion** — Le pion est promu en dame en dernière rangée
- ✅ **Surbrillances visuelles** — Coups valides, dernier coup, échec
- ✅ **Thème sombre élégant** — Design moderne avec palette échecs

---

## 🛠 Prérequis

- **Qt 6** (testé avec Qt 6.11.0)
- **MinGW 64-bit** ou tout compilateur C++17 compatible
- **Qt Creator** (recommandé)

---

## 🚀 Installation et Exécution (Comment tester)

### Avec Qt Creator (Méthode Recommandée)

1. **Ouvrir le projet** : Lancez Qt Creator, allez dans `Fichier -> Ouvrir un fichier ou projet...` et sélectionnez le fichier `echecs.pro`.
2. **Configurer le projet** : Choisissez le kit de compilation (ex: `Desktop Qt 6.11.0 MinGW 64-bit`) et cliquez sur "Configure Project".
3. **Compiler et Lancer** : Appuyez sur le bouton vert ▶ (ou `Ctrl+R` / `Cmd+R`) en bas à gauche pour compiler le code et lancer l'interface graphique.

### En ligne de commande (Console C++)

Si vous souhaitez tester la logique pure du jeu sans l'interface graphique Qt, vous pouvez utiliser la version console fournie :

1. Ouvrez un terminal dans le dossier du projet.
2. Compilez les fichiers avec `g++` :
   ```bash
   g++ -o echecs_console main_console.cpp plateau.cpp -std=c++17
   ```
3. Exécutez le programme généré :
   ```bash
   ./echecs_console
   ```

### 🧪 Comment tester les fonctionnalités

Une fois le jeu lancé :
1. **Sélectionnez le mode** Joueur vs Joueur (pour tester avec un ami) ou Joueur vs IA (pour tester l'algorithme).
2. **Déplacement** : Cliquez sur une pièce (les coups valides s'affichent avec des points gris), puis cliquez sur une case de destination.
3. **Échec** : Mettez le roi adverse en danger. Vous verrez la case du roi s'illuminer en rouge et la barre de statut indiquera "ECHEC !".
4. **Mat/Pat** : Essayez de bloquer totalement le roi adverse pour vérifier que la boîte de dialogue de fin de partie s'affiche correctement annonçant le vainqueur ou le match nul.

---

## 📂 Structure du Projet

```
jeu-echecs-cpp/
│
├── echecs.pro              # Fichier projet Qt (qmake)
├── main.cpp                # Point d'entrée (Qt)
├── main_console.cpp        # Point d'entrée (version console)
│
├── plateau.h               # Classe plateau — déclarations
├── plateau.cpp             # Classe plateau — logique du jeu
│
├── mainwindow.h            # Fenêtre principale — déclarations
├── mainwindow.cpp          # Fenêtre principale — menu + layout
│
├── echiquierwidget.h       # Widget échiquier — déclarations
├── echiquierwidget.cpp     # Widget échiquier — dessin + interactions
│
├── .gitignore              # Fichiers ignorés par Git
└── README.md               # Ce fichier
```

---

## 🧠 Architecture

Le projet suit le principe de **séparation des responsabilités** :

```
┌─────────────────────────────────┐
│     Interface Graphique (Qt)    │  mainwindow + echiquierwidget
│   - Dessin du plateau           │
│   - Gestion des clics souris    │
│   - Affichage des surbrillances │
├─────────────────────────────────┤
│       Moteur de Jeu (C++)       │  plateau.h / plateau.cpp
│   - Règles de déplacement       │
│   - Détection échec/mat/pat     │
│   - Intelligence artificielle   │
└─────────────────────────────────┘
```

---

## ♟ Règles Implémentées

| Pièce | Déplacement |
|-------|-------------|
| ♙ Pion | Avance 1 (ou 2 depuis position initiale), capture en diagonale, promotion |
| ♖ Tour | Lignes droites horizontales et verticales |
| ♗ Fou | Diagonales |
| ♘ Cavalier | Mouvement en "L" (saute par-dessus) |
| ♕ Dame | Combinaison Tour + Fou |
| ♔ Roi | 1 case dans toutes les directions |

---

## 🤖 Intelligence Artificielle

L'IA utilise un algorithme d'**évaluation simple** :

1. **Scanner** tous les coups légaux possibles
2. **Évaluer** chaque coup (bonus si capture d'une pièce de grande valeur)
3. **Sélectionner** aléatoirement parmi les meilleurs coups

---

## 🛠 Technologies Utilisées

- **Langage** : C++17
- **Framework GUI** : Qt 6 (Widgets)
- **Build System** : qmake
- **IDE** : Qt Creator
- **Concepts C++** : Classes, héritage, polymorphisme, encapsulation, structures

---

## 👤 Auteur

- **Nom** : Hamza Dadi-Mohammed Senhaji-Ziyad El Rhermoul
- **École** : ESISA — 2ème Année
- **Année** : 2025-2026

