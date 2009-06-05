cmake_minimum_required(VERSION 2.6)

PROJECT(TetraBot)

SET(TetraBot_VERSION 0.0.1)

SET(LIBRARY_OUTPUT_PATH bin)

SET(EXECUTABLE_OUTPUT_PATH bin)

SET(CMAKE_VERBOSE_MAKEFILE 0)

SET(CMAKE_COLOR_MAKEFILE ON)

SET(CMAKE_C_FLAGS -W -Wall -ansi -pedantic -O3 -pipe -fomit-frame-pointer -msse -msse2 -msse3 -mmmx -m3dnow)

#FIND_PACKAGE(OGRE REQUIRED)

#FIND_PACKAGE(CEGUI REQUIRED)

#FIND_PACKAGE(OIS REQUIRED)

#FIND_PACKAGE(bullet REQUIRED)

#FIND_PACKAGE(GL REQUIRED)

#FIND_PACKAGE(glut REQUIRED)

INCLUDE_DIRECTORIES(
	include
	ConvexDecomposition
	BulletGL
	/usr/local/include
	/usr/local/include/OGRE
	/usr/local/include/CEGUI
	/usr/local/lib
)

LINK_DIRECTORIES(
	/usr/local/include
	/usr/local/include/OGRE
	/usr/local/include/CEGUI
	/usr/local/lib
)

LINK_LIBRARIES(
	BulletDynamics
	BulletCollision
	LinearMath

	OgreMain
	OIS
	CEGUIBase
	CEGUIOgreRenderer

	GL
	glut
)

FILE(
	GLOB_RECURSE
	source_files
	./src/*
)

FILE(
	GLOB_RECURSE
	include_files
	./include/*
)

FILE(
	GLOB_RECURSE
	BulletGL_files
	./BulletGL/*
)

FILE(
	GLOB_RECURSE
	ConvexDecomposition_files
	./ConvexDecomposition/*
)

ADD_LIBRARY(
	BulletGL
	SHARED

	${BulletGL_files}
)

ADD_LIBRARY(
	ConvexDecomposition
	SHARED

	${ConvexDecomposition_files}
)

ADD_EXECUTABLE(
	tetrabot

	${include_files}
	${source_files}

	BulletGL
	ConvexDecomposition
)

TARGET_LINK_LIBRARIES(
	BulletGL

	GL
	glut
)

TARGET_LINK_LIBRARIES(
	tetrabot

	BulletDynamics
	BulletCollision
	LinearMath

	OgreMain
	OIS
	CEGUIBase
	CEGUIOgreRenderer

	BulletGL
	ConvexDecomposition
)

