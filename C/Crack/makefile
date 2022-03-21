SOURCES       = crack.c \
				Text/Text.c

OBJECTS       = crack.o \
				Text.o

TARGET 		  = Crack

DEL_FILE      = rm -f


all:  $(OBJECTS)  
	gcc -o $(TARGET) $(OBJECTS)

crack.o: crack.c \
		Text/Text.h \
		Struct/Struct.h
	gcc -c -o crack.o crack.c

Text.o: Text/Text.c Text/Text.h \
		Struct/Struct.h
	gcc -c -o Text.o Text/Text.c

clean: 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) $(TARGET)