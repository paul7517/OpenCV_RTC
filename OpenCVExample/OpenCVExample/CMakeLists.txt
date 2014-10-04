cmake_minimum_required(VERSION 2.8)

########################################################
SET(ProjectName ProjectIPCV)
PROJECT( ${ProjectName} )
  
########################################################
# Find OpenCV.
FIND_PACKAGE( OpenCV REQUIRED )
 IF ( OpenCV_FOUND )
	INCLUDE_DIRECTORIES( ${OPENCV_INCLUDE_DIR} )
ENDIF( OpenCV_FOUND )

########################################################
# Set your files and resources here

FILE(GLOB_RECURSE SrcList RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
SET( Srcs
${CMAKE_CURRENT_SOURCE_DIR}/${SrcList}
)
SOURCE_GROUP( "Source Files" FILES ${Srcs} )

FILE(GLOB_RECURSE HeaderList RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.h)
SET( Headers
${CMAKE_CURRENT_SOURCE_DIR}/${HeaderList}
)
SOURCE_GROUP( "Header Files" FILES ${Headers} )

########################################################
# source files -> add files to project directory
ADD_EXECUTABLE( ${ProjectName}
${Srcs}
${Headers}
)

########################################################
TARGET_LINK_LIBRARIES ( ${ProjectName}
${OpenCV_LIBS}
)
