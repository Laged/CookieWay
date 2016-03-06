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
    qDebug() << "SurveyFiller::fillSurvey NOT IMPLEMETED";

    return QString("SurveyFiller::fillSurvey NOT IMPLEMETED");
}
