#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "echiquierwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);

private slots:
    void lancerJvJ();
    void lancerJvIA();
    void updateStatus(const QString& msg);
    void afficherResultat(const QString& msg);

private:
    QStackedWidget* pages;
    EchiquierWidget* echiquier;
    QLabel* statusLabel;

    QWidget* creerPageMenu();
    QWidget* creerPageJeu();
};

#endif
