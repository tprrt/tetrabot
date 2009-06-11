CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(TetraBot)

SET(TetraBot_VERSION 0.0.1)

SET(LIBRARY_OUTPUT_PATH bin)

SET(EXECUTABLE_OUTPUT_PATH bin)

SET(CMAKE_VERBOSE_MAKEFILE OFF)

SET(CMAKE_COLOR_MAKEFILE ON)

#SET(CMAKE_SYSTEM_NAME Linux)

#IF(WIN32 AND NOT UNIX)

#ELSE

SET(CMAKE_LINK_LIBRARY_FLAG "${CMAKE_LINK_LIBRARY_FLAG} -fPIC ")

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -pipe -fomit-frame-pointer -msse -msse2 -msse3 -mmmx -m3dnow")

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -pipe -fomit-frame-pointer -msse -msse2 -msse3 -mmmx -m3dnow")

#SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -W -Wall -ansi -pedantic -O3 -pipe -fomit-frame-pointer -msse -msse2 -msse3 -mmmx -m3dnow")

#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -ansi -pedantic -O3 -pipe -fomit-frame-pointer -msse -msse2 -msse3 -mmmx -m3dnow")

#FIND_PACKAGE(OGRE REQUIRED)

#FIND_PACKAGE(CEGUI REQUIRED)

#FIND_PACKAGE(OIS REQUIRED)

#FIND_PACKAGE(bullet REQUIRED)

#FIND_PACKAGE(GL REQUIRED)

#FIND_PACKAGE(glut REQUIRED)

ADD_SUBDIRECTORY(
	include
)

ADD_SUBDIRECTORY(
	src
)

ADD_SUBDIRECTORY(
	ConvexDecomposition
)

ADD_SUBDIRECTORY(
	BulletGL
)

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

