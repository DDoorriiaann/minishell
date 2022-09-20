#include "proto.h"

int	prompt_shell(void)
{
	char	*buffer;
//	size_t	buf_size;

//	buf_size = 2048;
	/*buffer = (char *)malloc(sizeof(char) * buf_size);
	if (!buffer)
	{
		perror("Malloc failure");
		return (1);
	}*/
	while ((buffer = readline("Mickeytotal$>")) != NULL)
	{
		printf("cmd = %s\n", buffer);
		write(1, "$> ", 3);
		free(buffer);
	}
	printf("\nHave a nice day with MickeyTotal \n");
	return (0);
}
