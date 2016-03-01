#include "imagereader.h"
#include <QDebug>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <locale.h>

ImageReader::ImageReader()
{
    qDebug() << "Init ImageReader()";
}

//Takes a path to an image
//Uses OCR on the image
//Returns the needed text fields from the receipt for survey filling
//TODO: Refactor output to QStringList with the needed fields? ALEKSI TEE TÄÄ :D
QString ImageReader::readImage(QString fileName)
{
    qDebug() << "Reading image: " + fileName;
    //Init Tesseract
    tesseract::TessBaseAPI* tesseract = new tesseract::TessBaseAPI();
    setlocale(LC_NUMERIC, "C");
    if(tesseract->Init(NULL, "eng")) {
        qDebug() << "Could not init tesseract";
        return QString("");
    }

    //OCR the image in the file
    Pix* image = pixRead(fileName.toUtf8());
    //TODO: MANIPULATE THE IMAGE TO MAKE OCR BETTER ???
    tesseract->SetImage(image);
    QString output(tesseract->GetUTF8Text());
    qDebug() << "OCR DONE";
    return output;
}
