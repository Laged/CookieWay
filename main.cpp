#include "mainwindow.h"
#include <QApplication>
#include "imagereader.h"
#include <QLoggingCategory>
int main(int argc, char *argv[])
{
    // Set SSL restrictions off
    QLoggingCategory::setFilterRules("qt.network.ssl.warning=false");

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
