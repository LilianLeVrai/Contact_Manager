QT -= gui

QT += sql \
    widgets

CONFIG += c++17 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        Contact.cpp \
        ContactCRUD.cpp \
        DatabaseManagement.cpp \
        Date.cpp \
        Interaction.cpp \
        ListContact.cpp \
        ListInteraction.cpp \
        MainWindow.cpp \
        Todo.cpp \
        ListTodo.cpp \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    Contact.h \
    ContactCRUD.h \
    DatabaseManagement.h \
    Date.h \
    Interaction.h \
    ListContact.h \
    ListInteraction.h \
    MainWindow.h \
    Todo.h \
    ListTodo.h

FORMS +=
