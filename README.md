# Overview 
DICOMeter is a simple application to read DICOM (Digital Imaging and Communications in Medicine) files. It can be used as a template for working with such files using the Qt and the DCMTK libraries on x64 Windows.

# Features
At this point in time DICOMeter limits itself to opening a DICOM file and presenting its associate image and the "patient name" field from the file's metadata.

# Limitations
This is very, very far from being a thoroughly tested way of handling DICOM files; there are many DICOM files not handled well by this application. It can however be used as a starting point for using DCMTK.
Some sample files known to work are provided within the "sample-dicom-files" directory (taken from [this repository](https://github.com/robyoung/dicom-test-files)); contributions are welcome.

## Getting Started (Building and Running)

*Follow the following steps to build and run DICOMeter on your machine:*

1. **Assure Required Software Are Installed**  
   *Make sure you have installed the following software components on your machine:*
   - Visual Studio
   - Visual Studio Code (not strictly necessary but good to have)
   - Python
   - CMake
   - Make

2. **Install vcpkg and the required vcpkg packages**

   *DICOMeter uses vcpkg, a C++ package manager, to manage some of its requirements; make sure to follow the following steps to install vcpkg in your machine and acquire the required packages:*
   1. Navigate to a folder where vcpkg is to be installed; as a suggestion, "C:\devtools"
   2. Clone the vcpkg repository on GitHub and cd onto it:  
      ```bash
      git clone https://github.com/microsoft/vcpkg.git && cd vcpkg
      ```
   3. Run vcpkg's bootstrap batch script, which will download and build the vcpkg executable:
      ```bash
      bootstrap-vcpkg.bat
      ```
   4. Integrate vcpkg with Visual Studio (optional, but recommended):
      ```bash
      vcpkg integrate install
      ```
   5. Add a VCPKG_ROOT environment variable pointing to the vcpkg directory (if the suggestion was followed, it should be "C:\devtools\vcpkg")
   6. Add an entry to the path environment variable pointing to that same directory to make vcpkg's executable accessible through the command line (restart command line so that this change takes place)   
   > *At this point, vcpkg is installed; now, install the dependencies:*
   7. Install the required packages for the build, which are provided by vcpkg (this might take a while): 
      ```bash
      vcpkg install qt5-base:x64-windows dcmtk:x64-windows
      ```

4. **Clone and Build DICOMeter** 
   *At this point, we have everything we need to clone and build Travailleur*
   1. Clone Travailleur's repository somewhere and cd onto it:
      ```bash
      git clone https://github.com/DaviFN/DICOMeter && cd DICOMeter
      ```
   2. Generate the Visual Studio solution by issuing the following command:
      ```bash
      make
      ```
   3. Open the solution with the following command:
      ```bash
      make open
      ```

      > Obs: it may be needed to run Visual Studio / Visual Studio Code as admin
   4. Open the solution explorer window, if not open already (CTRL + ALT + L hotkey)
   5. Right-click the "INSTALL" project and select "build"; wait until the build process completes
   
5. **Run the Application**   
   1. Set the DICOMeter target to be the startup one by right-clicking it and selecting "set as startup project"
   2. Launch the app through the Local Windows Debugger (or directly via the generated executable file)

---

## License

![License: GPL v3](https://img.shields.io/badge/license-%20%20GNU%20GPLv3%20-green?style=plastic)

This application is licensed under the [GNU GENERAL PUBLIC LICENSE v3](https://www.gnu.org/licenses/gpl-3.0.en.html).

Third-party libraries use their own licenses:
- **[Qt]** (GNU General Public License (GPL) v3): <https://www.gnu.org/licenses/gpl-3.0.en.html>  
- **[DCMTK]** (OFFIS license): <https://support.dcmtk.org/docs/file_copyright.html>  
