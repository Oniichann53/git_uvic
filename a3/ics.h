/** @file ics.h
 *  @brief Relevant definitions for representing an iCalendar event.
 *
 */
#ifndef _ICS_H_
#define _ICS_H_

// Revelant constants for the program.
#define MAX_LINE_LEN 80
#define REPETITION_LEN 80
#define DATE_LEN 17
#define SUMMARY_LEN 80
#define LOCATION_LEN 80

/**
 * @brief Enum for representing the days of the week.
 *
 */
typedef enum day
{
    SU,
    MO,
    TU,
    WE,
    TH,
    FR,
    SA,
    NO_D
} day;

/**
 * @brief Enum for representing the possible frequencies of the events to be managed by the program.
 *
 */
typedef enum frequency
{
    WEEKLY = 7,
    NO_F = 0
} frequency;

/**
 * @brief An struct that represents a repetition rule for an event.
 *
 */
typedef struct repetition_t
{
    // Start day of the week for the repetition.
    day wkst;
    // End day of week for the repetition.
    day byday;
    // Frequency of the repetition
    frequency freq;
    // Last date of the repetition.
    char until[DATE_LEN];

} repetition_t;

/**
 * @brief An struct that represents an event.
 *
 */
typedef struct event_t
{
    // The repetition rule for the event.
    repetition_t repetition;
    // The description of the event.
    char description[SUMMARY_LEN];
    // The start date of the event.
    char start_date[DATE_LEN];
    // The end date of the event.
    char end_date[DATE_LEN];
    // The location of the event.
    char location[LOCATION_LEN];
} event_t;

#endif