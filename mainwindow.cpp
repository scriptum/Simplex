#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int i, j;
    la_f[0][0] = new QLabel(ui->scrollArea);
    la_f[0][0]->setText("max f(x) =");
    la_f[0][0]->setMinimumWidth(60);
    ui->horizontalLayout_2->addWidget(la_f[0][0]);
    for(i=0;i<MAX;i++)
    {
        le_f[i] = new QLineEdit(ui->scrollArea);
        le_f[i]->setMinimumWidth(60);
        ui->horizontalLayout_2->addWidget(le_f[i]);
        la_f[0][i+1] = new QLabel(ui->scrollArea);
        la_f[0][i+1]->setText("x"+QString::number(i+1)+" +");
        ui->horizontalLayout_2->addWidget(la_f[0][i+1]);
    }
    le_f[i] = new QLineEdit(ui->scrollArea);
    le_f[i]->setMinimumWidth(60);
    ui->horizontalLayout_2->addWidget(le_f[i]);
    for(i=0;i<MAX;i++)
    {
        hl[i] = new QHBoxLayout();
        ui->verticalLayout_4->addLayout(hl[i]);
        la_f[i+1][0] = new QLabel(ui->scrollArea);
        la_f[i+1][0]->setText("y"+QString::number(i+1) + " =         -(");
        la_f[i+1][0]->setMinimumWidth(60);
        hl[i]->addWidget(la_f[i+1][0]);
        for(j=0;j<MAX;j++)
        {
            le_o[i][j] = new QLineEdit(ui->scrollArea);
            le_o[i][j]->setMinimumWidth(60);
            hl[i]->addWidget(le_o[i][j]);
            la_f[i+1][j+1] = new QLabel(ui->scrollArea);
            la_f[i+1][j+1]->setText("x"+QString::number(j+1)+" +");
            hl[i]->addWidget(la_f[i+1][j+1]);
        }
        le_o[i][j] = new QLineEdit(ui->scrollArea);
        le_o[i][j]->setMinimumWidth(60);
        hl[i]->addWidget(le_o[i][j]);
    }
    verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    ui->verticalLayout_4->addItem(verticalSpacer);


    updateInput();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}


void MainWindow::updateInput()
{
    int i, j;
    bool t;
    for(i=0;i<MAX;i++)
    {
        t=i<ui->spinBox->value();
        le_f[i]->setVisible(t);
        la_f[0][i+1]->setVisible(t);
        for(j=0;j<MAX;j++)
        {
            t=i<ui->spinBox_2->value()&&j<ui->spinBox->value();
            la_f[i+1][j+1]->setVisible(t);
            le_o[i][j]->setVisible(t);
            la_f[i+1][j+1]->setText("x"+QString::number(j+1)+(j+1==ui->spinBox->value()?") +":" +"));
        }
        t=i<ui->spinBox_2->value();
        la_f[i+1][0]->setVisible(t);
        le_o[i][10]->setVisible(t);
    }
}

void MainWindow::prnt(int _i, int _j)
{
    int i, j;
    int max_p = ui->spinBox->value(), max_o = ui->spinBox_2->value();
    QString s;
    s = (QString::fromLocal8Bit("Базис\tСвоб. пер.\t"));
    for(i=0;i<max_p;i++)
    {
        s+="x"+QString::number(i+1)+"\t";
    }
    for(i=0;i<max_o;i++)
    {
        s+="y"+QString::number(i+1)+"\t";
    }
    s+="\n";
    for(i=0;i<max_o;i++)
    {
        s += basis[i]+"\t";
        for(j=0;j<max_p+max_o+1;j++)
        {
            s+=m[i][j].str()+(i==_i&&j==_j?"<-":"")+"\t";
        }
        s+="\n";
    }
    s += "f(x)\t";
    for(j=0;j<max_p+max_o+1;j++)
    {
        s+=m[i][j].str()+"\t";
    }
    s+="\n";
    ui->plainTextEdit->appendPlainText(s);
}
void MainWindow::random()
{
    int i, j;
    int max_p = ui->spinBox->value(), max_o = ui->spinBox_2->value();
    for(i=0;i<max_o;i++)
    {
        for(j=0;j<max_p;j++)
        {
            le_o[i][j]->setText(QString::number(qrand()%19));
        }
        le_o[i][MAX]->setText(QString::number(qrand()%19));

    }
    for(j=0;j<max_p;j++)
        le_f[j]->setText(QString::number(qrand()%19));
    le_f[MAX]->setText(QString::number(qrand()%19));
}
