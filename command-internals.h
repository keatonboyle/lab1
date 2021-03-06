// UCLA CS 111 Lab 1 command internals

enum command_type
  {
    AND_COMMAND,         // A && B
    SEQUENCE_COMMAND,    // A ; B
    OR_COMMAND,          // A || B
    PIPE_COMMAND,        // A | B
    SIMPLE_COMMAND,      // a simple command
    SUBSHELL_COMMAND,    // ( A )
  };

struct command_text
{
  char *start;
  char *end;
  int startln;
  int endln;
};


// Data associated with a command.
struct command
{
  enum command_type type;

  // Exit status, or -1 if not known (e.g., because it has not exited yet).
  int status;

  // I/O redirections, or null if none.
  char *input;
  char *output;

  union
  {
    // for AND_COMMAND, SEQUENCE_COMMAND, OR_COMMAND, PIPE_COMMAND:
    struct command *command[2];

    // for SIMPLE_COMMAND:
    char **word;

    // for SUBSHELL_COMMAND:
    struct command *subshell_command;
  } u;
};

/* Allocate memory for a new command struct, populate its fields according
 * to arguments, and return a pointer (of type command_t) to it */
command_t construct_command (enum command_type type, char *input, char *output,
    void *u0, void *u1);

void dump_command (command_t com);

void print_words (char **words);

bool isWordChar(char c);

bool isWhite(char c);

command_t parse_command_string (char *comString, int line);

command_t parse_ao_string (com_text_t comText);

command_t parse_pipe_string(com_text_t comText);

command_t parse_io_string(com_text_t comText);

command_t parse_sub_string(com_text_t comText);

command_t parse_seq_string(com_text_t comText);
command_t sub_command_build(com_text_t comText, char *input, char *output);
command_t simple_command_build(com_text_t comText, char *input, char *output);

char **get_word_array(char *sentence);

com_text_t *strip_text(com_text_t *pComText);

char *strip_string(char *start);

char *drop_trailing_nulls(char *endbyte);

command_stream_t stringsToStream(char **commandStrings, int *line_nums, int count);

bool anything_before(char *last, char *first);

