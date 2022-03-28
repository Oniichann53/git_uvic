/** @file process_cal3.c
 *  @brief A pipes & filters program that uses dynamic memory allocation in C for processing iCalendar events as nodes in
 *  a linked list, and printing them in a user-friendly format.
 *  @author Brian K.
 *  @author Rob P.
 *  @author Mike Z.
 *  @author Adam N.
 *  @author Felipe R.
 *  @author Hausi M.
 *  @author Juan G.
 *  @author Saasha J.
 *  @author STUDENT_NAME
 *
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "emalloc.h"
#include "ics.h"
#include "listy.h"

// Function prototypes
event_t *new_event(event_t *);
void print_formatted_date(char *);
void print_formatted_event(char *, char *, char *, char *);
int process_program_args(int, char *[], char **, struct tm *, struct tm *);
void new_list(char *, node_t **);
void read_line(char *, node_t **);
void clear_event(event_t *);
void add_recurring_events(node_t **);
int is_date_in_range(char *, struct tm *, struct tm *);
int compare_time(char *, char *, int);
void format_date(char *, const char *, const int, int);
void date_increment(char *, const char *, const int);
void print_list(node_t *, struct tm *, struct tm *);

/**
 * Function:  new_event
 * --------------------
 * @brief Creates a event instance containing event information using dynamic memory allocation (i.e., emalloc())
 *
 * This function allows to reserve memory for an event using emalloc(). For this, we invoke emalloc() appropriately to reserver the space required for the event and then
 * copy the data from the temporary event passed as an argument to new event instance created with emalloc().
 *
 * @param event The temporary event that contains the event info.
 * @return event_t* The new instance of the event that has been dynamically allocated in memory using emalloc(). This event will be the value of the node in the linked list.
 *
 */
event_t *new_event(event_t *event)
{
    day *wkst = (day*)emalloc(sizeof(day));
    day *byday = (day*)emalloc(sizeof(day));
    frequency *freq = (frequency*)emalloc(sizeof(frequency));
    char *until = (char*)emalloc(sizeof(DATE_LEN));
    repetition_t *repetition = (repetition_t*)emalloc(REPETITION_LEN);
    *wkst = event->repetition.wkst;
    *byday = event->repetition.byday;
    *freq = event->repetition.freq;
    strcpy(until, event->repetition.until);
    repetition->wkst = *wkst;
    repetition->byday = *byday;
    repetition->freq = *freq;
    strcpy(repetition->until, until);
    char *description = (char*)emalloc(SUMMARY_LEN);
    char *start_date = (char*)emalloc(DATE_LEN);
    char *end_date = (char*)emalloc(DATE_LEN);
    char *location = (char*)emalloc(LOCATION_LEN);
    strcpy(description, event->description);
    strcpy(start_date, event->start_date);
    strcpy(end_date, event->end_date);
    strcpy(location, event->location);
    event_t *temp = (event_t*)emalloc(sizeof(event_t));
    temp->repetition = *repetition;
    strcpy(temp->description, description);
    strcpy(temp->start_date, start_date);
    strcpy(temp->end_date, end_date);
    strcpy(temp->location, location);
    return temp;
}

/**
 * Function:  print_formatted_date
 * -------------------------------
 * @brief Prints a date in the required format.
 *
 * This is a simple auxiliary function that is used to print each day in the required format. That is, given a string with a date (e.g., "March 10, 2022 (Thu)"), the function
 * will print (using the printf() function) the string and the appropriate number of dashes\hyphens underneat the date. An example of the ouput produced by this function is
 * shown below:
 *
 * March 10, 2022 (Thu)
 * --------------------
 *
 * @param date The date to format (e.g., "March 10, 2022 (Thu)")
 */
void print_formatted_date(char *date)
{
    printf("%s\n", date);
    int length = strlen(date);
    for (int i = 0; i < length; i++) {
        printf("-");
    }
    printf("\n");
}

