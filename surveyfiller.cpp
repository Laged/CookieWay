#include "surveyfiller.h"
#include <QDebug>

SurveyFiller::SurveyFiller()
{
    qDebug() << "Init SurveyFiller()";
}

//Takes the needed text fields from the receipt
//Fills the survey with the given data
//Returns the code for a free cookie
//TODO: Refactor surveyData to QStringList with needed fields? ALEKSI TEE TÄÄ :D
QString SurveyFiller::fillSurvey(QString surveyData) {
    //TODO: Fill the survey
    qDebug() << "SurveyFiller::fillSurvey NOT IMPLEMETED";

    return QString("SurveyFiller::fillSurvey NOT IMPLEMETED - STRING GIVEN: " + surveyData);
}
