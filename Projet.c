#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void addRoundKey(unsigned char *stateIn, unsigned char *stateOut, char *cle)
{
    for (int i = 0; i < 16; i++){
        stateOut[i] = cle[i] ^ stateIn[i];
    }
}

void subBytes(unsigned char *stateIn, unsigned char *stateOut)
{
    unsigned char sbytes[256] =
    {
        0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
        0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
        0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
        0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
        0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
        0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
        0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
        0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
        0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
        0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
        0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
        0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
        0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
        0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
        0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
        0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16
    };
    for (int i = 0;i < 4; i++){
        stateOut[i] = sbytes[stateIn[i]];
    }
}

void invSubBytes(unsigned char *stateIn, unsigned char *stateOut)
{
    unsigned char sbytesInv[256] =
    {
        0x52 ,0x09 ,0x6a ,0xd5 ,0x30 ,0x36 ,0xa5 ,0x38 ,0xbf ,0x40 ,0xa3 ,0x9e ,0x81 ,0xf3 ,0xd7 ,0xfb,
        0x7c ,0xe3 ,0x39 ,0x82 ,0x9b ,0x2f ,0xff ,0x87 ,0x34 ,0x8e ,0x43 ,0x44 ,0xc4 ,0xde ,0xe9 ,0xcb,
        0x54 ,0x7b ,0x94 ,0x32 ,0xa6 ,0xc2 ,0x23 ,0x3d ,0xee ,0x4c ,0x95 ,0x0b ,0x42 ,0xfa ,0xc3 ,0x4e,
        0x08 ,0x2e ,0xa1 ,0x66 ,0x28 ,0xd9 ,0x24 ,0xb2 ,0x76 ,0x5b ,0xa2 ,0x49 ,0x6d ,0x8b ,0xd1 ,0x25,
        0x72 ,0xf8 ,0xf6 ,0x64 ,0x86 ,0x68 ,0x98 ,0x16 ,0xd4 ,0xa4 ,0x5c ,0xcc ,0x5d ,0x65 ,0xb6 ,0x92,
        0x6c ,0x70 ,0x48 ,0x50 ,0xfd ,0xed ,0xb9 ,0xda ,0x5e ,0x15 ,0x46 ,0x57 ,0xa7 ,0x8d ,0x9d ,0x84,
        0x90 ,0xd8 ,0xab ,0x00 ,0x8c ,0xbc ,0xd3 ,0x0a ,0xf7 ,0xe4 ,0x58 ,0x05 ,0xb8 ,0xb3 ,0x45 ,0x06,
        0xd0 ,0x2c ,0x1e ,0x8f ,0xca ,0x3f ,0x0f ,0x02 ,0xc1 ,0xaf ,0xbd ,0x03 ,0x01 ,0x13 ,0x8a ,0x6b,
        0x3a ,0x91 ,0x11 ,0x41 ,0x4f ,0x67 ,0xdc ,0xea ,0x97 ,0xf2 ,0xcf ,0xce ,0xf0 ,0xb4 ,0xe6 ,0x73,
        0x96 ,0xac ,0x74 ,0x22 ,0xe7 ,0xad ,0x35 ,0x85 ,0xe2 ,0xf9 ,0x37 ,0xe8 ,0x1c ,0x75 ,0xdf ,0x6e,
        0x47 ,0xf1 ,0x1a ,0x71 ,0x1d ,0x29 ,0xc5 ,0x89 ,0x6f ,0xb7 ,0x62 ,0x0e ,0xaa ,0x18 ,0xbe ,0x1b,
        0xfc ,0x56 ,0x3e ,0x4b ,0xc6 ,0xd2 ,0x79 ,0x20 ,0x9a ,0xdb ,0xc0 ,0xfe ,0x78 ,0xcd ,0x5a ,0xf4,
        0x1f ,0xdd ,0xa8 ,0x33 ,0x88 ,0x07 ,0xc7 ,0x31 ,0xb1 ,0x12 ,0x10 ,0x59 ,0x27 ,0x80 ,0xec ,0x5f,
        0x60 ,0x51 ,0x7f ,0xa9 ,0x19 ,0xb5 ,0x4a ,0x0d ,0x2d ,0xe5 ,0x7a ,0x9f ,0x93 ,0xc9 ,0x9c ,0xef,
        0xa0 ,0xe0 ,0x3b ,0x4d ,0xae ,0x2a ,0xf5 ,0xb0 ,0xc8 ,0xeb ,0xbb ,0x3c ,0x83 ,0x53 ,0x99 ,0x61,
        0x17 ,0x2b ,0x04 ,0x7e ,0xba ,0x77 ,0xd6 ,0x26 ,0xe1 ,0x69 ,0x14 ,0x63 ,0x55 ,0x21 ,0x0c ,0x7d,
    };
    for (int i = 0;i < 4; i++){
        stateOut[i] = sbytesInv[stateIn[i]];
    }
}

