#include <stdio.h>
#include <string.h>

#include "zlib.h"
#include "sign.h"

int main() {
	if (0)
	{
		zlib::ScopeFile sf("./data/input/test", "r");
		FILE* file = sf.get_ptr();

		char line[1024];
		char seg[1024];
		while (NULL != fgets(line, 1024, file)) {
			fprintf(stdout, "%lu, %s", strlen(line), line);
			const char* p = zlib::seg_sentence(line, "\t", seg, 2);
			if (NULL != p) {
				fprintf(stdout, "seg: %s\n", seg);
			}
			int cnt = zlib::count_sep(line, "\t");
			fprintf(stdout, "count: %d\n", cnt);
		}
	}

	fprintf(stdout, "length of int: %lu\n", sizeof(int));
	fprintf(stdout, "length of short: %lu\n", sizeof(short));
	fprintf(stdout, "length of long: %lu\n", sizeof(long));
	fprintf(stdout, "length of long long: %lu\n", sizeof(long long));
	zint64 sign1, sign2;
	create_sign(sign1, sign2, "caoyangzhaodongwei");
	fprintf(stdout, "sign for %s\n", "caoyangzhaodongwei");
	fprintf(stdout, "sign1: %02llx\n", sign1);
	fprintf(stdout, "sign2: %02llx\n", sign2);
	fprintf(stdout, "sign for %s\n", "./data/input/test");
	create_sign(sign1, sign2, "./data/input/test", 0);
	fprintf(stdout, "sign1: %02llx\n", sign1);
	fprintf(stdout, "sign2: %02llx\n", sign2);
	return 0;
}
