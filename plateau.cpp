#include "plateau.h"
#include <cstdlib>
#include <ctime>

using namespace std;
plateau::plateau()
{
    srand(time(NULL));

    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
            ech[i][j] = 0;

    tour = -1;
    nbCoups = 0;

    initPlateau();
}
plateau::~plateau()
{
	
}

int plateau::evalCavalier(int ld,int cd,int la,int ca)
{
    if(ech[ld][cd] * ech[la][ca] > 0)
    return 0;
    if( (ld+2==la && cd+1==ca) ||
        (ld+2==la && cd-1==ca) ||
        (ld-2==la && cd+1==ca) ||
        (ld-2==la && cd-1==ca) ||
        (ld+1==la && cd+2==ca) ||
        (ld+1==la && cd-2==ca) ||
        (ld-1==la && cd+2==ca) ||
        (ld-1==la && cd-2==ca) )
    {
        return 1;
    }

    return 0;
}
int plateau::evalPion(int ld,int cd,int la,int ca)
{
    int piece = ech[ld][cd];

    if(ech[ld][cd] * ech[la][ca] > 0) return 0;

    if(piece == 1)
    {
        if(la==ld+1 && ca==cd && ech[la][ca]==0) return 1;

        if(ld==1 && la==ld+2 && ca==cd &&
           ech[ld+1][cd]==0 && ech[la][ca]==0) return 1;

        if(la==ld+1 && (ca==cd+1 || ca==cd-1) && ech[la][ca]<0) return 1;
    }

    if(piece == -1)
    {
        if(la==ld-1 && ca==cd && ech[la][ca]==0) return 1;

        if(ld==6 && la==ld-2 && ca==cd &&
           ech[ld-1][cd]==0 && ech[la][ca]==0) return 1;

        if(la==ld-1 && (ca==cd+1 || ca==cd-1) && ech[la][ca]>0) return 1;
    }

    return 0;
}
int plateau::evalTour(int ld,int cd,int la,int ca)
{
    if(ech[ld][cd] * ech[la][ca] > 0) return 0;

    if(ld == la)
    {
        int step = (ca > cd) ? 1 : -1;
        for(int j = cd + step; j != ca; j += step)
            if(ech[ld][j] != 0) return 0;

        return 1;
    }

    if(cd == ca)
    {
        int step = (la > ld) ? 1 : -1;
        for(int i = ld + step; i != la; i += step)
            if(ech[i][cd] != 0) return 0;

        return 1;
    }

    return 0;
}
int plateau::evalFou(int ld,int cd,int la,int ca)
{
    if(ech[ld][cd] * ech[la][ca] > 0)
    return 0;

    if( (la-ld == ca-cd) || (la-ld == -(ca-cd)) )
    {
        int i = ld;
        int j = cd;

        if(la > ld && ca > cd)
        {
            i++; j++;
            while(i<la && j<ca)
            {
                if(ech[i][j]!=0) return 0;
                i++; j++;
            }
        }
        else if(la > ld && ca < cd)
        {
            i++; j--;
            while(i<la && j>ca)
            {
                if(ech[i][j]!=0) return 0;
                i++; j--;
            }
        }
        else if(la < ld && ca > cd)
        {
            i--; j++;
            while(i>la && j<ca)
            {
                if(ech[i][j]!=0) return 0;
                i--; j++;
            }
        }
        else if(la < ld && ca < cd)
        {
            i--; j--;
            while(i>la && j>ca)
            {
                if(ech[i][j]!=0) return 0;
                i--; j--;
            }
        }

        return 1;
    }

    return 0;
}
int plateau::evalDame(int ld,int cd,int la,int ca)
{
    if(ech[ld][cd] * ech[la][ca] > 0)
    return 0;
    if(evalTour(ld,cd,la,ca)==1)
        return 1;

    if(evalFou(ld,cd,la,ca)==1)
        return 1;

    return 0;
}
int plateau::evalRoi(int ld,int cd,int la,int ca)
{
    if(ech[ld][cd] * ech[la][ca] > 0)
    return 0;

    if( (la==ld+1 || la==ld-1 || la==ld) &&
        (ca==cd+1 || ca==cd-1 || ca==cd) )
    {
        if(!(la==ld && ca==cd))
            return 1;
    }

    return 0;
}
int plateau::evaluation(int ld,int cd,int la,int ca)
{
    if(ld<0||ld>7||cd<0||cd>7||la<0||la>7||ca<0||ca>7)
        return 0;

    int piece = ech[ld][cd];
    int cible = ech[la][ca];

    if(piece == 0) return 0;

    if(ld==la && cd==ca) return 0;

    if(piece * cible > 0) return 0;

    switch(piece)
    {
        case  1: case -1: return evalPion(ld,cd,la,ca);
        case  2: case -2: return evalTour(ld,cd,la,ca);
        case  3: case -3: return evalFou(ld,cd,la,ca);
        case  4: case -4: return evalCavalier(ld,cd,la,ca);
        case  5: case -5: return evalDame(ld,cd,la,ca);
        case  6: case -6: return evalRoi(ld,cd,la,ca);
    }
    return 0;
}
int plateau::roiEnEchec(int couleur)
{
    int roi = couleur * 6;
    int lr = -1;
    int cr = -1;

    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(ech[i][j] == roi)
            {
                lr = i;
                cr = j;
            }
        }
    }

    if(lr == -1) return 1;

    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(ech[i][j] * couleur < 0 && evaluation(i, j, lr, cr) == 1)
            {
                return 1;
            }
        }
    }

    return 0;
}

