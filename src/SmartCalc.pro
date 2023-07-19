QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ./view/Qcustomplot/qcustomplot.cpp \
    ./view/main.cc \
    ./view/MainWindow.cc \
    ./controller/CalculationController.cc \
    ./model/CalculateModel.cc \
    ./model/EquationMember.cc \
    ./model/StringTransformer.cc \
    ./model/Validator.cc \
    ./view/graph.cc \


HEADERS += \
    ./view/Qcustomplot/qcustomplot.h \
    ./view/MainWindow.h \
    ./controller/CalculationController.h \
    ./model/CalculateModel.h \
    ./model/EquationMember.h \
    ./model/StringTransformer.h \
    ./model/Utility.h \
    ./model/Validator.h \
    ./view/graph.h \


FORMS += \
    ./view/MainWindow.ui \
    ./view/graph.ui

TRANSLATIONS += \
    ./view/SmartCalc_en_US.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Makefile \
    SmartCalc.pro.user
