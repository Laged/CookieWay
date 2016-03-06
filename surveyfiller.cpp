#include "surveyfiller.h"
#include <QDebug>

SurveyFiller::SurveyFiller()
{
    qDebug() << "Init SurveyFiller()";
}

//Takes the needed text fields from the receipt
//Fills the survey with the given data
//Returns the code for a free cookie
QString SurveyFiller::fillSurvey(QStringList surveyData) {
    //TODO: Fill the survey
    qDebug() << "SurveyFiller::fillSurvey NOT IMPLEMETED - given data:";
    qDebug() << "Restaurant code: " + surveyData[0];
    qDebug() << "Date (dd/mm/yyyy): " + surveyData[1];
    qDebug() << "Receipt code: " + surveyData[2];
    return QString("SurveyFiller::fillSurvey NOT IMPLEMETED");
}