int plateau::aMouvementLegal(int couleur)
{
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(ech[i][j] * couleur <= 0) continue;

            for(int k = 0; k < 8; k++)
            {
                for(int l = 0; l < 8; l++)
                {
                    if(ech[k][l] == -couleur * 6) continue;

                    if(evaluation(i, j, k, l) == 1)
                    {
                        int piece = ech[i][j];
                        int sauvegarde = ech[k][l];

                        ech[k][l] = piece;
                        ech[i][j] = 0;

                        int encoreEchec = roiEnEchec(couleur);

                        ech[i][j] = piece;
                        ech[k][l] = sauvegarde;

                        if(encoreEchec == 0) return 1;
                    }
                }
            }
        }
    }

    return 0;
}

int plateau::finPartie()
{
    int couleur = tour;

    if(roiEnEchec(couleur) == 1 && aMouvementLegal(couleur) == 0)
    {
        if(couleur == -1)
        {
            return -1;
        }

        return 1;
    }

    if(roiEnEchec(couleur) == 0 && aMouvementLegal(couleur) == 0)
    {
        return 2;
    }

    return 0;
}
int plateau::getTour()
{
    return tour;
}
bool plateau::deplacer(int ld,int cd,int la,int ca)
{
    if(evaluation(ld,cd,la,ca) == 0)
    {
        cout << "Mouvement invalide !" << endl;
        return false;
    }

    int piece = ech[ld][cd];
    int couleur = (piece > 0) ? 1 : -1;

    if(ech[la][ca] == 6 || ech[la][ca] == -6)
    {
        cout << "Mouvement invalide : on ne capture pas le roi." << endl;
        return false;
    }

    if(couleur != tour)
    {
        cout << "Ce n'est pas le tour de cette piece !" << endl;
        return false;
    }

    int sauvegarde = ech[la][ca];

    ech[la][ca] = ech[ld][cd];
    ech[ld][cd] = 0;

    if(roiEnEchec(couleur) == 1)
    {
        ech[ld][cd] = piece;
        ech[la][ca] = sauvegarde;
        cout << "Mouvement invalide, votre roi est en echec !" << endl;
        return false;
    }

    // Promotion du pion
    if(ech[la][ca] == 1 && la == 7)
        ech[la][ca] = 5;   // Pion noir promu en dame noire

    if(ech[la][ca] == -1 && la == 0)
        ech[la][ca] = -5;  // Pion blanc promu en dame blanche

    tour = -tour;

    return true;
}

bool plateau::estCoupLegal(int ld, int cd, int la, int ca)
{
    if(evaluation(ld, cd, la, ca) == 0) return false;

    int piece = ech[ld][cd];
    int couleur = (piece > 0) ? 1 : -1;

    if(ech[la][ca] == 6 || ech[la][ca] == -6) return false;
    if(couleur != tour) return false;

    int sauvegarde = ech[la][ca];
    ech[la][ca] = piece;
    ech[ld][cd] = 0;

    bool legal = (roiEnEchec(couleur) == 0);

    ech[ld][cd] = piece;
    ech[la][ca] = sauvegarde;

    return legal;
}

