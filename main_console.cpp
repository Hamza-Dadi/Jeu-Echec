#include <iostream>
#include <limits>
#include "plateau.h"

using namespace std;

void afficher(plateau& p)
{
    cout << endl;
    cout << "     0    1    2    3    4    5    6    7" << endl;
    cout << "  +----+----+----+----+----+----+----+----+" << endl;

    for (int i = 0; i <= 7; i++)
    {
        cout << i << " |";

        for (int j = 0; j <= 7; j++)
        {
            switch (p.getPiece(i, j))
            {
                case  0: cout << " .. "; break;

                case  1: cout << " PN "; break;
                case  2: cout << " TN "; break;
                case  3: cout << " FN "; break;
                case  4: cout << " CN "; break;
                case  5: cout << " DN "; break;
                case  6: cout << " RN "; break;

                case -1: cout << " PB "; break;
                case -2: cout << " TB "; break;
                case -3: cout << " FB "; break;
                case -4: cout << " CB "; break;
                case -5: cout << " DB "; break;
                case -6: cout << " RB "; break;

                default: cout << " ?? "; break;
            }
            cout << "|";
        }

        cout << " " << i << endl;
        cout << "  +----+----+----+----+----+----+----+----+" << endl;
    }

    cout << "     0    1    2    3    4    5    6    7" << endl;
    cout << endl;
}

int menu()
{
    int choix;
    cout << "==============================" << endl;
    cout << "      JEU D'ECHECS C++        " << endl;
    cout << "==============================" << endl;
    cout << " 1 - Joueur vs Joueur         " << endl;
    cout << " 2 - Joueur vs IA             " << endl;
    cout << "==============================" << endl;
    cout << " Votre choix : ";
    cin  >> choix;
    cout << endl;
    return choix;
}

void afficherResultat(int resultat)
{
    cout << endl;
    cout << "==============================" << endl;
    if (resultat == 1)
        cout << "  Les BLANCS ont gagne !      " << endl;
    else if (resultat == -1)
        cout << "  Les NOIRS ont gagne !       " << endl;
    else if (resultat == 2)
        cout << "  Match nul !                 " << endl;
    cout << "==============================" << endl;
}

bool lireEntier(int& valeur)
{
    if (!(cin >> valeur))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  Entree invalide. Veuillez entrer un nombre." << endl;
        return false;
    }
    return true;
}

bool jouerTour(plateau& p, int couleur)
{
    string nomCouleur = (couleur == -1) ? "BLANCS" : "NOIRS";
    cout << "--- Tour des " << nomCouleur << " ---" << endl;

    int ligDepart, colDepart, ligArrivee, colArrivee;
    bool ok = false;

    while (!ok)
    {
        cout << "  Piece  - Ligne (0-7) : ";
        if (!lireEntier(ligDepart)) continue;

        cout << "  Piece  - Colonne (0-7) : ";
        if (!lireEntier(colDepart)) continue;

        if (ligDepart < 0 || ligDepart > 7 || colDepart < 0 || colDepart > 7)
        {
            cout << "  Coordonnees hors du plateau." << endl;
            continue;
        }

        int piece = p.getPiece(ligDepart, colDepart);

        if ((couleur == -1 && piece >= 0) || (couleur == 1 && piece <= 0))
        {
            cout << "  Piece invalide. Choisissez une piece " << nomCouleur << "." << endl;
            continue;
        }

        cout << "  Dest   - Ligne (0-7) : ";
        if (!lireEntier(ligArrivee)) continue;

        cout << "  Dest   - Colonne (0-7) : ";
        if (!lireEntier(colArrivee)) continue;

        if (ligArrivee < 0 || ligArrivee > 7 || colArrivee < 0 || colArrivee > 7)
        {
            cout << "  Destination invalide." << endl;
            continue;
        }

        if (ligArrivee == ligDepart && colArrivee == colDepart)
        {
            cout << "  Vous n'avez pas bouge." << endl;
            continue;
        }

        ok = true;
    }

    return p.deplacer(ligDepart, colDepart, ligArrivee, colArrivee);
}

int main()
{
    int choix = menu();

    plateau p;

    int numTour = 0;
    int resultat = 0;

    if (choix == 1)
    {
        cout << " Blancs = pieces negatives (PB TB FB CB DB RB)" << endl;
        cout << " Noirs  = pieces positives (PN TN FN CN DN RN)" << endl;
        cout << endl;

        while ((resultat = p.finPartie()) == 0)
        {
            afficher(p);

            int couleur = (numTour % 2 == 0) ? -1 : 1;

            if (jouerTour(p, couleur))
            {
                numTour++;
            }
        }
    }
    else
    {
        cout << " Vous jouez les BLANCS (PB TB FB CB DB RB)" << endl;
        cout << " L'IA joue  les NOIRS  (PN TN FN CN DN RN)" << endl;
        cout << endl;

        while ((resultat = p.finPartie()) == 0)
        {
            afficher(p);

            if (numTour % 2 == 0)
            {
                if (jouerTour(p, -1))
                {
                    numTour++;
                }
            }
            else
            {
                cout << "--- Tour de l'IA (NOIRS) ---" << endl;
                if (p.deplacerIA())
                {
                    cout << "  L'IA a joue." << endl;
                    numTour++;
                }
                else
                {
                    cout << "  L'IA ne trouve aucun coup." << endl;
                    resultat = p.finPartie();
                    break;
                }
            }
        }
    }

    afficher(p);
    afficherResultat(resultat);

    return 0;
}
