/*

2026 - Davi Feliciano Nonnenmacher

Simple application to show the image contained within a DICOM (Digital Imaging and Communications in Medicine) file, along with the "patient name" field from its metadata

*/

#include <QApplication>
#include <QFileDialog>
#include <QLabel>
#include <QMainWindow>
#include <QMessageBox>
#include <QPixmap>
#include <QPushButton>
#include <QString>
#include <QTextCodec>
#include <QVBoxLayout>

#include "DicomLoader.h"

constexpr const char* appName = "DICOMeter";

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QMainWindow window;
    window.setWindowTitle(QString(appName) + " - no DICOM loaded");
    window.setFixedSize(800, 600);

    window.setStyleSheet("QMainWindow { background-color: #a177f7; }"); // light purple

    QWidget centralWidget(&window);
    QVBoxLayout layout(&centralWidget);

    QPushButton chooseDicomFileButton("Open DICOM File");
    QLabel imageLabel;
    constexpr uint32_t imageWidth = 500;
    constexpr uint32_t imageHeight = 500;
    imageLabel.setFixedSize(imageWidth, imageHeight);
    imageLabel.setAlignment(Qt::AlignCenter);
    imageLabel.setText("No DICOM currently loaded");
    QFont font;
    font.setPointSize(20);
    font.setBold(true);
    imageLabel.setFont(font);

    QLabel patientLabel;
    patientLabel.setText("Patient: no DICOM currently loaded");
    patientLabel.setStyleSheet(
        "QLabel {"
        "    font-size: 16px;"
        "    font-weight: bold;"
        "    padding: 5px;"
        "}"
    );
    patientLabel.setAlignment(Qt::AlignCenter);

    layout.addWidget(&chooseDicomFileButton, 0, Qt::AlignHCenter);
    layout.addWidget(&imageLabel, 0, Qt::AlignHCenter);
    layout.addWidget(&patientLabel, 0, Qt::AlignHCenter);
    
    window.setCentralWidget(&centralWidget);

    QObject::connect(&chooseDicomFileButton, &QPushButton::clicked, [&]() {
        QString filePath = QFileDialog::getOpenFileName(&window, "Open DICOM File");

        if (!filePath.isEmpty()) {
            DicomData dicomData = DicomLoader().load(filePath.toLatin1().data());

            if (dicomData.image != nullptr) {
                QImage scaledImage = dicomData.image->scaled(
                    imageLabel.width(),
                    imageLabel.height(),
                    Qt::KeepAspectRatio,
                    Qt::SmoothTransformation
                );
                imageLabel.setPixmap(QPixmap::fromImage(scaledImage));
                window.setWindowTitle(QString(appName) + " - " + QFileInfo(filePath).fileName());

                patientLabel.setText(QString("Patient name: " + dicomData.patientName));
            }
            else {
                const QString msgBoxBody = QString("Error: ") + QFileInfo(filePath).fileName() + QString(" is either not a valid DICOM file or is not able to be handled by this application");
                QMessageBox::critical(&window, "Error", msgBoxBody);
            }
        }
    });

    window.show();
    return app.exec();
}