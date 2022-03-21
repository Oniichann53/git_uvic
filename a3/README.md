# Description of files in this directory.

The files here are starter files for UVic SENG 265, Spring 2022
Assignment #3.  The files are as follows:

* ```makefile```: Needed to build the assignment. In order to
construct the ```process_cal3``` executable, type either ```make``` or
```make process_cal3```.

* ```process_cal3.c```: The C file containing the ```main()``` function.
(There must only exist one ```main``` in any program.)  This should be
suitably modified to complete the assignment.

* ```emalloc.[ch]```: Source code and header file for the
```emalloc``` function described in lecture. This is kept in its own
source-code file as it can be used independently in both
```process_cal3.c``` and ```listy.c```.

* ```ics.h```: The definition of the ```struct event_t``` type.

* ```listy.[ch]```: Linked-list routines based on the lectures. The
routines here may be added to or modified. Regardless, however,
students are responsible for any segmentation faults that occur as a
result of using this code.

# How to test your solution?

1. Make sure that you complete the required functions:
   * listy.c -> node_t *new_node(event_t *val)
   * listy.c -> node_t *add_inorder(node_t *list, node_t *new)
   * process_cal3.c -> event_t *new_event(event_t *event)
   * process_cal3.c -> void print_formatted_date(char *date)
   * process_cal3.c -> void print_formatted_event(char *start_time, char *end_time, char *description, char *location)
2. Follow the guidelines in TESTS.md for using tester.py to validate that the program produces the required outputs for the provided test cases.

# How to test incrementally?

We're giving you the option to be creative here and do your best to test after you complete each function. You can use assertions (i.e., assert()), comment lines of code, use a preferred debugger, use printf() statements or any other mechanism to validate your code advancements.

We confirm that if you complete the functions described above, the tests will pass. That is, you don't need to create extra functions, but you are allowed to do so. However, you're fully responsible for any errors that this or your testing process might cause (e.g., commented lines).

When submitting, make sure that the program passes all the tests in Senjhalla, and that you have removed debugging-related elements in the solution (e..g, lines commented, unnecessary comments, etc.).
