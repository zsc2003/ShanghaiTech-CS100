#ifndef __IBF_H__  // This is called an "include guard".
#define __IBF_H__  // Include guards prevent errors of including a header twice.

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>


#define BRAINFUCK_MAX_LINE_LENGTH 1000000

/*-----------------------------------------------------
   WARNING: DO NOT CHANGE THE CODE BELOW.
   Here defined the input and output handler types.
   You may consult it to understand the framework.
  -----------------------------------------------------*/

  /**
   * @brief The input handler of IBF.
   * @return The character to input.
   */
typedef uint8_t(*brainfuck_input_handler)();

/**
 * @brief The output handler of IBF.
 * @param c The character to output.
 */
typedef void (*brainfuck_output_handler)(uint8_t c);

struct brainfuck_state; // A declaration of brainfuck_state
struct brainfuck_state* brainfuck_state_new();
void brainfuck_state_free(struct brainfuck_state* state);
bool brainfuck_main(struct brainfuck_state* state, char* src,
    brainfuck_input_handler input_handler, brainfuck_output_handler output_handler);
/*-----------------------------------------------------*/


/*-----------------------------------------------------
   WARNING: DO NOT CHANGE THE CODE BELOW.
   Here defined the error handlers in IBF. You should
   call the corresponding error handler when an error
   occured.
  -----------------------------------------------------*/

  /**
   * @brief Print the error message of unmatched loop end.
   */
void print_error_unmatched_loop_end() {
    fprintf(stderr, "SyntaxError: unmatched ']'.\n");
}

/**
 * @brief Print the error message of unmatched loop start.
 */
void print_error_unmatched_loop_start() {
    fprintf(stderr, "SyntaxError: unmatched '['.\n");
}

/**
 * @brief Print the error message of maximum loop depth exceeded.
 */
void print_error_max_loop_depth() {
    fprintf(stderr, "LoopError: maximum loop depth exceeded.\n");
}

/**
 * @brief Print the error message of maximum line length exceeded.
 */
void print_error_max_line_length() {
    fprintf(stderr, "InputError: max line length exceeded.\n");
}

/**
 * @brief Print the error message of maximum loop size exceeded.
 */
void print_error_max_loop_size() {
    fprintf(stderr, "LoopError: maximum loop size exceeded.\n");
}

/**
 * @brief Print the error message of unexpected EOF.
 */
void print_error_unexpected_eof() {
    fprintf(stderr, "IOError: unexpected EOF.\n");
}

/*-----------------------------------------------------*/



/*-----------------------------------------------------
   WARNING: DO NOT CHANGE THE CODE BELOW.
   Here is where all the magic happens (beyond the scope of CS100).
  -----------------------------------------------------*/

#if defined(WIN32) || defined(_WIN32) || \
    defined(__WIN32) && !defined(__CYGWIN__)
#include <io.h>
#define isatty _isatty
#define STDIN_FILENO 0
#else
#include <stdio_ext.h>
#include <termios.h>
#include <unistd.h>
#endif

  /**
   * @brief Flush the stdin buffer.
   */
void stdin_flush() {
#if defined(WIN32) || defined(_WIN32) || \
    defined(__WIN32) && !defined(__CYGWIN__)
    fflush(stdin);
#else
    __fpurge(stdin);
    tcflush(STDIN_FILENO, TCIFLUSH);
#endif
}

#if defined(__GNUC__)
#define COMPILER_NAME "GCC"
#define COMPILER_VERSION __VERSION__
#elif defined(_MSC_VER)
#define COMPILER_NAME "MSVC"
#define COMPILER_VERSION _MSC_VER
#elif defined(__clang__)
#define COMPILER_NAME "Clang"
#define COMPILER_VERSION __clang_version__
#else
#define COMPILER_NAME "Unknown"
#define COMPILER_VERSION "Unknown"
#endif

#if defined(__linux__)
#define OS_NAME "linux"
#elif defined(__APPLE__)
#define OS_NAME "macos"
#elif defined(_WIN32) || defined(_WIN64)
#define OS_NAME "win32"
#else
#define OS_NAME "unknown"
#endif

#define IBF_VERSION_MAJOR 0
#define IBF_VERSION_MINOR 1
#define IBF_VERSION_PATCH 0

/**
 * @brief Read a line ending with `until` from a stream.
 * @param stream The stream to read.
 * @param dest The destination buffer.
 * @param size The size of the destination buffer.
 * @param until The character to end the line.
 * @return True if the line is read successfully.
 */
