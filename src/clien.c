#include "mini_project.h"

int		print_clients_menu()
{
	int	choice;

	choice = 0;
	do
	{
//		system("clear");
		printf("\t\t -------------------------------\t\t\t\n");
		printf("\t\t|\tGestion des Clients\t\t|\n");
		printf("\t\t -------------------------------\t\t\t\n\n");
		printf("\t -------------------------------------------------------\t\t\t\n");
		printf("\t|\tList des clients................................1\t\t|\n");
		printf("\t|\tAjouter client...................................2\t\t|\n");
		printf("\t|\tModifier client.................................3\t\t|\n");
		printf("\t|\tSupprimer client................................4\t\t|\n");
		printf("\t|\tretour..........................................5\t\t|\n");
		printf("\t -------------------------------------------------------\t\t\t\n");
		printf("\t\t votre choix  :  ");
		scanf("%d", &choice);
	} while (choice < 1 || choice > 6);
	return (choice);
}


void	ft_clients_management(void)
{
	int choice;

	choice = print_clients_menu();

}
