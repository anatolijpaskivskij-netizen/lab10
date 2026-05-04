#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insertInMiddle(const char *filename, const char *newText);

int main() {
    int choice;
    char filename[] = "data.txt";

    while (1) {
        printf("\n--- МЕНЮ ---\n");
        printf("1. Переглянути вміст файлу\n");
        printf("2. Додати рядок у середину файлу\n");
        printf("0. Вихід\n");
        printf("Ваш вибір: ");

        if (scanf("%d", &choice) != 1) {
            printf("Помилка: введіть число!\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1: {
                FILE *f = fopen(filename, "r");
                if (!f) {
                    printf("Файл не знайдено.\n");
                } else {
                    char buf[1024];
                    int n = 1;
                    printf("\n--- Вміст файлу %s ---\n", filename);
                    while (fgets(buf, sizeof(buf), f)) {
                        printf("%d: %s", n++, buf);
                    }
                    fclose(f);
                }
                break;
            }
            case 2: {
                char newText[1024];
                printf("Введіть рядок для вставки: ");
                getchar();
                fgets(newText, sizeof(newText), stdin);
                newText[strcspn(newText, "\n")] = 0;

                insertInMiddle(filename, newText);
                break;
            }
            case 0:
                return 0;
            default:
                printf("Невірний вибір.\n");
        }
    }
    return 0;
}
void insertInMiddle(const char *filename, const char *newText) {
    FILE *src = fopen(filename, "r");
    FILE *temp = fopen("temp.tmp", "w");

    if (src == NULL || temp == NULL) {
        printf("\n[ПОМИЛКА] Не вдалося відкрити файл для обробки.\n");
        if (src) fclose(src);
        return;
    }

    char buffer[1024];
    int totalLines = 0;

    while (fgets(buffer, sizeof(buffer), src)) {
        totalLines++;
    }
    rewind(src);

    int middleLine = totalLines / 2;
    int currentLine = 0;
    int inserted = 0;

    while (fgets(buffer, sizeof(buffer), src)) {
        if (currentLine == middleLine) {
            fputs(newText, temp);
            fputs("\n", temp);
            inserted = 1;
        }
        fputs(buffer, temp);
        currentLine++;
    }

    if (totalLines == 0) {
        fputs(newText, temp);
        fputs("\n", temp);
        inserted = 1;
    }

    fclose(src);
    fclose(temp);

    if (inserted) {
        remove(filename);
        rename("temp.tmp", filename);
        printf("\nРядок успішно вставлено у середину (після %d рядка).\n", middleLine);
    } else {
        remove("temp.tmp");
        printf("\n[УВАГА] Не вдалося виконати вставку.\n");
    }
}