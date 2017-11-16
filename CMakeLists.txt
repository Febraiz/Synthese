CMAKE_MINIMUM_REQUIRED(VERSION 2.8.11)

PROJECT(Projet_Image_M2)

# Find includes in corresponding build directories
#set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
SET(CMAKE_AUTOMOC ON)
#SET(CMAKE_AUTOUIC ON)
#SET(CMAKE_AUTORCC ON)
SET(CMAKE_INCLUDE_CURRENT_DIR ON)


#SET(Qt5Core_DIR E:/msys2/mingw64/qt5-static/lib/cmake/Qt5Core)

SET(ITK_DIR E:/msys2/mingw64/lib/cmake/ITK-4.11)
SET(OpenCV_DIR E:/msys2/mingw64/share/OpenCV/lib)
SET(VTK_DIR E:/msys2/mingw64/lib/cmake/vtk-8.0)

#Find ITK
FIND_PACKAGE(ITK REQUIRED)
INCLUDE(${ITK_USE_FILE} )

#Ajout du QRC
SET(RESOURCES images.qrc)
QT5_ADD_RESOURCES(RES_SOURCES ${RESOURCES})

SET(Qt5Widgets_DIR E:/msys2/mingw64/qt5-static/lib/cmake/Qt5Widgets)
SET(Qt5OpenGL_DIR E:/msys2/mingw64/qt5-static/lib/cmake/Qt5OpenGL)
SET(Qt5OpenGLExtensions_DIR E:/msys2/mingw64/qt5-static/lib/cmake/Qt5OpenGLExtensions)

#FIND_PACKAGE(Qt5Core)
FIND_PACKAGE(Qt5OpenGLExtensions)
FIND_PACKAGE(Qt5OpenGL)
FIND_PACKAGE(Qt5Widgets)
#INCLUDE(${QT_USE_FILE})

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})


ADD_EXECUTABLE(Projet_Image_M2 main.cpp mainwindow.cpp mainwindow.h view.cpp view.h chip.cpp chip.h ${RES_SOURCES})

TARGET_LINK_LIBRARIES(Projet_Image_M2  Qt5::OpenGLExtensions Qt5::OpenGL Qt5::Widgets ${ITK_LIBRARIES})
