#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDragEnterEvent>
#include <QMimeData>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    qDebug() << "Init MainWindow";
    ui->setupUi(this);
    setAcceptDrops(true);
}

//Sets a new ImageReader
void MainWindow::setReader(ImageReader* newReader) {
    currentReader = newReader;
}

//Sets a new SurveyFiller
void MainWindow::setFiller(SurveyFiller* newFiller) {
    currentFiller = newFiller;
}

//Accept drag events
void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("text/uri-list"))
        event->acceptProposedAction();
}

//dropEvent: call getCookie if the file is valid
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
    updateStatus("New receipt given");
    //getCookie: call the main method with the image
    getCookie(fileName);
}

//Updates the status to the UI
void MainWindow::updateStatus(QString newStatus) {
    qDebug() << "New status: " + newStatus;
    ui->labelOutput->setText(newStatus);
}

/*THE IMPORTANT STUFF IS HERE
  getCookie: the main method for getting a cookie
  Takes a valid fileName to an image
  Calls ImageReader::readImage to OCR the image of the receipt
  Calls SurveyFiller::fillSurvey to fill a survey based on the receipt
  Updates the UI with the code for a free cookie
*/
void MainWindow::getCookie(QString fileName) {
    //File is valid, OCR dat shit and get content
    updateStatus("Reading the receipt");
    QString currentFile = QString(fileName);
    updateStatus(currentFile);
    QString fileContent = currentReader->readImage(currentFile);
    //Debug content
    qDebug() << fileContent;


    //TODO: Validate content?
    updateStatus("Filling the survey");
    QString cookieCode = currentFiller->fillSurvey(fileContent);
    //TODO: Show cookie code in UI
    updateStatus(cookieCode);
    //TODO: :-D COOKIEZ
}

//Destructor for MainWindow
MainWindow::~MainWindow()
{
    delete ui;
}
