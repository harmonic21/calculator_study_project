QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ./view/Qcustomplot/qcustomplot.cpp \
    ./view/main.cc \
    ./view/main_window.cc \
    ./controller/calculation_controller.cc \
    ./model/calculate_model.cc \
    ./model/equation_member.cc \
    ./model/string_transformer.cc \
    ./model/validator.cc \
    ./view/graph.cc \


HEADERS += \
    ./view/Qcustomplot/qcustomplot.h \
    ./view/main_window.h \
    ./controller/calculation_controller.h \
    ./model/calculate_model.h \
    ./model/equation_member.h \
    ./model/string_transformer.h \
    ./model/utility.h \
    ./model/validator.h \
    ./view/graph.h \


FORMS += \
    ./view/main_window.ui \
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
