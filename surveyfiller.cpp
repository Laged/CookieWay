#include "surveyfiller.h"
#include <QDebug>
#include <QWebFrame>
#include <QThread>
#include <QObject>
#include <QTimer>
#include <QtGlobal>


SurveyFiller::SurveyFiller(): webView(new QWebView(NULL)), webView1(new QWebView(NULL))
{
    qDebug() << "Init SurveyFiller()";
}

//Takes the needed text fields from the receipt
//Fills the survey with the given data
//Returns the code for a free cookie
QString SurveyFiller::fillSurvey(QStringList surveyData) {

    connect(webView, SIGNAL(loadFinished(bool)), SLOT(pageReady(bool)) );
    //connect(webView1, SIGNAL(loadFinished(bool)), SLOT(emailReady(bool)) );

    data = surveyData;

    webView->setGeometry(0,0,400,400);
    webView->show();

    webView1->setGeometry(0,0,400,400);
   // webView1->show();

    qDebug() << "GEOMETRIA ASETETTU";

    webView->load(QUrl("https://www.tellsubway.fi/ContentManager/Controller.aspx?page=CustomerExperience/SurveyNew&surveyId=320&storeId="+surveyData[0]+"-0"));

    qDebug() << "ELEMENTTIA EI VIELA HAETTU";

    qDebug() << "SurveyFiller::fillSurvey NOT IMPLEMETED - given data:";
    qDebug() << "Restaurant code: " + surveyData[0];
    qDebug() << "Date (dd/mm/yyyy): " + surveyData[1];
    qDebug() << "Receipt code: " + surveyData[2];
    qDebug() << "Time: " + surveyData[3];

    webView1->load(QUrl("http://users.aalto.fi/~yrjanav1/QT_JS_TEST/"));

    return QString("SurveyFiller::fillSurvey NOT IMPLEMETED");
}

void SurveyFiller::pageReady(bool a) {
    qDebug() << "load finished";
    if (a) {
        fillPage();
    } else {
        qDebug() << "An error occured while loading the page";
        emit codeReady("An error occured while loading the page");
    }
}

void SurveyFiller::fillPage() {

    emit codeReady(QString("PROCESSING"));
    QWebFrame *frame = webView->page()->currentFrame();

    // Fill fields from top to bottom

    frame->evaluateJavaScript("document.getElementById('answ8351').value = '"+ data[2] +"';");
    frame->evaluateJavaScript("document.getElementById('answ8252').value = '"+data[1]+"';");
    // time, format '16:38:03'
    frame->evaluateJavaScript("document.getElementById('answHour8252').value = " + data[3].left(2) + ";");
    frame->evaluateJavaScript("document.getElementById('answMinute8252').value = " + data[3].mid(3,2) + ";");

    // recommendation 1-10, last number of element id is the value (9)
    frame->evaluateJavaScript("document.getElementById('answc82549').click();");

    // satisfaction 1-10, fifth number of element id is the value (7)
    frame->evaluateJavaScript("document.getElementById('answ39287Q8255').click();");

    // satisfaction 1-10, fifth number of element id is the value (7)
    frame->evaluateJavaScript("document.getElementById('answ39287Q8255').click();");

    // next one, six questions in this field, everything 9/10
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
    frame->evaluateJavaScript("document.getElementById('answ8279').value = 39437;");
    // how often subway
    frame->evaluateJavaScript("document.getElementById('answ8280').value = (Math.floor(Math.random()*10)) + +30+10+39405;");

    // fill email
    frame->evaluateJavaScript("document.getElementById('answ8281').value = '"+ randomEmail() +"';");
    // no spam pls
    frame->evaluateJavaScript("document.getElementById('answ8282').value = 'No';");
    // no spam pls pt.2
    frame->evaluateJavaScript("document.getElementById('DdlContact').value = 'No';");

    // submit
    frame->evaluateJavaScript("document.getElementById('btnSubmit').click();");

    frame = webView->page()->currentFrame();
    // return value
    qDebug() << "COOKIE CODE:";

    QString finalCode = frame->findFirstElement("#ctl03_lblTag").toPlainText();

    qDebug() << finalCode;
    if (finalCode != "") {
        emit codeReady("Code: \n"+ finalCode);
    }

}

QString SurveyFiller::randomEmail()
{
   // cookie codes are restricted to 1 per 24 hours per email
   // so create a random string

   qsrand(QTime::currentTime().msec());
   QString chars("abcdefghijklmnopqrstuvwxyz0123456789");
   const int randomStringLength = 4 + (qrand() % 8) ;
   QString randomString;
   for (int i=0; i < randomStringLength; ++i) {
       int index = rand() % chars.length();
       QChar nextChar = chars.at(index);
       randomString.append(nextChar);
   }
   return randomString+ "@yopmail.com";
}
