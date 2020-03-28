/******************************************************************************/
/*                              Mohamed zaboub                                */
/******************************************************************************/

#include "mini_project.h"

/*
** ****************************************************************************
** the main function for cars menu.
*/

void	ft_cars_management(void)
{
	int	choice;
	char	str[100];

	char buff[6][50] = {"    Gestion des voiture   ", 
		"List des voitures.....................1", 
		"Ajouter voiture.......................2", 
		"Modifier voiture......................3", 
		"supprimer voiture.....................4", 
		"retour................................5"};
	while (1)
	{
		system("clear");
		choice = print_this_menu(buff, 6);
		if (choice == 1)	ft_list_cars();
		else if (choice == 2)	ft_add_car();
		else if(choice == 3)	ft_modify_car_info();
		else if(choice == 4)	ft_delete_car();
		else if(choice == 5)	break ;
		printf("saisir un chiffre pour revenir au menu precedent : ");
		scanf("%s", str);// this just a trick to free the input buffer
	}
}

/*
** ****************************************************************************
** this function lists all available cars in the file.
*/

void	ft_list_cars(void)
{
	int	ret;
	voiture	car;
	FILE	*file;

	if (!(file = fopen(CARS_FILE, "r")))
	{
		printf("ERROR couldn't open Voitures file\n");
		return ;
	}
	system("clear");
	while ((ret = read_one_car_info(file, &car)) != EOF)
		print_one_car(car);
	fclose(file);
}

/*
** ****************************************************************************
** printfs the menu and get the input of the new car from the user.
** saves those information to the file.
*/

void	get_car_input(voiture *car)
{
	char temp[10];

	printf("Saisir les informations de la nouvelle voiture:\n");
	printf("\tnomVoiture  : ");
	ft_read_buffer(car->nomVoiture, 15);
	printf("\tidVoiture   : ");
	ft_read_buffer(temp, 10);
	car->idVoiture = atoi(temp);
	printf("\tmarque      : ");
	ft_read_buffer(car->marque, 15);
	printf("\tnbplaces    : ");
	ft_read_buffer(temp, 10);
	car->nbplaces = atoi(temp);
	printf("\tcouleur     : ");
	ft_read_buffer(car->couleur, 7);
	printf("\tprixJour    : ");
	ft_read_buffer(temp, 10);
	car->prixJour = atoi(temp);
	strcpy(car->EnLocation, "Non"); 
}

void	ft_add_car(void)
{
	voiture car;

	get_car_input(&car);
	if (false == check_dup_car(car.idVoiture))
		ft_add_this_car(car, CARS_FILE);
	else
		printf("Id is not valid: duplicated id!\n");
}

/*
** ***************************************************************************
**  return true if the car exists in the file, and false otherwise.
*/

bool	check_dup_car(int id)
{
	int	ret;
	voiture	car;
	FILE	*file;

	if (!(file = fopen(CARS_FILE, "r")))
		return (false);
	while ((ret = read_one_car_info(file, &car)) != EOF)
		if (car.idVoiture == id)
		{
			fclose(file);
			return (true);
		}
	fclose(file);
	return (false);
}

/*
** ****************************************************************************
** asks the user for what he wants to edit, and edit that 
*/

void	ft_modify_car_info(void)
{
	char	input_str[20];
	int	input_nbr;
	int	choice;
	FILE	*file;
	int	num;
	voiture car;
	int	ret;
	int	id;

	if (!(file = fopen(CARS_FILE, "r")))
	{
		printf("Voitures file Doesn't exist.\n");
		return ;
	}
	print_modify_menu(&id, &choice, &input_nbr, input_str);
	while ((ret = read_one_car_info(file, &car)) != EOF)
	{
		if (car.idVoiture == id)
		{
			fclose(file);
			delete_this_car(car);
			if(choice == 1)
				car.nbplaces = input_nbr;
			else if (choice == 2)
				car.prixJour = input_nbr;
			else if (choice == 3)
				car.idVoiture = input_nbr;
			else if (choice == 4)
				strncpy(car.marque, input_str, 15);
			else if (choice == 5) 
				strncpy(car.couleur, input_str, 7);
			else if (choice == 6)
				strncpy(car.nomVoiture, input_str, 15);
			else if (choice == 7)
			{
				if ((strcmp(input_str, "non") == 0) || \
					(strcmp(input_str, "NON") == 0) || \
					(strcmp(input_str, "NO") == 0) || \
					(strcmp(input_str, "no") == 0) || \
					(strcmp(input_str, "Non") == 0))
					strcpy(car.EnLocation, "Non");
				else
					strcpy(car.EnLocation, "Oui");
			}
			file = fopen(CARS_FILE, "a+");
			ft_add_this_car(car, CARS_FILE);
			break;
		}
	}
	fclose(file);
}

