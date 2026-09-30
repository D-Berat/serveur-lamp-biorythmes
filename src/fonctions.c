//==============================================================
// Programme : fonctions.c
// Role :      Calcul des biorythmes (fonctions)
// Auteur :    Bruno ERNET
//==============================================================

// Fichiers d'ent�te
#include <stdio.h>
#include <string.h>

#include "fonctions.h"

int mois[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

// Fonction d�terminant si une ann�e est bissextile
// elle retourne :
//   1 si bissextile
//   0 si non bissextile
int bissextile(int an) {
	return ((an % 400 == 0) || ((an % 4 == 0) && (an % 100 != 0)));
}

// Proc�dure de saisie et de contr�le de date sous la forme jj mm aaaa
void saisirDate(char *msg, t_date *date) {
	do {
		printf("%s", msg);
		// saisie de la date sous la forme jj mm aaaa
		scanf("%d%d%d", &date->jour, &date->mois, &date->an);
		// v�rification
		if (dateValide(*date))
			break; // c'est correct, on sort de la boucle
		printf("ERREUR de jour ou de mois, recommencez...\n");
	} while (1);
}

// Fonction calculant le num�ro de jour
int numJour(t_date date) {
	int n = date.jour,
	    i;
		
	for (i = 1; i < date.mois; i++) n += mois[i - 1];
	if (date.mois > 2) n += bissextile(date.an);
	
	return n;
}

// Fonction calculant le nombre de jours entre 2 dates
int nbJours(t_date date1, t_date date2) {
    int jours;
    int i;
		
	jours = numJour(date2) - numJour(date1);
	for (i = date1.an; i < date2.an; i++) jours += 365 + bissextile(i);

	return jours;
}

// Fonction contr�lant la validit� de la date
// retour : 1 (OK) - 0 (NOK)
int dateValide(t_date date) {
    return (((date.mois >= 1) && (date.mois <= 12)) &&
            ((date.jour >= 1) && (date.jour <= (mois[date.mois - 1] +
                               ((date.mois == 2) ? bissextile(date.an) : 0))))
           );
}

// Fonction calculant la somme de date + jours
void addJours(t_date *date, int nbJours) {
    int i;
    for (i = 0; i < nbJours; i++) {
        date->jour++;
        
        int maxJours = mois[date->mois - 1];
        if (date->mois == 2 && bissextile(date->an)) {
            maxJours = 29;
        }
        
        if (date->jour > maxJours) {
            date->jour = 1;
            date->mois++;
            if (date->mois > 12) {
                date->mois = 1;
                date->an++;
            }
        }
    }
}