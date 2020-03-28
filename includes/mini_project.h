#ifndef MINI_PROJECT_H
#define MINI_PROJECT_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>

#define  HORZ	"\e[0;36m\u2501\u2501\u2501\u2501\e[0m"
#define  T_HORZ	"\e[0;36m\u2500\u2500\u2500\u2500\e[0m"
#define  VERT	"\e[0;36m\u2503\e[0m"
#define  UL	"\e[0;36m\u250F\e[0m"
#define  ML	"\e[0;36m\u2520\e[0m"
#define  UR	"\e[0;36m\u2513\e[0m"
#define  MR	"\e[0;36m\u2528\e[0m"
#define  DL	"\e[0;36m\u2517\e[0m"
#define  DR	"\e[0;36m\u251B\e[0m"
#define	 ENDL	   "\n"

#define  G_HORZ	"\e[0;32m\u2501\u2501\u2501\u2501\e[0m"
#define  G_T_HORZ	"\e[0;32m\u2500\u2500\u2500\u2500\e[0m"
#define  G_VERT	"\e[0;32m\u2503\e[0m"
#define  G_UL	"\e[0;32m\u250F\e[0m"
#define  G_ML	"\e[0;32m\u2520\e[0m"
#define  G_UR	"\e[0;32m\u2513\e[0m"
#define  G_MR	"\e[0;32m\u2528\e[0m"
#define  G_DL	"\e[0;32m\u2517\e[0m"
#define  G_DR	"\e[0;32m\u251B\e[0m"

#define CARS_FILE   "./Data/Voitures"
#define CLIENT_FILE "./Data/Clients"
#define CONTRA_FILE "./Data/ContratsLocations"

typedef struct	date
{
	int	year;
	int	mois;
	int	jour;
	int	hh;
}		date;

typedef struct	Voiture
{
	int	nbplaces;
	int	prixJour;
	int	idVoiture;
	char	marque[15];
	char	couleur[7];
	char	nomVoiture[15];
	char	EnLocation[4];
}		voiture;

typedef	struct	contratLocation
{
	date	debut;
	date	fin;
	float	numContrat;
	int	idVoiture;
	int	idClient;
	int	cout;
}				contrat;

typedef	struct	client
{
	int	cin;
	int	idClient;
	int	telephone;
	char	nom[20];
	char	prenom[20];
	char	adresse[15];
}		client;
 
/*
**  in file : main.c
*/
int		print_this_menu(char buff[][50], int size);
char		*ft_read_buffer(char *str, int buff_size);

/*
**  in file : rental.c
*/
void	ft_rental_management(void);

void	ft_visualizer_les_contrat();
int	read_one_contrat(FILE *file, contrat *cntr);// from a file 
void	print_one_contrat(contrat contrat);

void	louer_une_voiture();
void	get_contrat_input(contrat *cntr);
int	verify_this_contrat(contrat cntr);
void	add_this_contrat(contrat cntr, char *filename);

void	retourner_une_voiture();

void	modifier_une_contrat();
void	get_contrat_modification(float *contrat_id, int *choix);

void	sup_une_contrat();
void	del_this_contrat(int idContrat);
//void	del_one_contrat(contrat cntr);

/*
**  in file : clien.c
*/
void	ft_clients_management(void);
void	list_all_clients();
void	add_client();
void	modify_client();
void	del_client();

void	add_this_client(client cl, char *file);
bool	ft_check_client(int id);
int	read_one_client(client *cl, FILE *file);
int	del_this_client(int id);
void	print_one_client(client cl);
void	get_client_info(client *cl);

/*
**  in file : cars.c
*/
void	ft_cars_management(void);
void	ft_list_cars(void);

int	read_one_car_info(FILE *cars, voiture *car);
void	print_one_car(voiture car);

void	ft_add_car(void);
void	get_car_input(voiture *car);
void	ft_add_this_car(voiture car, char *filename);

void	ft_modify_car_info(void);
int	print_modify_menu(int *id, int *choice, int *nbr, char *str);
void	modifier_car_enLocation(int id, char *str);

void	ft_delete_car(void);
void	delete_this_car(voiture car);

#endif
