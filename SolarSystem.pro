#
# SCC0650 - Computação Gráfica
# Universidade de São Paulo (USP) - São Carlos
# Instituto de Ciências Matemáticas e de Computação (ICMC)
# Autores: Guilherme Caixeta de Oliveira - nUSP 8504368
#          Andressa ?     - nUSP XX
#          Lucas dos Santos Luchiari     - nUSP XX
#
# This file is part of SolarSystem project.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

# Application info
TEMPLATE = app
DESTDIR = bin
TARGET = SolarSystem
VERSION = 1.0

# Qt config
CONFIG -= c++11
CONFIG -= qt app_bundle
CONFIG += console

# Libs
LIBS += -lglut -lGLU -lGL -lX11 -pthread

# Temporary dirs
OBJECTS_DIR = tmp/obj
MOC_DIR = tmp/moc
UI_DIR = tmp/moc
RCC_DIR = tmp/rc

# Source files
INCLUDEPATH *= . src

SOURCES += \
    src/main.cc \
    src/SolarSystem/solarsystem.cc \
    src/SolarSystem/object/object.cc \
    src/SolarSystem/object/planet/planet.cc \
    src/SolarSystem/utils/color.cc \
    src/SolarSystem/utils/position.cc \
    src/3rdparty/imageloader.cc

# Header files
HEADERS += \
    src/SolarSystem/solarsystem.hh \
    src/SolarSystem/object/object.hh \
    src/SolarSystem/object/planet/planet.hh \
    src/SolarSystem/utils/color.hh \
    src/SolarSystem/utils/position.hh \
    src/3rdparty/imageloader.hh

# Other files
DISTFILES +=
