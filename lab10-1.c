#include <stdio.h>
#include <stdlib.h>

int main() {
    int choice;
    char filename[] = "numbers.txt";
    FILE *file;

     while (1) {
        printf("\n--МЕНЮ ПРОГРАМИ--\n");
        printf("1. Визначити кількість непарних чисел у файлі %s\n", filename);
        printf("2. Довідка про програму\n");
        printf("0. Вихід\n");
        printf("Ваш вибір: ");

        if (scanf("%d", &choice) != 1) {
            printf("Помилка: введіть число!\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1:
               file = fopen(filename, "r");
                if (file == NULL) {
                    printf("\n[ПОМИЛКА] Не вдалося відкрити файл '%s'.\n", filename);
                    printf("Переконайтеся, що файл створений у папці з проєктом.\n");
                } else {
                    int number;
                    int odd_count = 0;

                    printf("\nНепарні числа у файлі: ");
                    while (fscanf(file, "%d", &number) != EOF) {
                        if (number % 2 != 0) {
                            printf("%d ", number);
                            odd_count++;
                        }
                    }

                    printf("\n\nРезультат: знайдено %d непарних чисел.\n", odd_count);
                    fclose(file);
                }
                break;

            case 2:
                printf("\n--- ДОВІДКА ---\n");
                printf("Програма зчитує цілі числа з файлу та шукає непарні.\n");
                printf("Файл %s повинен містити числа, розділені пробілами.\n", filename);
                break;


            case 0:
                printf("Вихід з програми. Гарного дня!\n");
                return 0;
                
            default:
                printf("Невірний вибір!Спробуйте ще раз\n");
                break;
        }
     }

    return 0;
}