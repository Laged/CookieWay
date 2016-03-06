#ifndef IMAGEREADER_H
#define IMAGEREADER_H
#include <QString>


class ImageReader
{
public:
    ImageReader();
    QStringList readImage(QString fileName);

};

#endif // IMAGEREADER_H
