#include "mini_project.h"
//1) afficher la liste des voitures déjà enregistrées dans le fichier « Voitures » ; 
//2) ajouter une nouvelle voiture dans le fichier « Voitures »; 
//3) modifier les informations concernant une voiture déjà enregistrée ; 
//4) de supprimer une voiture du fichier « Voitures »
//5) retourner au menu principal.
  
int		print_cars_menu()
{
	int	choice;

	choice = 0;
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

void	ft_cars_management(FILE *cars_fd)
{
	int choice;

	choice = print_cars_menu();
	if (choice == 1)
		ft_list_cars(cars_fd);
	else if (choice == 2)
		ft_add_car();
	/*else if(choice == 3)
		ft_modify_car_info(cars_fd);
	else if(choice == 4)
		ft_delete_car(cars_fd);
*/
}

void	ft_list_cars(FILE *fd)
{
	voiture car;
	char line[5];
	int ret;
	FILE *cars = fopen("Voitures", "r");

	if (cars == NULL)
	{
		printf("ERROR couldn't open cars file\n");
		sleep(1);
		return ;
	}
	do
	{
		fscanf(cars, "%s", line);
		fscanf(cars, "nbplaces: %d\n",  &(car.nbplaces));
		fscanf(cars, "prixJour: %d\n",  &(car.prixJour));
		fscanf(cars, "idVoiture: %d\n", &(car.idVoiture));
		fscanf(cars, "marque: %s\n",    &(car.marque));
		fscanf(cars, "couleur: %s\n",   &(car.couleur));
		fscanf(cars, "nomVoiture: %s\n", &(car.nomVoiture));
		fscanf(cars, "EnLocation: %s\n", &(car.EnLocation));
		ret = fscanf(cars, "%s", line);
	
		printf("------------------------\n\n");
		printf("nbplaces: %d\n",   car.nbplaces);
		printf("prixJour: %d\n",   car.prixJour);
		printf("idVoiture: %d\n",  car.idVoiture);
		printf("marque: %s\n",     car.marque);
		printf("couleur: %s\n",    car.couleur);
		printf("nomVoiture: %s\n", car.nomVoiture);
		printf("EnLocation: %s\n", car.EnLocation);
		sleep(5);
	} while (ret != EOF);
}

void	ft_add_car(void)
{
	FILE *ptr = fopen("Voitures", "a+");
	voiture car;

	get_car_input(&car);
	fprintf(ptr, "<\n");
	fprintf(ptr, "nbplaces: %d\n",   car.nbplaces);
	fprintf(ptr, "prixJour: %d\n",   car.prixJour);
	fprintf(ptr, "idVoiture: %d\n",  car.idVoiture);
	fprintf(ptr, "marque: %s\n",     car.marque);
	fprintf(ptr, "couleur: %s\n",    car.couleur);
	fprintf(ptr, "nomVoiture: %s\n", car.nomVoiture);
	fprintf(ptr, "EnLocation: %s\n", car.EnLocation);
	fprintf(ptr, "/>\n");
	
}

void	get_car_input(voiture *car)
{
	printf("please write the information of this car:\n");
	printf("nbplaces:   "); scanf("%d",   &(car->nbplaces));
	printf("\nprixJour:   "); scanf("%d", &(car->prixJour));
	printf("\nidVoiture:  "); scanf("%d", &(car->idVoiture));
	printf("\nmarque:     "); scanf("%s", &(car->marque));
	printf("\ncouleur:    "); scanf("%s", &(car->couleur));
	printf("\nnomVoiture: "); scanf("%s", &(car->nomVoiture));
	printf("\nEnLocation: "); scanf("%s", &(car->EnLocation));
}