bool brainfuck_readline_util(FILE* stream, char* dest, size_t size,
    const char until) {
    if (stream == NULL || dest == NULL || size == 0) {
        return false;
    }
    char ch = fgetc(stream);
    size_t i = 0;
    while (true) {
        if (ch == until || ch == EOF || feof(stream)) {
            break;
        }
        if (i >= size - 1) { /* Leave a space for '\0'. */
            print_error_max_line_length();
            return false;
        }
        else {
            dest[i] = ch;
            i += 1;
        }
        ch = fgetc(stream);
    }
    dest[i] = '\0';
    return true;
}

uint8_t brainfuck_input_handler_stdin() {
    char ch = getchar();
    if (ch == EOF) {
        // print_error_unexpected_eof();
        exit(EXIT_FAILURE);
    }
    return ch;
}

void brainfuck_output_handler_stdout(uint8_t c) {
    if (putchar(c) == EOF) {
        // print_error_unexpected_eof();
        exit(EXIT_FAILURE);
    }
}

void console_print_help() {
    fprintf(stderr, "Welcome to IBF %d.%d.%d!\n", IBF_VERSION_MAJOR,
        IBF_VERSION_MINOR, IBF_VERSION_PATCH);
    fprintf(stderr, "\n");
    fprintf(
        stderr,
        "Brainfuck is an esoteric programming language created in 1993 "
        "by Urban \nMuller. And it is the smallest Turing-complete language.\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "Instructions of Brainfuck:\n");
    fprintf(stderr,
        ">  Increment the data pointer (to point to the next cell to the "
        "right).\n");
    fprintf(
        stderr,
        "Decrement the data pointer (to point to the next cell to the left).\n");
    fprintf(stderr,
        "+  Increment (increase by one) the byte at the data pointer.\n");
    fprintf(stderr,
        "-  Decrement (decrease by one) the byte at the data pointer.\n");
    fprintf(stderr, ".  Output the byte at the data pointer.\n");
    fprintf(stderr,
        ",  Accept one byte of input, storing its value in the byte at the "
        "data \n   pointer.\n");
    fprintf(stderr,
        "[  If the byte at the data pointer is zero, then instead of moving "
        "the \n   instruction pointer forward to the next command, jump it "
        "forward to \n   the command after the matching ] command.\n");
    fprintf(
        stderr,
        "]  If the byte at the data pointer is nonzero, then instead of "
        "moving \n   the instruction pointer forward to the next command, jump "
        "it back to \n   the command after the matching [ command.\n");

    fprintf(stderr, "\n");
    fprintf(stderr, "Any other characters are seen as comments.\n");
}

void console_print_copyright() {
    fprintf(stderr, "Copyright (C) 2023 CS100, Shanghaitech University.\n");
    fprintf(stderr, "All rights reserved.\n");
}

void console_print_credits() {
    fprintf(stderr,
        "Thanks to Linshu Yang, Yuqi Liu, Ke Gong and other teaching "
        "crews for \nsupporting IBF development. See cs100.geekpie.club for "
        "more information.\n");
}

void console_print_license() {
    fprintf(
        stderr,
        "IBF is licensed under the GNU General Public License v3.0. See \n"
        "https://www.gnu.org/licenses/gpl-3.0.en.html for more information.\n");
}

/**
 * @brief Run IBF interactively in the console.
 */
void run_console() {
    fprintf(stderr, "IBF %d.%d.%d (tags/v%d.%d.%d, %s, %s) [%s %s] on %s\n",
        IBF_VERSION_MAJOR, IBF_VERSION_MINOR, IBF_VERSION_PATCH,
        IBF_VERSION_MAJOR, IBF_VERSION_MINOR, IBF_VERSION_PATCH, __DATE__,
        __TIME__, COMPILER_NAME, COMPILER_VERSION, OS_NAME);
    fprintf(stderr,
        "Type \"help\", \"copyright\", \"credits\" or \"license\" for more "
        "information.\n");
    struct brainfuck_state* state = brainfuck_state_new();
    char* line = (char*)calloc(BRAINFUCK_MAX_LINE_LENGTH + 1, sizeof(char));
    char* curr_pos = line;
    fprintf(stderr, ">>> ");
    int32_t unmatched_loop = 0;
    while (true) {
        fflush(stdout);
        if (!brainfuck_readline_util(stdin, curr_pos, BRAINFUCK_MAX_LINE_LENGTH + 1,
            '\n')) {
            stdin_flush();
            fprintf(stderr, ">>> ");
            continue;
        }
        if (strcmp(line, "help") == 0) {
            console_print_help();
        }
        else if (strcmp(line, "copyright") == 0) {
            console_print_copyright();
        }
        else if (strcmp(line, "credits") == 0) {
            console_print_credits();
        }
        else if (strcmp(line, "license") == 0) {
            console_print_license();
        }
        else {
            // Save unmatched loops before calling brainfuck_main

            // Add newly read line's # unmatched loops 
            size_t curr_line_len = strlen(curr_pos);
            for (size_t i = 0; i < curr_line_len; i++) {
                if (curr_pos[i] == '[') {
                    unmatched_loop += 1;
                }
                else if (curr_pos[i] == ']') {
                    unmatched_loop -= 1;
                    if (unmatched_loop < 0) {
                        // Jump out (4 lines down) to continue in outer while(true).
                        break;
                    }
                }
            }
            if (unmatched_loop < 0) {
                print_error_unmatched_loop_end();
                // Reset all buffers
                curr_pos = line;
                unmatched_loop = 0;
                fprintf(stderr, ">>> ");
                continue;
            }
            else if (unmatched_loop > 0) {
                curr_pos += curr_line_len;
                fprintf(stderr, ">>> ");
                continue;
            }
            else {
                brainfuck_main(state, line, brainfuck_input_handler_stdin, brainfuck_output_handler_stdout);
                // Reset all buffers
                curr_pos = line;
                unmatched_loop = 0;
            }
        }
        stdin_flush();
        fprintf(stderr, ">>> ");
    }
    free(line);
    brainfuck_state_free(state);
}

/**
 * @brief Run IBF from a file.
 * @param file The file to run.
 * @return True if the file is run successfully.
 */
bool run_file(FILE* file) {
    struct brainfuck_state* state = brainfuck_state_new();
    char* line = (char*)calloc(BRAINFUCK_MAX_LINE_LENGTH + 1, sizeof(char));
    char* curr_pos = line;
    while (true) {
        if (feof(file) || !brainfuck_readline_util(
            file, curr_pos, BRAINFUCK_MAX_LINE_LENGTH + 1, '\n')) {
            break;
        }
        curr_pos += strlen(curr_pos);
    }
    if (!brainfuck_main(state, line,
        brainfuck_input_handler_stdin, brainfuck_output_handler_stdout)) {
        free(line);
        brainfuck_state_free(state);
        return false;
    }
    free(line);
    brainfuck_state_free(state);
    return true;
}

/**
 * @brief Run IBF from a command.
 * @param command The command to run.
 * @return True if the command is run successfully.
 */
bool run_command(char* command) {
    int32_t unmatched_loop = 0;
    size_t command_len = strlen(command);
    for (size_t i = 0; i < command_len; i++) {
        if (command[i] == '[') {
            unmatched_loop += 1;
        }
        else if (command[i] == ']') {
            unmatched_loop -= 1;
            if (unmatched_loop < 0) {
                // Jump out (4 lines down).
                break;
            }
        }
    }
    if (unmatched_loop < 0) {
        print_error_unmatched_loop_end();
        return false;
    }
    else if (unmatched_loop > 0) {
        print_error_unmatched_loop_start();
        return false;
    }
    struct brainfuck_state* state = brainfuck_state_new();
    if (!brainfuck_main(state, command,
        brainfuck_input_handler_stdin, brainfuck_output_handler_stdout)) {
        brainfuck_state_free(state);
        return false;
    }
    brainfuck_state_free(state);
    return true;
}


/**
 * @brief Print the version of IBF.
 */
void print_version() {
    /* Version format: MAJOR.MINOR.PATCH */
    fprintf(stderr, "IBF %d.%d.%d\n", IBF_VERSION_MAJOR, IBF_VERSION_MINOR,
        IBF_VERSION_PATCH);
}

/**
 * @brief Print the usage of IBF.
 */
void print_usage() {
    fprintf(stderr, "usage: ibf [options] ... [-c cmd | file]\n");
    fprintf(stderr, "Try `ibf -h` for more information.\n");
}

/**
 * @brief Print the help of IBF.
 */
void print_help() {
    fprintf(stderr, "usage: ibf [options] ... [-c cmd | file]\n");
    fprintf(stderr, "Options and arguments:\n");
    fprintf(stderr, "-v, --version\t  : Print the version of IBF.\n");
    fprintf(stderr, "-h, --help\t  : Print the help of IBF.\n");
    fprintf(stderr, "-c, --cmd\t  : Run program passed in as string. \n");
    fprintf(stderr, "file\t\t  : Program read from script file.\n");
}



#endif //__IBF_H__
