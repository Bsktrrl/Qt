QT          += core gui widgets opengl

TEMPLATE    = app
CONFIG      += c++17

TARGET      = 3D-programmering

SOURCES += main.cpp \
    camera.cpp \
    collider.cpp \
    component.cpp \
    consoleapplication.cpp \
    cube.cpp \
    disc.cpp \
    door.cpp \
    gameobject.cpp \
    house.cpp \
    interpolation.cpp \
    landscapes.cpp \
    logger.cpp \
    mainwindow.cpp \
    octahedronball.cpp \
    parabel.cpp \
    perlinnoise.cpp \
    pickup.cpp \
    player.cpp \
    points.cpp \
    ppm.cpp \
    renderwindow.cpp \
    shader.cpp \
    spherecollider.cpp \
    tetraeder.cpp \
    transform.cpp \
    trianglesurface.cpp \
    vertex.cpp \
    visualobject.cpp \
    visualobjectcomponent.cpp \
    xyz.cpp

HEADERS += \
    Math.h \
    camera.h \
    collider.h \
    component.h \
    consoleapplication.h \
    cube.h \
    disc.h \
    door.h \
    gameobject.h \
    house.h \
    interpolation.h \
    landscapes.h \
    logger.h \
    mainwindow.h \
    octahedronball.h \
    parabel.h \
    perlinnoise.h \
    pickup.h \
    player.h \
    points.h \
    ppm.h \
    renderwindow.h \
    shader.h \
    spherecollider.h \
    tetraeder.h \
    transform.h \
    trianglesurface.h \
    vertex.h \
    visualobject.h \
    visualobjectcomponent.h \
    xyz.h

FORMS += \
    mainwindow.ui

DISTFILES += \
    plainshader.frag \
    plainshader.vert
