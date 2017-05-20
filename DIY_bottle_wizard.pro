HEADERS += \
    mafenetre.h \
    myqspinbox.h \
    arome.h \
    base.h \
    listaromes.h \
    listbases.h \
    liquid.h \
    alcool.h \
    listalcools.h \
    fentextegenere.h \
    fenaddalcool.h \
    fenaddbase.h \
    fenaddarome.h \
    fenoptions.h \
    myqdoublespinbox.h

SOURCES += \
    main.cpp \
    mafenetre.cpp \
    myqspinbox.cpp \
    arome.cpp \
    base.cpp \
    listaromes.cpp \
    listbases.cpp \
    liquid.cpp \
    alcool.cpp \
    listalcools.cpp \
    fentextegenere.cpp \
    fenaddalcool.cpp \
    fenaddbase.cpp \
    fenaddarome.cpp \
    fenoptions.cpp \
    myqdoublespinbox.cpp

RESOURCES += \
    DIY_bottle_wizard.qrc

win32:RC_ICONS += eliquidico.ico

QT += widgets
QT += printsupport

QTPLUGIN     += qjpeg qgif    # image formats

DISTFILES +=

