void A_Propos();

void AfficheClient(client cl);

void AfficheContrat(contrat crt);

void AfficheType(voiture voit);

void AfficheVoiture(matriculVoiture mt);

cellule_client* chargementClient(char *nom);

ListeContrat chargementContrat(char *nom);

listeMatricul ChargementMatricul(char *nom);

liste chargementType(char *nom);

int ConditionLocation(client cl);

date convertDate();

int dateDiff(int fin);

void EnTete();

float generationCode();

liste inserer_en_fin(liste l,cellule *elt);

liste_client InsererEnFinClient(liste_client l,client cl);

liste_client insererClient(liste_client l, cellule_client *inser);

listeMatricul insererVoiture(listeMatricul l,Matricul *m);

int ListeMatriculVide(listeMatricul l);

int ListeVide(liste l);

int MenuGestionClient();

int MenuGestionVoiture();

int MenuLocation();

int MenuPrincipal();

void MessageUrgence(char *msg);

liste_client modifierClient(liste_client l);

ListeContrat ModifierContrat(ListeContrat l,listeMatricul m);

liste ModifierTypeVoiture(liste l);

void msgSauvCharg(char *msg);

listeMatricul rechecherMatricul(listeMatricul,int m);

liste_client RechercheClient(liste_client l,char *nom,char *pnom);

ListeContrat RechercheContrat(ListeContrat l);

liste RechercheTypeVoiture(liste l,char rech[]);

listeMatricul RechercheVoitureLibre(listeMatricul lm, char *typ);

void RetourContrat(ListeContrat lcr,listeMatricul lm,liste l);

cellule_client* RetourTete(cellule_client *t);

cellule_client* SaisieClient();

ListeContrat saisieContrat(cellule_client *person,listeMatricul l);

listeMatricul saisieMatricul(listeMatricul l1,liste l);

liste SaisieTypeVoiture(liste l);

void sauvgarde(liste l,char nom[]);

void sauvgardeClient(liste_client l,char *nom);

void SauvgardeContrat(ListeContrat l,char *nom);

void SauvgardeGeneral(int verif,liste stock_voiture,liste_client lesclients,ListeContrat lescontrat,listeMatricul stock_matricul);

void SauvgardeMatricule(listeMatricul l,char *nom);

void Statistique(liste typ,liste_client clt,listeMatricul mat,ListeContrat crt);

liste_client supprimerClient(liste_client l);

ListeContrat SupprimerContrat(ListeContrat l,CelluleContrat *supp);

listeMatricul supprimerMatricul(listeMatricul l);

liste SupprimerPosition(liste l,cellule *supp);

liste SupprimerVoiture(liste l);
