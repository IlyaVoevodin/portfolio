#include "input.h"

segment_table* parse_segment_table(char* filename)
{
	segment_table* Head = NULL;
	segment_table* seg_node = NULL;

	FILE* file = fopen(filename, "r");
	int seg_num = 0;
	char buf[ArrSize];
	char* Path = (char*)malloc(sizeof(char) * ArrSize);
	while (fgets(buf, ArrSize, file))
	{
		int ind = 0;
		for (int i = 0; i < ArrSize; i++)
		{
			Path[i] = NULL;
		}
		char record[ArrSize] = { NULL };

		for (int i = 0; buf[i]; i++)
		{
			if (buf[i] != ';') {
				Path[i] = buf[i];
				Path[i + 1] = '\0';
			}
			else
				break;
			ind++;
		}

		int j = 0;
		for (int i = ind + 1; buf[i]; i++)
		{

			if (buf[i] != ';') {
				record[j] = buf[i];
				j++;
			}
			else
				break;
			ind++;
		}

		add_segment(Path, atoi(record), seg_num, &seg_node);
		seg_num++;

		if (Head == NULL)
			Head = seg_node;
	}
	fclose(file);
	return Head;
}

page_table* parse_pages_table(char* filename)
{
	page_table* Head = NULL;
	page_table* page_node = NULL;

	FILE* file = fopen(filename, "r");
	char buffer[ArrSize];

	while (fgets(buffer, ArrSize, file))
	{
		int ind = 0;
		char page_num[ArrSize] = { NULL };
		char frame[ArrSize] = { NULL };
		char bit[1] = { NULL };
		for (int i = 0; buffer[i]; i++)
		{
			if (buffer[i] != ';')
				page_num[i] = buffer[i];
			else {
				ind = i + 1;
				break;
			}
		}

		bit[0] = buffer[ind];
		ind += 2;

		int j = 0;
		for (int i = ind; buffer[i]; i++)
		{
			if (buffer[i] != ';')
			{
				frame[j] = buffer[i];
				j++;
			}
			else
				break;
		}

		add_page(atoi(bit), atoi(page_num), atoi(frame), &page_node);

		if (Head == NULL)
			Head = page_node;
	}
	fclose(file);
	return Head;
}

segment_table* add_segment(char* path, int record, int seg_num, segment_table** seg_node)
{
	segment_table* tmp = *seg_node;
	if (*seg_node == NULL)
		(*seg_node) = (segment_table*)malloc(sizeof(segment_table));
	else
	{
		while (tmp->next_seg)
			tmp = tmp->next_seg;
	}
	tmp = (segment_table*)malloc(sizeof(segment_table));

	tmp->pages_table_path = path;
	tmp->records = record;
	tmp->segment_number = seg_num;
	tmp->next_seg = NULL;
	(*seg_node)->next_seg = tmp;
	(*seg_node) = tmp;

	return (*seg_node);
}

page_table* add_page(int bit, int page_num, int frame, page_table** page_node) {
	page_table* tmp = *page_node;
	if (*page_node == NULL)
		(*page_node) = (page_table*)malloc(sizeof(page_table));
	else
	{
		while (tmp->next_page)
			tmp = tmp->next_page;
	}
	tmp = (page_table*)malloc(sizeof(page_table));

	tmp->bit = bit;
	tmp->page_number = page_num;
	tmp->frame = frame;
	tmp->next_page = NULL;
	(*page_node)->next_page = tmp;
	(*page_node) = tmp;
	
	return (*page_node);
}

