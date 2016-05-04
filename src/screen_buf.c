#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>

#include "screen_buf.h"

/* globals */
static unsigned g_display_width = 0;
static char *g_screen_buf = NULL;
static char *g_line_buf = NULL;

static void
set_padding(const unsigned msg_len, unsigned *padding)
{
	*padding = (g_display_width - msg_len - 1) / 2;
}

void 
init_screen_buf(unsigned n_lines) {
	struct winsize w;
	ioctl(0, TIOCGWINSZ, &w);
	g_display_width = w.ws_col;
	g_line_buf      = malloc(g_display_width * sizeof(char));
	g_screen_buf    = malloc(g_display_width * n_lines * sizeof(char));
}

void
free_screen_buf(void){
	free(g_line_buf);
	free(g_screen_buf);
}

/* returns a pointer to the screen buffer */
char *
get_screen_buf(void)
{
	return g_screen_buf;
}

/* returns the width (chars) of the screen */
unsigned
get_screen_width(void)
{
	return g_display_width;
}

/* returns the number of newline characters in a string */
static unsigned
newlines_in(const char *str)
{
	unsigned i, newlines = 0;
	for (i = 0; i < strlen(str); i++) {
		if (str[i] == '\n') newlines++;
	}
	return newlines;
}

void
center_add_mult_lines(const char **msg,
					  unsigned idx,
					  const unsigned num_lines)
{
    unsigned tmp_idx, padding, stop_idx;
	stop_idx = idx + num_lines;
	
	/* find the longest line length, we'll use that for padding */
	unsigned max_len = 0;
	for (tmp_idx = idx; tmp_idx < stop_idx; tmp_idx++) {
		if(strlen(msg[tmp_idx]) > max_len) {
			max_len = strlen(msg[tmp_idx]);
		}
	}
	set_padding(max_len, &padding);
	
	/* print each line with the new padding that we found */
	while (idx < stop_idx) {
		sprintf(g_line_buf, 
				"%*s%s\n",
				padding, " ",
				msg[idx++]);
		strcat(g_screen_buf, g_line_buf);
	}
}

void
center_add_line(const char **msg, const unsigned idx)
{
	unsigned padding = 0;
	set_padding(strlen(msg[idx]), &padding);
	sprintf(g_line_buf,
			"%*s%s\n",
			padding, " ",
			msg[idx]); /* fix number of newlines */
    strcat(g_screen_buf, g_line_buf);
}

void
center_split_two(const char *msg_left, const char *msg_right)
{
    unsigned padding = g_display_width 
	                 - strlen(msg_left) 
			         - strlen(msg_right)
					 - newlines_in(msg_right);
    sprintf(g_line_buf,
            "%s%*s%s\n",
            msg_left,
            padding, " ",
            msg_right);
    strcat(g_screen_buf, g_line_buf);
}