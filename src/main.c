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
		printf("%s       pour vider l'ecran ...............0      %s\n", VERT, VERT);
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
		choice = print_this_menu(buff, 5);
		if (choice == 0)
			system("clear");
		else if (choice == 1)
			ft_rental_management();
	   	else if (choice == 2)
	   		ft_cars_management();
	   	else if (choice == 3)
	   		ft_clients_management();
	} while (choice >= 0 && choice < 4);
	return (0);
}
