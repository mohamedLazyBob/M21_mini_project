#include "mini_project.h"

int	print_this_menu(char buff[][50], int size)
{
	int	choice;
	int	idx;

	choice = 0;
	do
	{
		printf("      %s", UL HORZ HORZ HORZ HORZ HORZ HORZ HORZ HORZ HORZ UR ENDL);
		printf("      %s     %s     %s\n", VERT, buff[0], VERT);
		printf("      %s", DL HORZ HORZ  HORZ HORZ HORZ HORZ HORZ HORZ HORZ DR ENDL);

		idx = 1;
		printf(UL HORZ HORZ HORZ HORZ HORZ  HORZ HORZ  HORZ HORZ HORZ HORZ HORZ UR ENDL);
		printf("%s                                                %s\n", VERT, VERT);
		while (idx < size)
			printf("%s     %s    %s\n", VERT, buff[idx++], VERT);
		printf("%s                                                %s\n", VERT, VERT);
		printf(DL HORZ HORZ HORZ  HORZ HORZ  HORZ HORZ  HORZ HORZ HORZ HORZ HORZ DR ENDL);
		printf("\t\t votre choix : ");
		scanf("%d", &choice);
	} while (choice < 0 || choice > size);

	return (choice);
}

/*
** ***************************************************************************
*/

char	*ft_read_buffer(char *str, int buff_size)
{
	//char buff[514] = { 0 };
	char	*buff = NULL;
	size_t	len = 0;
	int	linesize = 0;
	char	*ret;

	//ret = fgets(buff, 514, stdin);
	//scanf("%s", buff);
	do
	{
		linesize = getline(&buff, &len, stdin);
		//printf("buff == [%s] , size = %d;\n", buff, linesize);
	} while (linesize == 1);// in case of a leftover newline/whitespace
	buff[linesize - 1] = 0;
//	printf("buff == [%s] , size = %d;\n", buff, linesize);
	memset(str, 0, buff_size);
	strncpy(str, buff, buff_size - 1);
	if (buff)
		free(buff);
	return (ret);
}

/*
** ***************************************************************************
*/

int		main(void)
{
	int	choice;
	char	buff[5][50] = {"     Menu    Principal    ", 
				"Location..............................1", 
				"Gestion voitures......................2", 
				"Gestion clients.......................3", 
				"Quitter...............................4"};

	do
	{
		system("clear");
		choice = print_this_menu(buff, 5);
		if (choice == 1)
			ft_rental_management();
	   	else if (choice == 2)
	   		ft_cars_management();
	   	else if (choice == 3)
	   		ft_clients_management();
	} while (choice >= 0 && choice < 4);

/*	char line[10];
	for (int i = 0; i < 5; i++)
	{
		char *ret = ft_read_buffer(line, 10);
		printf("you've entred : [%s], %s;\n", line, ret);
		printf("number : ");
		scanf("%d\n", &choice);
	}
*/
	return (0);
}
