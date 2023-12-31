include(GetGitRevisionDescription)
get_git_head_revision(GIT_REFSPEC GIT_SHA1)
git_local_changes(GIT_LOCAL_CHANGES)
if (${GIT_LOCAL_CHANGES} STREQUAL "DIRTY")
	set(COMPILER_MESSAGE "#pragma WARNING(Local changes not committed.)")
endif()

file (STRINGS "../version.txt" PBD_VERSION)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Version.h.in ${CMAKE_CURRENT_SOURCE_DIR}/Version.h @ONLY)

add_library(Utils
		FileSystem.h
		Hashmap.h
		IndexedFaceMesh.cpp
		IndexedFaceMesh.h
		IndexedTetMesh.cpp
		IndexedTetMesh.h
		Logger.h
		OBJLoader.h
		PLYLoader.h
		SceneLoader.cpp
		SceneLoader.h
		StringTools.h
		SystemInfo.h
		TetGenLoader.cpp
		TetGenLoader.h
		Timing.h
		Version.h
		VolumeIntegration.cpp
		VolumeIntegration.h

		CMakeLists.txt
)

############################################################
# GenericParameters
############################################################
include_directories(${GenericParameters_INCLUDE_DIR})
if(TARGET Ext_GenericParameters)
	add_dependencies(Utils Ext_GenericParameters)
endif()

find_package( Eigen3 REQUIRED )
include_directories( ${EIGEN3_INCLUDE_DIR} )

install(TARGETS Utils
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

install(DIRECTORY .
DESTINATION include/Utils
FILES_MATCHING PATTERN "*.h")