#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "imagereader.h"
#include "surveyfiller.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void setReader(ImageReader* newReader);
    void setFiller(SurveyFiller* newFiller);
    ~MainWindow();

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

private:
    Ui::MainWindow *ui;
    ImageReader* currentReader = 0;
    SurveyFiller* currentFiller = 0;
    void updateStatus(QString newStatus, int newPageIndex = -1);
    void updateImage(QString filePath);
    void updateResult(QString cookieCode);
    void getCookie(QString fileName);
    int currentPageIndex = 0;

};

#endif // MAINWINDOW_H
