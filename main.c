#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Structura pentru o carte de joc
typedef struct {
    int valoare;
    const char* nume;
    const char* simbol;
} Carte;

Carte pachet[52];
int index_carte_trasa = 0;

// Genereaza pachetul de 52 carti
void initializarePachet() {
    const char* simboluri[] = { "Inima Rosie", "Romb", "Trefla", "Inima Neagra" };
    const char* nume_carti[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "Valet", "Dama", "Rege", "As" };
    int valori[] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11 };

    int k = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            pachet[k].simbol = simboluri[i];
            pachet[k].nume = nume_carti[j];
            pachet[k].valoare = valori[j];
            k++;
        }
    }
}

// Amestecare folosind algoritmul Fisher-Yates simplificat
void amestecaPachet() {
    srand((unsigned int)time(NULL));
    for (int i = 0; i < 52; i++) {
        int j = rand() % 52;
        Carte aux = pachet[i];
        pachet[i] = pachet[j];
        pachet[j] = aux;
    }
    index_carte_trasa = 0; // Reset pachet
}

// Trage o carte (returneaza adresa din memorie)
Carte* trageCarte() {
    if (index_carte_trasa >= 52) return NULL;
    return &pachet[index_carte_trasa++];
}

// Calculeaza scorul si gestioneaza valoarea Asului
int calculeazaScor(Carte* mana[], int nr_carti) {
    int total = 0, nr_asi = 0;
    for (int i = 0; i < nr_carti; i++) {
        total += mana[i]->valoare;
        if (mana[i]->valoare == 11) nr_asi++;
    }
    while (total > 21 && nr_asi > 0) {
        total -= 10;
        nr_asi--;
    }
    return total;
}

int main() {
    int bani_totali = 100;
    int pariu;

    printf("=== Casino C - Blackjack ===\n");
    printf("Sold initial: %d$\n", bani_totali);

    while (bani_totali > 0) {
        initializarePachet();
        amestecaPachet();

        printf("\nCat pariezi? (Sold: %d$ | 0 pentru exit): ", bani_totali);
        if (scanf("%d", &pariu) != 1) break;

        if (pariu <= 0) break;
        if (pariu > bani_totali) {
            printf("Fonduri insuficiente!\n");
            continue;
        }

        // Folosim pointeri pentru a nu duplica structurile de carti
        Carte* mana_jucator[10];
        Carte* mana_dealer[10];
        int nr_j = 0, nr_d = 0;

        // Impartirea initiala
        mana_jucator[nr_j++] = trageCarte();
        mana_jucator[nr_j++] = trageCarte();
        mana_dealer[nr_d++] = trageCarte();
        mana_dealer[nr_d++] = trageCarte();

        int scor_j = calculeazaScor(mana_jucator, nr_j);
        printf("\nCartile tale: %s si %s (Total: %d)\n", mana_jucator[0]->nume, mana_jucator[1]->nume, scor_j);

        // Bucla pentru decizia jucatorului (Hit or Stand)
        int opt;
        while (scor_j < 21) {
            printf("Mai tragi o carte? (1-DA, 0-NU): ");
            scanf("%d", &opt);
            if (opt == 1) {
                mana_jucator[nr_j++] = trageCarte();
                scor_j = calculeazaScor(mana_jucator, nr_j);
                printf("Ai tras %s de %s. Scor: %d\n", mana_jucator[nr_j - 1]->nume, mana_jucator[nr_j - 1]->simbol, scor_j);
            }
            else break;
        }

        // Logica automata pentru Dealer
        int scor_d = calculeazaScor(mana_dealer, nr_d);
        if (scor_j <= 21) {
            printf("Dealerul arata a doua carte: %s. Trage...\n", mana_dealer[1]->nume);
            while (scor_d < 17) {
                mana_dealer[nr_d++] = trageCarte();
                scor_d = calculeazaScor(mana_dealer, nr_d);
            }
        }

        // Compararea scorurilor si actualizarea balantei
        printf("\n--- REZULTAT ---\n");
        printf("Tu: %d | Dealer: %d\n", scor_j, scor_d);

        if (scor_j > 21) {
            printf("Bust! Ai pierdut %d$\n", pariu);
            bani_totali -= pariu;
        }
        else if (scor_d > 21 || scor_j > scor_d) {
            printf("Ai castigat %d$!\n", pariu);
            bani_totali += pariu;
        }
        else if (scor_j < scor_d) {
            printf("Dealerul a castigat. Ai pierdut %d$\n", pariu);
            bani_totali -= pariu;
        }
        else {
            printf("Push (Egalitate). Pariul a fost returnat.\n");
        }
    }

    printf("\nJoc incheiat. Sold final: %d$\n", bani_totali);
    return 0;
}