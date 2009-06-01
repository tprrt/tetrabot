cmake_minimum_required(VERSION 2.6)

PROJECT(TetraBot)
SET(TetraBot_VERSION 0.0.1)

SET(EXECUTABLE_OUTPUT_PATH bin)

INCLUDE_DIRECTORIES(
	include
	ConvexDecomposition
	OpenGL
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
	OpenGL_files
	./OpenGL/*
)

FILE(
	GLOB_RECURSE
	ConvexDecomposition_files
	./ConvexDecomposition/*
)

ADD_EXECUTABLE(
	tetrabot

	${include_files}
	${source_files}

	${OpenGL_files}
	${ConvexDecomposition_files}
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

	GL
	glut
)

