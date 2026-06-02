
#ifndef PLATEAU_H
#define PLATEAU_H

#include <iostream>
#include <string>
#include <vector>

struct Coup
{
    int ligDep, colDep, ligArr, colArr, poids;
};

class plateau
{
    public:
        plateau();
        ~plateau();

        bool deplacer(int ld, int cd, int la, int ca);
        void initPlateau();
        int getPiece(int i, int j);
        int evaluation(int ld, int cd, int la, int ca);
        int evalCavalier(int ld, int cd, int la, int ca);
        int evalPion(int ld, int cd, int la, int ca);
        int evalTour(int ld, int cd, int la, int ca);
        int evalFou(int ld, int cd, int la, int ca);
        int evalDame(int ld, int cd, int la, int ca);
        int evalRoi(int ld, int cd, int la, int ca);
        int roiEnEchec(int couleur);
        int aMouvementLegal(int couleur);
        int finPartie();
        bool estCoupLegal(int ld, int cd, int la, int ca);
        bool deplacerSilent(int ld, int cd, int la, int ca);
        int getTour();
        void scannerPlateauIA();
        void evalMovIA();
        bool deplacerIA();

    private:
        int ech[8][8];
        int tour;
        Coup coups[1000];
        int nbCoups;
};

#endif
