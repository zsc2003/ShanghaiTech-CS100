#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *determine_file_kind(const char *file) {
  const char *dot_pos = strrchr(file, '.');
  if (strcmp(dot_pos, ".c") == 0)
    return "C source code";
  else if (strcmp(dot_pos, ".cpp") == 0 || strcmp(dot_pos, ".C") == 0 ||
           strcmp(dot_pos, ".cc") == 0 || strcmp(dot_pos, ".cxx") == 0)
    return "C++ source code";
  else if (strcmp(dot_pos, ".hpp") == 0 || strcmp(dot_pos, ".hxx") == 0)
    return "C++ header file";
  else
    return "C/C++ header file";
}

int main(int argc, char **argv) {
  for (int i = 1; i < argc; ++i) {
    if (strcmp(argv[i], "-Wall") == 0)
      puts("-Wall: Enable all the warnings about constructions that some "
           "users consider questionable, and that are easy to avoid (or modify "
           "to prevent the warning).");
    else if (strcmp(argv[i], "-Wpedantic") == 0)
      puts("-Wpedantic: Issue all the warnings demanded by strict ISO C and "
           "ISO C++ and reject all programs that use forbidden extensions.");
    else if (strcmp(argv[i], "-Wextra") == 0)
      puts("-Wextra: Enable some extra warning flags that are not enabled by "
           "-Wall.");
    else if (strcmp(argv[i], "-Werror") == 0)
      puts("-Werror: Make all warnings into errors.");
    else if (strcmp(argv[i], "-o") == 0) {
      printf("-o %s: Place the primary output in file %s.\n", argv[i + 1],
             argv[i + 1]);
      ++i;
    } else if (strcmp(argv[i], "-I") == 0) {
      printf("-I %s: Add the directory %s to the list of directories to be "
             "searched for header files during preprocessing.\n",
             argv[i + 1], argv[i + 1]);
      ++i;
    } else if (strncmp(argv[i], "-std=", 5) == 0) {
      printf("%s: Set the language standard to ", argv[i]);
      if (argv[i][5] == 'c')
        printf("ISO C%s.\n", argv[i] + 6);
      else
        printf("GNU dialect of C%s.\n", argv[i] + 8);
    } else
      printf("%s: %s as input file.\n", argv[i], determine_file_kind(argv[i]));
  }
  return 0;
}