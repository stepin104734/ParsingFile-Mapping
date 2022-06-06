#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void FileParse();
    void showMap();
    Ui::MainWindow *ui;
    QFile m_file;
    QString path;


private slots:
   void slot_browsed();

};

class neighborlink
{
public:
    QString hostname;
    QString neighborName;
    int hostPortId;
    int neighborPortId;
};



#endif // MAINWINDOW_H
