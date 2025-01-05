#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

/* kuafor takip sistemi. yetkili giris yapar. yeni yetkili eklenebilir, varolan yetkili silinebilir. musterinin saci icin gecmis boya numarasini goruntuleyebilir, yeni boya numarasi ekleyebilir, musteriyi silebilir.*/

#define max_yetkili 10 
#define max_musteri 10000 
#define max_boyanumarasi 5


typedef struct 
{
	char ad[50];
	char sifre[20];	
} Yetkili;

typedef struct 
{
	char ad[50];
	char soyad[50];
	int boya_numaralari[max_boyanumarasi];
	int boya_sayisi; 
} Musteri;

Yetkili yetkililer[max_yetkili];
int yetkili_sayisi=3;

Musteri musteriler[max_musteri];
int musteri_sayisi=0;


//fonksiyon prototipleri:
void yetkili_islemleri();
void yetkili_girisi(); 
void yeni_yetkili_ekle();
void musteri_islemleri();
void boya_numaralari_goruntule(int musteri_index);
void yeni_boya_numarasi_ekle(int musteri_index);
void musteri_sil(int musteri_index);
void musteri_bul(char*ad, char*soyad);
void musteri_bilgilerini_dosyaya_yaz();
void musteri_bilgilerini_dosyadan_oku();

int main() {

	//baslangicta tanimli yetkililer
	strcpy (yetkililer[0].ad,"seref");
	strcpy (yetkililer[0].sifre,"seref123");
	strcpy (yetkililer[1].ad,"sila");
	strcpy (yetkililer[1].sifre,"1703");
	strcpy (yetkililer[2].ad,"nisa");
	strcpy (yetkililer[2].sifre,"5225");
	
yetkili_girisi(); 

while(1)
	{
	int islem;
	printf ("ANA MENU:\n");
	printf ("1-Yetkili Islemleri \n");
	printf ("2-Musteri Islemleri \n");
	printf ("3-Cikis \n");
	printf ("Yapmak istediginiz islemin numarasini giriniz: \n");
	scanf ("%d", &islem);
	
	switch (islem)
		{
		case 1:
			yetkili_islemleri(); 
			break;
			
		case 2:
			musteri_bilgilerini_dosyadan_oku();
			musteri_islemleri(); 
			break;
			
		case 3:
			printf ("Cikis yapiliyor. Iyi gunler! \n");
			return 0; 
			
		default: 
			printf ("Gecersiz islem yaptiniz. \n");
			break; 
		}	
	}
	return 0;
}


void yetkili_girisi()
{
    char ad[50], sifre[20];
    int i=0, dogru_giris=0;
    
    while (!dogru_giris)
    {    
        printf ("Yetkili adini giriniz. (kucuk harfler ile) \n");
        scanf ("%49s",ad);
        
        for (i=0; i<yetkili_sayisi;i++) 
        {
            if (strcmp(ad,yetkililer[i].ad)==0) 
            {
                break;
            }
        }
        
        if (i==yetkili_sayisi) 
        {
            printf ("Yetkili adi bulunamadi. Tekrar deneyin ya da cikis yapin. \n");
            printf("1-Tekrar dene \n");
            printf("2-Cikis \n");
            int secim;
            scanf("%d", &secim);
            if (secim == 2) 
            {
                printf("Cikis yapiliyor. Iyi gunler! \n");
                exit(0); 
            }
            else 
            {
                continue; 
            }
        }
        
        while (1) 
        {
            printf ("Yetkili sifresini giriniz. \n");
            scanf ("%19s",sifre);
            if (strcmp(sifre,yetkililer[i].sifre)==0) 
            {
                dogru_giris=1; 
                printf ("Giris basarili. Ana menuye yonlendiriliyorsunuz...\n");
                break; 
            }
            else 
            {
                printf ("Yanlis sifre! Tekrar deneyin ya da cikis yapin. \n");
                printf ("1-Tekrar dene \n");
                printf ("2-Cikis \n");
                int secim;
                scanf("%d",&secim);
                if (secim==2)
                {
                    printf ("Cikis yapiliyor. Iyi gunler! \n");
                    exit (0); 
                }
                else 
                {
                	continue;
				}
            }
        }
    } 
} 

