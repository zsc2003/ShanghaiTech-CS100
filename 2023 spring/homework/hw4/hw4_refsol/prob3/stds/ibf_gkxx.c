#include <assert.h>
#include <errno.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define brainfuck_main your_brainfuck_main_is_missing_const

#include "ibf.h"

#undef brainfuck_main

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

struct stack {
  int *data;
  size_t size, capacity;
};

void stack_ctor(struct stack *s) {
  s->data = NULL;
  s->size = 0;
  s->capacity = 0;
}

void stack_dtor(struct stack *s) {
  free(s->data);
}

void stack_grow(struct stack *s) {
  size_t grow_to = s->capacity == (size_t)0 ? 1 : s->capacity * 2;
  int *new_data = malloc(sizeof(int) * grow_to);
  assert(new_data != NULL);
  memcpy(new_data, s->data, sizeof(int) * s->size);
  free(s->data);
  s->data = new_data;
  s->capacity = grow_to;
}

void stack_push(struct stack *s, int value) {
  if (s->size == s->capacity)
    stack_grow(s);
  s->data[s->size++] = value;
  assert(s->size <= s->capacity);
}

int stack_pop(struct stack *s) {
  assert(s->size != (size_t)0);
  return s->data[--s->size];
}

/**
 * @brief The state of IBF.
 * @note Feel free to add more fields if needed.
 */
struct brainfuck_state {
  uint8_t *memory_buffer;
  size_t memory_pointer_offset;
};

struct brainfuck_state *brainfuck_state_new(void) {
  struct brainfuck_state *sp = malloc(sizeof(*sp));
  assert(sp != NULL);
  sp->memory_buffer = calloc(BRAINFUCK_MEMORY_BUFFER_SIZE, sizeof(uint8_t));
  sp->memory_pointer_offset = 0;
  return sp;
}

void brainfuck_state_free(struct brainfuck_state *state) {
  assert(state != NULL);
  assert(state->memory_buffer != NULL);
  free(state->memory_buffer);
  free(state);
}

/**
 * @brief Execute the plus instruction `+` of brainfuck.
 * @param state The state of IBF.
 * @note Overflowing UINT8_MAX will turn the current byte into 0.
 */
void brainfuck_execute_plus(struct brainfuck_state *state) {
  ++state->memory_buffer[state->memory_pointer_offset];
}

/**
 * @brief Execute the minus instruction `-` of brainfuck.
 * @param state The state of IBF.
 * @note Underflowing 0 will turn the current byte into UINT8_MAX.
 */
void brainfuck_execute_minus(struct brainfuck_state *state) {
  --state->memory_buffer[state->memory_pointer_offset];
}

/**
 * @brief Execute the previous instruction `<` of brainfuck.
 * @param state The state of IBF.
 * @note Backwarding on the first byte (indexed 0)
 * @note will move onto the last byte (indexed BRAINFUCK_MEMORY_BUFFER_SIZE -
 * 1).
 */
void brainfuck_execute_previous(struct brainfuck_state *state) {
  if (state->memory_pointer_offset-- == 0)
    state->memory_pointer_offset = BRAINFUCK_MEMORY_BUFFER_SIZE - 1;
}

/**
 * @brief Execute the next instruction `>` of brainfuck.
 * @param state The state of IBF.
 * @note Forwarding on the last byte (indexed BRAINFUCK_MEMORY_BUFFER_SIZE - 1)
 * @note will move onto the first byte (indexed 0).
 */
void brainfuck_execute_next(struct brainfuck_state *state) {
  if (++state->memory_pointer_offset == BRAINFUCK_MEMORY_BUFFER_SIZE)
    state->memory_pointer_offset = 0;
}

/**
 * @brief Execute the input instruction `,` of brainfuck.
 * @param state The state of IBF.
 * @param input_handler An input handler function that returns a character from
 * input.
 * @note You can call uint8_t c = input_handler() like calling uint8_t c =
 * getchar().
 */
void brainfuck_execute_input(struct brainfuck_state *state,
                             brainfuck_input_handler input_handler) {
  state->memory_buffer[state->memory_pointer_offset] = input_handler();
}

/**
 * @brief Execute the output instruction `.` of brainfuck.
 * @param state The state of IBF.
 * @param output_handler An output handler function that outputs a character.
 * @note You can call onput_handler(c) like calling putchar(c).
 */
void brainfuck_execute_output(const struct brainfuck_state *state,
                              brainfuck_output_handler output_handler) {
  output_handler(state->memory_buffer[state->memory_pointer_offset]);
}

bool brainfuck_loop_condition(const struct brainfuck_state *state) {
  return state->memory_buffer[state->memory_pointer_offset] != 0;
}

const char *find_loop_end(const char *pos) {
  assert(*pos == BRAINFUCK_TOKEN_LOOP_START);
  int cnt = 0;
  while (true) {
    if (*pos == BRAINFUCK_TOKEN_LOOP_START)
      ++cnt;
    else if (*pos == BRAINFUCK_TOKEN_LOOP_END) {
      if (--cnt == 0)
        return pos;
    }
    ++pos;
  }
}

/**
 * @brief Excute a line of brainfuck code.
 * @param state The state of IBF. It has already been created by
 * `brainfuck_state_new()` you wrote.
 * @param src A line of brainfuck code to execute.
 * @param input_handler The input handler. You will pass it as a parameter to
 * `brainfuck_execute_input()`.
 * @param output_handler The output handler. You will pass it as a parameter to
 * `brainfuck_execute_output()`.
 * @return True if the line is executed successfully, false otherwise.
 */
bool brainfuck_main(struct brainfuck_state *state, const char *src,
                    brainfuck_input_handler input_handler,
                    brainfuck_output_handler output_handler) {
  struct stack left_brackets;
  stack_ctor(&left_brackets);

  const char *cur = src;
  while (*cur != '\0') {
    switch (*cur) {
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
        if (brainfuck_loop_condition(state))
          stack_push(&left_brackets, cur - src);
        else
          cur = find_loop_end(cur);
        break;
      case BRAINFUCK_TOKEN_LOOP_END:
        cur = src + stack_pop(&left_brackets);
        continue;
        break;
    }
    ++cur;
  }

  stack_dtor(&left_brackets);
  return true;
}

inline bool
your_brainfuck_main_is_missing_const(struct brainfuck_state *state, char *src,
                                     brainfuck_input_handler input_handler,
                                     brainfuck_output_handler output_handler) {
  return brainfuck_main(state, src, input_handler, output_handler);
}

/**
 * @brief Options for IBF.
 * Version: -v, --version. Print the version of the program.
 * Help: -h, --help. Print the help of the program.
 * Command: -c, --command. Run the command from the command line.
 */
static struct option long_options[] = {{"version", no_argument, 0, 'v'},
                                       {"help", no_argument, 0, 'h'},
                                       {"cmd", required_argument, 0, 'c'},
                                       {0, 0, 0, 0}};

int main(int argc, char *argv[]) {
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
    FILE *file = fopen(argv[1], "r");
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
  } else {
    /* Run interactively in the console. */
    if (isatty(STDIN_FILENO)) {
      run_console();
    } else {
      run_file(stdin);
    }
  }
  return EXIT_SUCCESS;
}