/**
 * Function:  print_formatted_event
 * --------------------------------
 * @brief Prints an event in the required format.
 *
 * This is an auxiliary function that is used to print each event in the required format. Given the arguments passed to the function and by using printf(), the function prints
 * the event in the required format (e.g., " 8:00 AM to 11:00 AM: F1 2022 Pre-Season Testing Day 4 - Session 1 {{Sakhir, Bahrain}}").
 *
 * @param start_time The start time of the event to be printed.
 * @param end_time The start time of the event to be printed.
 * @param description The description\summary of the event to be printed.
 * @param location The location of the event to be printed.
 *
 */

void print_formatted_event(char *start_time, char *end_time, char *description, char *location)
{
    printf("%s to %s: %s {{%s}}\n", start_time, end_time, description, location);
}

/**
 * Function:  process_program_args
 * -------------------------------
 * @brief Validates the arguments passed to the program.
 *
 * @param argc The number of arguments passed.
 * @param argv The array of arguments passed.
 * @param filename The path to the .ics file to process.
 * @param from_date The range of the dates to process.
 * @param to_date  The range of the dates to process.
 *
 * @return int 0: no errors produced during execution ; 1: errors produced during execution
 */
int process_program_args(int argc, char *argv[], char **filename, struct tm *from_date, struct tm *to_date)
{
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./program --start=yyyy/mm/dd --end=yyyy/mm/dd --file=icsfile\n");
        return 1;
    }
    for (int i = 0; i < argc; i++)
    {
        if (strncmp(argv[i], "--start=", 8) == 0)
        {
            sscanf(argv[i], "--start=%d/%d/%d", &from_date->tm_year, &from_date->tm_mon, &from_date->tm_mday);
        }
        else if (strncmp(argv[i], "--end=", 6) == 0)
        {
            sscanf(argv[i], "--end=%d/%d/%d", &to_date->tm_year, &to_date->tm_mon, &to_date->tm_mday);
        }
        else if (strncmp(argv[i], "--file=", 7) == 0)
        {
            *filename = argv[i] + 7;
        }
    }
    from_date->tm_hour = 0;
    from_date->tm_min = 0;
    from_date->tm_sec = 0;
    to_date->tm_hour = 0;
    to_date->tm_min = 0;
    to_date->tm_sec = 0;
    if (from_date->tm_year == 0 || to_date->tm_year == 0 || filename == NULL)
    {
        fprintf(stderr, "Usage: ./program --start=yyyy/mm/dd --end=yyyy/mm/dd --file=icsfile\n");
        return 1;
    }
    return 0;
}

/**
 * Function:  new_list
 * -------------------
 * @brief Creates a new linked list using the .ics passed as an argument to the program.
 *
 * @param filename The path to the .ics file passed to the program.
 * @param list The head node of the list.
 *
 */
void new_list(char *filename, node_t **list)
{
    FILE *file = NULL;
    char line[MAX_LINE_LEN] = "\0";
    file = fopen(filename, "r");
    // Loop to iterate over each line in the file
    while (fgets(line, sizeof(line), file) != NULL)
        read_line(line, list);
    fclose(file);
}

/**
 * Function:  read_line
 * --------------------
 * @brief Reads a line form the .ics file passed as an argument to the program.
 *
 * @param line The line to read.
 * @param list The linked list used to store the events.
 *
 */
