#include "mini_project.h"

//int MenuPrincipal()
//{
//    int choix;
//
//	printf("\n                               \xda\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xbf");
//	printf("\n                               \xb3 Menu Principal  \xb3");
//	printf("\n                               \xc0\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xd9");
//
//    printf("\n\n");
//
//    printf("\n               \xc9\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbb");
//    printf("\n               \xba                                              \xba");
//    printf("\n               \xba    Location..............................1   \xba");
//    printf("\n               \xba    Gestion voitures......................2   \xba");
//    printf("\n               \xba    Gestion clients.......................3   \xba");
//    printf("\n               \xba    Quitter...............................4   \xba");
//    printf("\n               \xba                                              \xba");
//    printf("\n               \xc8\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbc");
//    printf("\n\n                                Votre choix  :  ");
//
//    scanf("%d",&choix);
//
//    return choix;
//}

int		print_menu_principal()
{
	int	choice;

	choice = 0;
	do
	{
//		system("clear");
		printf("\t\t -------------------------------\t\t\t\n");
		printf("\t\t|\tMenu Principal\t\t|\n");
		printf("\t\t -------------------------------\t\t\t\n\n");
		printf("\t -------------------------------------------------------\t\t\t\n");
		printf("\t|\tLocation..............................1\t\t|\n");
		printf("\t|\tGestion voitures......................2\t\t|\n");
		printf("\t|\tGestion clients.......................3\t\t|\n");
		printf("\t|\tQuitter...............................4\t\t|\n");
		printf("\t -------------------------------------------------------\t\t\t\n");
		printf("\t\t votre choix : ");
		scanf("%d", &choice);
	} while (choice < 1 || choice > 4);

	return (choice);
}

int		main(void)
{
	int choice;

	do
	{
		choice = print_menu_principal();
		if (choice == 1)
			ft_rental_management();
	   	else if (choice == 2)
	   		ft_cars_management();
	   	else if (choice == 3)
	   		ft_clients_management();
	} while (choice > 0 && choice < 4);
	return (0);
}

