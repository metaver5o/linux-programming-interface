/*
6-3. Implement setenv() and unsetenv() using getenv(), putenv(), and, where
necessary, code that directly modifies environ. Your version of unsetenv()
should check to see whether there are multiple definitions of an environment
variable, and remove them all (which is what the glibc version of unsetenv()
does).

setenv() - inserts or resets environment variable in the current env list; has
multiple arguments, one for key, one for value, one for overwrite
unsetenv() - delete all instances of variable name from environment list. (only
the variable name, not "name=key", should be given)

which should be implemented in terms of putenv() and getenv()...

getenv() - takes a name and returns the key
putenv() - similar to setenv(), but takes an argument of the form "name, value"
and always overwrites

----

We have a couple of cases here:
  - we set a variable that already exists
    - we overwrite it if overwrite is set
    - we do not overwrite it if overwrite is set
  - we set a variable that doesn't exist
    - we overwrite

  - we unset a variable that already exists
  - we unset a variable that doesn't exist
    - These can be handled with a simple check from getenv()
*/
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define STDIN 0
// #define STDOUT 1
#define ENOMEM 12
#define PRINT_ERROR_AND_QUIT(errno) \
  char *msg = strerror(errno);      \
  perror(msg);                      \
  exit(-1);

extern char **environ;

// j_setenv() - implement setenv() via putenv() and getenv()
static char *j_setenv(const char *const name, const char *const value,
                      const int overwrite) {
  char *nameval = NULL;
  // set variable if not currently set or we are overwriting
  if (getenv(name) == NULL || overwrite) {
    const char *const equals = "=";

    // allocate memory for concatenated "name=val"
    nameval = malloc(strlen(name) + 1 + strlen(value) + 1);
    if (nameval == NULL) {
      PRINT_ERROR_AND_QUIT(ENOMEM);
    }

    // Loop through name, equals sign, and value strings and concatenate
    const char *const stringp[3] = {name, equals, value};
    for (int i = 0; i < 3; i++) {
      const char *const string = stringp[i];
      if (strcat(nameval, string) == NULL) {
        free(nameval);
        PRINT_ERROR_AND_QUIT(errno);
      }
    }
    printf("j_setenv() || setting: %s\n", nameval);
    if (putenv(nameval) != 0) {
      free(nameval);
      PRINT_ERROR_AND_QUIT(errno);
    }
  }

  return nameval;
}

// j_unsetenv(): delete matching keys from the environment's key/val pairs
static int j_unsetenv(const char *name) {
  // NOTE - env vars can be longer than 1000 chars; I am being lazy
  char temp[1000];
  int env_i = 0;

  // Search through environ for matching name
  while (environ[env_i] != NULL) {
    char *env_var = environ[env_i];

    // Copy name portion of environ to temp array
    for (int i = 0; env_var[i] != '='; i++) {
      temp[i] = env_var[i];
    }

    // Unset if match
    if (strcmp(temp, name) == 0) {
      environ[env_i] = NULL;
    }
    env_i++;
  }

  return 0;
}

// Dumps entire environment
static void show_env() {
  for (int i = 0; environ[i] != NULL; i++) {
    printf("%s\n", environ[i]);
  }
  printf("----------------------------------------------\n");
}

int main() {
  char *nameval = j_setenv("FOO", "BAR", 1);
  show_env();
  j_unsetenv("FOO");
  free(nameval);
  show_env();
  return 0;
}
