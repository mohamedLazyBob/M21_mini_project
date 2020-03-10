#include "mini_project.h"
//1) afficher la liste des voitures déjà enregistrées dans le fichier « Voitures » ; 
//2) ajouter une nouvelle voiture dans le fichier « Voitures »; 
//3) modifier les informations concernant une voiture déjà enregistrée ; 
//4) de supprimer une voiture du fichier « Voitures »
//5) retourner au menu principal.

/*
** ****************************************************************************
*/

int		print_cars_menu()
{
	int	choice;

	choice = 0;
	do
	{
		//system("clear");
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

/*
** ****************************************************************************
*/

void	ft_cars_management()
{
	int choice;

	do
	{
		choice = print_cars_menu();
		if (choice == 1)
			ft_list_cars();
		else if (choice == 2)
			ft_add_car();
		else if(choice == 3)
			ft_modify_car_info();
		else if(choice == 4)
			ft_delete_car();
	} while (choice != 5);
}

/*
** ****************************************************************************
*/

void	ft_list_cars()
{
	voiture car;
	char line[5];
	int ret;
	FILE *file = fopen("Voitures", "r");

	if (file == NULL)
	{
		printf("ERROR couldn't open cars file\n");
		return ;
	}
	while ((ret = read_one_car_info(file, &car)) != EOF)
	{
		printf("<\n");
		printf("\tnbplaces: %d\n",   car.nbplaces);
		printf("\tprixJour: %d\n",   car.prixJour);
		printf("\tidVoiture: %d\n",  car.idVoiture);
		printf("\tmarque: %s\n",     car.marque);
		printf("\tcouleur: %s\n",    car.couleur);
		printf("\tnomVoiture: %s\n", car.nomVoiture);
		printf("\tEnLocation: %s\n", car.EnLocation);
		printf("/>\n");
	}
	fclose(file);
}

int		read_one_car_info(FILE *file, voiture *car)
{
	char line[100];
	int ret;

	fscanf(file, "%s", line);
	fscanf(file, "%d\n",  &(car->nbplaces));
	fscanf(file, "%d\n",  &(car->prixJour));
	fscanf(file, "%d\n", &(car->idVoiture));
	fscanf(file, "%s\n",    car->marque);
	fscanf(file, "%s\n",   car->couleur);
	fscanf(file, "%s\n", car->nomVoiture);
	fscanf(file, "%s\n", car->EnLocation);
	ret = fscanf(file, "%s", line);
	return (ret);
}

/*
** ****************************************************************************
*/

void	ft_add_car(void)
{
	voiture car;

	get_car_input(&car);
	ft_add_this_car(car, "Voitures");
}

void	get_car_input(voiture *car)
{
	printf("please write the information of this car:\n");
	printf("nbplaces:   "); scanf("%d",   &(car->nbplaces));
	printf("\nprixJour:   "); scanf("%d", &(car->prixJour));
	printf("\nidVoiture:  "); scanf("%d", &(car->idVoiture));
	printf("\nmarque:     "); scanf("%s", car->marque);
	printf("\ncouleur:    "); scanf("%s", car->couleur);
	printf("\nnomVoiture: "); scanf("%s", car->nomVoiture);
	printf("\nEnLocation: "); scanf("%s", car->EnLocation);
}

void	ft_add_this_car(voiture car, char *filename)
{

	FILE *ptr = fopen(filename, "a+");
	fprintf(ptr, "<\n");
	fprintf(ptr, "%d\n",   car.nbplaces);
	fprintf(ptr, "%d\n",   car.prixJour);
	fprintf(ptr, "%d\n",  car.idVoiture);
	fprintf(ptr, "%s\n",     car.marque);
	fprintf(ptr, "%s\n",    car.couleur);
	fprintf(ptr, "%s\n", car.nomVoiture);
	fprintf(ptr, "%s\n", car.EnLocation);
	fprintf(ptr, "/>\n");
	fclose(ptr);
}

/*
** ****************************************************************************
*/

void	ft_modify_car_info()
{
	int num;
	int	nbr;
	int	id;
	int	ret;
	char str[20];
	int	choice;
	voiture car;
	FILE *file = fopen("Voitures", "r");

	print_modify_menu(&id, &choice, &nbr, str);
	while ((ret = read_one_car_info(file, &car)) != EOF)
	{
		if (car.idVoiture == id)
		{
			fclose(file);
			delete_this_car(car);
			if(choice == 1)	car.nbplaces = nbr;
			else if (choice == 2)	car.prixJour = nbr;
			else if (choice == 3)	car.idVoiture = nbr;
			else if (choice == 4)	strcpy(car.marque, str);
			else if (choice == 5) 	strcpy(car.couleur, str);
			else if (choice == 6) 	strcpy(car.nomVoiture, str);
			else if (choice == 7) 	strcpy(car.EnLocation, str);
			file = fopen("Voitures", "a+");
			ft_add_this_car(car, "Voitures");
			break;
		}
	}
	fclose(file);
}

int		print_modify_menu(int *id, int *choice, int *nbr, char *str)
{
	printf("écrivez l'identifiant de la voiture que vous souhaitez modifier.\n--> ");
	scanf("%d", id);
	printf("choisissez le nombre qui correspond à l'attribut que vous souhaitez modifier:\n");
	while (1)
	{
		printf("nbplaces:.........1\n");
		printf("prixJour:.........2\n");
		printf("idVoiture:........3\n");
		printf("marque:...........4\n");
		printf("couleur:..........5\n");
		printf("nomVoiture:.......6\n");
		printf("EnLocation:.......7\n");
		scanf("%d", choice);
		if (*choice > 0 && *choice < 4)
		{
			printf("saisir la modification: ");
			scanf("%d", nbr);
			return (0);
		}
		else if (*choice > 3 && *choice < 8)
		{
			printf("saisir la modification: ");
			scanf("%s", str);
			return (1);
		}
	}
}

/*
** ****************************************************************************
*/

void	ft_delete_car()
{
	int	id;
	int ret;
	voiture car;
	FILE	*file = fopen("Voitures", "r");

	printf("Donner l'id de la voiture tu veut supprimer : ");
	scanf("%d", &id);
	while ((ret = read_one_car_info(file, &car)) != EOF)
	{
		if (car.idVoiture == id)
		{
			fclose(file);
			delete_this_car(car);
			return ;
		}
	}
	fclose(file);
	return ;
}

void	delete_this_car(voiture car)
{
	FILE *fileptr1, *fileptr2;
	voiture temp_car;
	int	end;

	fileptr1 = fopen("Voitures", "r");
	fileptr2 = fopen("replica.txt", "w");
	fclose(fileptr2);

	while (1)
	{
		end = read_one_car_info(fileptr1, &temp_car);
		if (end != EOF && temp_car.idVoiture != car.idVoiture)
			ft_add_this_car(temp_car, "replica.txt");
		if (end == EOF)
			break;
	}
	fclose(fileptr1);
	remove("Voitures");
	rename("replica.txt", "Voitures");
	return ;
}


/*
** ****************************************************************************
*/

void	modifier_car_enLocation(int	id, char *str)
{
	FILE	*file = fopen("Voitures", "r");
	voiture  car;


	while (read_one_car_info(file, &car) != EOF)
	{
		if (car.idVoiture == id)
		{
			fclose(file);
			delete_this_car(car);
			strcpy(car.EnLocation, str);
			ft_add_this_car(car, "Voitures");
			return ;
		}
	}
	fclose(file);
}
