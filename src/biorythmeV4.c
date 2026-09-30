//==============================================================
// Programme : biorythmeV4.c
// Rôle :      Calcul des biorythmes (Version Dynamique Sans Fichier)
// Principe :  Saisit une date de naissance et un nombre de jours
//             Calcule les biorythmes de manière dynamique
// Auteur :    Bruno ERNET / BERAT
//==============================================================

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#include "fonctions.h"

// Constantes définies en flottants pour éviter la division entière
#define CYCLE_P 23.0
#define CYCLE_E 28.0
#define CYCLE_I 33.0

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void getDataV4(t_date *dateN, int *nbJoursGraph);

int main() {
    char    *erreur;
    t_date  dateN;          
    t_date  dateJ;          
    int     jours;          
    int     nbJoursGraph = 33; 
    float   physique;
    float   emotionnel;
    float   intellectuel;
    time_t  tps;
    struct  tm *x;
    int     i;
    
    tps = time(NULL);
    x = localtime(&tps);
    
    dateJ.jour = x->tm_mday;
    dateJ.mois = x->tm_mon + 1;
    dateJ.an   = x->tm_year + 1900;

    getDataV4(&dateN, &nbJoursGraph);

    erreur = "";
    
    printf("Content-type: text/html\n\n");
    printf("<html>\n<head>\n");
    printf("    <title>Biorythmes</title>\n");
    printf("    <meta http-equiv=\"content-type\" content=\"text/html; charset=utf-8\" />\n");
    printf("    <link rel=\"stylesheet\" type=\"text/css\" href=\"../Biorythme/css/style.css\" />\n");
    printf("    <link rel=\"shortcut icon\" href=\"../Biorythme/biorythme.ico\" />\n");
    printf("</head>\n<body>\n");

    if (dateValide(dateN)) {
        jours = nbJours(dateN, dateJ);
    } else {
        jours = -1;
        erreur = "<-- Date incorrecte";
    }

    printf("    <div class=\"ligne\"><div class=\"libelle\">Date de naissance :</div><div class=\"contenu\">%.2d-%.2d-%4d</div><div class=\"erreur\">%s</div></div>\n", dateN.jour, dateN.mois, dateN.an, erreur);
    printf("    <div class=\"ligne\"><div class=\"libelle\">Aujourd'hui :</div><div class=\"contenu\">%.2d-%.2d-%4d</div></div>\n", dateJ.jour, dateJ.mois, dateJ.an);
    printf("    <div class=\"ligne\"><div class=\"libelle\">Nombre de jours vécus :</div><div class=\"contenu\">%d</div></div>\n", jours);
    
    printf("    <div style=\"width: 95%%; max-width: 1400px; margin: 20px auto; height: 60vh;\">\n");
    printf("        <canvas id=\"myChart\"></canvas>\n");
    printf("    </div>\n");
    
    printf("    <button class=\"boutonLarge\" onclick=\"window.location='http://lainf-sae2-08.univ-lemans.fr/~info/Biorythme/biorythme.php';\">Nouvelle date de naissance</button>\n");
    
    printf("    <script src=\"https://cdn.jsdelivr.net/npm/chart.js\"></script>\n");
    printf("    <script>\n");
    printf("        var txtLabels = [];\n");
    printf("        var dataP = [];\n");
    printf("        var dataE = [];\n");
    printf("        var dataI = [];\n");

    if (jours != -1) {
        int j = jours;
        t_date dateCourante = dateJ;
        for (i = 0; i < nbJoursGraph; i++) {
            // Calculs basés sur des doubles
            physique = sin(2 * M_PI * (double)j / CYCLE_P);
            emotionnel = sin(2 * M_PI * (double)j / CYCLE_E);
            intellectuel = sin(2 * M_PI * (double)j / CYCLE_I);

            printf("        txtLabels.push(\"%.2d-%.2d-%4d\");\n", dateCourante.jour, dateCourante.mois, dateCourante.an);
            printf("        dataP.push(%f);\n", physique);
            printf("        dataE.push(%f);\n", emotionnel);
            printf("        dataI.push(%f);\n", intellectuel);

            j++;
            addJours(&dateCourante, 1);
        }
    }

    printf("        var ctx = document.getElementById('myChart').getContext('2d');\n");
    printf("        new Chart(ctx, {\n");
    printf("            type: 'line',\n");
    printf("            data: {\n");
    printf("                labels: txtLabels,\n");
    printf("                datasets: [\n");
    printf("                    { label: 'Physique', borderColor: 'rgba(255, 99, 132, 1)', data: dataP, borderWidth: 2, fill: false, tension: 0.1 },\n");
    printf("                    { label: 'Emotionnel', borderColor: 'rgba(54, 162, 235, 1)', data: dataE, borderWidth: 2, fill: false, tension: 0.1 },\n");
    printf("                    { label: 'Intellectuel', borderColor: 'rgba(75, 192, 192, 1)', data: dataI, borderWidth: 2, fill: false, tension: 0.1 }\n");
    printf("                ]\n");
    printf("            },\n");
    printf("            options: {\n");
    printf("                responsive: true,\n");
    printf("                maintainAspectRatio: false,\n");
    printf("                scales: { y: { min: -1.1, max: 1.1 } }\n");
    printf("            }\n");
    printf("        });\n");
    printf("    </script>\n");
    printf("</body>\n</html>\n");
    
    return 0;
}

void getDataV4(t_date *dateN, int *nbJoursGraph) {
    char *chaine = getenv("QUERY_STRING");
    if (chaine != NULL) {
        char *pJour  = strstr(chaine, "jour=");
        char *pMois  = strstr(chaine, "mois=");
        char *pAn    = strstr(chaine, "an=");
        char *pJours = strstr(chaine, "nbJours=");

        if (pJour)  sscanf(pJour, "jour=%d", &dateN->jour);
        if (pMois)  sscanf(pMois, "mois=%d", &dateN->mois);
        if (pAn)    sscanf(pAn, "an=%d", &dateN->an);
        if (pJours) sscanf(pJours, "nbJours=%d", nbJoursGraph);
    }
}