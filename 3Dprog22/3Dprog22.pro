QT          += core gui widgets opengl

TEMPLATE    = app
CONFIG      += c++17

TARGET      = 3D-programmering

SOURCES += main.cpp \
    camera.cpp \
    collider.cpp \
    consoleapplication.cpp \
    cube.cpp \
    disc.cpp \
    door.cpp \
    house.cpp \
    interpolation.cpp \
    landscapes.cpp \
    logger.cpp \
    mainwindow.cpp \
    octahedronball.cpp \
    parabel.cpp \
    perlinnoise.cpp \
    player.cpp \
    points.cpp \
    ppm.cpp \
    renderwindow.cpp \
    shader.cpp \
    spherecollider.cpp \
    tetraeder.cpp \
    trianglesurface.cpp \
    vertex.cpp \
    visualobject.cpp \
    xyz.cpp

HEADERS += \
    Math.h \
    camera.h \
    collider.h \
    consoleapplication.h \
    cube.h \
    disc.h \
    door.h \
    house.h \
    interpolation.h \
    landscapes.h \
    logger.h \
    mainwindow.h \
    octahedronball.h \
    parabel.h \
    perlinnoise.h \
    player.h \
    points.h \
    ppm.h \
    renderwindow.h \
    shader.h \
    spherecollider.h \
    tetraeder.h \
    trianglesurface.h \
    vertex.h \
    visualobject.h \
    xyz.h

FORMS += \
    mainwindow.ui

DISTFILES += \
    plainshader.frag \
    plainshader.vert
