#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LINE_LEN 200
#define MAX_EVENTS 1000

typedef struct{
    int day;
    int month;
    int year;
}date;

typedef struct{
    char des[MAX_LINE_LEN];
    char zone[MAX_LINE_LEN];
    char loca[MAX_LINE_LEN];
    date dt;
    char dweek[MAX_LINE_LEN];
    char start[MAX_LINE_LEN];
    char end[MAX_LINE_LEN];
}event;

FILE* openfile(char *argv[]);
void readfile(FILE* fl, event evt[], int* sizep);
void printdate(event evt[], char *argv[], int size);
int compare_date (date d1, date d2);
void sort(event evt[], int size);

int main(int argc, char *argv[]) {
    event evt[MAX_EVENTS];
    FILE* fl = openfile(argv);
    int size = 0;
    readfile(fl, evt, &size);
    sort(evt, size);
    printf("\n\n\n\n\n");
    for (int i = 0; i < size; i++) {
        printf("%s\n", evt[i].des);
        printf("%s\n", evt[i].zone);
        printf("%s\n", evt[i].loca);
        printf("%d/%d/%d\n", evt[i].dt.year,evt[i].dt.month, evt[i].dt.day);
        printf("%s\n", evt[i].dweek);
        printf("%s\n", evt[i].start);
        printf("%s\n", evt[i].end);
    }
    printdate(evt, argv, size);
    return 0;
}

FILE* openfile(char *argv[]) {
    char ch[] = "=";
    char *temp = strtok(argv[3],ch);
    temp= strtok(NULL, ch);
    FILE* fl = fopen(temp, "r");
    return fl;
    if (fl == NULL) {
        printf("Unable to open the file for reading\n");
        return 0;
    }
}

void readfile(FILE* fl, event evt[], int* sizep) {
    int i = 0;
    char details[50] = "<description>";
    char lines[MAX_LINE_LEN];
    while(fgets(lines, MAX_LINE_LEN, fl) ) {
        if(strstr(lines, "</event>")!= NULL){
            i++;
        }else if(strstr(lines, details)!= NULL){
            char* tok = strtok(lines, ">");
            tok = strtok (NULL, ">");
            tok = strtok(tok, "<");
            char str[MAX_LINE_LEN];
            strcpy(str, tok);
            if (strcmp("<description>", details) == 0) {
                strcat (evt[i].des, str);
                printf("%s\n", evt[i].des);
                strcpy(details, "<timezone>");
            }
            else if (strcmp("<timezone>", details) == 0){
                strcat (evt[i].zone, str);
                printf("%s\n", evt[i].zone);
                strcpy(details, "<location>");
            }
            else if (strcmp("<location>", details) == 0) {
                strcat (evt[i].loca, str);
                printf("%s\n", evt[i].loca);
                strcpy(details, "<day>");
            }
            else if (strcmp("<day>", details) == 0) {
                int numb = atoi(str);
                evt[i].dt.day = numb;
                printf("%d\n", evt[i].dt.day);
                strcpy(details, "<month>");
            }
            else if (strcmp("<month>", details) == 0) {
                int numb = atoi(str);
                evt[i].dt.month = numb;
                printf("%02d\n", evt[i].dt.month);
                strcpy(details, "<year>");
            }
            else if (strcmp("<year>", details) == 0) {
                int numb = atoi(str);
                evt[i].dt.year =  numb;
                printf("%02d\n", evt[i].dt.year);
                strcpy(details, "<dweek>");
            }
            else if (strcmp("<dweek>", details) == 0) {
                strcat (evt[i].dweek, str);
                printf("%s\n", evt[i].dweek);
                strcpy(details, "<start>");
            }
            else if (strcmp("<start>", details) == 0) {
                strcat (evt[i].start, str);
                printf("%s\n", evt[i].start);
                strcpy(details, "<end>");
            }
            else if (strcmp("<end>",details) == 0) {
                strcat (evt[i].end, str);
                printf("%s\n", evt[i].end);
                strcpy(details, "<description>");
            }
        }
    }
    *sizep = i;
}

void printdate(event evt[], char *argv[], int size){
    char ch[] = "=";
    char *temp = strtok(argv[1],ch);
    temp= strtok(NULL, ch);
    date d_s;
    evt[0] = evt[0];
    sscanf(temp, "%d/%d/%d", &d_s.year, &d_s.month, &d_s.day);
    printf("%d",d_s.day);
    temp = strtok(argv[2],ch);
    temp= strtok(NULL, ch);
    date d_e;
    sscanf(temp, "%d/%d/%d", &d_e.year, &d_e.month, &d_e.day);
    printf("\n%d",size);
    event temp_evt[MAX_EVENTS] = evt;
    event *temp_evt_p = &temp_evt[0];
    for (int i = 0; i<size; i++) {
        if ((compare_date(evt[i].dt, d_s) == 1) || (compare_date(evt[i].dt, d_s) == 0)) {
            if ((compare_date(evt[i].dt, d_e) == -1) || (compare_date(evt[i].dt, d_e) == 0)) {
                *temp_evt_p = evt[i];
                printf(temp_evt[0].des);
            }
        }
    }
}

void sort(event evt[], int size) {
    int numb = 0;
    while (numb < size){
        for (int i = size-1; i >0; i--) {
            if (compare_date(evt[i-1].dt,evt[i].dt) == 1) {
                event temp = evt[i];
                evt[i] = evt[i-1];
                evt[i-1] = temp;
            }
        }
        numb++;
    }
}
int compare_date (date d1, date d2) {
    if (d1.year > d2.year) {
        return 1;
    }
    else if (d1.year < d2.year) {
        return -1;
    } else {
        if (d1.month > d2.month) {
            return 1;
        }else if (d1.month < d2.month) {
            return -1;
        } else {
            if (d1.day >d2.day) {
                return 1;
            } else if (d1.day < d2.day) {
                return -1;
            } else {
                return 0;
            }
        }
    }
}

