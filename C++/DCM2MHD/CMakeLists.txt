cmake_minimum_required(VERSION 2.8)
 
PROJECT(DCM2MHD)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

FIND_PACKAGE(ITK REQUIRED)
INCLUDE(${ITK_USE_FILE})
 
add_executable(${PROJECT_NAME} MACOSX_BUNDLE dcm2mhd.cxx)
 
if(VTK_LIBRARIES)
  target_link_libraries(${PROJECT_NAME} ${VTK_LIBRARIES})
else()
  target_link_libraries(${PROJECT_NAME} vtkHybrid vtkWidgets)
endif()

IF(ITK_LIBRARIES)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${ITK_LIBRARIES})
ENDIF()