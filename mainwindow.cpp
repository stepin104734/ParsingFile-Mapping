#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "QFile"
#include "QTextStream"
#include "QDebug"
#include "QPushButton"

QMap<int, neighborlink *> neighborlinkmap;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(slot_browsed()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::FileParse()
{
    m_file.setFileName(path);
    QTextStream in(&m_file);
    QString line;
    QStringList list;
    int i=0;
    m_file.open(QFile::ReadOnly);
    while(!in.atEnd())
    {

        line = in.readLine();
        if(line.startsWith('#'))
            continue;
        if(line == "")
            continue;

        neighborlink *obj = new neighborlink();

        if(line.contains("hostname"))
        {
            list = line.split('=');
            list[1].remove(' ');
            list[1].remove('\"');
            list[1].remove(',');
            obj->hostname = list[1];
            line = in.readLine();
        }

        if(line.contains("neighborName"))
        {
            list = line.split('=');
            list[1].remove(" ");
            list[1].remove("\"");
            list[1].remove(',');
            obj->neighborName = list[1];
            line = in.readLine();
        }

        if(line.contains("hostPortId"))
        {
            list = line.split('=');
            list[1].remove(',');
            obj->hostPortId = list[1].toInt();
            line = in.readLine();
        }

        if(line.contains("neighborPortId"))
        {
            list = line.split('=');
            list[1].remove(',');
            list[1].remove(';');
            obj->neighborPortId = list[1].toInt();
        }
        neighborlinkmap.insert(i, obj);
        i++;
    }
    ui->textEdit->setText("Total LRU's are:" + QString::number(neighborlinkmap.count()));
    m_file.close();

}

void MainWindow::showMap()
{
    QMapIterator<int, neighborlink*> iterator(neighborlinkmap);
    while(iterator.hasNext())
    {
        iterator.next();
        ui->textEdit->append(QString::number(iterator.key()) + " : " + iterator.value()->hostname);
    }


}


void MainWindow::slot_browsed()
{
    path = QFileDialog::getOpenFileName();
    ui->lineEdit->setText(path);
    FileParse();
    showMap();
}



