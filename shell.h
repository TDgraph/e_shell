#include <fcntl.h>
#include <stddef.h>

#define  partitioner " \t\n"
extern char **environ;

char *read_command_entered(void);
char **handling_command_entered_args(char *command_entered);
int command_execution(char **args_present, char **argv);

/* ===== stringhelpers.c ===== */
char *_strdup(const char *str);

/* ====tokenizing.c ==== */


/* ====environment.c ==== */
char **get_environ(ino_t *);
int _unsetenv(ino_t *, char *);
int _setenv(ino_t *, char *, char *);

/* ==== getenv.c ==== */
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

/* ==== top_history.c ==== */
char *shell_history_file(ino_t *info);
int pen_history(ino_t *info);
int read_history(ino_t *info);
int dev_history_list(ino_t *info, char *buf, int linecount);
int rearrange_history(ino_t *info);

#endif
