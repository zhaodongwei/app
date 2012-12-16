#include <stdio.h>
#include <string.h>

#include "zlib.h"
#include "sign.h"

int main() {

	zlib::ScopeFile sf("./data/input/test", "r");
	FILE* file = sf.get_ptr();

	char line[1024];
	char seg[1024];
	while (NULL != fgets(line, 1024, file)) {
		fprintf(stdout, "%d, %s", strlen(line), line);
		const char* p = zlib::seg_sentence(line, "\t", seg, 2);
		if (NULL != p) {
			fprintf(stdout, "seg: %s\n", seg);
		}
		int cnt = zlib::count_sep(line, "\t");
		fprintf(stdout, "count: %d\n", cnt);
	}

	fprintf(stdout, "length of int: %d\n", sizeof(int));
	fprintf(stdout, "length of short: %d\n", sizeof(short));
	fprintf(stdout, "length of long: %d\n", sizeof(long));
	fprintf(stdout, "length of long long: %d\n", sizeof(long long));
	int64 sign1, sign2;
	create_sign(sign1, sign2, "caoyangzhaodongwei");
	fprintf(stdout, "%llx\n", sign1);
	fprintf(stdout, "%llx\n", sign2);
	return 0;
}
