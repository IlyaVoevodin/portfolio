#include "data.h"

void data_analyze(char* dat_filename, page_table* page_node, segment_table* seg_node)
{
	FILE* file = fopen(dat_filename, "rb");

	int i = 0;
	unsigned __int8 byte;
	long lst_result[ArrSize] = { NULL };

	while (fread(&byte, sizeof(byte), 1, file))
	{	
		switch (byte)
		{
		case 0x1A: 
		{
			printf("%X ", byte);
			strcat(lst_result, "MOV ");

			fread(&byte, sizeof(byte), 1, file);
			printf("%X ", byte);
			char lst_buf[ArrSize] = "";
			sprintf(lst_buf, "R%X ", byte);
			strcat(lst_result, lst_buf);

			fread(&byte, sizeof(byte), 1, file);
			printf("%X ", byte);
			sprintf(lst_buf, "R%X", byte);
			strcat(lst_result, lst_buf);
			break;
		}
		case 0x1B:
		{
			printf("%X ", byte);
			strcat(lst_result, "MOV ");

			fread(&byte, sizeof(byte), 1, file);
			printf("%X ", byte);

			char lst_buf[ArrSize] = "";
			if (byte == 1)
			{
				unsigned __int32 addr;
				fread(&addr, sizeof(addr), 1, file);
				printf("%.8X ", addr);
				sprintf(lst_buf, "[0x%.8X] ", addr);
				strcat(lst_result, lst_buf);

				fread(&byte, sizeof(byte), 1, file);
				printf("%X ", byte);
				sprintf(lst_buf, "R%X ", byte);
				strcat(lst_result, lst_buf);

				addr = address_checkout(addr, page_node, seg_node);
				break;
			}
			
			fread(&byte, sizeof(byte), 1, file);
			printf("%X ", byte);
			sprintf(lst_buf, "R%X ", byte);
			strcat(lst_result, lst_buf);

			unsigned __int32 addr;
			fread(&addr, sizeof(addr), 1, file);
			printf("%.8X ", addr);
			addr = address_checkout(addr, page_node, seg_node);
			sprintf(lst_buf, "[0x%.8X] ", addr);
			strcat(lst_result, lst_buf);
			break;
		}
		case 0x01:
		{
			printf("%.2X ", byte);
			strcat(lst_result, "ADD ");

			char lst_buf[ArrSize] = "";
			fread(&byte, sizeof(byte), 1, file);
			printf("%X ", byte);
			sprintf(lst_buf, "R%X ", byte);
			strcat(lst_result, lst_buf);

			fread(&byte, sizeof(byte), 1, file);
			printf("%X ", byte);
			sprintf(lst_buf, "R%X ", byte);
			strcat(lst_result, lst_buf);
			break;
		}
		case 0x02:
		{
			printf("%.2X ", byte);
			strcat(lst_result, "ADD ");

			fread(&byte, sizeof(byte), 1, file);
			printf("%X ", byte);

			char lst_buf[ArrSize] = "";
			fread(&byte, sizeof(byte), 1, file);
			printf("%X ", byte);
			sprintf(lst_buf, "R%X ", byte);
			strcat(lst_result, lst_buf);

			unsigned __int32 addr;
			fread(&addr, sizeof(addr), 1, file);
			printf("%.8X ", addr);
			addr = address_checkout(addr, page_node, seg_node);
			sprintf(lst_buf, "[0x%.8X] ", addr);
			strcat(lst_result, lst_buf);
			break;
		}
		case 0x94:
		{
			printf("%X ", byte);
			strcat(lst_result, "JG ");

			char lst_buf[ArrSize] = "";
			fread(&byte, sizeof(byte), 1, file);
			printf("%X ", byte);
			sprintf(lst_buf, "%X ", byte);
			strcat(lst_result, lst_buf);
			break;
		}
		case 0x95:
		{
			printf("%X ", byte);
			strcat(lst_result, "JG ");

			char lst_buf[ArrSize] = "";
			unsigned __int32 addr;
			fread(&addr, sizeof(addr), 1, file);
			printf("%.8X ", addr);
			addr = address_checkout(addr, page_node, seg_node);
			sprintf(lst_buf, "[0x%.8X] ", addr);
			strcat(lst_result, lst_buf);
			break;
		}
		case 0x80:
		{
			printf("%X ", byte);
			strcat(lst_result, "CMP ");

			fread(&byte, sizeof(byte), 1, file);
			printf("%X ", byte);
			char lst_buf[ArrSize] = "";
			sprintf(lst_buf, "R%X ", byte);
			strcat(lst_result, lst_buf);

			fread(&byte, sizeof(byte), 1, file);
			printf("%X ", byte);
			sprintf(lst_buf, "R%X ", byte);
			strcat(lst_result, lst_buf);
			break;
		}
		case 0x1C:
		{
			printf("%X ", byte);
			strcat(lst_result, "MOV ");

			char lst_buf[ArrSize] = "";
			fread(&byte, sizeof(byte), 1, file);
			printf("%X ", byte);
			
			fread(&byte, sizeof(byte), 1, file);
			printf("%X ", byte);
			sprintf(lst_buf, "R%X ", byte);
			strcat(lst_result, lst_buf);

			unsigned __int16 num;
			fread(&num, sizeof(num), 1, file);
			printf("%.4X ", num);
			sprintf(lst_buf, "%.4X ", num);
			strcat(lst_result, lst_buf);
			break;
		}
		default:
			break;
		}

		printf(":\n\t// %s //\n", lst_result);
		
		for (int j = 0; lst_result[j]; j++)
			lst_result[j] = NULL;
	}
	
	fclose(file);
}