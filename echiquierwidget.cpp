#include "echiquierwidget.h"
#include <QPainterPath>
#include <QApplication>

EchiquierWidget::EchiquierWidget(QWidget* parent)
    : QWidget(parent), modeJeu(1), pieceSelectionnee(false),
      selLig(-1), selCol(-1), numTour(0), partieTerminee(false),
      dernLD(0), dernCD(0), dernLA(0), dernCA(0), aDernierCoup(false)
{
    setFixedSize(TAILLE_CASE * 8 + MARGE * 2, TAILLE_CASE * 8 + MARGE * 2);
    setMouseTracking(true);
}

void EchiquierWidget::setMode(int mode)
{
    modeJeu = mode;
}

void EchiquierWidget::nouvellePartie()
{
    jeu = plateau();
    pieceSelectionnee = false;
    selLig = -1;
    selCol = -1;
    numTour = 0;
    partieTerminee = false;
    aDernierCoup = false;

    QString msg = "Tour des BLANCS";
    if (jeu.roiEnEchec(jeu.getTour()))
        msg += "  |  ECHEC !";
    emit statusChanged(msg);
    update();
}

QSize EchiquierWidget::sizeHint() const
{
    return QSize(TAILLE_CASE * 8 + MARGE * 2, TAILLE_CASE * 8 + MARGE * 2);
}

QSize EchiquierWidget::minimumSizeHint() const
{
    return sizeHint();
}

QString EchiquierWidget::pieceVersUnicode(int piece)
{
    switch(piece)
    {
        case -6: return QString::fromUtf8("\u2654");  // ♔ Roi blanc
        case -5: return QString::fromUtf8("\u2655");  // ♕ Dame blanche
        case -2: return QString::fromUtf8("\u2656");  // ♖ Tour blanche
        case -3: return QString::fromUtf8("\u2657");  // ♗ Fou blanc
        case -4: return QString::fromUtf8("\u2658");  // ♘ Cavalier blanc
        case -1: return QString::fromUtf8("\u2659");  // ♙ Pion blanc

        case  6: return QString::fromUtf8("\u265A");  // ♚ Roi noir
        case  5: return QString::fromUtf8("\u265B");  // ♛ Dame noire
        case  2: return QString::fromUtf8("\u265C");  // ♜ Tour noire
        case  3: return QString::fromUtf8("\u265D");  // ♝ Fou noir
        case  4: return QString::fromUtf8("\u265E");  // ♞ Cavalier noir
        case  1: return QString::fromUtf8("\u265F");  // ♟ Pion noir

        default: return "";
    }
}

void EchiquierWidget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);

    // Fond
    painter.fillRect(rect(), QColor(30, 30, 30));

    // Cadre du plateau
    QRect cadre(MARGE - 4, MARGE - 4, TAILLE_CASE * 8 + 8, TAILLE_CASE * 8 + 8);
    painter.setPen(QPen(QColor(80, 60, 40), 3));
    painter.setBrush(QColor(60, 45, 30));
    painter.drawRoundedRect(cadre, 4, 4);

    QColor claireCouleur(240, 217, 181);   // Beige clair
    QColor fonceeCouleur(181, 136, 99);    // Marron

    QColor selectionCouleur(130, 190, 80, 160);
    QColor coupValideCouleur(0, 0, 0, 50);
    QColor dernierCoupCouleur(255, 255, 100, 80);
    QColor echecCouleur(230, 60, 60, 140);

    // Trouver le roi en echec
    int roiEchecLig = -1, roiEchecCol = -1;
    int tourActuel = jeu.getTour();
    if (jeu.roiEnEchec(tourActuel))
    {
        int roiVal = tourActuel * 6;
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                if (jeu.getPiece(i, j) == roiVal)
                { roiEchecLig = i; roiEchecCol = j; }
    }

    // Dessiner les cases
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            int x = MARGE + j * TAILLE_CASE;
            int y = MARGE + i * TAILLE_CASE;
            QRect caseRect(x, y, TAILLE_CASE, TAILLE_CASE);

            // Couleur de base
            bool caseSombre = (i + j) % 2 == 1;
            QColor couleur = caseSombre ? fonceeCouleur : claireCouleur;
            painter.fillRect(caseRect, couleur);

            // Surbrillance dernier coup
            if (aDernierCoup &&
                ((i == dernLD && j == dernCD) || (i == dernLA && j == dernCA)))
            {
                painter.fillRect(caseRect, dernierCoupCouleur);
            }

            // Surbrillance roi en echec
            if (i == roiEchecLig && j == roiEchecCol)
            {
                painter.fillRect(caseRect, echecCouleur);
            }

            // Surbrillance piece selectionnee
            if (pieceSelectionnee && i == selLig && j == selCol)
            {
                painter.fillRect(caseRect, selectionCouleur);
            }

            // Points pour les coups valides
            if (pieceSelectionnee && !partieTerminee)
            {
                if (jeu.estCoupLegal(selLig, selCol, i, j))
                {
                    int piece = jeu.getPiece(i, j);
                    if (piece == 0)
                    {
                        // Petit cercle gris au centre
                        painter.setBrush(coupValideCouleur);
                        painter.setPen(Qt::NoPen);
                        int r = TAILLE_CASE / 6;
                        painter.drawEllipse(
                            x + TAILLE_CASE / 2 - r,
                            y + TAILLE_CASE / 2 - r,
                            r * 2, r * 2);
                    }
                    else
                    {
                        // Cercle sur les coins pour capture
                        painter.setBrush(Qt::NoBrush);
                        painter.setPen(QPen(QColor(0, 0, 0, 80), 6));
                        painter.drawEllipse(caseRect.adjusted(4, 4, -4, -4));
                    }
                }
            }

            // Dessiner la piece
            int piece = jeu.getPiece(i, j);
            if (piece != 0)
            {
                QString symbole = pieceVersUnicode(piece);
                QFont font("Segoe UI Symbol", TAILLE_CASE / 2);
                font.setStyleStrategy(QFont::PreferAntialias);
                painter.setFont(font);

                // Ombre
                painter.setPen(QColor(0, 0, 0, 80));
                painter.drawText(caseRect.adjusted(2, 2, 2, 2),
                                 Qt::AlignCenter, symbole);

                // Piece
                if (piece > 0)
                    painter.setPen(QColor(40, 40, 40));
                else
                    painter.setPen(QColor(255, 255, 255));

                painter.drawText(caseRect, Qt::AlignCenter, symbole);
            }
        }
    }

    // Coordonnees (a-h, 1-8)
    painter.setFont(QFont("Segoe UI", 11, QFont::Bold));
    painter.setPen(QColor(180, 170, 160));

    for (int j = 0; j < 8; j++)
    {
        QString lettre = QString(QChar('a' + j));
        int x = MARGE + j * TAILLE_CASE + TAILLE_CASE / 2 - 5;

        painter.drawText(x, MARGE - 8, lettre);
        painter.drawText(x, MARGE + TAILLE_CASE * 8 + 18, lettre);
    }

    for (int i = 0; i < 8; i++)
    {
        QString num = QString::number(8 - i);
        int y = MARGE + i * TAILLE_CASE + TAILLE_CASE / 2 + 5;

        painter.drawText(MARGE - 20, y, num);
        painter.drawText(MARGE + TAILLE_CASE * 8 + 8, y, num);
    }
}

