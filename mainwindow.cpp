#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDragEnterEvent>
#include <QMimeData>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setAcceptDrops(true);
}

void MainWindow::setReader(ImageReader* newReader) {
    currentReader = newReader;
}

//Accept drag events
void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("text/uri-list"))
        event->acceptProposedAction();
}

//Call FileReader::readImage if valid file
void MainWindow::dropEvent(QDropEvent *event)
{
    //Ignore if mimeData->urls() is empty
    QList<QUrl> urls = event->mimeData()->urls();
    if (urls.isEmpty())
        return;

    //Ignore if there is no file name
    QString fileName = urls.first().toLocalFile();
    if (fileName.isEmpty())
        return;

    //File is valid, OCR dat shit and get content
    QString currentFile = QString(fileName);
    QString fileContent = currentReader->readImage(currentFile);
    //Debug content
    qDebug() << fileContent;

    //TODO: Validate content and fill survey
    //TODO: Show cookie code in UI
    //TODO: :-D COOKIEZ
}

MainWindow::~MainWindow()
{
    delete ui;
}
