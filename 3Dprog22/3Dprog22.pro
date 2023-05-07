QT          += core gui widgets opengl

TEMPLATE    = app
CONFIG      += c++17

TARGET      = 3D-programmering

SOURCES += main.cpp \
    barysentrisk.cpp \
    camera.cpp \
    collider.cpp \
    component.cpp \
    consoleapplication.cpp \
    cube.cpp \
    disc.cpp \
    door.cpp \
    gameobject.cpp \
    house.cpp \
    houseobject.cpp \
    interpolation.cpp \
    landscapes.cpp \
    light.cpp \
    logger.cpp \
    mainwindow.cpp \
    movementball.cpp \
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
    texture.cpp \
    transform.cpp \
    trianglesurface.cpp \
    uniforms.cpp \
    vec.cpp \
    vertex.cpp \
    visualobject.cpp \
    visualobjectcomponent.cpp \
    xyz.cpp

HEADERS += \
    Math.h \
    barysentrisk.h \
    camera.h \
    collider.h \
    component.h \
    consoleapplication.h \
    cube.h \
    disc.h \
    door.h \
    gameobject.h \
    house.h \
    houseobject.h \
    interpolation.h \
    landscapes.h \
    light.h \
    logger.h \
    mainwindow.h \
    movementball.h \
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
    stb_image.h \
    tetraeder.h \
    texture.h \
    transform.h \
    trianglesurface.h \
    uniforms.h \
    vec.h \
    vertex.h \
    visualobject.h \
    visualobjectcomponent.h \
    xyz.h

FORMS += \
    mainwindow.ui

DISTFILES += \
    PhongShader.frag \
    PhongShader.vert \
    plainshader.frag \
    plainshader.vert \
    textureshader.frag \
    textureshader.vert
