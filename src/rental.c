#include "mini_project.h"

int		print_rental_menu()
{
	int	choice;

	choice = 0;
	do
	{
//		system("clear");
		printf("\t\t -------------------------------\t\t\t\n");
		printf("\t\t|\tLocation d'une voiture\t\t|\n");
		printf("\t\t -------------------------------\t\t\t\n\n");
		printf("\t -------------------------------------------------------\t\t\t\n");
		printf("\t|\tVisualiser contrat..............................1\t\t|\n");
		printf("\t|\tlouer voiture...................................2\t\t|\n");
		printf("\t|\tRetourner voiture...............................3\t\t|\n");
		printf("\t|\tModifier contrat................................4\t\t|\n");
		printf("\t|\tsupprimer contrat...............................5\t\t|\n");
		printf("\t|\tretour..........................................6\t\t|\n");
		printf("\t -------------------------------------------------------\t\t\t\n");
		printf("\t\t votre choix  :  ");
		scanf("%d", &choice);
	} while (choice < 1 || choice > 6);
	return (choice);
}
void	ft_rental_management(void)
{
	int choice;

	choice = print_rental_menu();

}

