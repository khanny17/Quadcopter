
CC = ../../SysGCC/Raspberry/bin/arm-linux-gnueabihf-g++.exe 
CFLAGS = -ggdb
CCFLAGS = -std=c++11

TARGET = quad

default: $(TARGET)

$(TARGET):
	$(CC) $(CFLAGS) $(CCFLAGS) src/main/cpp/main.cpp -I src/AttitudeDeterminator/headers -I src/Motors/ -I src/Controller/ -I src/Utils/ -o $(TARGET)

clean:
	$(RM) quad *.o 
