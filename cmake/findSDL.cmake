
IF (WIN32)
	FIND_PATH(SDL_INCLUDE_PATH SDL2/SDL.h
		DOC "The directory where GL/glew.h resides")

    FIND_LIBRARY( SDL_LIBRARY
        NAMES SDL SDL2
        PATHS
        DOC "The SDL library")
ELSE (WIN32)
    FIND_PATH( SDL_INCLUDE_PATH SDL2/SDL.h
    /usr/local/Cellar/sdl2/2.0.20/include
    DOC "The directory where SDL2/SDL.h resides")

# Prefer the static library.
    FIND_LIBRARY( SDL_LIBRARY
    NAMES SDL2
    PATHS
    /usr/local/Cellar/sdl2/2.0.20/lib
    DOC "The SDL2 library")
ENDIF (WIN32)

SET(SDL_FOUND "NO")
IF (SDL_INCLUDE_PATH AND SDL_LIBRARY)
	SET(SDL_LIBRARIES ${SDL_LIBRARY} )
	SET(SDL_FOUND "YES")
ENDIF (SDL_INCLUDE_PATH AND SDL_LIBRARY)