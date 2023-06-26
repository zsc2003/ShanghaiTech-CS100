#include <errno.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "ibf.h"

// Defined tokens and constants for your use.
#define BRAINFUCK_TOKEN_PLUS '+'
#define BRAINFUCK_TOKEN_MINUS '-'
#define BRAINFUCK_TOKEN_PREVIOUS '<'
#define BRAINFUCK_TOKEN_NEXT '>'
#define BRAINFUCK_TOKEN_OUTPUT '.'
#define BRAINFUCK_TOKEN_INPUT ','
#define BRAINFUCK_TOKEN_LOOP_START '['
#define BRAINFUCK_TOKEN_LOOP_END ']'

#define BRAINFUCK_MEMORY_BUFFER_SIZE 30000
#define BRAINFUCK_LOOP_BUFFER_SIZE 100000
#define BRAINFUCK_MAX_LOOP_DEPTH 65536

/**
 * @brief The state of IBF.
 * @note Feel free to add more fields if needed.
 */
struct brainfuck_state {
  uint8_t* memory_buffer;        /* A byte-array representing the memory of brainfuck. */
  size_t memory_pointer_offset;  /* The offset of memory pointer. */

  // --- FOR PART B ONLY --- Uncomment to start part B ---
  // char* loop_buffer;             /* A buffer to store all commands within a loop. */
  // size_t loop_size;              /* The loop size. */
  size_t unmatched_depth;        /* The unmatched nesting depth of loops. */
  size_t* loop_indexes;          /* A buffer to store [s' positions. */
};

/**
 * @brief Create a new dynamically-allocated state of IBF.
 * @return The new state of IBF.
 * @note You should both dynamically-allocate a new state, and initialize its members.
 * @note memory_buffer should be allocated a 30000-byte array and initialized to zero.
 * @note memory_pointer_offset should be 0.
 * @note You do not need to call this function anywhere in your code. We will call it in the framework.
 * @note You do not need to consider failure in allocation.
 * @note --- FOR PART B ONLY ---
 * @note Don't forget to also initialize new members introduced in part B!
 */
struct brainfuck_state* brainfuck_state_new() {
  struct brainfuck_state* new_state = (struct brainfuck_state*)malloc(sizeof(struct brainfuck_state));
  new_state->memory_buffer = (uint8_t*)calloc(BRAINFUCK_MEMORY_BUFFER_SIZE, sizeof(uint8_t));
  new_state->memory_pointer_offset = 0;
  new_state->loop_indexes = (size_t*)calloc(BRAINFUCK_LOOP_BUFFER_SIZE, sizeof(size_t));
  new_state->unmatched_depth = 0;

  return new_state;
}

/**
 * @brief Free the state of IBF.
 * @param state The state of IBF.
 * @note To prevent memory leak, you should free ALL dynamically allocated memory.
 * @note Free those memory in its member variables first,
 * @note and finally the `state` itself, since it is also dynamically allocated.
 * @note Remember, always "free" for each "malloc" or "calloc" you used.
 * @note You do not need to call this function anywhere in your code. We will call it in the framework.
 */
void brainfuck_state_free(struct brainfuck_state* state) {
  free(state->memory_buffer);
  free(state->loop_indexes);
  free(state);
}


/**
 * @brief Execute the plus instruction `+` of brainfuck.
 * @param state The state of IBF.
 */
void brainfuck_execute_plus(struct brainfuck_state* state) {
  state->memory_buffer[state->memory_pointer_offset]++;
}

/**
 * @brief Execute the minus instruction `-` of brainfuck.
 * @param state The state of IBF.
 */
void brainfuck_execute_minus(struct brainfuck_state* state) {
  state->memory_buffer[state->memory_pointer_offset]--;
}

/**
 * @brief Execute the previous instruction `<` of brainfuck.
 * @param state The state of IBF.
 */
void brainfuck_execute_previous(struct brainfuck_state* state) {
  if (state->memory_pointer_offset == 0) {
    state->memory_pointer_offset = BRAINFUCK_MEMORY_BUFFER_SIZE - 1;
  }
  else {
    state->memory_pointer_offset--;
  }
}

/**
 * @brief Execute the next instruction `>` of brainfuck.
 * @param state The state of IBF.
 */
void brainfuck_execute_next(struct brainfuck_state* state) {
  if (state->memory_pointer_offset == BRAINFUCK_MEMORY_BUFFER_SIZE - 1) {
    state->memory_pointer_offset = 0;
  }
  else {
    state->memory_pointer_offset++;
  }
}

/**
 * @brief Execute the input instruction `,` of brainfuck.
 * @param state The state of IBF.
 * @param input_handler An input handler function that returns a character from input.
 * @note You can call uint8_t c = input_handler() like calling uint8_t c = getchar().
 */
void brainfuck_execute_input(struct brainfuck_state* state, brainfuck_input_handler input_handler) {
  state->memory_buffer[state->memory_pointer_offset] = input_handler();
}

/**
 * @brief Execute the output instruction `.` of brainfuck.
 * @param state The state of IBF.
 * @param output_handler An output handler function that outputs a character.
 * @note You can call onput_handler(c) like calling putchar(c).
 */
