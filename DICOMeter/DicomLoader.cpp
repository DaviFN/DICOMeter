#include "DicomLoader.h"

#include <QImage>

#include <dcmtk/dcmdata/dcfilefo.h>
#include <dcmtk/dcmimgle/dcmimage.h>
#include <dcmtk/dcmjpeg/djdecode.h>

#include <dcmtk/dcmdata/dctk.h>
#include <dcmtk/dcmdata/dcdeftag.h>

DicomLoader::DicomLoader()
{
	DJDecoderRegistration::registerCodecs();
}

DicomLoader::~DicomLoader()
{
	DJDecoderRegistration::cleanup();
}

QString getDicomString(DcmDataset* dataset, DcmTagKey tag, const QString& defaultValue)
{
    if (!dataset) {
        return defaultValue;
    }

    OFString value;
    if (dataset->findAndGetOFString(tag, value).good()) {
        return QString(value.c_str()).trimmed();
    }

    return defaultValue;
}

DicomData DicomLoader::load(const std::string& filepath) const
{
    DicomData dicomData;

    DicomImage dicomImage(filepath);
    if (dicomImage.getStatus() != EIS_Normal) {
        return dicomData;
    }

    dicomData.image = createQImageFromDicomImage(dicomImage);
    extractMetadata(filepath, dicomData);

    return dicomData;
}

std::unique_ptr<QImage> DicomLoader::createQImageFromDicomImage(DicomImage& dicomImage)
{
    std::unique_ptr<QImage> image = std::make_unique<QImage>(dicomImage.getWidth(), dicomImage.getHeight(), QImage::Format_RGB888);
    
    if (dicomImage.isMonochrome()) {
        dicomImage.setMinMaxWindow(); // Adjust brightness and contrast
        const uchar* pixelData = (uchar*)dicomImage.getOutputData(8); // 8 bits per sample
        if (pixelData) {
            for (int y = 0; y < dicomImage.getHeight(); ++y) {
                for (int x = 0; x < dicomImage.getWidth(); ++x) {
                    int value = pixelData[y * dicomImage.getWidth() + x];
                    image->setPixelColor(x, y, QColor(value, value, value));
                }
            }
        }
    }
    else {
        // Handle color images (e.g., RGB)
        const uchar* pixelData = (uchar*)dicomImage.getOutputData(24); // 24 bits per sample
        if (pixelData) {
            memcpy(image->bits(), pixelData, dicomImage.getWidth() * dicomImage.getHeight() * 3); // Copy RGB data directly
        }
    }

    return image;
}

void DicomLoader::extractMetadata(const std::string& filepath, DicomData& dicomData)
{
    DcmFileFormat fileformat;
    OFCondition status = fileformat.loadFile(filepath.c_str());

    if (status.good()) {
        DcmDataset* dataset = fileformat.getDataset();
        dicomData.patientName = getDicomString(dataset, DCM_PatientName, "no patient name");
    }
}