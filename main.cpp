#include "mainwindow.h"
#include <QApplication>
#include "imagereader.h"

int main(int argc, char *argv[])
{
    //Init QApplication and MainWindow
    QApplication a(argc, argv);
    MainWindow w;
    //Init ImageReader and set it to MainWindow
    ImageReader* currentReader = new ImageReader();
    w.setReader(currentReader);
    //Init SurveyFiller and set it to MainWindow
    SurveyFiller* currentFiller = new SurveyFiller();
    w.setFiller(currentFiller);
    //Show MainWindow
    w.show();

    return a.exec();
}