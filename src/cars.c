#include "mini_project.h"

/*
** ****************************************************************************
*/

void	ft_cars_management(void)
{
	int choice;

	char buff[][50] = {"    Gestion des voiture   ", 
		"List des voitures.....................1", 
		"Ajouter voiture.......................2", 
		"Modifier voiture......................3", 
		"supprimer voiture.....................4", 
		"retour................................5"};
	do
	{
		system("clear");
		choice = print_this_menu(buff, 6);
		if (choice == 1)	ft_list_cars();
		else if (choice == 2)	ft_add_car();
		else if(choice == 3)	ft_modify_car_info();
		else if(choice == 4)	ft_delete_car();
	} while (choice != 5);
}

/*
** ****************************************************************************
*/

void	ft_list_cars()
{
	int	ret;
	voiture	car;
	FILE	*file;
	char	line[5];

	file = fopen("Voitures", "r");
	if (file == NULL)
	{
		printf("ERROR couldn't open cars file\n");
		return ;
	}
	while ((ret = read_one_car_info(file, &car)) != EOF)
		print_one_car(car);
	fclose(file);
	printf("write a number to go back to the menu : ");
	scanf("%d", &ret);
}

/*
** ****************************************************************************
*/

void	print_one_car(voiture car)
{
	printf(G_UL G_HORZ G_HORZ G_HORZ G_HORZ G_HORZ G_HORZ G_HORZ G_HORZ \
		G_HORZ G_HORZ G_HORZ G_HORZ G_HORZ G_HORZ G_HORZ G_UR ENDL);
	printf("%s                        idVoiture: %.3d                      %s\n", \
		G_VERT, car.idVoiture, G_VERT);

	printf(G_ML G_T_HORZ G_T_HORZ G_T_HORZ G_T_HORZ G_T_HORZ G_T_HORZ G_T_HORZ G_T_HORZ \
		G_T_HORZ G_T_HORZ G_T_HORZ G_T_HORZ G_T_HORZ G_T_HORZ G_T_HORZ G_MR ENDL);

	printf("%s nomVoiture: %-15s  %s marque    : %-15s %s\n", \
		G_VERT, car.nomVoiture, G_VERT, car.marque, G_VERT);
	printf("%s nbplaces: %.2d                 %s couleur : %-7s           %s\n", \
		G_VERT, car.nbplaces, G_VERT, car.couleur, G_VERT);
	printf("%s prixJour: %.3d                %s EnLocation : %-4s           %s\n", \
		G_VERT, car.prixJour, G_VERT, car.EnLocation, G_VERT);

	printf(G_DL G_HORZ G_HORZ G_HORZ G_HORZ G_HORZ G_HORZ G_HORZ G_HORZ \
		G_HORZ G_HORZ G_HORZ G_HORZ G_HORZ G_HORZ G_HORZ G_DR ENDL);
}

/*
** ***************************************************************************
** this function reads from the data/file one car information at every call
*/

int		read_one_car_info(FILE *file, voiture *car)
{
	char	line[100];
	int	ret;

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


/*
** ****************************************************************************
*/

void	get_car_input(voiture *car)
{
	printf("please write the information of this car:\n");
	printf("nomVoiture: "); scanf("%s", car->nomVoiture);
	printf("idVoiture:  "); scanf("%d", &(car->idVoiture));
	printf("marque:     "); scanf("%s", car->marque);
	printf("nbplaces:   "); scanf("%d",   &(car->nbplaces));
	printf("couleur:    "); scanf("%s", car->couleur);
	printf("prixJour:   "); scanf("%d", &(car->prixJour));
	strcpy(car->EnLocation, "Non"); 
}

/*
** ****************************************************************************
*/

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
	int	id;
	int	ret;
	int	nbr;
	int	num;
	int	choice;
	voiture car;
	char	str[20];
	FILE	*file = fopen("Voitures", "r");

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
			else if (choice == 6)	strcpy(car.nomVoiture, str);
			else if (choice == 7)
			{
				if ((strcmp(str, "non") == 0) || \
					(strcmp(str, "NON") == 0) || (strcmp(str, "NO") == 0) || \
					(strcmp(str, "no") == 0) || (strcmp(str, "Non") == 0))
					strcpy(car.EnLocation, "Non");
				else
					strcpy(car.EnLocation, "Yes");
			}
			file = fopen("Voitures", "a+");
			ft_add_this_car(car, "Voitures");
			break;
		}
	}
	fclose(file);
}

/*
** ****************************************************************************
*/

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


/*
** ****************************************************************************
*/

void	delete_this_car(voiture car)
{
	FILE	*fileptr1, *fileptr2;
	voiture	temp_car;
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
	voiture	car;

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

/*
** ****************************************************************************
*/