void read_line(char *line, node_t **list)
{
    node_t **temp = list;
    char t[REPETITION_LEN] = "\0";
    event_t event;
    // Process event info
    if (strncmp(line, "BEGIN:VEVENT", 12) == 0)
        clear_event(&event);
    if (strncmp(line, "DTSTART:", 8) == 0)
        sscanf(line, "DTSTART:%s", event.start_date);
    if (strncmp(line, "DTEND:", 6) == 0)
        sscanf(line, "DTEND:%s", event.end_date);
    // Process repetition rule
    if (strncmp(line, "RRULE:", 6) == 0)
    {
        sscanf(line, "RRULE:%s", t);
        char *token = strtok(t, ";");
        while (token != NULL)
        {
            if (strncmp(token, "FREQ=", 5) == 0)
            {
                sscanf(token, "FREQ=%s", t);
                if (strncmp(t, "WEEKLY", 6) == 0)
                    event.repetition.freq = WEEKLY;
            }
            if (strncmp(token, "WKST=", 5) == 0)
            {
                sscanf(token, "WKST=%s", t);
                if (strncmp(t, "SU", 2) == 0)
                    event.repetition.wkst = SU;
                if (strncmp(t, "MO", 2) == 0)
                    event.repetition.wkst = MO;
                if (strncmp(t, "TU", 2) == 0)
                    event.repetition.wkst = TU;
                if (strncmp(t, "WE", 2) == 0)
                    event.repetition.wkst = WE;
                if (strncmp(t, "TH", 2) == 0)
                    event.repetition.wkst = TH;
                if (strncmp(t, "FR", 2) == 0)
                    event.repetition.wkst = FR;
                if (strncmp(t, "SA", 2) == 0)
                    event.repetition.wkst = SA;
            }
            if (strncmp(token, "UNTIL=", 6) == 0)
                sscanf(token, "UNTIL=%s", event.repetition.until);
            if (strncmp(token, "BYDAY=", 6) == 0)
            {
                sscanf(token, "BYDAY=%s", t);
                if (strncmp(t, "SU", 2) == 0)
                    event.repetition.byday = SU;
                if (strncmp(t, "MO", 2) == 0)
                    event.repetition.byday = MO;
                if (strncmp(t, "TU", 2) == 0)
                    event.repetition.byday = TU;
                if (strncmp(t, "WE", 2) == 0)
                    event.repetition.byday = WE;
                if (strncmp(t, "TH", 2) == 0)
                    event.repetition.byday = TH;
                if (strncmp(t, "FR", 2) == 0)
                    event.repetition.byday = FR;
                if (strncmp(t, "SA", 2) == 0)
                    event.repetition.byday = SA;
            }
            token = strtok(NULL, ";");
        }
    }
    // Process remaining event info
    if (strncmp(line, "LOCATION:", 9) == 0)
        sscanf(line, "LOCATION:%[^\n]", event.location);
    if (strncmp(line, "SUMMARY:", 8) == 0)
        sscanf(line, "SUMMARY:%[^\n]", event.description);
    if (strncmp(line, "END:VEVENT", 10) == 0)
        *temp = add_inorder(*temp, new_node(new_event(&event)));
}

/**
 * Function:  clear_event
 * ----------------------
 * @brief Allows clearing/resetting the values from an event.
 *
 * @param event The event to process.
 *
 */
void clear_event(event_t *event)
{
    strcpy(event->start_date, "");
    strcpy(event->end_date, "");
    strcpy(event->location, "");
    strcpy(event->description, "");
    strcpy(event->repetition.until, "");
    event->repetition.byday = NO_D;
    event->repetition.wkst = NO_D;
    event->repetition.freq = NO_F;
}

/**
 * Function:  add_recurring_events
 * -------------------------------
 * @brief Allows to generate nodes in the list for the events with repetition rules.
 *
 * @param list The list where the nodes will be added.
 *
 */
void add_recurring_events(node_t **list)
{
    node_t *curr = *list;
    char incr_date[MAX_LINE_LEN] = "\0";
    char until_date[MAX_LINE_LEN] = "\0";
    char curr_date[MAX_LINE_LEN] = "\0";
    int freq = 1;
    while (curr != NULL)
    {
        // Validate that the event repeats
        if (strlen(curr->val->repetition.until) > 0)
        {
            strcpy(until_date, curr->val->repetition.until);
            strcpy(curr_date, curr->val->start_date);
            freq = curr->val->repetition.freq;
            while (1)
            {
                date_increment(incr_date, curr_date, freq);
                if (compare_time(incr_date, until_date, 1) > 0)
                    break;
                node_t *new = new_node(new_event(curr->val));
                strcpy(new->val->start_date, incr_date);
                strcpy(new->val->repetition.until, "");
                curr = add_inorder(curr, new);
                strcpy(curr_date, incr_date);
            }
        }
        curr = curr->next;
    }
}

