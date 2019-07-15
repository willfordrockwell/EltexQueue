#menu
CC = gcc
CCFLAGS = -g

LIBRARY = menu
SOURCES = Parse_Command.c 
SOURCES += strlwr.c
OBJECTS = $(SOURCES:.c=.o)

#Library Menu library from objects
all: $(OBJECTS)
	ar rc lib$(LIBRARY).a $(OBJECTS)

#Library Menu objects from sources
$(OBJECTS): $(SOURCES)
	$(CC) $(SOURCES) -c $(CCFLAGS)
