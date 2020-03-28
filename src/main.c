/******************************************************************************/
/*                              Mohamed zaboub                                */
/******************************************************************************/

#include "mini_project.h"

/*
** ***************************************************************************
**  This function is used to print all the principal menus. 
**  So that we have a standard menu shape.
*/

int	print_this_menu(char buff[][50], int size)
{
	int	choice;
	int	idx;

	choice = 0;
	do
	{
		printf("      %s", UL HORZ HORZ HORZ HORZ HORZ HORZ HORZ \
					HORZ HORZ UR ENDL);
		printf("      %s     %s     %s\n", VERT, buff[0], VERT);
		printf("      %s", DL HORZ HORZ  HORZ HORZ HORZ HORZ HORZ \
					HORZ HORZ DR ENDL);

		idx = 1;
		printf(UL HORZ HORZ HORZ HORZ HORZ  HORZ HORZ  HORZ HORZ \
					HORZ HORZ HORZ UR ENDL);
		printf("%-47s %28s\n", VERT, VERT);
		while (idx < size)
			printf("%s     %s    %s\n", VERT, buff[idx++], VERT);
		printf("%-47s %28s\n", VERT, VERT);
		printf(DL HORZ HORZ HORZ  HORZ HORZ  HORZ HORZ  HORZ HORZ \
					HORZ HORZ HORZ DR ENDL);
		printf("\t\t votre choix : ");
		scanf("%d", &choice);
	} while (choice < 0 || choice > size);

	return (choice);
}

/*
** ****************************************************************************
** reads one whole line from the input.
** then copys just the first buff_size characters to str.
*/

char	*ft_read_buffer(char *str, int buff_size)
{
	int	linesize;
	char	*buff;
	char	*ret;
	size_t	len;

	len = 0;
	linesize = 0;
	buff = NULL;
	do
	{
		linesize = getline(&buff, &len, stdin);
	} while (linesize == 1);// in case of a leftover newline/whitespace
	buff[linesize - 1] = 0;
	memset(str, 0, buff_size);
	strncpy(str, buff, buff_size - 1);
	if (buff)
		free(buff);
	return (ret);
}

/*
** ****************************************************************************
** the main.
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
	return (0);
}

/*
** ****************************************************************************
*/