void yetkili_islemleri()
{
	int islem;
	while(1)
	{
		printf ("\n YETKILI ISLEMLERI MENUSU: \n");
		printf ("1-Yeni yetkili ekle \n");
		printf ("2- Yetkili sil \n");
		printf ("3- Cikis \n");
		printf ("Lutfen yapmak istediginiz islemi seciniz. \n");
		scanf ("%d", &islem);
		
		switch (islem)
		{
			case 1:
				if (yetkili_sayisi>=max_yetkili)
				{
					printf ("Maksimum yetkili sayisina ulasildi. Yeni yetkili eklenemez.\n");
					break;
				}
				else 
				{
					char yeni_ad[50], yeni_sifre[20];
					printf ("Yeni yetkilinin adini giriniz. \n");
					scanf ("%49s", yeni_ad);
					printf ("Yeni yetkilinin sifresini giriniz. \n");
					scanf ("%19s",yeni_sifre);
					
					strcpy(yetkililer[yetkili_sayisi].ad, yeni_ad); 
					strcpy(yetkililer[yetkili_sayisi].sifre, yeni_sifre);
					yetkili_sayisi++; 
					printf ("Yeni yetkili basariyla eklendi. \n");
					break;
				}
			
			case 2:
				if (yetkili_sayisi==0)
				{
					printf ("Silinecek yetkili yok. \n");
					break;
				}
				else
				{
					char sil_ad[50];
					printf ("Silmek isteginiz yetkilinin adini giriniz. \n");
					scanf ("%49s", sil_ad);
					
					
					int bulundu=0;
					int i;
						for (i=0; i<yetkili_sayisi; i++) 
					{
						if (strcmp(yetkililer[i].ad, sil_ad)==0) 
						{
							int j;
							for (j=i; j<yetkili_sayisi-1;j++)
							{
								yetkililer[j]=yetkililer[j+1]; 
							}
							yetkili_sayisi--;
							bulundu=1;
							printf ("Yetkili basariyla silindi. \n");
							break;
						}
					}
						if (!bulundu)
						{
							printf ("Yetkili bulunamadi. \n");
						}
						break;
				}
			
			case 3:
				return; 
				
			default: 
				printf ("Gecersiz islem. Lutfen tekrar deneyiniz. \n");	
				break;
}

// Menuyu terk etmek istiyorsa
int secim;
while (1)
 {  // Sonsuz dongu, gecerli bir giris alinana kadar devam eder
    printf("Islem tamamlandi. Menuye donmek ister misiniz? (1-Evet, 2-Hayir): ");
    scanf("%d", &secim);
    
    if (secim == 1) {
        // menuye donme islemi
        break;  // donguden cikip menuye donulur
    }
    else if (secim == 2) {
        // Çýkýþ iþlemi
        printf("Cikis yapiliyor. Iyi gunler! \n");
        exit(0); // programdan cikilir
    }
    else 
	{
        // Gecersiz giris durumu
        printf("Gecersiz secim yaptiniz. Lutfen sadece 1 veya 2 giriniz.\n");
    }
}
	}
}

void musteri_bilgilerini_dosyaya_yaz() {
    FILE *file = fopen("musteriler.txt", "a");
    if (file == NULL) {
        printf("Dosya acilamadi. \n");
        return;
    }
	int i=0;
    for (i = 0; i < musteri_sayisi; i++) {
        fprintf(file, "%s %s %d", musteriler[i].ad, musteriler[i].soyad, musteriler[i].boya_sayisi);

        
        int j=0;
		for (j = 0; j < musteriler[i].boya_sayisi; j++) {
            fprintf(file, " %d", musteriler[i].boya_numaralari[j]);
        }

        // Satir sonu ekliyoruz, boylece her musteri bilgisi yeni bir satýrda olacak
        fprintf(file, "\n");
    }

    fclose(file);
}


void musteri_bilgilerini_dosyadan_oku() {
    FILE *file = fopen("musteriler.txt", "r");
    if (file == NULL) {
        printf("Dosya bulunamadi, yeni dosya olusturuluyor. \n");
        file = fopen("musteriler.txt", "w");
        return;
    }

    while (fscanf(file, "%s %s %d", musteriler[musteri_sayisi].ad, musteriler[musteri_sayisi].soyad, &musteriler[musteri_sayisi].boya_sayisi) != EOF) {
        int i=0;
		for (i = 0; i < musteriler[musteri_sayisi].boya_sayisi; i++) {
            fscanf(file, " %d", &musteriler[musteri_sayisi].boya_numaralari[i]);
        }
        musteri_sayisi++; 
    }

    fclose(file);
}


