#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void rand_str(char *dest, size_t length) {
  char charset[] = "0123456789"
                   "abcdefghijklmnopqrstuvwxyz"
                   "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

  while (length-- > 0) {
    size_t index = (double) rand() / RAND_MAX * (sizeof charset - 1);
    *dest++ = charset[index];
  }
  *dest = '\0';
}

char *wrap_string(const char *prefix, const char *suffix, const char *str) {
  char *new_str = malloc(strlen(prefix) + strlen(suffix) + strlen(str) + 1);
  if (new_str == NULL) {
    perror("Error allocating memory");
    return NULL;
  }
  sprintf(new_str, "%s%s%s", prefix, str, suffix);
  return new_str;
}

char *read_file(FILE *script_fp) {
  size_t line_len = 0;
  char *line = NULL;

  char *accum;
  int accum_len = 0;
  char *prev_accum = "";
  int is_first_line = 1;

  while (getline(&line, &line_len, script_fp) != -1) {
    if (!is_first_line) {
      accum = malloc(accum_len + line_len);
      strcpy(accum, prev_accum);
      strcat(accum, line);
      accum_len += line_len;
      prev_accum = accum;
    } else {
      is_first_line = 0;
    }
  }
  return accum;
}

int main(int argc, char **argv) {
  if (argc < 2) return 1;
  char uid[] = { [41] = '\1' };
  rand_str(uid, sizeof uid - 1);
  char *prefix = wrap_string("cat << tmpl", "\n", uid);
  char *suffix = wrap_string("tmpl", "\n", uid);

  FILE *script_fp = fopen(argv[1], "r");
  char *script_src = read_file(script_fp);
  char **exec_args = malloc(255);
  exec_args[0] = "bash";
  exec_args[1] = "-c";
  exec_args[2] = wrap_string(prefix, suffix, script_src);

  int exec_arg_count = 3;
  for (int i = 0; i < argc; i++) {
    exec_args[i + 3] = argv[i + 1];
    exec_arg_count += 1;
  }
  exec_args[exec_arg_count] = (char *)NULL;

  execv("/bin/bash", exec_args);
}
