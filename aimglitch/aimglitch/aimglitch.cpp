#include <windows.h>
#include <iostream>
#include <cstdlib>

using namespace std; 

static int y = 0;

INPUT input; // Déclaration d'un structure INPUT utilisée par la fonction SendInput permettant de simuler des keyboard events comme les clics de souris, touches de clavier, etc

unsigned int random_state = 1234;

int random(void) { // Utilisation d'une générateur pseudo aléatoire d'entiers pour la fonction randomval (plus optimisé que rand()). Modèle reposant sur un générateur xorshift basé sur le décallage binaire

    unsigned int r = random_state; // type de bit significatif

    // Opérations logiques
    r ^= r << 13; // Décale les bits vers la gauche. 
    r ^= r >> 17; // Décale les bits vers la droite.

    random_state = r; 
    return (int)(r & INT_MAX); // retour de la valeur finale 
}

int randomval() { // la fonction randomval de type int retournant une valeur finale utilisée comme coordonnée y pour la fonction fakeaa. 

    int k = random() % 2; // k aléatoire compris entre 0 et 1

    if (k == 0) y = 20000; // si k génère un entier égal à 0, y prend la valeur 20000
    if (k == 1) y = -20000; // si k génère un entier égal à 1, y prend la valeur -20000

    return y; // retour d'entier utilisé par input.mi.dy
}


void spinbot() { // Fonction spinbot : Fov sur le sol - lorsque la touche W (voir fcnt main), le joueur tourne sur lui même (pitch positif) 

    input.type = INPUT_MOUSE; // Type d'évènement
    input.mi.mouseData = 0;
    input.mi.time = 0;

    input.mi.dx = 5000; // coordonnées X du curseur qui sera retrounée par sendinput 
    input.mi.dy = 5000; // coordonnées Y du curseur qui sera retrounée par sendinput 
    input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE; // Indicateur binaire quant aux divers aspects du mouvement de la souris 

    SendInput(1, &input, sizeof(input)); //&input étant les paramètres et leur valeur de la structure input créee précédemment. Le dernier paramètre de la fonction correspond à la taille en octet de la structure 
 
}

void respinbot() { // Même fonction qu'au dessus, sauf que le joueur regarde vers le ciel (pitch négatif) 

    input.type = INPUT_MOUSE;
    input.mi.mouseData = 0;
    input.mi.time = 0;
 
    input.mi.dx = -5000;
    input.mi.dy = -5000;
    input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;

    SendInput(1, &input, sizeof(input));

}
void toupie() { // le joueur tourne sur lui même, reproduction de la célèbre fonctionnalité d'un cheat csgo "toupie"

    input.type = INPUT_MOUSE;
    input.mi.mouseData = 0;
    input.mi.time = 0;

    input.mi.dx = 10000;
    input.mi.dy = 0;
    input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;

    SendInput(1, &input, sizeof(input));
    
}

void fakeaa() { // fonction imitant (ou presque) la fonctionnalité d'un anti-aim sur csgo | A l'activation le joueur regarde vers le sol ou vers le ciel lorsque le bouton gauche de la souris est appuyé

    input.type = INPUT_MOUSE;
    input.mi.mouseData = 0;
    input.mi.time = 0;


    input.mi.dx =0;
    input.mi.dy = randomval(); // les coordonnées y varient entre 20000 et -20000 selon l'entier k aléatoire généré et retourné
    input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;

    SendInput(1, &input, sizeof(input));

}

int main() {

    HWND hwnd = GetConsoleWindow(); // contexte périphérique (la console du programme) 
    MoveWindow(hwnd, 0, 0, 610, 330, TRUE); // position en haut à gauche de l'écran (610 px de largeur et 330 px de hauteur) 
    SetWindowTextW(hwnd, L"aimglitch"); // Titre de la fenêtre

    // Présentation avec différentes couleurs de texte
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 30); // (texte blanc surligné de bleu)
    cout << "=======================================================================" << endl;
    cout << "//                            aimglitch                              //" << endl;
    cout << "=======================================================================\n" << endl;

    cout << "\n";

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    cout << "SPINBOT = [W] Key\n\n";

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << "REVERSED SPINBOT = [X] Key\n\n";

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
    cout << "TOUPIE = [C] Key\n\n";

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << "FAKE ANTI-AIM = [V] Key (Press left mouse button to apply the effect)\n\n\n\n";

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "EXIT = [ESCAPE] Key\n";

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    cout << "Created By Ulysse/DalasK/Jootzu\n";
        
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);


    while (true) {

          if (GetAsyncKeyState(0x57)) { // Vérification de l'état de la touche W (up ou down) - GetAsync pour l'asynchrone (tant que la touche est pressé, le code qui suit est exécuté) 

           spinbot(); // Appel de fonction
    }

          if (GetAsyncKeyState(0x58)) { // X

            respinbot();
    }

          if (GetAsyncKeyState(0x43)) { // C

            toupie();
    }

          if (GetKeyState(0x56)) { // V - GetKeyState - détéction synchrone (si la touche est pressé une seule fois, le code qui suit cette condition est exécuté !)

                if ((GetKeyState(VK_LBUTTON) & 0x8000) != 0) { // clique gauche de la souris 

                fakeaa();
    }

}
        
          if (GetAsyncKeyState(VK_ESCAPE)) { // echap - pour quitter le programme

                HWND hwnd = GetConsoleWindow(); 
       
                CloseWindow(hwnd); // Fermeture du programme en utilisant une macro de sortie 

                return EXIT_SUCCESS; 

          }
    }
}