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

	while (1)
	{
		choice = print_clients_menu();
		if (choice == 1)		list_all_clients();
		else if (choice == 2)	add_client();
		else if (choice == 3)	modify_client();
		else if (choice == 4)	del_client();
		else if (choice == 5)	break ;
	}
}


void	list_all_clients()
{
	client	cl;
	FILE	*fileptr = fopen("Clients", "r");

	if (fileptr == NULL)
		return ;
	while (read_one_client(&cl, fileptr) != EOF)
		print_one_client(cl);
	fclose(fileptr);
}

/*
**	**************************************************************************
*/

void	add_client()
{
	client	cl;

	get_client_info(&cl);
	add_this_client(cl, "Clients");
}

void	get_client_info(client *cl)
{
	printf("please write the information of the new client : \n");
	printf("idClient   : ");	scanf("%d", &cl->idClient);
	printf("nom        : ");	scanf("%s", cl->nom);
	printf("prenom     : ");	scanf("%s", cl->prenom);
	printf("cin        : ");	scanf("%d", &cl->cin);
	printf("adresse    : ");	scanf("%s", cl->adresse);
	printf("Telephone  : ");	scanf("%d", &cl->telephone);
}
/*
**	**************************************************************************
*/

void	modify_client()
{
	int		id;
	int		choix;
	int		ret;
	FILE	*file = fopen("Clients", "r");
	client	cl;

	printf("Donner l'id du client : ");	scanf("%d", &id);

	printf("saisir la modification : ");
	printf("\tque voulez-vous modifier?\n");
	printf("\nnom................1\n");
	printf("\tprenom.............2\n");
	printf("\tcin................3\n");
	printf("\tadresse............4\n");
	printf("\ttelephone..........5\n");
	printf("\t\tvotre choix :  ");	scanf("%d", &choix);

	while (1)
	{
		ret = read_one_client(&cl, file);
		if (ret == EOF)
		{
			fclose(file);
			return;
		}
		if (cl.idClient == id)
		{
			fclose(file);
			if (choix >= 1 && choix <= 5)
			{
				del_this_client(cl);
				
				printf("saisir la modification : ");
				if (choix == 1)			scanf("%s", cl.nom);
				else if (choix == 2)	scanf("%s", cl.prenom);
				else if (choix == 3)	scanf("%d", &cl.cin);
				else if (choix == 4)	scanf("%s", cl.adresse);
				else if (choix == 5)	scanf("%d", &cl.telephone);

				add_this_client(cl, "Clients");
			}
			else
				printf("choix invalid.\n");
			return ;
		}
	}
	fclose(file);
}

/*
**	**************************************************************************
*/

void	del_client()
{
	

}

/*
**	**************************************************************************
**	**************************************************************************
*/

void	add_this_client(client cl, char *filename)
{
	FILE	*file = fopen(filename, "a+");

	fprintf(file, "<<\n");	
	fprintf(file, "%d\n", cl.idClient);	
	fprintf(file, "%s\n", cl.nom);	
	fprintf(file, "%s\n", cl.prenom);	
	fprintf(file, "%d\n", cl.cin);	
	fprintf(file, "%s\n", cl.adresse);	
	fprintf(file, "%d\n", cl.telephone);	
	fprintf(file, "/>>\n");	
	fclose(file);
}

int	read_one_client(client *cl, FILE *file)
{
	int ret;
	char line[10];

	ret = fscanf(file, "%s\n", line);
	if (ret == EOF)	return (ret);
	ret = fscanf(file, "%d\n", &cl->idClient);
	if (ret == EOF)	return (ret);
	ret = fscanf(file, "%s\n", cl->nom);
	if (ret == EOF)	return (ret);
	ret = fscanf(file, "%s\n", cl->prenom);
	if (ret == EOF)	return (ret);
	ret = fscanf(file, "%d\n", &cl->cin);
	if (ret == EOF)	return (ret);
	ret = fscanf(file, "%s\n", cl->adresse);
	if (ret == EOF)	return (ret);
	ret = fscanf(file, "%d\n", &cl->telephone);
	if (ret == EOF)	return (ret);
	ret = fscanf(file, "%s\n", line);
	return (ret);
}

void	del_this_client(client cl)
{
	FILE	*ptr1, *ptr2;
	client	temp_client;
	int tmp;

	ptr1 = fopen("Clients", "r");
	ptr2 = fopen("clients_replica.txt", "w");
	fclose(ptr2);

	while (1)
	{
		tmp = read_one_client(&temp_client, ptr1);
		if (tmp == EOF)
			break;
		if (temp_client.idClient != cl.idClient)
			add_this_client(temp_client, "clients_replica.txt");
	}
	fclose(ptr1);
	remove("Clients");
	rename("clients_replica.txt", "Clients");
}

void	print_one_client(client cl)
{
	printf("____________________________________\n");
	printf("\tidClient  : %d\n", cl.idClient);
	printf("\tnom       : %s\n", cl.nom);
	printf("\tprenom    : %s\n", cl.prenom);
	printf("\tcin       : %d\n", cl.cin);
	printf("\tadresse   : %s\n", cl.adresse);
	printf("\ttelephone : %12.12d\n", cl.telephone);
	printf("____________________________________\n");

}
