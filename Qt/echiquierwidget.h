#ifndef ECHIQUIERWIDGET_H
#define ECHIQUIERWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QTimer>
#include "../plateau.h"

class EchiquierWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EchiquierWidget(QWidget* parent = nullptr);
    void setMode(int mode);
    void nouvellePartie();

signals:
    void statusChanged(const QString& message);
    void partieTermineeSignal(const QString& message);

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

private:
    plateau jeu;
    int modeJeu;
    bool pieceSelectionnee;
    int selLig, selCol;
    int numTour;
    bool partieTerminee;

    int dernLD, dernCD, dernLA, dernCA;
    bool aDernierCoup;

    static const int TAILLE_CASE = 80;
    static const int MARGE = 30;

    QString pieceVersUnicode(int piece);
    void jouerIA();
    void verifierFinPartie();
};

#endif
