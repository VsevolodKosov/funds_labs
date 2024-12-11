# Пути к директориям
BASE_DIR = ../../
TASK_DIR = .
ADDITIONAL_DIR = $(BASE_DIR)/basis/additionally

# Исходные файлы
SRC = $(TASK_DIR)/func.c $(TASK_DIR)/task.c

# Заголовочные файлы
INC = -I$(TASK_DIR) -I$(ADDITIONAL_DIR)

# Имя итогового исполнимого файла
OUT = $(TASK_DIR)/program

# Компилятор и флаги
CC = gcc
CFLAGS = -Wall -std=c99 

# Основная цель
all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(INC) -o $(OUT) 

# Чистка
clean:
	rm -f $(OUT)

# Фикс для перегенерации Makefile
.PHONY: all clean
