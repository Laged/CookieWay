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

void MainWindow::setFiller(SurveyFiller* newFiller) {
    currentFiller = newFiller;
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

    //TODO: Check if the file is an image (.png / .jpg or whatever is ok for OpenCV OCR??)

    //File is valid, OCR dat shit and get content
    updateStatus("Reading the receipt");
    QString currentFile = QString(fileName);
    QString fileContent = currentReader->readImage(currentFile);
    //Debug content
    qDebug() << fileContent;


    //TODO: Validate content?
    updateStatus("Filling the survey");
    currentFiller->fillSurvey(fileContent);
    //TODO: Show cookie code in UI
    //TODO: :-D COOKIEZ
    updateStatus("Waiting for input..");
}


void MainWindow::updateStatus(QString newStatus) {
    ui->labelOutput->setText(newStatus);
}

MainWindow::~MainWindow()
{
    delete ui;
}
