#ifndef NMS_H
#define NMS_H 1

#include <stddef.h>
#include <stdbool.h>

// Default arguments for nms_exec()
#define INIT_NMSARGS { NULL, NULL, -1, -1, false }

// Argument structure for nms_exec()
typedef struct {
	const char *src;
	const char *return_opts;
	const int input_cursor_x;
	const int input_cursor_y;
	bool show_cursor;
} NmsArgs;

// Display the characters stored in the display queue
char nms_exec(NmsArgs *);

#endif