void musteri_islemleri() 
{ 
char ad[50], soyad[50];
printf ("Musteri adi: \n");
scanf ("%49s",ad); 
printf ("Musteri soyadi: \n");
scanf ("%49s", soyad);

//musteri kayitli mi kontrol et
int musteri_index=-1;
int i=0;
for (i=0;i<musteri_sayisi;i++) 
	{
		if (strcmp(musteriler[i].ad,ad)==0 && strcmp(musteriler[i].soyad,soyad)==0) 
		{
			musteri_index=i;
			break;	
		}
	}

if (musteri_index==-1) //musteri kayitli degil ise yeni musteriyi kaydet.
	{
		printf ("Musteri kaydedildi. \n");
		strcpy(musteriler[musteri_sayisi].ad,ad);
		strcpy(musteriler[musteri_sayisi].soyad,soyad);
		musteriler[musteri_sayisi].boya_sayisi= 0; 
		musteri_sayisi++; 	
	}

//musteri islemleri menusu
	int islem;
	while (1)
	{
		printf ("\n MUSTERI ISLEMLERI MENUSU: \n");
		printf ("1- Boya numaralarini goruntule \n");	
		printf ("2- Yeni boya numarasi ekle \n");	
		printf ("3- Musteri sil \n");
		printf ("4- Cikis \n");
		printf ("Lutfen yapmak istediginiz islemi seciniz. \n");
		scanf ("%d", &islem);
		
		switch (islem)
			{
			case 1: 
			boya_numaralari_goruntule(musteri_index); 
			break;
			
			case 2: 
			yeni_boya_numarasi_ekle(musteri_index); 
			break;
			
			case 3: 
			musteri_sil(musteri_index);
			break;
			
			case 4:
				printf ("Cikis yapiliyor. Iyi gunler! \n");
				musteri_bilgilerini_dosyaya_yaz();
				exit(0); 
				
			default:
				printf ("Gecersiz Islem \n");
				break;
		}
		
// Menuye donmek isteyip istemedigi kontrolu
		int secim;
        while (1) {
            printf("Islem tamamlandi. Menuye donmek ister misiniz? (1-Evet, 2-Hayir): ");
            scanf("%d", &secim);
            
            if (secim == 1) {
                break;  // Menüye dön
            }
            else if (secim == 2) {
                printf("Cikis yapiliyor. Iyi gunler! \n");
                musteri_bilgilerini_dosyaya_yaz();
                exit(0); // Programdan çýk
            }
            else {
                printf("Gecersiz secim yaptiniz. Lutfen sadece 1 veya 2 giriniz.\n");
            }
        }
    }    
}		
				
	
//Boya numaralarini goruntuleme fonksiyonu
void boya_numaralari_goruntule(int musteri_index)
	{
	if (musteriler[musteri_index].boya_sayisi==0)
		{
			printf ("Bu musterinin kayitli boya numarasi yok. \n");
		}
	else
		{
			printf ("Musteri Boya Numaralari: \n");
			int i;
			for (i=0; i<musteriler[musteri_index].boya_sayisi; i++)
			{
				printf ("%d. boya numarasi %d \n", i+1, musteriler[musteri_index].boya_numaralari[i]);
			}
		}
	}

//Yeni boya numarasi ekleme fonksiyonu
void yeni_boya_numarasi_ekle(int musteri_index)
	{
		if (musteriler[musteri_index].boya_sayisi>=max_boyanumarasi)
		{
			printf ("Maksimum boya sayisina ulasildi. En eski boya silindi.\n");
			int i=0;
			for (i=0;i<max_boyanumarasi-1;i++)
			{	//tum elemanlarý 1 sola kaydýr
				musteriler[musteri_index].boya_numaralari[i]=musteriler[musteri_index].boya_numaralari[i+1];
			}
			int yeni_boya;
			printf ("Yeni boya numarasini giriniz. \n");
			scanf ("%d", &yeni_boya);
			musteriler[musteri_index].boya_numaralari[max_boyanumarasi-1]=yeni_boya;
			printf ("Yeni boya numarasi eklendi.");
			
		}
		
		else
		{
			int yeni_boya;
			printf ("Yeni boya numarasini giriniz: \n");
			scanf ("%d", &yeni_boya);
			
			musteriler[musteri_index].boya_numaralari[musteriler[musteri_index].boya_sayisi] = yeni_boya;
			musteriler[musteri_index].boya_sayisi++;
			printf ("Yeni boya numarasi eklendi. \n");
		}
	}

//musteri silme fonksiyonu
void musteri_sil(int musteri_index)
	{
		int i;
		for (i=musteri_index; i<musteri_sayisi-1; i++)
		{	
			musteriler[i]=musteriler[i+1];
		}
		musteri_sayisi--;
		printf ("Musteri basariyla silindi. \n");
	}
	
