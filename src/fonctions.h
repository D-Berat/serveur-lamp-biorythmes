//==============================================================
// Programme : fonctions.h
// Role :      Calcul des biorythmes (fonctions)
// Auteur :    Bruno ERNET
//==============================================================

typedef struct {
    int jour;
    int mois;
    int an;
} t_date;

// Fonction déterminant si une année est bissextile
// elle retourne :
//   1 si bissextile
//   0 si non bissextile
int bissextile(int an);

// Procédure de saisie et de contrôle de date sous la forme jj mm aaaa
void saisirDate(char *msg, t_date *date);

// Fonction calculant le numéro de jour
int numJour(t_date date);

// Fonction calculant le nombre de jours entre 2 dates
int nbJours(t_date date1, t_date date2);

// Fonction contrôlant la validité de la date
// retour : 1 (OK) - 0 (NOK)
int dateValide(t_date date);

// Fonction calculant la somme de date + jours
void addJours(t_date *date, int nbJours);
