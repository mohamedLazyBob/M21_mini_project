#ifndef MINI_PROJECT_H
#define MINI_PROJECT_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>


typedef struct	date
{
	int	hh;
	int mm;
	int	ss;
}				date;

typedef struct	Voiture
{
	int		nbplaces;
	int		prixJour;
	int		idVoiture;
	char	marque[15];
	char	couleur[7];
	char	nomVoiture[15];
	char	EnLocation[4];
}				voiture;

typedef	struct	contratLocation
{
	float	numContrat;
	int		idVoiture;
	int		idClient;
	int		cout;
	date	debut;
	date	fin;
}				contrat;

typedef	struct	client
{
	char	nom[20];
	char	prenom[20];
	char	adresse[15];
	int		cin;
	int		idClient;
	int		telephone;
}				client;
 
/*
**  in file : main.c
*/
int		print_menu_principal();

/*
**  in file : rental.c
*/
void	ft_rental_management(void);

/*
**  in file : clien.c
*/
void	ft_clients_management(void);

/*
**  in file : cars.c
*/
void	ft_cars_management(void);
int		print_cars_menu(void);
void	ft_list_cars();
int		read_one_car_info(FILE *cars, voiture *car);
void	ft_add_car(void);
void	ft_add_this_car(voiture car, char *filename);
void	get_car_input(voiture *car);
void	ft_modify_car_info(void);
int		print_modify_menu(int *id, int *choice, int *nbr, char *str);
void	ft_delete_car(void);
void	delete_this_car(voiture car);
#endif
