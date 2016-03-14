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
public slots:
    void printkalja(bool a);
private:
    QWebView *webView;


};

#endif // SURVEYFILLER_H
