 Blackjack Casino Simulation (C Language)

Proiect dezvoltat în C care simulează experiența jocului de Blackjack (21), punând accent pe eficiența codului și utilizarea conceptelor de programare procedurală.

 Funcționalități principale
* **Sistem de Pariuri:** Jucătorul începe cu un sold virtual și poate paria sume diferite la fiecare mână.
* **Gestiune inteligentă a cărților:** Utilizarea structurilor (`struct`) pentru definirea pachetului de 52 de cărți.
* **Algoritm de Amestecare:** Implementare proprie a algoritmului Fisher-Yates pentru un pachet aleatoriu la fiecare rundă.
* **Logica Asului:** Calcularea automată a valorii Asului (1 sau 11) pentru a preveni depășirea scorului de 21.

 Concepte Tehnice Utilizate
* **Pointeri:** Utilizați pentru a accesa adresele de memorie ale cărților din pachet, evitând duplicarea inutilă a datelor în RAM.
* **Structuri de date:** Organizarea informațiilor despre cărți (nume, simbol, valoare).
* **Control Flow:** Bucle complexe (`while`, `for`) și structuri decizionale pentru logica Dealerului și a Jucătorului.
* **Standard I/O:** Interacțiune curată cu utilizatorul prin consolă.

 Cum se rulează
1. Se deschide fișierul `main.c` în orice compilator de C (recomandat Visual Studio).
2. Se compilează și se rulează (Ctrl + F5 în Visual Studio).
3. Se urmează instrucțiunile din consolă pentru a paria și a juca.
