/* Misc. utility functions and C-library extensions for finit and its plugins
 *
 * Copyright (c) 2008-2010  Claudio Matsuoka <cmatsuoka@gmail.com>
 * Copyright (c) 2008-2015  Joachim Nilsson <troglobit@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef FINIT_HELPERS_H_
#define FINIT_HELPERS_H_

#include <stdio.h>
#include <string.h>		/* strerror() */
#include <syslog.h>

#define DO_LOG(level, fmt, args...)				\
do {								\
	openlog("finit", LOG_CONS | LOG_PID, LOG_DAEMON);	\
	syslog(level, fmt, ##args);				\
	closelog();						\
} while (0)

#define FLOG_DEBUG(fmt, args...)  DO_LOG(LOG_DEBUG, fmt, ##args)
#define FLOG_INFO(fmt, args...)   DO_LOG(LOG_INFO, fmt, ##args)
#define FLOG_WARN(fmt, args...)   DO_LOG(LOG_WARNING, fmt, ##args)
#define FLOG_ERROR(fmt, args...)  DO_LOG(LOG_CRIT, fmt, ##args)
#define FLOG_PERROR(fmt, args...) DO_LOG(LOG_CRIT, fmt ". Error %d: %s", ##args, errno, strerror(errno))


/* Esc[2JEsc[1;1H          Clear screen and move cursor to 1,1 (upper left) pos. */
#define clrscr()           fputs("\e[2J\e[1;1H", stderr)
/* Esc[K                   Erases from the current cursor position to the end of the current line. */
#define clreol()           fputs("\e[K", stderr)
/* Esc[2K                  Erases the entire current line. */
#define delline()          fputs("\e[2K", stderr)
/* Esc[Line;ColumnH        Moves the cursor to the specified position (coordinates) */
#define gotoxy(x,y)        fprintf(stderr, "\e[%d;%dH", y, x)
/* Esc[?25l (lower case L) Hide Cursor */
#define hidecursor()       fputs("\e[?25l", stderr)
/* Esc[?25h (lower case H) Show Cursor */
#define showcursor()       fputs("\e[?25h", stderr)

#define echo(fmt, args...) do {              fprintf(stderr,                    fmt "\n", ##args); } while (0)
#define   _d(fmt, args...) do { if (debug) { fprintf(stderr, "finit:%s:%s() - " fmt "\n", __FILE__, __func__, ##args); } } while (0)
#define   _e(fmt, args...) do {              fprintf(stderr, "finit:%s:%s() - " fmt "\n", __FILE__, __func__, ##args); } while (0)
#define  _pe(fmt, args...) do {              fprintf(stderr, "finit:%s:%s() - " fmt ". Error %d: %s\n", __FILE__, __func__, ##args, errno, strerror(errno)); } while (0)

void    runlevel_set    (int pre, int now);
int     runlevel_get    (void);
char   *runlevel_string (int levels);

int     pid_alive       (pid_t pid);
char   *pid_get_name    (pid_t pid, char *name, size_t len);

void    procname_set    (char *name, char *args[]);

void    print           (int action, const char *fmt, ...);
void    print_desc      (char *action, char *desc);
int     print_result    (int fail);
int     start_process   (char *cmd, char *args[], int console);
void    do_sleep        (unsigned int sec);
int     getuser         (char *username);
int     getgroup        (char *group);
void    set_hostname    (char **hostname);

int     complete        (char *cmd, int pid);
int     run             (char *cmd);
int     run_interactive (char *cmd, char *fmt, ...);
pid_t   run_getty       (char *cmd, char *args[], int console);
int     run_parts       (char *dir, char *cmd);

#endif /* FINIT_HELPERS_H_ */

/**
 * Local Variables:
 *  version-control: t
 *  indent-tabs-mode: t
 *  c-file-style: "linux"
 * End:
 */
