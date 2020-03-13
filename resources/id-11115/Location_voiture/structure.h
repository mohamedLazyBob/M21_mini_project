
typedef struct matriculVoiture
{
	int matricule;
	char type[5];
	int kilometrage;
	char stats;
} matriculVoiture;

typedef struct Matricul
{
	matriculVoiture mat;
	struct Matricul *suivant;
} Matricul;

typedef struct Matricul *listeMatricul;


typedef struct voiture
{
	char marque[15];
	char nom[15];
	int cylindree;
	int puissance;
	char moteur;
	char couleur[7];
	char clim;
	char interieur;
	char sono;
	char identit[5];
	char abs;
	char dirAssis;
	int prixKilo;
	int prixJour;
	char vitElec[2];
	int nbplace;

} voiture;


typedef struct contrat 
{
	float num;
	char nom[20];
	char pnom[20];
	int debu;
	int fin;
	char type[2];
	int cout; 
	int assurance;
	char agencDepar[15];
	char agencRetour[15];
	int voit_loue;
	char supcond;
	char liv;
	char bebe;
} contrat;




typedef struct client
{
	int age;
	float num;
	char rue[15];
	int cpostal;
	char ville[15];
	int cin;
	int date_permi;
	char nom[20];
	int telephone;
	char travail[15];
	float ctr;
	char prenom[20];
}client;
 
 

typedef struct cellule
{
	voiture voit;
	struct cellule *suivant;
} cellule,*liste;


typedef struct cellule_client
{
	client person;
	struct cellule_client *suivant;
	struct cellule_client *precedent;
} cellule_client, *liste_client;


typedef struct CelluleContrat
{
	contrat cont;
	struct CelluleContrat *suivant;
}CelluleContrat, *ListeContrat;





typedef struct date
{
	int jj;
	int mm;
	int aa;
} date;