#include <stdio.h>
#include <getopt.h>

int main(int argc, char *argv[])
{
	char c;
	int num = 0;
	while((c = getopt_long(argc, argv, short_option, long_option, NULL))!=-1){
		switch(c){
		case 'f':
			num = atoi(optarg);
			break;
		case 'i':
			num = atoi(optarg)*2;
			break;
		case '?':
		case 'h':
		default:
			printf("help info:\n");
		}
	}
	printf("num = %d\n", num);
	return 0;
}
