#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
#define ArrSize 50

#pragma warning(disable : 4996)

typedef struct segments_table {
	char* pages_table_path;
	int records;
	int segment_number;

	struct segment_table* next_seg;
} segment_table;


typedef struct pages_table {
	int bit;
	int page_number;
	int frame;

	struct pages_table* next_page;
} page_table;


segment_table* parse_segment_table(char* filename);
segment_table* add_segment(char* path, int record, int seg_num, segment_table** seg_node);

page_table* parse_pages_table(char* filename);
page_table* add_page(int bit, int page_num, int frame, page_table** pages_node);