int moduloMixColumns(int temp)
{
    if (temp >= 1024)
    {
        temp = temp ^ 108;
        temp = temp - 1024;
    }
    if (temp >= 512)
    {
        temp = temp ^ 54;
        temp = temp - 512;
    }
    if (temp >= 256)
    {
        temp = temp ^ 27;
        temp = temp - 256;
    }
    return temp;
}

void mixColumns(unsigned char *stateIn, unsigned char *stateOut)
{
    unsigned char temp='0';
    for (int i = 0; i < 4; ++i) //Pour chaque ligne
    {
        int temp=0;
        // Mélange de la première colonne
        temp = (2*stateIn[0+i*4]) ^ (3*stateIn[1+i*4]) ^ stateIn[2+i*4] ^ stateIn[3+i*4];
        temp = moduloMixColumns(temp);
        stateOut[0+i*4]=(char)temp;
        // Mélange de la deuxième colonne
        temp = stateIn[0+i*4] ^ (2*stateIn[1+i*4]) ^ (3*stateIn[2+i*4]) ^ stateIn[3+i*4];
        temp = moduloMixColumns(temp);
        stateOut[1+i*4]=(char)temp;
        // Mélange de la troisième colonne
        temp = stateIn[0+i*4] ^ stateIn[1+i*4] ^ (2*stateIn[2+i*4]) ^ (3*stateIn[3+i*4]);
        temp = moduloMixColumns(temp);
        stateOut[2+i*4]=(char)temp;
        // Mélange de la dernière colonne
        temp = (3*stateIn[0+i*4]) ^ stateIn[1+i*4] ^ stateIn[2+i*4] ^ (2*stateIn[3+i*4]);
        temp = moduloMixColumns(temp);
        stateOut[2+i*4]=(char)temp;
    }
}

void invMixColumns(unsigned char *stateIn, unsigned char *stateOut)
{

}

void shiftRows(unsigned char *stateIn, unsigned char *stateOut)
{
    // Deuxième ligne on décale de 1 à gauche
    for(int j=0; j<3; j++)
    {
        stateOut[4*j+1] = stateIn[4*(j+1)+1];
    }
    stateOut[13] = stateIn[1];
    // Troisième ligne on décale de 2 à gauche
    for(int j=0; j<2; j++)
    {
        stateOut[4*j+2] = stateIn[4*(j+2)+2];
        stateOut[4*(j+2)+2] = stateIn[4*j+2];
    }
    // Quatrième ligne on décale de 3 à gauche
    for(int j=1; j<4; j++)
    {
        stateOut[4*j+3] = stateIn[4*(j-1)+3];
    }
    stateOut[3] = stateIn[15];
}

void invShiftRows(unsigned char *stateIn, unsigned char *stateOut)
{
    // Deuxième ligne on décale de 1 à droite 
    for(int j=0; j<3; j++)
    {
        stateOut[4*(j+1)+1] = stateIn[4*j+1];
    }
    stateIn[1] = stateIn[13];
    // Troisième ligne on décale de 2 à droite
    for(int j=0; j<2; j++)
    {
        stateOut[4*(j+2)+2] = stateIn[4*j+2];
        stateOut[4*j+2] = stateIn[4*(j+2)+2];
    }
    // Quatrième ligne on décale de 3 à droite
    for(int j=1; j<4; j++)
    {
        stateOut[4*(j-1)+3] = stateIn[4*j+3];
    }
    stateOut[15] = stateIn[3];
}

void keyExpansion(char *cle)
{
    char sbytes[256] =
    {
        0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
        0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
        0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
        0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
        0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
        0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
        0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
        0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
        0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
        0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
        0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
        0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
        0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
        0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
        0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
        0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16
    };
    for (int i = 0;i < 4; i++){
        cle[i] = sbytes[(unsigned char)cle[i]];
    }
}

void roundChiffrementAES(unsigned char *stateIn, unsigned char *stateOut, char *cle, int Nr)
{
    addRoundKey(stateIn, cle);
    for (int i=0; i<Nr-1; i++)
    {
        subBytes(stateIn, stateOut);
        shiftRows(stateIn, stateOut);
        mixColumns(stateIn, stateOut);
        keyExpansion(cle);
        addRoundKey(stateIn, stateOut, cle);
    }
    subBytes(stateIn, stateOut);
    shiftRows(stateIn, stateOut);
    keyExpansion(cle);
    addRoundKey(stateIn, stateOut, cle);
}

