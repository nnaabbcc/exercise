
TARGET=crc32sum
CC64=g++

CFLAGS=-g

all : $(TARGET)

$(TARGET) : main.cpp
	$(CC64) $(CFLAGS) -o $@ $< 

clean:
	rm -f $(TARGET)
