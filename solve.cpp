#include "mainwindow.h"
#include "ui_mainwindow.h"
frac MainWindow::parse(QLineEdit *w)
{
    frac d;
    bool t;
    QRegExp rx("^(-?[0-9]+)(?:/([0-9]+))?$");

    if (rx.indexIn(w->text(), 0) != -1) {
        d = frac(rx.cap(1).toInt(), rx.cap(2).toInt());
        t = true;
    }
    else {
        t = false;
        d = 0;
    }
    w->setStyleSheet(t?"background-color:#ffffff":"background-color:#ffcccc");
    return d;
}

void MainWindow::solve()
{
    int i, j;
    int max_p = ui->spinBox->value(), max_o = ui->spinBox_2->value();
    int max_y=max_o+1, max_x=max_o+max_p+1;
    frac min;
    ui->plainTextEdit->clear();
    //Строится таблица
    for(i=0;i<max_o;i++)
    {
        basis[i]="y"+QString::number(i+1);
        for(j=0;j<max_p;j++)
        {
            m[i][j+1] = parse(le_o[i][j]);
        }
        for(j=0;j<max_o;j++)
            m[i][max_p+j+1] = (int)i==j;
        m[i][0] = parse(le_o[i][MAX]);
    }
    for(j=0;j<max_p;j++)
    {
        m[i][j+1] = -parse(le_f[j]);
    }
    for(j=0;j<max_o;j++)
        m[i][max_p+j+1]=0;
    m[i][0] = parse(le_f[MAX]);
    //Второй шаг: выбираем минимальный коэффициент и разрешающий элемент
    //минимальный коэффициент
    int min_j, min_i, c=0;
    frac buf;
    while(true)
    {
        c++;
        if(c>100)
        {
            ui->plainTextEdit->appendPlainText(QString::fromLocal8Bit("Слишком много итераций"));
            break;
        }
        min = 0;
        min_j = min_i = -1;
        for(i=1;i<max_x;i++)
        {
            if(m[max_o][i]<min){
                min=m[max_o][i];
                min_j=i;
            }
        }
        if(min_j<0)
        {
            prnt();
            ui->plainTextEdit->appendPlainText(QString::fromLocal8Bit("Решение найдено"));
            break;
        }
        min = -1;
        for(i=0;i<max_o;i++)
        {
            if(m[i][min_j]>0)
            {
                buf = m[i][0]/m[i][min_j];
                if(buf<min||min < 0)
                {
                    min = buf;
                    min_i = i;
                }
            }

        }
        if(min_i<0)
        {
            prnt();
            ui->plainTextEdit->appendPlainText(QString::fromLocal8Bit("Решений нет"));
            break;
        }
        prnt(min_i, min_j);
        //процессинг матрицы
        //замена базиса
        basis[min_i]=(min_j>max_p?"y":"x")+QString::number((min_j>max_p?min_j-max_p:min_j));
        //деление строки
        buf = m[min_i][min_j];
        for(i=0;i<max_x;i++)
        {
            if(i==min_j)
                m[min_i][i] = 1;
            else
             m[min_i][i] = m[min_i][i] / buf;
        }
        for(i=0;i<max_y;i++)
        {
            if(i!=min_i)
            {
                buf = m[i][min_j];
                for(j=0;j<max_x;j++)
                {
                    m[i][j] = m[i][j] - buf * m[min_i][j];
                }
            }
        }

    }
    ui->tabWidget->setCurrentIndex(1);
}


