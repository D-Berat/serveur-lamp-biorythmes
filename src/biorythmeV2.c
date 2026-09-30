//==============================================================
// Programme : biorythme.c
// Rôle :      Calcul des biorythmes
// Principe :  Saisit une date de naissance
//             Saisit la date du jour
//             Calcule les biorythmes selon 3 CYCLEs :
//               - physique     : 23
//               - émotionnel   : 28
//               - intellectuel : 33
// Auteur :    Bruno ERNET
//==============================================================

// Fichiers d'entête
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "fonctions.h"

#define CYCLE_P 23
#define CYCLE_E 28
#define CYCLE_I 33

void getData(t_date *dateN);

// Programme principal
int main() {
    t_date  dateN;          // date de naissance
    t_date  dateJ;          // date du jour
    int     totalJours;     // nombre de jours vécus
    
    getData(&dateN);

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    dateJ.jour = tm.tm_mday;
    dateJ.mois = tm.tm_mon + 1;
    dateJ.an = tm.tm_year + 1900;

    totalJours = nbJours(dateN, dateJ);

    printf ("\
Content-type: text/html\n\n\
<html>\n\
<head>\n\
    <title>Biorythmes</title>\n\
    <meta http-equiv=\"content-type\" content=\"text/html; charset=utf-8\" />\n\
    <meta name=\"language\" content=\"fr\" />\n\
</head>\n\
<body>\n\
    <div class=\"ligne\"><div class=\"libelle\">Date de naissance :</div><div class=\"contenu\">%.2d-%.2d-%4d</div></div>\n\
    <div class=\"ligne\"><div class=\"libelle\">Date du jour :</div><div class=\"contenu\">%.2d-%.2d-%4d</div></div>\n\
    <div class=\"ligne\"><div class=\"libelle\">Nombre de jours vécus :</div><div class=\"contenu\">%d</div></div>\n\
</body>\n\
</html>\n\
", dateN.jour, dateN.mois, dateN.an, dateJ.jour, dateJ.mois, dateJ.an, totalJours);
    
    return 0;
}

void getData(t_date *dateN) {
    char *chaine = getenv("QUERY_STRING");
    if (chaine != NULL) {
        char *pJour = strstr(chaine, "jour=");
        char *pMois = strstr(chaine, "mois=");
        char *pAn   = strstr(chaine, "an=");

        if (pJour) sscanf(pJour, "jour=%d", &dateN->jour);
        if (pMois) sscanf(pMois, "mois=%d", &dateN->mois);
        if (pAn)   sscanf(pAn, "an=%d", &dateN->an);
    }
}