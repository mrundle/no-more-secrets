#include <stdio.h>
#include <string.h>

#include "nms.h"
#include "screen_buf.h"

int main(void) {
    const char *msg[] = {
        "DATANET PROC RECORD:  45-3456-W-3452",
        "Transnet on/xc-3\n",
        "FEDERAL RESERVE TRANSFER NODE\n",
        "National Headquarters\n",
        "************  Remote Systems Network Input Station  ************",
        "================================================================\n",
        "[1] Interbank Funds Transfer  (Code Prog: 485-GWU)",
        "[2] International Telelink Access  (Code Lim: XRP-262)",
        "[3] Remote Facsimile Send/Receive  (Code Tran:  2LZP-517)",
        "[4] Regional Bank Interconnect  (Security Code:  47-B34)",
        "[5] Update System Parameters  (Entry Auth. Req.)",
        "[6] Remote Operator Logon/Logoff\n",
        "================================================================\n",
        "[ ] Select Option or ESC to Abort"
    };
	
	unsigned n_lines = sizeof(msg) / sizeof(msg[0]);
	init_screen_buf(n_lines);
	
	unsigned ctr = 0;
    center_split_two(msg[ctr], msg[ctr + 1]); ctr += 2;
	center_add_line(msg, ctr++);
	center_add_line(msg, ctr++);
	center_add_line(msg, ctr++);
	center_add_line(msg, ctr++);
	center_add_mult_lines(msg, ctr, 6); ctr += 6;
	center_add_line(msg, ctr++);
	center_add_line(msg, ctr++);

	NmsArgs nms_args = {
		.src = get_screen_buf(),
		.return_opts = "123456",
		.input_cursor_y = 18,
		.input_cursor_x = ((get_screen_width() - strlen(msg[n_lines - 1])) / 2) + 1
	};
	char input = nms_exec(&nms_args);

	unsigned i;
	for (i = 0; i < strlen(nms_args.return_opts); i++) {
		if (nms_args.return_opts[i] == input) {
			printf("User chose %c\n", input);
		}
		else if (i == strlen(nms_args.return_opts)) {
			printf("Unrecognized selection: %c\n", input);
		}
	}
	
    free_screen_buf();
	return 0;
}
