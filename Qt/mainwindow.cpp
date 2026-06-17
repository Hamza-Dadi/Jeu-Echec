#include "mainwindow.h"
#include <QFont>
#include <QMessageBox>
#include <QGraphicsDropShadowEffect>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    setWindowTitle("Jeu d'Echecs C++");
    setFixedSize(740, 780);
    setStyleSheet(
        "QMainWindow { background-color: #1e1e1e; }"
    );

    pages = new QStackedWidget(this);
    setCentralWidget(pages);

    pages->addWidget(creerPageMenu());
    pages->addWidget(creerPageJeu());

    pages->setCurrentIndex(0);
}

QWidget* MainWindow::creerPageMenu()
{
    QWidget* page = new QWidget();
    page->setStyleSheet("background-color: #1e1e1e;");

    QVBoxLayout* layout = new QVBoxLayout(page);
    layout->setAlignment(Qt::AlignCenter);
    layout->setSpacing(20);

    // Titre
    QLabel* titre = new QLabel("JEU D'ECHECS");
    titre->setAlignment(Qt::AlignCenter);
    titre->setStyleSheet(
        "QLabel {"
        "  color: #f0d9b5;"
        "  font-size: 42px;"
        "  font-weight: bold;"
        "  font-family: 'Georgia', serif;"
        "  padding: 20px;"
        "}"
    );
    layout->addWidget(titre);

    // Sous-titre avec pieces Unicode
    QLabel* deco = new QLabel(QString::fromUtf8("\u265A \u2655 \u265C \u2657 \u265E \u2659"));
    deco->setAlignment(Qt::AlignCenter);
    deco->setStyleSheet(
        "QLabel { color: #b58863; font-size: 36px; padding-bottom: 30px; }"
    );
    layout->addWidget(deco);

    QString btnStyle =
        "QPushButton {"
        "  background-color: #b58863;"
        "  color: #1e1e1e;"
        "  font-size: 18px;"
        "  font-weight: bold;"
        "  font-family: 'Segoe UI', sans-serif;"
        "  padding: 15px 50px;"
        "  border: none;"
        "  border-radius: 8px;"
        "  min-width: 280px;"
        "}"
        "QPushButton:hover {"
        "  background-color: #d4a86a;"
        "}"
        "QPushButton:pressed {"
        "  background-color: #956b47;"
        "}";

    QPushButton* btnJvJ = new QPushButton("Joueur vs Joueur");
    btnJvJ->setStyleSheet(btnStyle);
    btnJvJ->setCursor(Qt::PointingHandCursor);
    connect(btnJvJ, &QPushButton::clicked, this, &MainWindow::lancerJvJ);
    layout->addWidget(btnJvJ, 0, Qt::AlignCenter);

    QPushButton* btnJvIA = new QPushButton("Joueur vs IA");
    btnJvIA->setStyleSheet(btnStyle);
    btnJvIA->setCursor(Qt::PointingHandCursor);
    connect(btnJvIA, &QPushButton::clicked, this, &MainWindow::lancerJvIA);
    layout->addWidget(btnJvIA, 0, Qt::AlignCenter);

    // Credits
    QLabel* credits = new QLabel("Projet C++ - ESISA 2eme Annee");
    credits->setAlignment(Qt::AlignCenter);
    credits->setStyleSheet(
        "QLabel { color: #666; font-size: 13px; padding-top: 40px; }"
    );
    layout->addWidget(credits);

    return page;
}

