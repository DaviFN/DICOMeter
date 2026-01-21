#ifndef DICOM_LOADER
#define DICOM_LOADER

#include <memory>
#include <string>
#include <QString>

class QImage;
class DicomImage;

struct DicomData
{
    std::unique_ptr<QImage> image;
    QString patientName;
};

class DicomLoader {
public:
    DicomLoader();
    ~DicomLoader();
    
    DicomData load(const std::string& filepath) const;
private:
    static std::unique_ptr<QImage> createQImageFromDicomImage(DicomImage& dicomImage);
    static void extractMetadata(const std::string& filepath, DicomData& dicomData);
};

#endif