void brainfuck_execute_output(struct brainfuck_state* state, brainfuck_output_handler output_handler) {
  output_handler(state->memory_buffer[state->memory_pointer_offset]);
}

// ↓↓↓ FOR PART B ONLY ↓↓↓
//
// Add your own functions to handle instructions `[` and `]`!
//
// ↑↑↑ FOR PART B ONLY ↑↑↑

/**
 * @brief Excute a line of brainfuck code.
 * @param state The state of IBF. It has already been created by `brainfuck_state_new()` you wrote.
 * @param src A line of brainfuck code to execute.
 * @param input_handler The input handler. Pass it as a parameter when processing input.
 * @param output_handler The output handler. Pass it as a parameter when processing output.
 * @return True if the line is executed successfully, false otherwise.
 */
bool brainfuck_main(struct brainfuck_state* state, char* src,
  brainfuck_input_handler input_handler, brainfuck_output_handler output_handler) {
  char* curr = src;
  size_t len = strlen(src);
  while (curr - src < (int)len) {
    switch (*curr) {
    case BRAINFUCK_TOKEN_PLUS:
      brainfuck_execute_plus(state);
      break;
    case BRAINFUCK_TOKEN_MINUS:
      brainfuck_execute_minus(state);
      break;
    case BRAINFUCK_TOKEN_PREVIOUS:
      brainfuck_execute_previous(state);
      break;
    case BRAINFUCK_TOKEN_NEXT:
      brainfuck_execute_next(state);
      break;
    case BRAINFUCK_TOKEN_OUTPUT:
      brainfuck_execute_output(state, output_handler);
      break;
    case BRAINFUCK_TOKEN_INPUT:
      brainfuck_execute_input(state, input_handler);
      break;
    case BRAINFUCK_TOKEN_LOOP_START:
      if (state->memory_buffer[state->memory_pointer_offset] != 0) {
        state->unmatched_depth++;
        state->loop_indexes[state->unmatched_depth] = curr - src;
      }
      else {
        size_t right_brackets_needed = 1;
        while (right_brackets_needed > 0) {
          curr++;
          if (*curr == BRAINFUCK_TOKEN_LOOP_START) {
            right_brackets_needed++;
          }
          else if (*curr == BRAINFUCK_TOKEN_LOOP_END) {
            right_brackets_needed--;
          }
        }
      }
      break;
    case BRAINFUCK_TOKEN_LOOP_END:
      if (state->unmatched_depth == 0) {
        print_error_unmatched_loop_end();
        return false;
      }
      if (state->memory_buffer[state->memory_pointer_offset] != 0) {
        curr = src + state->loop_indexes[state->unmatched_depth];
      }
      else {
        state->unmatched_depth--;
      }
      break;
    default:
      break;
    }
    curr++;
  }
  if (state->unmatched_depth > 0) {
    print_error_unmatched_loop_start();
    return false;
  }
  return true;
}



/**
 * @brief Options for IBF.
 * Version: -v, --version. Print the version of the program.
 * Help: -h, --help. Print the help of the program.
 * Command: -c, --command. Run the command from the command line.
 */
static struct option long_options[] = { {"version", no_argument, 0, 'v'},
                                       {"help", no_argument, 0, 'h'},
                                       {"cmd", required_argument, 0, 'c'},
                                       {0, 0, 0, 0} };

int main(int argc, char* argv[]) {
  while (true) {
    int option_index = 0;
    /* Parse the options. */
    int c = getopt_long(argc, argv, ":vhc:", long_options, &option_index);
    if (c == -1) {
      break;
    }
    switch (c) {
    case 0: /* Long option. */
      if (long_options[option_index].flag != 0) {
        break;
      }
      break;
    case 'v': /* Version. */
      print_version();
      return EXIT_SUCCESS;
    case 'h': /* Help. */
      print_help();
      return EXIT_SUCCESS;
    case 'c': /* Command. */
      if (!run_command(optarg)) {
        return EXIT_FAILURE;
      }
      return EXIT_SUCCESS;
    case '?': /* Unknown option. */
      fprintf(stderr, "Unknown option %s\n", argv[optind - 1]);
      print_usage();
      return EXIT_FAILURE;
    case ':': /* Missing argument. */
      fprintf(stderr, "Argument expected for the %s option\n",
        argv[optind - 1]);
      print_usage();
      return EXIT_FAILURE;
    default:
      abort();
    }
  }
  /* If there is no argument, run interactively in the console or from a file.
   */
  if (argc > 1) {
    /* Run from a file. */
    FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
      fprintf(stderr, "%s: Cannot open file '%s': [Errno %d] %s\n", argv[0],
        argv[1], errno, strerror(errno));
      return EXIT_FAILURE;
    }
    if (!run_file(file)) {
      fclose(file);
      return EXIT_FAILURE;
    }
    fclose(file);
  }
  else {
    /* Run interactively in the console. */
    if (isatty(STDIN_FILENO)) {
      run_console();
    }
    else {
      run_file(stdin);
    }
  }
  return EXIT_SUCCESS;
}
