#include <stdio.h>
#include <string.h>

#include "tools.h"

int main() {

	tools::ScopeFile sf("./data/input/test", "r");
	FILE* file = sf.get_ptr();

	char line[1024];
	char seg[1024];
	while (NULL != fgets(line, 1024, file)) {
		fprintf(stdout, "%d, %s", strlen(line), line);
		const char* p = tools::seg_sentence(line, "\t", seg, 2);
		if (NULL != p) {
			fprintf(stdout, "seg: %s\n", seg);
		}
		int cnt = tools::count_sep(line, "\t");
		fprintf(stdout, "count: %d\n", cnt);
	}

	return 0;
}
