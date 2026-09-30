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

// Gestion du temps
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#include "fonctions.h"

#define CYCLE_P 23
#define CYCLE_E 28
#define CYCLE_I 33

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void getData(t_date *dateN);

// Programme principal
int main() {
    char    *erreur;
    t_date  dateN;          // date de naissance
    t_date  dateJ;          // date du jour
    int     jours;          // nombre de jours
    float   physique;
    float   emotionnel;
    float   intellectuel;
    time_t  tps;
    struct  tm *x;
    int     i;
    FILE    *data;
    
    tps = time(NULL);
    x = localtime(&tps);
    
    dateJ.jour = x->tm_mday;
    dateJ.mois = x->tm_mon + 1;
    dateJ.an   = x->tm_year + 1900;

    getData(&dateN);

    erreur = "";
    
    // Ouverture du fichier data.js en écriture
    data = fopen("../Biorythme/js/data.js", "w");

    if (dateValide(dateN)) {
        // Calcul du nombre de jours entre les 2 dates
        jours = nbJours(dateN, dateJ);

        // Ecriture dans le fichier data
        if (data != NULL) {
            int j = jours;
            t_date dateCourante = dateJ;
            for (i = 0; i < 33; i++) {
                physique = sin(2 * M_PI * j / CYCLE_P);
                emotionnel = sin(2 * M_PI * j / CYCLE_E);
                intellectuel = sin(2 * M_PI * j / CYCLE_I);

                fprintf(data, "labels[%d]=\"%.2d-%.2d-%4d\";\n", i, dateCourante.jour, dateCourante.mois, dateCourante.an);
                fprintf(data, "data.datasets[0].data[%d]=%f;\n", i, physique);
                fprintf(data, "data.datasets[1].data[%d]=%f;\n", i, emotionnel);
                fprintf(data, "data.datasets[2].data[%d]=%f;\n", i, intellectuel);

                j++;
                addJours(&dateCourante, 1);
            }
        }
    }
    else {
        jours = -1;
        erreur = "<-- Date incorrecte";
    }

    // Fermerture du fichier data
    if (data != NULL) {
        fclose(data);
    }

    // Génération de la page Web
    printf ("\
Content-type: text/html\n\n\
<html>\n\
<head>\n\
    <title>Biorythmes</title>\n\
    <meta http-equiv=\"content-type\" content=\"text/html; charset=utf-8\" />\n\
    <meta name=\"language\" content=\"fr\" />\n\
    <link rel=\"stylesheet\" type=\"text/css\" href=\"../Biorythme/css/style.css\" />\n\
    <link rel=\"shortcut icon\" href=\"../Biorythme/biorythme.ico\" />\n\
    <script src=\"../Biorythme/js/vars.js\"></script>\n\
    <script src=\"../Biorythme/js/displayChart.js\"></script>\n\
    <script src=\"../Biorythme/js/data.js\"></script>\n\
    <script src=\"../Biorythme/js/chart.js\"></script>\n\
</head>\n\
<body>\n\
    <div class=\"ligne\"><div class=\"libelle\">Date de naissance :</div><div class=\"contenu\">%.2d-%.2d-%4d</div>\n\
    <div class=\"erreur\">%s</div></div>\n\
    <div class=\"ligne\"><div class=\"libelle\">Aujourd'hui :</div><div class=\"contenu\">%.2d-%.2d-%4d</div></div>\n\
    <div class=\"ligne\"><div class=\"libelle\">Nombre de jours :</div><div class=\"contenu\">%d</div></div>\n\
    <canvas id=\"myChart\"></canvas>\n\
    <button class=\"boutonLarge\" onclick=\"window.location='http://lainf-sae2-08.univ-lemans.fr/~info/Biorythme/biorythme.php';\">Nouvelle date de naissance</button>\n\
</body>\n\
</html>\n\
", dateN.jour, dateN.mois, dateN.an, erreur, dateJ.jour, dateJ.mois, dateJ.an, jours);
    
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