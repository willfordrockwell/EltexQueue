#list
CC = gcc
CCFLAGS = -g

LIBRARY = list
SOURCES = Add_Pair.c 
SOURCES += Del_Pair.c
OBJECTS = $(SOURCES:.c=.o)

#Library Menu library from objects
all: $(OBJECTS)
	ar rc lib$(LIBRARY).a $(OBJECTS)

#Library Menu objects from sources
$(OBJECTS): $(SOURCES)
	$(CC) $(SOURCES) -c $(CCFLAGS)
