#include "converttograyscale.h"

QImage convertToGrayscale(const QImage &image)
{
   return image.convertToFormat(QImage::Format_Grayscale16);
}
