#include "headr.h"

void add_to_history(char *command) {

    /* Read number of lines in file */
    FILE *history_stream = fopen("history.txt", "a+");

    /* Write command at end of file */
    history_stream = fopen("history.txt", "a");
    fprintf(history_stream, "%s", command);

    fclose(history_stream);

}