/*
** ****************************************************************************
** prints the menu of new changes, and gets the input from the user
*/

int	print_modify_menu(int *id, int *choice, int *nbr, char *str)
{
	write (1, "\033[0;31m>> Modifier une voiture.\033[0m\n", 40);
	printf("L'id de la voiture que vous souhaitez modifier : ");
	scanf("%d", id);
	while (1)
	{
		printf("Que voulez-vous modifier?\n");
		printf("\t1 -- Nbplaces.\n");
		printf("\t2 -- PrixJour.\n");
		printf("\t3 -- IdVoiture.\n");
		printf("\t4 -- Marque.\n");
		printf("\t5 -- Couleur.\n");
		printf("\t6 -- NomVoiture.\n");
		printf("\t7 -- EnLocation.\n");
		printf("Votre choix :  ");
		scanf("%d", choice);
		if (*choice > 0 && *choice < 4)
		{
			printf("Saisir la modification: ");
			scanf("%d", nbr);
			return (0);
		}
		else if (*choice > 3 && *choice < 8)
		{
			printf("Saisir la modification : ");
			ft_read_buffer(str, 20);
			return (1);
		}
	}
}

/*
** ****************************************************************************
** asks the user for the car he wanna delete, and delte it
*/

void	ft_delete_car(void)
{
	FILE	*file;
	voiture car;
	int	ret;
	int	id;

	if (!(file = fopen(CARS_FILE, "r")))
	{
		printf("ERROR: Voiture file Doesn't exist.\n");
		return ;
	}
	printf("Donner l'id de la voiture tu veut supprimer : ");
	scanf("%d", &id);
	while ((ret = read_one_car_info(file, &car)) != EOF)
	{
		if (car.idVoiture == id)
		{
			fclose(file);
			ret = delete_this_car(car);
			if (ret == 1)
				printf("The car has been successfully deleted.\n");
			else
				printf("Could't find the car, id non valid.\n");
			return ;
		}
	}
	fclose(file);
	return ;
}


/*
** ****************************************************************************
** ****************************************************************************
**  all of those function does what their name says they do, for one only car.
*/

int	delete_this_car(voiture car)
{
	FILE	*fileptr1;
	FILE	*fileptr2;
	voiture	temp_car;
	int	end;
	int	ret = -1;

	if (!(fileptr1 = fopen(CARS_FILE, "r")))
	{
		printf("ERROR: Voiture file Doesn't exist.\n");
		return (ret);
	}
	fileptr2 = fopen("replica.txt", "w");
	fclose(fileptr2);
	while (1)
	{
		end = read_one_car_info(fileptr1, &temp_car);
		if (end == EOF)
			break;
		if (temp_car.idVoiture != car.idVoiture)
			ft_add_this_car(temp_car, "replica.txt");
		else
			ret = 1;
	}
	fclose(fileptr1);
	remove(CARS_FILE);
	rename("replica.txt", CARS_FILE);
	return (ret);
}

/*
** ----------------------------------------------------------------------------
** adds one car information to the file where we stock data.
*/

void	ft_add_this_car(voiture car, char *filename)
{
	FILE *ptr;

	if (!(ptr = fopen(filename, "a+")))
	{
		ptr = fopen(filename, "w");
		fclose(ptr);
		ptr = fopen(filename, "a+");
	}
	fprintf(ptr, "<car>\n");
	fprintf(ptr, "\t<nomVoiture> %s </nomVoiture>\n", car.nomVoiture);
	fprintf(ptr, "\t<idVoiture> %d </idVoiture>\n",  car.idVoiture);
	fprintf(ptr, "\t<nbplaces> %d </nbplaces>\n",   car.nbplaces);
	fprintf(ptr, "\t<prixJour> %d </prixJour>\n",   car.prixJour);
	fprintf(ptr, "\t<marque> %s </marque>\n",     car.marque);
	fprintf(ptr, "\t<couleur> %s </couleur>\n",    car.couleur);
	fprintf(ptr, "\t<enLocation> %s </enLocation>\n", car.EnLocation);
	fprintf(ptr, "</car>\n");
	fclose(ptr);
}

