#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 7

int maxTab2D(int tab[][N], int l) {

    int firstLoop = 1;
    int max;

    for (int i = 0; i < l; ++i) {
        for (int j = 0; j < N; ++j) {
            if (firstLoop) {
                max = tab[i][j];
                firstLoop = 0;
            } else if (max < tab[i][j]) {
                max = tab[i][j];
            }
        }
    }
    return max;
}

void afficheMenu(char *prenom) {

    printf("\nBienvenue, %s\n", prenom);
/*
    char inutile;
    scanf("%c%c", &inutile, &inutile);
*/

    printf("1. Afficher le tableau des resultats\n");
    printf("2. Modifier un resultat\n");
    printf("3. Calculer le nombre de points d'une equipe\n");
    printf("4. Afficher les scores\n");
    printf("5. Savoir quelle equipe a le plus de points\n");
    printf("6. Savoir quelle equipe a le plus de victoires a domicile\n");
    printf("7. Savoir quelle equipe a le plus de victoires a l'exterieur\n");
    printf("0. Quitter\n\n");
}

void afficheTab(int tab[N][N]) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            printf("[%d] ", tab[i][j]);
        }
        printf("\n");
    }
}

int nbPoints(int tab[N][N], int teamNb) {
    if (teamNb > N - 1) {
        printf(".........nbPoints invalide........");
        return -1;
    }
    int score = 0;

    for (int i = 0; i < N; ++i) { //team #teamNb plays abroad
        if (i != teamNb) {
            if (tab[i][teamNb] == 2) {
                score = score + 3;
            } else if (tab[i][teamNb] == 0) {
                ++score;
            }
        }
    }

    for (int j = 0; j < N; ++j) { //team #teamNb plays home
        if (j != teamNb) {
            if (tab[teamNb][j] == 1) {
                score = score + 3;
            } else if (tab[teamNb][j] == 0) {
                ++score;
            }
        }
    }
    return score;
}

void afficheScores(int tab[N][N]) {
    for (int i = 0; i < N; ++i) {
        printf("equipe %d -- score : %d\n", i, nbPoints(tab, i));
    }
}

void modifCase(int tab[N][N]) {

    char iChar[2] = {0};
    printf("Quel est le numero de l'equipe jouant a domicile?\n(entre 0 et %d)\n", N - 1);
    fgets(iChar, 10, stdin);
    int i = strtol(iChar, NULL, 10);

    char jChar[2] = {0};
    printf("Quel est le numero de l'equipe jouant a l'exterieur?\n(entre 0 et %d)\n", N - 1);
    fgets(jChar, 10, stdin);
    int j = strtol(jChar, NULL, 10);

    char scoreChar[2] = {0};
    printf("Quel est le nouveau resultat?\n(0: match nul, 1: equipe domicile gagnante, 2: equipe exterieur gagnante)\n");
    fgets(scoreChar, 10, stdin);
    int score = strtol(scoreChar, NULL, 10);

    if ((i != j)
        && ((score >= 0) || (score <= 2))
        && ((i >= 0) && (i < N))
        && ((j >= 0) && (j < N))) {
        printf("_________changing tab[%d][%d] from %d to %d\n", i, j, tab[i][j], score);
        tab[i][j] = score;
        afficheScores(tab);
    } else {
        printf("........woops in modifCase.........");
    }
}

int equipeLeader(int tab[N][N]) {
    int leadTeam = -1;
    int maxScore = -1;

    for (int i = 0; i < N; ++i) {
        int points = nbPoints(tab, i);
        if (maxScore <= points) {
            maxScore = points;
            leadTeam = i;
        }
    }
    return leadTeam;
}

int nbVictoires(int tab[N][N], int numEquipe, char domOuExt) {
    int nb = 0;
    if (domOuExt == 'd') {
        //domicile
        for (int i = 0; i < N; ++i) {
            if (tab[numEquipe][i] == 1) {
                ++nb;
            }
        }
    } else if (domOuExt == 'e') {
        //exterieur
        for (int i = 0; i < N; ++i) {
            if (tab[i][numEquipe] == 2) {
                ++nb;
            }
        }
    }
    return nb;
}

