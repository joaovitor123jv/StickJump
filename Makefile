#Executaveis
PLAY=play
PLAY_DEPENDENCIES=$(SCREEN) $(RECTANGLE) $(TEXT) $(BUTTON)




#Arquivos
INCLUDES=Includes
SCREEN=Screen
ANIMATION=Animation
IMAGE=Image
MAIN=Main
PLAYER=Player
RECTANGLE=Rectangle
BUTTON=Button
TEXT=Text

#Pastas
SOURCE_FOLDER=src

#Compilador
CC=g++

#Linkers
LINKERS=-lSDL2 -lSDL2_ttf

#Executor
EXECUTE=./

#Otimizador
OPTIMIZE=-o3

#Opções
#USE_ANSI=-ansi
USE_ANSI=-std=c++11
#LIKE_A_LIBRARY=-c
LIKE_A_LIBRARY=-c
LIKE_A_EXECUTABLE=-o

#Comandos
OPEN_FOLDER=cd
DEBUGGER=valgrind


################################################EXECUTABLES COMPILATION

#all: 
all: $(PLAY_DEPENDENCIES)
	$(OPEN_FOLDER) $(SOURCE_FOLDER); $(CC) $(USE_ANSI) $(MAIN:=.cpp) $(PLAY_DEPENDENCIES:=.o) $(OPTIMIZE) $(LIKE_A_EXECUTABLE) ../$(PLAY) $(LINKERS)



##############################################LIBRARIES COMPILATION
#$(SCREEN:=.o):
$(SCREEN):
	$(OPEN_FOLDER) $(SOURCE_FOLDER); $(CC) $(LIKE_A_LIBRARY) $(USE_ANSI) $(SCREEN)/$(SCREEN:=.cpp)


#$(RECTANGLE:=.o):
$(RECTANGLE): $(SCREEN)
	$(OPEN_FOLDER) $(SOURCE_FOLDER); $(CC) $(LIKE_A_LIBRARY) $(USE_ANSI) $(RECTANGLE)/$(RECTANGLE:=.cpp)


$(TEXT): $(SCREEN)
	$(OPEN_FOLDER) $(SOURCE_FOLDER); $(CC) $(LIKE_A_LIBRARY) $(USE_ANSI) $(TEXT)/$(TEXT:=.cpp)

$(BUTTON): $(SCREEN) $(TEXT) $(RECTANGLE)
	$(OPEN_FOLDER) $(SOURCE_FOLDER); $(CC) $(LIKE_A_LIBRARY) $(USE_ANSI) $(BUTTON)/$(BUTTON:=.cpp)
	

#Run
run:
	$(EXECUTE)$(PLAY)

#Debug
debug:
	$(DEBUGGER) $(EXECUTE)$(PLAY)
