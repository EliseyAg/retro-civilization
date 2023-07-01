cmake_minimum_required()

set(PROJECT_NAME RetroCivilization)
project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} 
	src/main.cpp
)

set(PUBLIC_INCLUDES
	external/stb_image/stb_image.h

	src/Game/Application.hpp

	src/RenderEngine/Window.hpp
	src/RenderEngine/Texture2D.hpp
	src/RenderEngine/ShaderProgram.hpp
	src/RenderEngine/VertexBuffer.hpp
	src/RenderEngine/VertexBufferLayout.hpp
	src/RenderEngine/IndexBuffer.hpp
	src/RenderEngine/VertexArray.hpp
	src/RenderEngine/Renderer_OpenGL.hpp

	src/Event/Event.hpp
	
	src/Resources/ResourceManager.hpp
)

set(PUBLIC_SOURCES
	src/Game/Application.cpp

	src/RenderEngine/Window.cpp
	src/RenderEngine/Texture2D.cpp
	src/RenderEngine/ShaderProgram.cpp
	src/RenderEngine/VertexBuffer.cpp
	src/RenderEngine/VertexBufferLayout.cpp
	src/RenderEngine/IndexBuffer.cpp
	src/RenderEngine/VertexArray.cpp
	src/RenderEngine/Renderer_OpenGL.cpp
	
	src/Resources/ResourceManager.cpp
)

set(ALL_SOURCES
	${PUBLIC_INCLUDES}
	${PUBLIC_SOURCES}
)

add_library(${PROJECT_NAME} STATIC
	${ALL_SOURCES}
)

target_include_directories(${PROJECT_NAME} PUBLIC source)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

add_subdirectory(../retro-civilization/external/glfw ${CMAKE_CURRENT_BINARY_DIR}/glfw)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw)

add_subdirectory(../retro-civilization/external/glad ${CMAKE_CURRENT_BINARY_DIR}/glad)
target_link_libraries(${PROJECT_NAME} PUBLIC glad)

add_subdirectory(../Minecraft/external/glm ${CMAKE_CURRENT_BINARY_DIR}/glm)
target_link_libraries(${PROJECT_NAME} PUBLIC glm)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_directory
					${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)
