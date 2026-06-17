# ♟ Jeu d'Échecs en C++ / Qt

Un jeu d'échecs complet développé en **C++** avec une interface graphique **Qt**, réalisé dans le cadre d'un projet de 2ème année à l'ESISA.

---

## 🎮 Fonctionnalités

- ✅ **Joueur vs Joueur** — Deux joueurs sur le même écran
- ✅ **Joueur vs IA** — Affrontez une intelligence artificielle
- ✅ **Interface graphique Qt** — Plateau interactif avec clics souris
- ✅ **Version console** — Plateau ASCII jouable en terminal
- ✅ **Validation complète** — Tous les mouvements vérifiés selon les règles officielles
- ✅ **Détection d'échec / mat / pat** — Fin de partie automatique
- ✅ **Promotion du pion** — Le pion est promu en dame en dernière rangée
- ✅ **Surbrillances visuelles** — Coups valides, dernier coup, échec
- ✅ **Thème sombre élégant** — Design moderne avec palette échecs

---

## 🛠 Prérequis

- **Qt 6** (testé avec Qt 6.11.0)
- **MinGW 64-bit** ou tout compilateur C++17 compatible
- **Qt Creator** (recommandé pour la version Qt)
- **Dev C++** ou **g++** (pour la version console)

---

## 📂 Structure du Projet

```
Projet Echec/
│
├── plateau.h              # Classe plateau — déclarations (partagé Console + Qt)
├── plateau.cpp            # Classe plateau — toute la logique du jeu (partagé)
├── README.md
├── .gitignore
│
├── Console/
│   ├── main_console.cpp   # Interface console — affichage ASCII + saisie joueur
│   ├── Echecs.dev         # Fichier projet Dev C++
│   └── echecs_console.exe # Exécutable console compilé
│
└── Qt/
    ├── echecs.pro              # Fichier projet Qt (qmake)
    ├── main.cpp                # Point d'entrée Qt
    ├── mainwindow.h            # Fenêtre principale — déclarations
    ├── mainwindow.cpp          # Fenêtre principale — menu + layout
    ├── echiquierwidget.h       # Widget échiquier — déclarations
    └── echiquierwidget.cpp     # Widget échiquier — dessin + interactions
```

> **Note :** `plateau.h` et `plateau.cpp` sont à la **racine**, partagés entre les deux versions. La logique du jeu n'est écrite qu'une seule fois.

---

## 🚀 Installation et Exécution

### Version Console (Dev C++ ou g++)

1. Ouvrir un terminal dans le dossier `Projet Echec/`
2. Compiler :
   ```bash
   g++ Console/main_console.cpp plateau.cpp -o Console/echecs_console.exe -std=c++17
   ```
3. Lancer :
   ```bash
   .\Console\echecs_console.exe
   ```

**Ou** ouvrir `Console/Echecs.dev` dans Dev C++ et appuyer sur F11 (Compiler & Exécuter).

---

### Version Qt (Qt Creator)

1. Ouvrir Qt Creator
2. `Fichier → Ouvrir un fichier ou projet...` → sélectionner `Qt/echecs.pro`
3. Choisir le kit `Desktop Qt 6.11.0 MinGW 64-bit`
4. Appuyer sur ▶ (`Ctrl+R`) pour compiler et lancer

---

### 🧪 Comment tester les fonctionnalités

1. **Sélectionner le mode** : Joueur vs Joueur ou Joueur vs IA
2. **Déplacer** : Cliquer sur une pièce → les coups valides apparaissent en points gris → cliquer sur la destination
3. **Tester l'échec** : Mettre le roi adverse en danger → la case du roi s'illumine en rouge
4. **Tester le mat/pat** : Bloquer totalement le roi → boîte de dialogue de fin de partie

---

## 🧠 Architecture

Le projet suit le principe de **séparation des responsabilités** :

```
┌─────────────────────────────────┐
│     Interface Graphique (Qt)    │  mainwindow + echiquierwidget
│   - Dessin du plateau           │
│   - Gestion des clics souris    │
│   - Signaux / Slots Qt          │
├─────────────────────────────────┤
│     Interface Console           │  Console/main_console.cpp
│   - Affichage ASCII             │
│   - Saisie sécurisée            │
├─────────────────────────────────┤
│       Moteur de Jeu (C++)       │  plateau.h / plateau.cpp  ← partagé
│   - Règles de déplacement       │
│   - Détection échec/mat/pat     │
│   - Intelligence artificielle   │
└─────────────────────────────────┘
```

---

## ♟ Règles Implémentées

| Pièce | Déplacement |
|-------|-------------|
| ♙ Pion | Avance 1 (ou 2 depuis position initiale), capture en diagonale, promotion en dame |
| ♖ Tour | Lignes droites horizontales et verticales (chemin libre vérifié) |
| ♗ Fou | Diagonales (chemin libre vérifié) |
| ♘ Cavalier | Mouvement en "L" — saute par-dessus les pièces |
| ♕ Dame | Combinaison Tour + Fou |
| ♔ Roi | 1 case dans toutes les directions |

---

## 🤖 Intelligence Artificielle

L'IA utilise un algorithme d'**évaluation gloutonne** :

1. **Scanner** tous les coups légaux des Noirs (`scannerPlateauIA`)
2. **Évaluer** chaque coup selon la valeur de la pièce capturée :
   - Pion : +5 | Fou : +20 | Cavalier : +30 | Tour : +50 | Dame : +100
3. **Trier** par score décroissant
4. **Choisir** aléatoirement parmi les meilleurs coups à égalité

> L'IA regarde un coup à l'avance (algorithme glouton, sans Minimax).

---

## 🛠 Technologies Utilisées

- **Langage** : C++17
- **Framework GUI** : Qt 6 (Widgets)
- **Build System** : qmake
- **IDE** : Qt Creator / Dev C++
- **Concepts C++** : Classes, héritage, polymorphisme, encapsulation, structures, signaux/slots

---

## 👤 Auteur

- **Nom** : Hamza Dadi — Mohammed Senhaji — Ziyad El Rhermoul
- **École** : ESISA — 2ème Année
- **Année** : 2025-2026
