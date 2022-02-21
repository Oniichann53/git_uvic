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
void final_event(event evt[], char *argv[], int size, event final_evt[], int *p);
int compare_date (date d1, date d2);
int compare_time(char time1[], char time2[]);
void sort(event evt[], int size);
void convert_date(date dt);
void output(event evt[],int size);
void convert_event(event evt);



int main(int argc, char *argv[]) {
    event evt[MAX_EVENTS];
    FILE* fl = openfile(argv);
    int size = 0;
    readfile(fl, evt, &size);
    sort(evt, size);
    event final_evt[MAX_EVENTS];
    int final_size = 0;
    final_event(evt, argv, size, final_evt, &final_size);
    output(final_evt, final_size);
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
                strcpy(details, "<timezone>");
            }
            else if (strcmp("<timezone>", details) == 0){
                strcat (evt[i].zone, str);
                strcpy(details, "<location>");
            }
            else if (strcmp("<location>", details) == 0) {
                strcat (evt[i].loca, str);
                strcpy(details, "<day>");
            }
            else if (strcmp("<day>", details) == 0) {
                int numb = atoi(str);
                evt[i].dt.day = numb;
                strcpy(details, "<month>");
            }
            else if (strcmp("<month>", details) == 0) {
                int numb = atoi(str);
                evt[i].dt.month = numb;
                strcpy(details, "<year>");
            }
            else if (strcmp("<year>", details) == 0) {
                int numb = atoi(str);
                evt[i].dt.year =  numb;
                strcpy(details, "<dweek>");
            }
            else if (strcmp("<dweek>", details) == 0) {
                strcat (evt[i].dweek, str);
                strcpy(details, "<start>");
            }
            else if (strcmp("<start>", details) == 0) {
                strcat (evt[i].start, str);
                strcpy(details, "<end>");
            }
            else if (strcmp("<end>",details) == 0) {
                strcat (evt[i].end, str);
                strcpy(details, "<description>");
            }
        }
    }
    *sizep = i;
}

void final_event(event evt[], char *argv[], int size, event final_evt[], int *p){
    char ch[] = "=";
    char *temp = strtok(argv[1],ch);
    temp= strtok(NULL, ch);
    date d_s;
    evt[0] = evt[0];
    sscanf(temp, "%d/%d/%d", &d_s.year, &d_s.month, &d_s.day);
    temp = strtok(argv[2],ch);
    temp= strtok(NULL, ch);
    date d_e;
    sscanf(temp, "%d/%d/%d", &d_e.year, &d_e.month, &d_e.day);
    event *final_evt_p = &final_evt[0];
    for (int i = 0; i<size; i++) {
        if ((compare_date(evt[i].dt, d_s) == 1) || (compare_date(evt[i].dt, d_s) == 0)) {
            if ((compare_date(evt[i].dt, d_e) == -1) || (compare_date(evt[i].dt, d_e) == 0)) {
                *final_evt_p = evt[i];
                (*p)++;
                final_evt_p++;
            }
        }
    }
    
}

void sort(event evt[], int size) {
    int numb = 0;
    while (numb < size){
        for (int i = size-1; i >0; i--) {
            if(compare_date(evt[i-1].dt,evt[i].dt) == 1) {
                event temp = evt[i];
                evt[i] = evt[i-1];
                evt[i-1] = temp;
            } else if (compare_date(evt[i-1].dt,evt[i].dt) == 0){
            	if (compare_time(evt[i-1].start, evt[i].start) == 1) {
            		event temp = evt[i];
                	evt[i] = evt[i-1];
                	evt[i-1] = temp;
                }
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

int compare_time(char time1[], char time2[]) {
    int hr1;
    int min1;
    int hr2;
    int min2;
	sscanf(time1, "%d:%d", &hr1, &min1);
	sscanf(time2, "%d:%d", &hr2, &min2);
	if (hr1 > hr2) {
		return 1;
	} else if (hr1 < hr2) {
		return -1;
	} else {
        if (min1 > min2) {
            return 1;
        } else if (min1 < min2) {
            return -1;
        } else {
            return 0;
        }
	}
}

void convert_date(date dt) {
    if (dt.month == 1) {
        printf("%d January, %d\n", dt.day, dt.year);
    }
    if (dt.month == 2) {
        printf("%d Febuary, %d\n", dt.day, dt.year);
    }
    if (dt.month == 3) {
        printf("%d March, %d\n", dt.day, dt.year);
    }
    if (dt.month == 4) {
        printf("%d April, %d\n", dt.day, dt.year);
    }
    if (dt.month == 5) {
        printf("%d May, %d\n", dt.day, dt.year);
    }
    if (dt.month == 6) {
        printf("%d June, %d\n", dt.day, dt.year);
    }
    if (dt.month == 7) {
        printf("%d July, %d\n", dt.day, dt.year);
    }
    if (dt.month == 8) {
        printf("%d August, %d\n", dt.day, dt.year);
    }
    if (dt.month == 9) {
        printf("%d September, %d\n", dt.day, dt.year);
    }
    if (dt.month == 10) {
        printf("%d October, %d\n", dt.day, dt.year);
    }
    if (dt.month == 11) {
        printf("%d November, %d\n", dt.day, dt.year);
    }
    if (dt.month == 12) {
        printf("%d December, %d\n", dt.day, dt.year);
    }
}

void convert_event(event evt) {
    int hr_s;
    int min_s;
    int hr_e;
    int min_e;
    char ch_s[50];
    char ch_e[50];
    char am[] = "AM";
    char pm[] = "PM";
	sscanf(evt.start, "%d:%d", &hr_s, &min_s);
	sscanf(evt.end, "%d:%d", &hr_e, &min_e);
    if (hr_s < 12) {
        strcpy(ch_s, am);
    } else {
        strcpy(ch_s, pm);
        if (hr_s != 12) {
            hr_s -= 12;
        }
    }
    if (hr_e < 12) {
        strcpy(ch_e, am);
    } else {
        strcpy(ch_e, pm);
        if (hr_e != 12) {
            hr_e -= 12;

        }
    }
    //printf("\n%s, %s\n",ch_s, ch_e);
    printf("%02d:%02d %s to %02d:%02d %s: %s {{%s}} | %s\n", hr_s, min_s, ch_s, hr_e, min_e, ch_e, evt.des, evt.loca, evt.zone);
}

void output(event evt[], int size) {
    convert_date(evt[0].dt);
    printf("‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐\n");
    convert_event(evt[0]);
    for (int i = 1; i < size; i++) {
        if (compare_date(evt[i].dt,evt[i-1].dt) == 0) {
            convert_event(evt[i]);
        } else {
            printf("\n");
            convert_date(evt[i].dt);
            printf("‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐\n");
            convert_event(evt[i]);
        }
    }
}