/**
 * Function:  is_date_in_range
 * ---------------------------
 * @brief Validates if a given date is in a particular range of dates.
 *
 * @param a The date to analyze.
 * @param b The lower bound of the range of dates.
 * @param c The upper bound of the range of dates.
 * @return int 0: The date is not within the range; 1: The date is whithin the range.
 *
 */
int is_date_in_range(char *a, struct tm *b, struct tm *c)
{
    struct tm date_1 = {0};
    struct tm date_2 = *b;
    struct tm date_3 = *c;
    int in_range = 0;
    memset(&date_1, 0, sizeof(struct tm));
    sscanf(a, "%4d%2d%2dT", &date_1.tm_year, &date_1.tm_mon, &date_1.tm_mday);
    date_1.tm_year -= 1900;
    date_1.tm_mon -= 1;
    date_2.tm_year -= 1900;
    date_2.tm_mon -= 1;
    date_3.tm_year -= 1900;
    date_3.tm_mon -= 1;
    in_range = (difftime(mktime(&date_1), mktime(&date_2)) >= 0) && (difftime(mktime(&date_1), mktime(&date_3)) <= 0);
    return in_range;
}

/**
 * Function:  compare_time
 * ----------------------
 * @brief Compares two YYYYMMDDTHHMMSS strings and determine if they represent the same calendar date
 *
 * @param a The first date to compare.
 * @param b The second date to compare.
 * @param flag 0: Compares the YYMMDD only. ; 1: Compares the entire YYYYMMDDTHHMMSS
 * @return int >0:  if date_1 (a) is later than date_2 (b); ==0: if date_1 (a) is equal to date_2 (b); <0: if date_1 (a) is sooner than date_2 (b).
 *
 */
int compare_time(char *a, char *b, int flag)
{
    if (flag == 0)
        return atoi(a) - atoi(b);
    struct tm date_1 = {0};
    struct tm date_2 = {0};
    memset(&date_1, 0, sizeof(struct tm));
    sscanf(a, "%4d%2d%2dT%2d%2d%2d",
           &date_1.tm_year, &date_1.tm_mon, &date_1.tm_mday,
           &date_1.tm_hour, &date_1.tm_min, &date_1.tm_sec);
    date_1.tm_year -= 1900;
    date_1.tm_mon -= 1;
    memset(&date_2, 0, sizeof(struct tm));
    sscanf(b, "%4d%2d%2dT%2d%2d%2d",
           &date_2.tm_year, &date_2.tm_mon, &date_2.tm_mday,
           &date_2.tm_hour, &date_2.tm_min, &date_2.tm_sec);
    date_2.tm_year -= 1900;
    date_2.tm_mon -= 1;
    return (int)difftime(mktime(&date_1), mktime(&date_2));
}

/**
 * Function:  format_date
 * ----------------------
 * @brief Allows to transform a string in the form YYYYMMDDTHHMMSS into th required format (i.e., stored in formatted_time).
 *
 * @param formatted_time The variable where the formatted string will be stored.
 * @param dt_time The string to format.
 * @param len The length of the string to format.
 * @param flag 0: Format the time (ie. 12:00 PM). ; 1: Format the date (ie. April 20, 2021 (Tue)).
 */
void format_date(char *formatted_time, const char *dt_time, const int len, int flag)
{
    struct tm temp_time = {0};
    time_t full_time = {0};
    memset(&temp_time, 0, sizeof(struct tm));
    sscanf(dt_time, "%4d%2d%2dT%2d%2d%2d",
           &temp_time.tm_year, &temp_time.tm_mon, &temp_time.tm_mday,
           &temp_time.tm_hour, &temp_time.tm_min, &temp_time.tm_sec);
    temp_time.tm_year -= 1900;
    temp_time.tm_mon -= 1;
    full_time = mktime(&temp_time);
    (flag == 1) ? strftime(formatted_time, len, "%B %d, %Y (%a)", localtime(&full_time)) : strftime(formatted_time, len, "%l:%M %p", localtime(&full_time));
}

