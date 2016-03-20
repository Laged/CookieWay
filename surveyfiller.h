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

private:
    QWebView *webView;
    QWebView *webView1;
    void fillPage();
    QStringList data;
    QString randomEmail();
};

#endif // SURVEYFILLER_H
