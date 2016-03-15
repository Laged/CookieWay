#include "surveyfiller.h"
#include <QDebug>
#include <QWebFrame>
#include <QThread>
#include <QObject>


SurveyFiller::SurveyFiller(): webView(new QWebView(NULL))
{
    emailAddress = "kaljaa";
    qDebug() << "Init SurveyFiller()";
}

//Takes the needed text fields from the receipt
//Fills the survey with the given data
//Returns the code for a free cookie
QString SurveyFiller::fillSurvey(QStringList surveyData) {

    connect(webView, SIGNAL(loadFinished(bool)), SLOT(pageReady(bool)) );

    webView->setGeometry(0,0,200,200);
    webView->show();
    qDebug() << "GEOMETRIA ASETETTU";

    webView->load(QUrl("https://www.tellsubway.fi/ContentManager/Controller.aspx?page=CustomerExperience/SurveyNew&surveyId=320&storeId="+surveyData[0]+"-0"));

    //
    qDebug() << "ELEMENTTIA EI VIELA HAETTU";

    // Find an element with "teskti" id from the text
    QWebElement e = webView->page()->currentFrame()->findFirstElement(QString("#teksti"));
    // Get inner HTML from the element
    QString kaliaa = e.toPlainText();

    qDebug() << kaliaa;

    qDebug() << "SurveyFiller::fillSurvey NOT IMPLEMETED - given data:";
    qDebug() << "Restaurant code: " + surveyData[0];
    qDebug() << "Date (dd/mm/yyyy): " + surveyData[1];
    qDebug() << "Receipt code: " + surveyData[2];

    return QString("SurveyFiller::fillSurvey NOT IMPLEMETED");
}

void SurveyFiller::pageReady(bool a) {
    if (a) {
        if (false) { // if this phase has not yet been executed
            fillPage();
        } else {
            getEmail();
        }
    } else {
        qDebug() << "An error occured while loading the page";
    }
}

void SurveyFiller::fillPage() {


    QWebFrame *frame = webView->page()->currentFrame();

    // Fill fields from top to bottom

    frame->evaluateJavaScript("document.getElementById('answ8351').value = 'TRANSACTION NUMBER';");
    frame->evaluateJavaScript("document.getElementById('answ8252').value = 'DATE';");
    // time
    frame->evaluateJavaScript("document.getElementById('answHour8252').value = 1;");
    frame->evaluateJavaScript("document.getElementById('answMinute8252').value = 1;");

    // recommendation 1-10, last number of element id is the value (9)
    frame->evaluateJavaScript("document.getElementById('answc82549').click();");

    // satisfaction 1-10, fifth number of element id is the value (7)
    frame->evaluateJavaScript("document.getElementById('answ39287Q8255').click();");

    // satisfaction 1-10, fifth number of element id is the value (7)
    frame->evaluateJavaScript("document.getElementById('answ39287Q8255').click();");

    // next one, six questions in this field
    // whatever
    // everything 9/10

    // answ39300C8257Q8256,answ39311C8258Q8256,answ39322C8259Q8256,answ39333C8260Q8256
    // answ39344C8261Q8256, answ39355C8262Q8256

    frame->evaluateJavaScript("document.getElementById('answ39300C8257Q8256').click();");
    frame->evaluateJavaScript("document.getElementById('answ39311C8258Q8256').click();");
    frame->evaluateJavaScript("document.getElementById('answ39322C8259Q8256').click();");
    frame->evaluateJavaScript("document.getElementById('answ39333C8260Q8256').click();");
    frame->evaluateJavaScript("document.getElementById('answ39344C8261Q8256').click();");
    frame->evaluateJavaScript("document.getElementById('answ39355C8262Q8256').click();");

    // positive feedback
    frame->evaluateJavaScript("document.getElementById('answ8275').value = 39402;");
    // wanna ask a question
    frame->evaluateJavaScript("document.getElementById('answ8277').value = 39405;");
    // how often do you eat at restaurant
    frame->evaluateJavaScript("document.getElementById('answ8279').value = (Math.floor(Math.random()*10)) + 10+39405;");
    // how often subway
    frame->evaluateJavaScript("document.getElementById('answ8280').value = (Math.floor(Math.random()*10)) + +30+10+39405;");

    // fill email
    frame->evaluateJavaScript("document.getElementById('answ8281').value = '"+ emailAddress+"@yopmail.com';");

    // no spam pls
    frame->evaluateJavaScript("document.getElementById('answ8282').value = 'No';");

    // no spam pls pt.2
    frame->evaluateJavaScript("document.getElementById('DdlContact').value = 'No';");



    webView->setUrl(QUrl(emailAddress+".yopmail.com/en/"));

}

void SurveyFiller::getEmail() {


    qDebug() << "GETTING EMAIL";

    QWebFrame *frame = webView->page()->currentFrame();
    QWebElement e = frame->findFirstElement(QString("#mailmillieu"));
    // Get inner HTML from the element
    QString kaliaa = e.toPlainText();

    if (kaliaa == "") { // size < 200 etc, there is no email from subway
        // load page again
        webView->load(QUrl(emailAddress+".yopmail.com/en/"));

    } else {

        qDebug() << kaliaa;

        // TODO : SEARCH CODE FROM EMAIL
    }


}
