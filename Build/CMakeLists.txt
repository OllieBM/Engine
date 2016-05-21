cmake_minimum_required(VERSION 2.8)

project(Engine)

file(GLOB Engine_SRC
	"../include/*.h"
	#"../source/*.h"
	"../source/*.cpp")
	



include_directories(${PROJECT_SOURCE_DIR}/../include)

include_directories(${PROJECT_SOURCE_DIR}/../external/DX)
	


add_executable(Engine ${Engine_SRC})


target_link_libraries(Engine ${PROJECT_SOURCE_DIR}/../libs/d3d11.lib)
target_link_libraries(Engine ${PROJECT_SOURCE_DIR}/../libs/dxgi.lib)
target_link_libraries(Engine ${PROJECT_SOURCE_DIR}/../libs/d3dx11.lib)
target_link_libraries(Engine ${PROJECT_SOURCE_DIR}/../libs/DxErr.lib)
