#include "imagereader.h"
#include <QDebug>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <locale.h>
#include <QStringList>

ImageReader::ImageReader()
{
    qDebug() << "Init ImageReader()";
}

//Takes a path to an image
//Uses OCR on the image
//Returns the needed text fields from the receipt for survey filling
QStringList ImageReader::readImage(QString fileName)
{
    qDebug() << "Reading image: " + fileName;
    //Init fieldContents to store the fields we find
    QStringList fieldContents;
    //Init Tesseract
    tesseract::TessBaseAPI* tesseract = new tesseract::TessBaseAPI();
    setlocale(LC_NUMERIC, "C");
    if(tesseract->Init(NULL, "eng")) {
        qDebug() << "Could not init tesseract";
        return fieldContents;
    }

    //OCR the image in the file
    Pix* image = pixRead(fileName.toUtf8());
    //TODO: MANIPULATE THE IMAGE TO MAKE OCR BETTER
   tesseract->SetImage(image);
    QString output(tesseract->GetUTF8Text());
    qDebug() << "OCR DONE";
    //TODO: Fill fieldContents with the actual content from OCR (Parse OCR)
    fieldContents << "RESTAURANTCODE" << "DATE" << "RECEIPTCODE" << "RECEIPTTIME";
    qDebug() << fieldContents;
    return fieldContents;
}
