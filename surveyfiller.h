#ifndef SURVEYFILLER_H
#define SURVEYFILLER_H
#include <QString>

#include <QWebView>
#include <QUrl>
#include <QObject>
#include <QWebElement>

class SurveyFiller: public QObject
{
    Q_OBJECT

public:
    SurveyFiller();
    QString fillSurvey(QStringList surveyData);
signals:
    void codeReady(QString code);

public slots:
    void pageReady(bool a);
    void emailReady(bool a);
    void getEmail();
private:
    QWebView *webView;
    QWebView *webView1;
    QString emailAddress;
    int loadcount = 0;
    void fillPage();
    QStringList data;
};

#endif // SURVEYFILLER_H
