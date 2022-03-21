#include "Text/Text.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


char* path = "/home/d0p1er/.dosbox/DOSBox/Bin/FUHAKER.COM";

int main() {
	int TikTok = 0;
	printf("vzlomator_jopi_MAXXA v 3 2 2\n");

	char* console_print = """ 0       0     0     0   0    000     0        00    0      0\
							  00     00     0     0  0    0        0       0  0    0    0 \
							  0 0   0 0    0 0    0 0    0        0 0     0    0    0  0  \
							  0  0 0  0   0   0   00    0        0   0   0      0    00   \
							  0   0   0  0     0  00    0       0     0  0      0    00   \
							  0       0 000000000 0 0    0     0       0  0    0    0  0  \
							  0       0 0       0 0  0    0    0       0   0  0    0    0 \
							  0       0 0       0 0   0    000 0       0    00    0      0""";

	printf("Поиск жопы...\n");
	usleep(5000000L);
	printf("Обнаружена жопа Макса 2.0...\n");
	usleep(5000000L);
	printf("Поиск ОТВЕРСТИЯ...\n");
	usleep(5000000L);
	printf("Обнаружено ОТВЕРСТИЕ в жопе Макса. Проверка валидности жопы...\n");
	usleep(2500000L);
	printf("%s\n", console_print);
	usleep(2500000L);
	printf("Жопа валидна! Подготовка к взлому...\n");
	usleep(1000000L);
	printf("ВНИМАНИЕ!!! Взламываю жопу Макса!\n");

	while (TikTok < 80) {
		printf("#");
		usleep(50000);
		fflush(stdout);
		TikTok++;
	}
	
	printf("\nСистемное сообщение: Жопа Макса взломана. Забирайте.\n");

	size_t size_file = GetFileSize(path);
	char* buffer = GetTextFromFile(path, size_file);
	buffer[size_file - 1] = 242;
	WriteText(buffer, path, size_file);
}
