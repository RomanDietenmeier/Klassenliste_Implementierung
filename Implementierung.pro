QT       += core gui
QT       += sql
QT       += widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG += console


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    KlassenkameradDAO.cpp \
    KlassenkameradDatensatz.cpp \
    ListeView.cpp \
    LoginView.cpp \
    Verwaltung.cpp \
    datensatzbearbeiten.cpp \
    finddb.cpp \
    main.cpp \
    mainwindow.cpp \
    qt_loginview.cpp

HEADERS += \
    KlassenkameradDAO.h \
    KlassenkameradDatensatz.h \
    ListeView.h \
    LoginView.h \
    Verwaltung.h \
    datensatzbearbeiten.h \
    finddb.h \
    mainwindow.h \
    qt_loginview.h

FORMS += \
    datensatzbearbeiten.ui \
    finddb.ui \
    mainwindow.ui \
    qt_loginview.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    .gitignore
