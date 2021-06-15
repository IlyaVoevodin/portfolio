#include "data.h"

int main() {
	page_table* page = NULL;
	segment_table* seg = NULL;

	seg = parse_segment_table("segments.csv");
	data_analyze("myfile.dat", page, seg);
	
	return 0;
}