int meilleureEquipe(int tab[N][N], char c) {
    int leadTeam = -1;
    int maxScore = -1;

    for (int i = 0; i < N; ++i) {
        int victories = nbVictoires(tab, i, c);
        if (maxScore <= victories) {
            maxScore = victories;
            leadTeam = i;
        }
    }
    return leadTeam;
}

int meilleureEquipeDomicile(int tab[N][N]) {
    return meilleureEquipe(tab, 'd');
}

int meilleureEquipeExterieur(int tab[N][N]) {
    return meilleureEquipe(tab, 'e');
}

int main(int argc, char *argv[]) {

    int i;
    int somme = 0;
    printf("Valeur de argc: %d\n", argc);
    for (i = 0; i < argc; i++) {
        printf("Argu. # %d: %s (nb de chars: %d)\n", i, argv[i], (int) strlen(argv[i]));
        if (i >= 1) {
            somme = somme + atoi(argv[i]);
        }
    }
    printf("somme: %d\n", somme);
    int tab1[][N] = {
            {3,   8,   65,  45, 12},
            {12,  63,  456, 32, 189},
            {189, 89,  123, 67, 15},
            {45,  489, 234, 16, 34}
    };

    int tab2[][N] = {
            {3,   8,   65,  45, 12},
            {12,  63,  456, 32, 189},
            {189, 89,  123, 67, 15},
            {45,  389, 234, 16, 34}
    };

    int tab3[][N] = {
            {3,   8,  65,  45, 12},
            {12,  63, 56,  32, 188},
            {189, 89, 123, 67, 15},
            {45,  89, 234, 16, 34}
    };

    printf("max1: %d\n", maxTab2D(tab1, 4)); // should return 489
    printf("max2: %d\n", maxTab2D(tab2, 4)); // should return 456
    printf("max3: %d\n\n", maxTab2D(tab3, 4)); // should return 234

    ///////////////////////////////////////////////////////////////////

    int resultats[N][N] = {{0, 1, 1, 2, 0, 1, 0},
                           {2, 0, 1, 1, 1, 2, 1},
                           {1, 1, 0, 2, 2, 2, 2},
                           {2, 0, 1, 0, 2, 1, 0},
                           {0, 1, 2, 0, 0, 1, 2},
                           {2, 1, 0, 0, 0, 0, 2},
                           {2, 0, 1, 2, 1, 1, 0}};
    //si l'on n'initialise pas le tableau complètement...
    //...on a des zéros dans les cases non-initialisées

    char nom[20];
    printf("Bienvenue, quel est votre nom ? ");
    fgets(nom, 20, stdin);

    char teamChar[10] = {'0'};
    int teamNb;
    int choice = 1;
    char choiceChar[10] = {'0'};
    while (choice) {

        afficheMenu(nom);
        fgets(choiceChar, 10, stdin);
        choice = strtol(choiceChar, NULL, 10);
        switch (choice) {
            case 0:
                break;
            case 1:
                afficheTab(resultats);
                break;
            case 2:
                modifCase(resultats);
                break;
            case 3:
                printf("Quelle equipe examiner?");
                fgets(teamChar, 10, stdin);
                teamNb = strtol(teamChar, NULL, 10);
                nbPoints(resultats, teamNb);
                break;
            case 4:
                afficheScores(resultats);
                break;
            case 5:
                printf("leader: team #%d\n", equipeLeader(resultats));
                break;
            case 6:
                printf("home leader: team #%d\n", meilleureEquipeDomicile(resultats));
                break;
            case 7:
                printf("abroad leader: team #%d\n", meilleureEquipeExterieur(resultats));
                break;
            default:
                printf("valeur non reconnue\n");
                break;
        }
    }

    printf("Au revoir\n");

    return 0;
}
