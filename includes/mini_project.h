#ifndef MINI_PROJECT_H
#define MINI_PROJECT_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

/*
**  in file : main.c
*/
int		print_menu_principal();

/*
**  in file : rental.c
*/
void	ft_rental_management(int cars_fd, int clients_fd, int contracts_fd);

/*
**  in file : clien.c
*/
void	ft_clients_management(int cars_fd, int clients_fd, int contracts_fd);

/*
**  in file : cars.c
*/
void	ft_cars_management(int cars_fd, int clients_fd, int contracts_fd);
#endif