void EchiquierWidget::mousePressEvent(QMouseEvent* event)
{
    if (partieTerminee) return;

    int x = event->pos().x() - MARGE;
    int y = event->pos().y() - MARGE;

    if (x < 0 || y < 0 || x >= TAILLE_CASE * 8 || y >= TAILLE_CASE * 8)
        return;

    int col = x / TAILLE_CASE;
    int lig = y / TAILLE_CASE;

    int couleurActuelle = jeu.getTour();

    // Mode IA : bloquer les clics pendant le tour de l'IA
    if (modeJeu == 2 && couleurActuelle == 1)
        return;

    if (!pieceSelectionnee)
    {
        int piece = jeu.getPiece(lig, col);
        if (piece == 0) return;

        int couleurPiece = (piece > 0) ? 1 : -1;
        if (couleurPiece != couleurActuelle) return;

        pieceSelectionnee = true;
        selLig = lig;
        selCol = col;
        update();
    }
    else
    {
        // Si on clique sur la meme case : deselectionner
        if (lig == selLig && col == selCol)
        {
            pieceSelectionnee = false;
            update();
            return;
        }

        // Si on clique sur une autre piece de la meme couleur : re-selectionner
        int piece = jeu.getPiece(lig, col);
        if (piece != 0)
        {
            int couleurPiece = (piece > 0) ? 1 : -1;
            if (couleurPiece == couleurActuelle)
            {
                selLig = lig;
                selCol = col;
                update();
                return;
            }
        }

        // Tenter le deplacement
        if (jeu.deplacerSilent(selLig, selCol, lig, col))
        {
            dernLD = selLig;
            dernCD = selCol;
            dernLA = lig;
            dernCA = col;
            aDernierCoup = true;
            numTour++;

            pieceSelectionnee = false;
            update();
            verifierFinPartie();

            // Tour de l'IA
            if (!partieTerminee && modeJeu == 2 && jeu.getTour() == 1)
            {
                QTimer::singleShot(400, this, &EchiquierWidget::jouerIA);
            }
        }
        else
        {
            pieceSelectionnee = false;
            update();
        }
    }
}

void EchiquierWidget::jouerIA()
{
    if (partieTerminee) return;

    if (jeu.deplacerIA())
    {
        numTour++;
        aDernierCoup = true;
        update();
        verifierFinPartie();
    }
    else
    {
        verifierFinPartie();
    }
}

void EchiquierWidget::verifierFinPartie()
{
    int resultat = jeu.finPartie();

    if (resultat != 0)
    {
        partieTerminee = true;
        QString msg;
        if (resultat == 1)
            msg = "Echec et mat ! Les BLANCS ont gagne !";
        else if (resultat == -1)
            msg = "Echec et mat ! Les NOIRS ont gagne !";
        else if (resultat == 2)
            msg = "Match nul (pat) !";

        emit statusChanged(msg);
        emit partieTermineeSignal(msg);
        update();
        return;
    }

    QString tourMsg = (jeu.getTour() == -1) ? "Tour des BLANCS" : "Tour des NOIRS";
    if (jeu.roiEnEchec(jeu.getTour()))
        tourMsg += "  |  ECHEC !";

    emit statusChanged(tourMsg);
}