/*
** ----------------------------------------------------------------------------
** this function reads from the data/file one car information at every call
*/

int		read_one_car_info(FILE *file, voiture *car)
{
	char	line[10];
	int	ret;

	fscanf(file, "%s\n", line);

	fscanf(file, "<nomVoiture> %[^<]s", car->nomVoiture);
	fscanf(file, "</nomVoiture>\n");
	car->nomVoiture[strlen(car->nomVoiture) - 1] = 0;

	fscanf(file, "<idVoiture> %d </idVoiture>\n",  &(car->idVoiture));
	fscanf(file, "<nbplaces> %d </nbplaces>\n",   &(car->nbplaces));
	fscanf(file, "<prixJour> %d </prixJour>\n",   &(car->prixJour));

	fscanf(file, "<marque> %[^<]s",     car->marque);
	fscanf(file, "</marque>\n");
	car->marque[strlen(car->marque) - 1] = 0;

	fscanf(file, "<couleur> %[^<]s",    car->couleur);
	fscanf(file, "</couleur>\n");
	car->couleur[strlen(car->couleur) - 1] = 0;

	fscanf(file, "<enLocation> %[^<]s", car->EnLocation);
	fscanf(file, "</enLocation>\n");
	car->EnLocation[strlen(car->EnLocation) - 1] = 0;

	ret = fscanf(file, "%s\n", line);
	return (ret);
}

/*
** ----------------------------------------------------------------------------
** this prints one car information in a user friendly manner 
*/

void	print_one_car(voiture car)
{
	printf(G_UL G_HORZ G_HORZ G_HORZ G_HORZ G_HORZ G_HORZ G_HORZ G_HORZ \
		G_HORZ G_HORZ G_HORZ G_HORZ G_HORZ G_HORZ G_HORZ G_UR ENDL);
	printf("%s                        idVoiture: %.3d                      %s\n", \
		G_VERT, car.idVoiture, G_VERT);

	printf(G_ML G_T_HORZ G_T_HORZ G_T_HORZ G_T_HORZ G_T_HORZ G_T_HORZ \
		G_T_HORZ G_T_HORZ G_T_HORZ G_T_HORZ G_T_HORZ G_T_HORZ \
		G_T_HORZ G_T_HORZ G_T_HORZ G_MR ENDL);

	printf("%s nomVoiture: %-15.15s  %s marque    : %-15.15s %s\n", \
		G_VERT, car.nomVoiture, G_VERT, car.marque, G_VERT);
	printf("%s nbplaces: %-16.2d   %s couleur : %-7.7s           %s\n", \
		G_VERT, car.nbplaces, G_VERT, car.couleur, G_VERT);
	printf("%s prixJour: %-17.3d  %s EnLocation : %-4.3s           %s\n", \
		G_VERT, car.prixJour, G_VERT, car.EnLocation, G_VERT);

	printf(G_DL G_HORZ G_HORZ G_HORZ G_HORZ G_HORZ G_HORZ G_HORZ G_HORZ \
		G_HORZ G_HORZ G_HORZ G_HORZ G_HORZ G_HORZ G_HORZ G_DR ENDL);
}

/*
** ----------------------------------------------------------------------------
** modifys the velue of enLocation string in the file (Oui or Non).
*/

void	modifier_car_enLocation(int id, char *str)
{
	FILE	*file;
	voiture	car;

	if (!(file = fopen(CARS_FILE, "r")))
	{
		printf("ERROR: Voiture file Doesn't exist.\n");
		return ;
	}
	while (read_one_car_info(file, &car) != EOF)
	{
		if (car.idVoiture == id)
		{
			fclose(file);
			delete_this_car(car);
			strcpy(car.EnLocation, str);
			ft_add_this_car(car, CARS_FILE);
			return ;
		}
	}
	fclose(file);
}

/*
** ****************************************************************************
*/
