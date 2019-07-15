CFLAGS = -lpthread
CC = gcc

SOURCES_SERVER = Change_Action.c
SOURCES_SERVER += Make_Message.c
SOURCES_SERVER += Server_Thread.c
SOURCES_SERVER += Server.c
OBJECTS_SERVER = $(SOURCES_SERVER:.c=.o)

SOURCES_CLIENT = Client.c
OBJECTS_CLIENT = $(SOURCES_CLIENT:.c=.o)
EXECUTABLE_SERVER = Server
EXECUTABLE_CLIENT = Client

LIB_LIST_DIR = list/
LIB_LIST = $(LIB_LIST_DIR:/=)
LIB_MENU_DIR = menu/
LIB_MENU = $(LIB_MENU_DIR:/=)

lib_List: 
	make -C $(LIB_LIST_DIR)

lib_Menu: 
	make -C $(LIB_MENU_DIR)

all: $(EXECUTABLE_SERVER) $(EXECUTABLE_CLIENT) lib_List lib_Menu

debug: clean
debug: CFLAGS += -g
debug: all

$(EXECUTABLE_SERVER): $(OBJECTS_SERVER)
	$(CC) $(OBJECTS_SERVER) -o $(EXECUTABLE_SERVER).elf $(CFLAGS) -L ./$(LIB_LIST) -l$(LIB_LIST) -L ./$(LIB_MENU) -l$(LIB_MENU)

$(EXECUTABLE_CLIENT): $(OBJECTS_CLIENT)
	$(CC) $(OBJECTS_CLIENT) -o $(EXECUTABLE_CLIENT).elf $(CFLAGS)

$(OBJECTS_CLIENT): $(SOURCES_CLIENT)
	$(CC) $(SOURCES_CLIENT) -c $(CFLAGS)

$(OBJECTS_SERVER): $(SOURCES_SERVER)
	$(CC) $(SOURCES_SERVER) -c $(CFLAGS)

.PHONY: clean
clean:
	rm *.elf *.o