bool plateau::deplacerSilent(int ld, int cd, int la, int ca)
{
    if(evaluation(ld, cd, la, ca) == 0) return false;

    int piece = ech[ld][cd];
    int couleur = (piece > 0) ? 1 : -1;

    if(ech[la][ca] == 6 || ech[la][ca] == -6) return false;
    if(couleur != tour) return false;

    int sauvegarde = ech[la][ca];
    ech[la][ca] = ech[ld][cd];
    ech[ld][cd] = 0;

    if(roiEnEchec(couleur) == 1)
    {
        ech[ld][cd] = piece;
        ech[la][ca] = sauvegarde;
        return false;
    }

    if(ech[la][ca] == 1 && la == 7) ech[la][ca] = 5;
    if(ech[la][ca] == -1 && la == 0) ech[la][ca] = -5;

    tour = -tour;
    return true;
}

int plateau::getPiece(int i,int j)
{
	return ech[i][j];
}

void plateau::initPlateau()
{
	for(int i=2;i<=5;i++)
	{
		for(int j=0;j<=7;j++)
		{
			ech[i][j]=0;
		}
	}
	
	for(int j=0;j<=7;j++)
	{
		ech[1][j]=1;
		ech[6][j]=-1;
	}
	
	ech[0][0]=2;
	ech[0][1]=4;
	ech[0][2]=3;
	ech[0][3]=5;
	ech[0][4]=6;
	ech[0][5]=3;
	ech[0][6]=4;
	ech[0][7]=2;

	ech[7][0]=-2;
	ech[7][1]=-4;
	ech[7][2]=-3;
	ech[7][3]=-5;
	ech[7][4]=-6;
	ech[7][5]=-3;
	ech[7][6]=-4;
	ech[7][7]=-2;
		
	
}
void plateau::scannerPlateauIA()
{
    nbCoups = 0;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (ech[i][j] > 0)
            {
                for (int k = 0; k < 8; k++)
                {
                    for (int l = 0; l < 8; l++)
                    {
                        int valeur = evaluation(i, j, k, l);

                        if (valeur > 0 && nbCoups < 1000 && ech[k][l] != -6)
                        {
                            int piece = ech[i][j];
                            int sauvegarde = ech[k][l];

                            ech[k][l] = piece;
                            ech[i][j] = 0;

                            int encoreEchec = roiEnEchec(1);

                            ech[i][j] = piece;
                            ech[k][l] = sauvegarde;

                            if(encoreEchec == 0)
                            {
                                coups[nbCoups].ligDep = i;
                                coups[nbCoups].colDep = j;
                                coups[nbCoups].ligArr = k;
                                coups[nbCoups].colArr = l;
                                coups[nbCoups].poids  = valeur;
                                nbCoups++;
                            }
                        }
                    }
                }
            }
        }
    }
}

void plateau::evalMovIA()
{
    if (nbCoups == 0) return;

    for (int i = 0; i < nbCoups; i++)
    {
        switch (ech[coups[i].ligArr][coups[i].colArr])
        {
            case -1: coups[i].poids +=    5; break;
            case -2: coups[i].poids +=   50; break;
            case -3: coups[i].poids +=   20; break;
            case -4: coups[i].poids +=   30; break;
            case -5: coups[i].poids +=  100; break;
            case -6: coups[i].poids += 1000; break;
            default: break;
        }
    }

    for (int i = 0; i < nbCoups - 1; i++)
    {
        for (int j = i + 1; j < nbCoups; j++)
        {
            if (coups[i].poids < coups[j].poids)
            {
                Coup temp = coups[i];
                coups[i] = coups[j];
                coups[j] = temp;
            }
        }
    }

    int nbMeilleurs = 0;
    for (int j = 0; j < nbCoups; j++)
    {
        if (coups[j].poids == coups[0].poids)
            nbMeilleurs++;
        else
            break;
    }

    if (nbMeilleurs == 0) return;

    int choixAleatoire = rand() % nbMeilleurs;

    Coup temp = coups[0];
    coups[0] = coups[choixAleatoire];
    coups[choixAleatoire] = temp;
}
bool plateau::deplacerIA()
{
    scannerPlateauIA();

    if (nbCoups == 0)
    {
        return false;
    }

    evalMovIA();

    return deplacer(coups[0].ligDep, coups[0].colDep, coups[0].ligArr, coups[0].colArr);
}
