#ifndef __SCREEN_BUF_H__
#define __SCREEN_BUF_H__

void init_screen_buf(unsigned n_lines);
void free_screen_buf(void);

void center_add_mult_lines(const char *msg[],
					       unsigned idx,
					       const unsigned num_lines);

void center_add_line(const char *msg[], const unsigned idx);

void center_split_two(const char *msg_left, const char *msg_right);

char *get_screen_buf(void);
unsigned get_screen_width(void);

#endif // __SCREEN_BUF_H__