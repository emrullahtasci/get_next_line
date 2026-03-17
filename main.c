#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

void run_test(const char *filename)
{
    int fd = open(filename, O_RDONLY);
    char *line;

    printf("=== Testing file: %s ===\n", filename);
    if (fd < 0)
    {
        perror("open");
        return;
    }

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s\n", line); // manuel newline
        free(line);
    }

    close(fd);
    printf("\n");
}

int main(void)
{
    // 1️⃣ Tek satırlık dosya
    run_test("test_single_line.txt");

    // 2️⃣ Boş dosya
    run_test("empty.txt");

    // 3️⃣ Son satırda newline yok
    run_test("no_newline.txt");

    // 4️⃣ Yalnızca newline
    run_test("only_newlines.txt");

    // 5️⃣ Multi-FD testi
    int fd1 = open("test1.txt", O_RDONLY);
    int fd2 = open("test2.txt", O_RDONLY);
    char *line1;
    char *line2;

    printf("=== Testing multi-FD: test1.txt + test2.txt ===\n");
    while (1)
    {
        line1 = get_next_line(fd1);
        line2 = get_next_line(fd2);

        if (!line1 && !line2)
            break;

        if (line1)
        {
            printf("File1: %s\n", line1);
            free(line1);
        }
        if (line2)
        {
            printf("File2: %s\n", line2);
            free(line2);
        }
    }
    close(fd1);
    close(fd2);
    printf("\n");

    // 6️⃣ Çok uzun satır
    run_test("long_line.txt");

    return 0;
}
