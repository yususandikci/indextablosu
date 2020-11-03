#include <stdio.h>
#include <stdlib.h>

int sayac = 0;  //index sayaci
int numara = 0; //ekle numara degiskeni
int not = 0;    //ekle not degiskeni

int secim = 0; //secim degiskeni

typedef struct ogrenci
{
    int index;
    int numara;
    int not ;
    struct ogrenci *sonraki;
} Ogrenci;

Ogrenci *listeSonEleman(Ogrenci *liste)
{
    Ogrenci *temp = liste;
    while (temp->sonraki != NULL)
    {
        temp = temp->sonraki;
    }
    return temp;
}

Ogrenci *indexElemanBul(Ogrenci *liste, int indexEleman, int oncekiSecim)
{
    Ogrenci *simdiki = liste;
    Ogrenci *onceki = NULL;
    while (simdiki != NULL)
    {
        if (simdiki->index == indexEleman)
        {
            if (oncekiSecim)
            {
                return onceki;
            }
            return simdiki;
        }
        onceki = simdiki;
        simdiki = simdiki->sonraki;
    }

    return NULL;
}

void sirala(Ogrenci *liste)
{
    Ogrenci *secilen = liste->sonraki;
    while (secilen != NULL)
    {
        Ogrenci *gezilen = secilen->sonraki;
        while (gezilen != NULL)
        {
            if ((secilen->not < gezilen->not ) || (secilen->not == gezilen->not &&secilen->numara > gezilen->numara))
            {
                int tempIndex = secilen->index;
                int tempNumara = secilen->numara;
                int tempNot = secilen->not ;
                secilen->index = gezilen->index;
                secilen->numara = gezilen->numara;
                secilen->not = gezilen->not ;
                gezilen->index = tempIndex;
                gezilen->numara = tempNumara;
                gezilen->not = tempNot;
            }
            gezilen = gezilen->sonraki;
        }
        secilen = secilen->sonraki;
    }
}

void ekle(Ogrenci *liste)
{
    printf("\nOgrenci Numarasini Giriniz: ");
    scanf("%d", &numara);
    printf("Ogrenci Notunu Giriniz: ");
    scanf("%d", &not );
    Ogrenci *sonDugum = listeSonEleman(liste);

    Ogrenci *yeni = (Ogrenci *)malloc(sizeof(Ogrenci));
    yeni->index = sayac;
    yeni->numara = numara;
    yeni->not = not ;
    yeni->sonraki = NULL;

    sayac++;

    sonDugum->sonraki = yeni;
    printf("\nEkleme Basarili\n");
    system("pause");
}

void yazdir(Ogrenci *liste,int min)
{
    Ogrenci *temp = liste->sonraki;
    printf("\n%-10s %-15s %-10s\n","Index","Numara","Not");
    printf("-------------------------------------\n");
    while (temp != NULL)
    { 
        // printf("Ogrenci Index: %d \n", temp->index);
        // printf("Ogrenci Numara: %d \n", temp->numara);
        // printf("Ogrenci Notu: %d \n", temp->not);
        if(temp->not >= min) printf("%-10d %-15d %-10d\n",temp->index,temp->numara,temp->not);
        
        temp = temp->sonraki;
    }
    printf("-------------------------------------\n");
}

void degistir(Ogrenci *liste)
{
    Ogrenci *degisecekOgrenci;
    int girilenIndex = 0;
    int yeniNotu = 0;

    yazdir(liste,0);
    printf("\nDegisilecek Ogrenci Index'ini Giriniz (%d-%d arasinda): ", 0, sayac-1);
    scanf("%d", &girilenIndex);

    if (degisecekOgrenci = indexElemanBul(liste, girilenIndex, 0))
    {
        printf("Yeni Notu Giriniz: ");
        scanf("%d", &yeniNotu);
        degisecekOgrenci->not = yeniNotu;
        printf("\nNot Degistirildi\n");
        system("pause");
    }
    else
    {
        printf("\nIndex Bulunamadi!!\n");
        system("pause");
    }
}

void sil(Ogrenci *liste)
{
    Ogrenci *silinecekOgrenciOnceki;
    Ogrenci *silinecekOgrenci;
    int girilenIndex = 0;

    yazdir(liste,0);
    printf("\nSilinecek Ogrenci Index'ini Giriniz (%d-%d arasinda): ", 0, sayac-1);
    scanf("%d", &girilenIndex);

    if (silinecekOgrenciOnceki = indexElemanBul(liste, girilenIndex, 1))
    {
        silinecekOgrenci = silinecekOgrenciOnceki->sonraki;
        silinecekOgrenciOnceki->sonraki = silinecekOgrenci->sonraki;

        printf("\nSilme Basarili\n");
        system("pause");

        free(silinecekOgrenci);
    }
    else
    {
        printf("\nIndex Bulunamadi!!\n");
        system("pause");
    }
}

void listeTemizle(Ogrenci *liste)
{
    Ogrenci *temp = liste;
    while (temp != NULL)
    {
        Ogrenci *sonrakiEleman = temp->sonraki;
        free(temp);
        temp = sonrakiEleman;
    }
}

int main()
{
    Ogrenci *ogrenciler = (Ogrenci *)malloc(sizeof(Ogrenci));
    ogrenciler->not = -1;
    ogrenciler->numara = -1;
    ogrenciler->index = -1;
    ogrenciler->sonraki = NULL;

    int minNot=0;

    do
    {
        printf("1. Ekle\n");
        printf("2. Sil\n");
        printf("3. Degistir\n");
        printf("4. Yazdir\n");
        printf("5. Cikis\n\n");
        printf("Bir Secim Giriniz (1-5 arasinda): ");
        scanf("%d", &secim);
        switch (secim)
        {
        case 1:
            ekle(ogrenciler);
            sirala(ogrenciler);
            break;
        case 2:
            sil(ogrenciler);
            sirala(ogrenciler);
            break;
        case 3:
            degistir(ogrenciler);
            sirala(ogrenciler);
            break;
        case 4:
            printf("\nListelenecek Minimum Notu Giriniz: ");
            scanf("%d",&minNot);
            yazdir(ogrenciler,minNot);
            system("pause");
            break;
        case 5:
            printf("Cikis Yapildi");
            break;
        default:
            printf("Hatali Secim");
            break;
        }
        system("cls");

    } while (secim != 5);

    listeTemizle(ogrenciler);
    return 0;
}