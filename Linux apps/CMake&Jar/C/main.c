#include "Print.h"
#include "Search.h"
#include <getopt.h>

int main(int argc, char** argv)
{
    	const int n = atoi(argv[1]);
	if(n == 0)
	{
		printf("Input matrix size!");
		return 0;
	}
    	int* A = (int*)malloc(n * n * sizeof(int));
    
    	int row, clmn,x;
    	menu(n, &A);

	printf("Input value to search:");
	scanf("%d",&x);
	printf("\n");

	int c = 0;
	const char* short_options = "dr";
	static struct option long_options[] = {{"debug", no_argument, 0, 'd'}, {"release", no_argument, 0, 'r'}, {0, 0, 0, 0}};
	int option_index = 0;
	while((c = getopt_long(argc, argv, short_options, long_options,&option_index)) != -1)
	{
		switch (c)
		{
		case 'd':
			DebugSearch(x, &row, &clmn, n, A);
			break;
		case 'r':
			ReleaseSearch(x, &row,&clmn, n, A);
        		printf("Row:%d, Clmn:%d", row, clmn);
			break;
		default:
			printf("Wrong option input!");
			break;
		}
	}
  	free(A);
    	return 0;
}
