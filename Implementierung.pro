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
    aendern.cpp \
    datensatzbearbeiten.cpp \
    finddb.cpp \
    firststart.cpp \
    klassenkamerad_einfuegen.cpp \
    main.cpp \
    mainwindow.cpp \
    newpasswort.cpp \
    organisator_erstellen.cpp \
    qt_loginview.cpp

HEADERS += \
    KlassenkameradDAO.h \
    KlassenkameradDatensatz.h \
    ListeView.h \
    LoginView.h \
    Verwaltung.h \
    aendern.h \
    datensatzbearbeiten.h \
    finddb.h \
    firststart.h \
    klassenkamerad_einfuegen.h \
    mainwindow.h \
    newpasswort.h \
    organisator_erstellen.h \
    qt_loginview.h

FORMS += \
    aendern.ui \
    datensatzbearbeiten.ui \
    finddb.ui \
    firststart.ui \
    klassenkamerad_einfuegen.ui \
    mainwindow.ui \
    newpasswort.ui \
    organisator_erstellen.ui \
    qt_loginview.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    .gitignore