/**
 * Function:  format_date
 * ----------------------
 * @brief Allows to increment a date-time string (i.e. before) by num_days and stores it in 'after'.
 *
 * @param after The result of the increment operation.
 * @param before The original date.
 * @param num_days The number of days to increment.
 *
 */
void date_increment(char *after, const char *before, const int num_days)
{
    struct tm temp_time = {0};
    time_t full_time = {0};
    memset(&temp_time, 0, sizeof(struct tm));
    sscanf(before, "%4d%2d%2dT%2d%2d%2d",
           &temp_time.tm_year, &temp_time.tm_mon, &temp_time.tm_mday,
           &temp_time.tm_hour, &temp_time.tm_min, &temp_time.tm_sec);
    temp_time.tm_year -= 1900;
    temp_time.tm_mon -= 1;
    temp_time.tm_mday += num_days;
    full_time = mktime(&temp_time);
    after[0] = '\0';
    strftime(after, 16, "%Y%m%dT%H%M%S", localtime(&full_time));
    strncpy(after + 16, before + 16, MAX_LINE_LEN - 16);
    after[MAX_LINE_LEN - 1] = '\0';
}

/**
 * Function:  add_recurring_events
 * -------------------------------
 * @brief Prints the events contained in the nodes of the linked list in the required format.
 *
 * @param list The list that contains the nodes associated with the events to print.
 * @param from_date The lowe bound of the range.
 * @param to_date The upper bound of the range.
 *
 */
void print_list(node_t *list, struct tm *from_date, struct tm *to_date)
{
    char date[MAX_LINE_LEN] = "\0";
    char start_time[MAX_LINE_LEN] = "\0";
    char end_time[MAX_LINE_LEN] = "\0";
    char current_date[MAX_LINE_LEN] = "\0";
    int first_event = 1;
    node_t *curr = list;
    while (curr != NULL)
    {
        // Validate the range of dates
        if (is_date_in_range(curr->val->start_date, from_date, to_date))
        {
            // Validate whether the event is in day already printed
            if (compare_time(current_date, curr->val->start_date, 0) != 0)
            {
                if (first_event)
                    first_event = 0;
                else
                printf("\n");
                strcpy(current_date, curr->val->start_date);
                // Format the date and time
                format_date(date, curr->val->start_date, MAX_LINE_LEN, 1);
                format_date(start_time, curr->val->start_date, MAX_LINE_LEN, 0);
                format_date(end_time, curr->val->end_date, MAX_LINE_LEN, 0);
                // Printing
                print_formatted_date(date);
                print_formatted_event(start_time, end_time, curr->val->description, curr->val->location);
            }
            else if (compare_time(current_date, curr->val->start_date, 0) == 0)
            {
                // The event to print is part of a day already printed
                format_date(start_time, curr->val->start_date, MAX_LINE_LEN, 0);
                format_date(end_time, curr->val->end_date, MAX_LINE_LEN, 0);
                // Printing
                print_formatted_event(start_time, end_time, curr->val->description, curr->val->location);
            }
        }
        curr = curr->next;
    }
}

/**
 * @brief The main function and entry point of the program.
 *
 * @param argc The number of arguments passed to the program.
 * @param argv The list of arguments passed to the program.
 * @return int 0: No errors; 1: Errors produced.
 *
 */
int main(int argc, char *argv[])
{
    struct tm from_date = {0};
    struct tm to_date = {0};
    char *filename = NULL;
    node_t *list = NULL;
    if (process_program_args(argc, argv, &filename, &from_date, &to_date) == 1)
    {
        printf("Error parsing command line arguments.\n");
        exit(1);
    }
    new_list(filename, &list);
    add_recurring_events(&list);
    print_list(list, &from_date, &to_date);
    free_list(list);
    exit(0);
}