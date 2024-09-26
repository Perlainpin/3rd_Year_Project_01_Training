#include <iostream>
#include <Windows.h>
#include <array>
#include <cmath>
#include <string>

/*
18 bits pour les case (2 bits par case)

1 bit pour le joueur en cours

2 bits pour l'etat de la partie

3 bits pour les parties gagnées j1

3 bits pour les parties gagnées j2

5 bits pour les parties nuls

donc a = 0b / 00000 / 000 / 000 / 00 / 0 / 00 00 00 00 00 00 00 00 00

#define Case1 0
#define Case2 2
#define Case3 4
#define Case4 6
#define Case5 8
#define Case6 10
#define Case7 12
#define Case8 14
#define Case9 16
*/

using namespace std;

unsigned int a = 0b00000000000000000000000000000000;

bool bit_set(unsigned bit)
{
    return a & (1 << bit);
}

void check_bit(unsigned bit)
{
    std::cout << "bit " << bit << " is " << (bit_set(bit - 1) ? "set" : "not set") << '\n';
}

void AddBinary(unsigned int mask)
{
    a = a | mask;
}

void RemoveBinary(unsigned int mask)
{
    a =  a & mask;
}

void CaseChange(int c) {
    if (not bit_set(c) & not bit_set(c+1)) {
        if (not bit_set(18)) {
            cout << "joueur 1 donc X donc 01 \n";
            AddBinary(pow(2, c));
            AddBinary(pow(2, 18));
        }
        else {
            cout << "joueur 1 donc O donc 10 \n";
            AddBinary(pow(2, c));
            RemoveBinary(pow(2, 18));
        }
    }
    else {
        cout << "case deja pleine, rejouer \n";

    }
}

void ShowGame(unsigned int a) {
    int y = 0;
    for (int i = 0; i < 18; i += 2) {
        if (y < 2) {
            if (not bit_set(i) & not bit_set(i + 1)) {
                std::cout << " [ ] ";
            }
            else if (bit_set(i) & not bit_set(i + 1)) {
                std::cout << " [X] ";
            }
            else if (not bit_set(i) & bit_set(i + 1)) {
                std::cout << " [O] ";
            }
            y++;
        }
        else {
            if (not bit_set(i) & not bit_set(i + 1)) {
                std::cout << " [ ] \n";
            }
            else if (bit_set(i) & not bit_set(i + 1)) {
                std::cout << " [X] \n";
            }
            else if (not bit_set(i) & bit_set(i + 1)) {
                std::cout << " [O] \n";
            }
            y = 0;
        }

    }
}

int main()
{
    bool KeyIsPress = false;
    
    for (int j = 0; j < 9; j++) {
        
        if (GetKeyState(VK_NUMPAD0 + j + 1) & 0x8000)
        {
            CaseChange(j * 2);
        }

    }
    //ShowGame(a);
    
    //std::array<unsigned, 32> bits = {32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1 };

    //for (auto bit : bits)
    //    check_bit(a, bit);

    //unsigned int num = 0b0101;

    //unsigned int mask = 0b0100;

}