void roundDechiffrementAES(unsigned char *stateIn, unsigned char *stateOut, char *cle, int Nr)
{
    addRoundKey(stateIn, cle);
    for (int i=0; i<Nr-1; i++)
    {
        invShiftRows(stateIn, stateOut);
        invSubBytes(stateIn, stateOut);
        keyExpansion(cle);
        addRoundKey(stateIn, stateOut, cle);
        invMixColumns(stateIn, stateOut);
    }
    invShiftRows(stateIn, stateOut);
    invSubBytes(stateIn, stateOut);
    keyExpansion(cle);
    addRoundKey(stateIn, stateOut, cle);
}


void chiffrerAES(int tailleCle, int Nr)
{
    printf("Vous avez choisi le chiffrement AES en %d bits !\n", tailleCle);
    int tailleCleByte = tailleCle/8;
    unsigned char stateIn[16];
    unsigned char stateOut[16];
    char *cle = malloc(tailleCleByte*sizeof(char));
    char normCle[32] = {0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73, 0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08};
    FILE* clair = NULL;
    FILE* cipher = NULL;
    clair = fopen("clair.txt", "r");
    cipher = fopen("cipher.txt", "w");
    printf("\n--> Entrez la clé de chiffrement <--\n");
    printf("Clé: ");
    scanf("%s", cle);
    if (strlen(cle) < tailleCleByte)
    {
        int m = strlen(cle);
        while (strlen(cle) < tailleCleByte)
        {
            cle[m] = cle[m-1] ^ normCle[m];
            m++;
        }
    }
    else if (strlen(cle) > tailleCleByte)
    {
        int n = strlen(cle);
        while (strlen(cle) > tailleCleByte)
        {
            cle[n] = 0;
            n--;
        }
    }
    if (clair == NULL || cipher == NULL)
    {
        printf ("\nErreur dans l'ouverture du fichier !\n\n");
    }
    else
    {
        while (!feof(clair))
        {
            // On remplit le bloc de 0
            for (int i=0; i<16; i++)
            {
                stateIn[i] = 0;
            }
            // Puis on met les valeurs du fichier dans le bloc
            for (int i=0; i<16; i++)
            {
                if (!feof(clair))
                {
                    stateIn[i] = fgetc(clair);
                }
                else
                {
                    break;
                }
            }
            // On effectue une round AES avec le bloc en question
            roundChiffrementAES(stateIn, stateOut, cle, Nr);
            // On écrit le bloc chiffré dans un fichier de sortie
            for (int i=0; i<16; i++)
            {
                fputc(stateOut[i], cipher);
            }
        }
        fclose (cipher);
        fclose (clair);
        printf("\nFélicitations, votre fichier a été chiffré en AES %d bits !\n\n", tailleCle);
    }
}

void chiffrementAES()
{
    int choixMenu;
    printf("Vous avez choisi le chiffrement AES !\n\n");
    printf("--> Sélectionner la taille de clé <--\n");
    printf("1.128 bits\n");
    printf("2.192 bits\n");
    printf("3.256 bits\n");
    printf("Votre choix: ");
    scanf("%d", &choixMenu);
    switch (choixMenu)
    {
    case 1:
        chiffrerAES(128,10);
        break;
    case 2:
        chiffrerAES(192,12);
        break;
    case 3:
        chiffrerAES(256,14);
        break;
    default:
        printf("Erreur, taille de clé incorrecte !\n\n");
        break;
    }

}

void chiffrementElGamal()
{
    printf("Vous avez choisi le chiffrement El-Gamal !\n\n");
}

void signatureElGamal()
{
    printf("Vous avez choisi la signature El-Gamal !\n\n");
}

int main(int argc, char *argv[])
{
    int choixMenu = 0;
    printf("--> Sélectionner votre fonction de chiffrement <--\n");
    printf("1.Chiffrement AES\n");
    printf("2.Chiffrement El-Gamal\n");
    printf("3.Signature El-Gamal\n");
    printf("Votre choix: ");
    scanf("%d", &choixMenu);
    switch(choixMenu)
    {
        case 1:
            chiffrementAES();
            break;
        case 2:
            chiffrementElGamal();
            break;
        case 3:
            signatureElGamal();
            break;
        default:
            printf("Erreur, choix non valide !\n\n");
            break;
    }
  	return 0;
}

/*void test_rabinMiller(mpz_t nbATester){
    int rep;
    mpz_t resultat, a, b;
    mpz_init(resultat);
    mpz_init(a);
    mpz_init(b);
    mpz_init_set_str(a, "2", 10);
    mpz_init_set_str(b, "1", 10);
    mpz_mod(resultat, nbATester,  a); //resultat=1 si nbatester impair sinon resultat=0
    rep= mpz_cmp(b,resultat);//si b=resultat, rep=0. Si b>resultat, rep=1.
    if (rep==1)
    {
        gmp_printf ("Nombre pair %Zd\n", "here", nbATester);
    }
    mpz_clear(resultat);
    mpz_clear(a);
    mpz_clear(b);
}*/
