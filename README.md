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

