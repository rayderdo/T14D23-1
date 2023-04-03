#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>


typedef struct  { // структур с целочисленными полями: год, месяц, день, час, минута, секунда, статус (0/1), код.
  int year;
  int month;
  int day;
  int hour;
  int minute;
  int second;
  int status;
  int cod;
}door_state;

int door_state_cmp(door_state* ds1, door_state* ds2) {
    if (ds1->year > ds2->year)
    {
        return 1;
    }else if(ds1->year == ds2->year) {
        if (ds1->month > ds2->month)
        {
            return 1;
        }else if (ds1->month == ds2->month)
        {
            if (ds1->day > ds2->day)
            {
                return 1;
            }else if (ds1->day == ds2->day) {
                if (ds1->hour > ds2->hour)
                {
                    return 1;
                }else if(ds1->hour == ds2->hour) {
                    if(ds1->minute > ds2->minute) {
                        return 1;
                    }else if(ds1->minute == ds2->minute) {
                        if(ds1->second > ds2->second) {
                            return 1;
                        }else if(ds1->second == ds2->second) {
                            return 0;
                        }else
                            return -1;
                    }else
                        return -1;
                }else
                    return -1;    
            }else
                return -1;  
        }else
            return -1; 
    }else
        return -1;
        
}

void file_print(FILE* file) {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
    int status;
    int cod;

    while (!feof(file)) {
        fread(&year, sizeof(int), 1, file);
        fread(&month, sizeof(int), 1, file);
        fread(&day, sizeof(int), 1, file);
        fread(&hour, sizeof(int), 1, file);
        fread(&minute, sizeof(int), 1, file);
        fread(&second, sizeof(int), 1, file);
        fread(&status, sizeof(int), 1, file);
        fread(&cod, sizeof(int), 1, file);

        printf("%d %d %d %d %d %d %d %d\n", year, month, day, hour, minute,
                second, status, cod);
    }
}

void sort_and_print(FILE* file) {
    char temp_file[100] = "temp";
    FILE* file_temp = fopen(temp_file, "w+b");

    int counter = 0;
        int year;
        int month;
        int day;
        int hour;
        int minute;
        int second;
        int status;
        int cod;
        while (!feof(file)) {
            fread(&year, sizeof(int), 1, file);
            fread(&month, sizeof(int), 1, file);
            fread(&day, sizeof(int), 1, file);
            fread(&hour, sizeof(int), 1, file);
            fread(&minute, sizeof(int), 1, file);
            fread(&second, sizeof(int), 1, file);
            fread(&status, sizeof(int), 1, file);
            fread(&cod, sizeof(int), 1, file);
            counter++;
        }

        rewind(file);

        for (int i = 1; i < counter; i++)
        {
            door_state ds;
            int tell;

            door_state ds_min = {9998, 9999, 9999, 9999, 9999, 9999, 9999, 9999};

            while (!feof(file)) {
                fread(&ds.year, sizeof(int), 1, file);
                fread(&ds.month, sizeof(int), 1, file);
                fread(&ds.day, sizeof(int), 1, file);
                fread(&ds.hour, sizeof(int), 1, file);
                fread(&ds.minute, sizeof(int), 1, file);
                fread(&ds.second, sizeof(int), 1, file);
                fread(&ds.status, sizeof(int), 1, file);
                fread(&ds.cod, sizeof(int), 1, file);


                if (door_state_cmp(&ds, &ds_min) == -1) {
                    ds_min = ds;
                    tell = ftell(file); 
                }
            }

            if(file_temp){
                fwrite(&ds_min.year, sizeof(int), 1, file_temp);
                fwrite(&ds_min.month, sizeof(int), 1, file_temp);
                fwrite(&ds_min.day, sizeof(int), 1, file_temp);
                fwrite(&ds_min.hour, sizeof(int), 1, file_temp);
                fwrite(&ds_min.minute, sizeof(int), 1, file_temp);
                fwrite(&ds_min.second, sizeof(int), 1, file_temp);
                fwrite(&ds_min.status, sizeof(int), 1, file_temp);
                fwrite(&ds_min.cod, sizeof(int), 1, file_temp);
            }

            int temp[8] = {9999, 9999, 9999, 9999, 9999, 9999, 9999, 9999};
            fseek(file, (tell-32), SEEK_SET);
            fwrite(&temp, sizeof(int), 8, file);
            rewind(file);
        }

        rewind(file_temp);
        file_print(file_temp);
        
        rewind(file_temp);
        rewind(file);
        door_state ds;
        while (!feof(file_temp) && !feof(file)) {
            fread(&ds.year, sizeof(int), 1, file_temp);
            fread(&ds.month, sizeof(int), 1, file_temp);
            fread(&ds.day, sizeof(int), 1, file_temp);
            fread(&ds.hour, sizeof(int), 1, file_temp);
            fread(&ds.minute, sizeof(int), 1, file_temp);
            fread(&ds.second, sizeof(int), 1, file_temp);
            fread(&ds.status, sizeof(int), 1, file_temp);
            fread(&ds.cod, sizeof(int), 1, file_temp);

            fwrite(&ds.year, sizeof(int), 1, file);
            fwrite(&ds.month, sizeof(int), 1, file);
            fwrite(&ds.day, sizeof(int), 1, file);
            fwrite(&ds.hour, sizeof(int), 1, file);
            fwrite(&ds.minute, sizeof(int), 1, file);
            fwrite(&ds.second, sizeof(int), 1, file);
            fwrite(&ds.status, sizeof(int), 1, file);
            fwrite(&ds.cod, sizeof(int), 1, file);
        }
}

int main() {

  int menu_item;
  scanf("%d", &menu_item);

  switch (menu_item) {
    case 0: // 0 - вывод содержимого файла в консоль
        char path[100];
        scanf("%s", path);

        FILE *file = fopen(path, "rb");

        if (!file) {
        printf("n/a");
        return 0;
        }

        file_print(file);

        fclose(file);
        break;
    case 1: // 1 - сортировка содержимого файла и вывод на экран

        scanf("%s", path);
        file = fopen(path, "r+b");

        if (!file) {
        printf("n/a");
        return 0;
        }

        sort_and_print(file);

        fclose(file);
        break;
  case 2: // 2 - добавление записи, сортировка и вывод на экран
    scanf("%s", path);
    file = fopen(path, "a+b");

    if (!file) {
    printf("n/a");
    return 0;
    }

    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
    int status;
    int cod;
    scanf("%d %d %d %d %d %d %d %d", &year, &month, &day, &hour, &minute, &second, &status, &cod);

    fwrite(&year, sizeof(int), 1, file);
    fwrite(&month, sizeof(int), 1, file);
    fwrite(&day, sizeof(int), 1, file);
    fwrite(&hour, sizeof(int), 1, file);
    fwrite(&minute, sizeof(int), 1, file);
    fwrite(&second, sizeof(int), 1, file);
    fwrite(&status, sizeof(int), 1, file);
    fwrite(&cod, sizeof(int), 1, file);

    fclose(file);
    file = fopen(path, "r+b");
    sort_and_print(file);
    fclose(file);

    break;
  default:
    printf("n/a");
    break;
  }

  return 0;
}