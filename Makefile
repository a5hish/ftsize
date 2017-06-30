CC = gcc
TARGET = ftsize

all:$(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(TARGET).c -Wall -Werror -o $(TARGET)

clean:
	$(RM) -r $(TARGET)

.PHONY:install
install: 
	mkdir undefined
	cp $(TARGET) undefined/

.PHONY:uninstall
uninstall:
	rm -rf undefined
