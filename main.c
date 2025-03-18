# include "philosopher.h"

int main (int argc, char *argv[])
{
	int count = 1;
	if(argc > 2)
	{
		while(count < argc)
		{
			printf("%s\n", argv[count]);
			count++;
		}
	}
	return (0);
}
