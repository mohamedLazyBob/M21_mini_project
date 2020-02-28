#include "mini_project.h"

int		print_cars_menu()
{
	int	choice;

	do
	{
		system("clear");
		printf("\t\t -------------------------------\t\t\t\n");
		printf("\t\t|\tGestion des voiture\t\t|\n");
		printf("\t\t -------------------------------\t\t\t\n\n");
		printf("\t -------------------------------------------------------\t\t\t\n");
		printf("\t|\tList des voitures.................................1\t\t|\n");
		printf("\t|\tAjouter voiture...................................2\t\t|\n");
		printf("\t|\tModifier voiture..................................3\t\t|\n");
		printf("\t|\tsupprimer voiture.................................4\t\t|\n");
		printf("\t|\tretour............................................5\t\t|\n");
		printf("\t -------------------------------------------------------\t\t\t\n");
		printf("\t\t votre choix  :  ");
		scanf("%d", &choice);
	} while (choice < 1 || choice > 6);
	return (choice);
}
void	ft_cars_management(int cars_fd, int clients_fd, int contracts_fd)
{
	int choice;

	choice = print_cars_menu();

}
