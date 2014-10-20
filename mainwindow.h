#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QSpacerItem>
#include "frac.h"
namespace Ui {
    class MainWindow;
}
#define MAX 10
class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void updateInput();
    void solve();
    void random();

protected:
    void changeEvent(QEvent *e);
    QLineEdit *le_f[MAX+1];
    QLineEdit *le_o[MAX][MAX+1];
    QLabel *la_f[MAX+1][MAX+1];
    QLabel *la_y[MAX];
    QHBoxLayout *hl[MAX];
    QSpacerItem *verticalSpacer;

private:
    Ui::MainWindow *ui;
    //массивы для решения задачи
    frac m[MAX+1][2*MAX+1];
    //Rational r[MAX];
    QString basis[MAX];
    frac parse(QLineEdit*);
    void prnt(int _i = -1, int _j = -1);

};

#endif // MAINWINDOW_H