QWidget* MainWindow::creerPageJeu()
{
    QWidget* page = new QWidget();
    page->setStyleSheet("background-color: #1e1e1e;");

    QVBoxLayout* layout = new QVBoxLayout(page);
    layout->setAlignment(Qt::AlignCenter);
    layout->setSpacing(10);

    // Barre de statut en haut
    statusLabel = new QLabel("Tour des BLANCS");
    statusLabel->setAlignment(Qt::AlignCenter);
    statusLabel->setStyleSheet(
        "QLabel {"
        "  color: #f0d9b5;"
        "  font-size: 20px;"
        "  font-weight: bold;"
        "  font-family: 'Segoe UI', sans-serif;"
        "  padding: 8px 20px;"
        "  background-color: #2a2a2a;"
        "  border-radius: 6px;"
        "}"
    );
    layout->addWidget(statusLabel);

    // Echiquier
    echiquier = new EchiquierWidget();
    connect(echiquier, &EchiquierWidget::statusChanged,
            this, &MainWindow::updateStatus);
    connect(echiquier, &EchiquierWidget::partieTermineeSignal,
            this, &MainWindow::afficherResultat);
    layout->addWidget(echiquier, 0, Qt::AlignCenter);

    // Boutons en bas
    QHBoxLayout* btnLayout = new QHBoxLayout();
    btnLayout->setSpacing(15);

    QString btnStyle =
        "QPushButton {"
        "  background-color: #3a3a3a;"
        "  color: #ccc;"
        "  font-size: 14px;"
        "  font-family: 'Segoe UI', sans-serif;"
        "  padding: 10px 25px;"
        "  border: 1px solid #555;"
        "  border-radius: 6px;"
        "}"
        "QPushButton:hover {"
        "  background-color: #4a4a4a;"
        "  color: #fff;"
        "}";

    QPushButton* btnNouvelle = new QPushButton("Nouvelle Partie");
    btnNouvelle->setStyleSheet(btnStyle);
    btnNouvelle->setCursor(Qt::PointingHandCursor);
    connect(btnNouvelle, &QPushButton::clicked, echiquier, &EchiquierWidget::nouvellePartie);
    btnLayout->addWidget(btnNouvelle);

    QPushButton* btnMenu = new QPushButton("Retour au Menu");
    btnMenu->setStyleSheet(btnStyle);
    btnMenu->setCursor(Qt::PointingHandCursor);
    connect(btnMenu, &QPushButton::clicked, [this]() {
        pages->setCurrentIndex(0);
    });
    btnLayout->addWidget(btnMenu);

    layout->addLayout(btnLayout);

    return page;
}

void MainWindow::lancerJvJ()
{
    echiquier->setMode(1);
    echiquier->nouvellePartie();
    pages->setCurrentIndex(1);
}

void MainWindow::lancerJvIA()
{
    echiquier->setMode(2);
    echiquier->nouvellePartie();
    pages->setCurrentIndex(1);
}

void MainWindow::updateStatus(const QString& msg)
{
    statusLabel->setText(msg);

    if (msg.contains("ECHEC"))
        statusLabel->setStyleSheet(
            "QLabel {"
            "  color: #ff6b6b; font-size: 20px; font-weight: bold;"
            "  font-family: 'Segoe UI'; padding: 8px 20px;"
            "  background-color: #3a2020; border-radius: 6px;"
            "}"
        );
    else if (msg.contains("gagne") || msg.contains("nul"))
        statusLabel->setStyleSheet(
            "QLabel {"
            "  color: #66bb6a; font-size: 20px; font-weight: bold;"
            "  font-family: 'Segoe UI'; padding: 8px 20px;"
            "  background-color: #203a20; border-radius: 6px;"
            "}"
        );
    else
        statusLabel->setStyleSheet(
            "QLabel {"
            "  color: #f0d9b5; font-size: 20px; font-weight: bold;"
            "  font-family: 'Segoe UI'; padding: 8px 20px;"
            "  background-color: #2a2a2a; border-radius: 6px;"
            "}"
        );
}

void MainWindow::afficherResultat(const QString& msg)
{
    QMessageBox box(this);
    box.setWindowTitle("Fin de la partie");
    box.setText(msg);
    box.setStyleSheet(
        "QMessageBox { background-color: #2a2a2a; }"
        "QMessageBox QLabel { color: #f0d9b5; font-size: 16px; }"
        "QPushButton { background-color: #b58863; color: #1e1e1e;"
        "  padding: 8px 20px; border-radius: 4px; font-weight: bold; }"
        "QPushButton:hover { background-color: #d4a86a; }"
    );
    box.exec();
}
