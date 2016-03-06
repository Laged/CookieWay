#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDragEnterEvent>
#include <QPixmap>
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
    //getCookie: call the main method with the image
    getCookie(fileName);
}

/*Updates the status to the UI
 * Accepts a secondary parameter, newPageIndex, for changing pages in the stackedWidget
 * Page numbering:
 *     0 - Initial page, drag&drop (ask user to give a receipt)
 *     1 - Reading the receipt (show user the given receipt)
 *     2 - Waiting for user review & filling the survey (ask user to input a review)
 *     3 - Here's your cookie (show the cookie code for free cookiez)
 *
 * TODO: FIX BUG OF PAGES 1/2 NOT UPDATING
 */
void MainWindow::updateStatus(QString newStatus, int newPageIndex) {
    qDebug() << "New status: " + newStatus + " at page " + QString::number(newPageIndex);
    //Change the label
    ui->labelOutput->setText(newStatus);
    //Change page if specified (newPageIndex default value = -1)
    if(newPageIndex >= 0) {
        currentPageIndex = newPageIndex;
        ui->stackedWidgetInput->setCurrentIndex(currentPageIndex);
    }
}

void MainWindow::updateImage(QString filePath) {
    QPixmap newImage(filePath);
    //TODO: resize image, set it to page1 background
    //ui->labelImage->setPixmap(newImage);
}

void MainWindow::updateResult(QString cookieCode) {
    ui->labelCookieCode->setText(cookieCode);
}

/*THE IMPORTANT STUFF IS HERE
  getCookie: the main method for getting a cookie
  Takes a valid fileName to an image
  Calls ImageReader::readImage to OCR the image of the receipt
  Calls SurveyFiller::fillSurvey to fill a survey based on the receipt
  Updates the UI with the code for a free cookie
*/
void MainWindow::getCookie(QString fileName) {
    //Phase 1: File is valid, OCR dat shit and get content
    QString currentFile = QString(fileName);
    updateImage(currentFile);
    updateStatus("Reading the receipt", 1);
    QStringList fileContent = currentReader->readImage(currentFile);
    //Debug content
    qDebug() << fileContent;
    //TODO: Phase 2: Validate content, ask for user review
    updateStatus("Waiting for user review (TODO)", 2);
    //TODO: Phase 3: Fill survey, show cookie code
    QString cookieCode = currentFiller->fillSurvey(fileContent);
    updateResult(cookieCode);
    updateStatus("Enjoy your cookie!", 3);
    //TODO: :-D COOKIEZ
}

//Destructor for MainWindow
MainWindow::~MainWindow()
{
    delete ui;
}
