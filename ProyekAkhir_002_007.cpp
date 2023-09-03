#include <windows.h>
#include <stdio.h>
#include <iomanip>
#include <iostream>
using namespace std;

struct karyawan{
	int id, gaji;
	char nama[100], posisi[100];
};

bool cek;
void input();
void output();
void searching(),sequential(),binary();
void sorting(),bubble(),selection(),insertion(),shell();
void quick(),sortingquick(karyawan *data,int low,int high,int sortquick,int s);
void sortingmerge(),merge(karyawan *data,int low,int mid,int up,int sortmerge,int byk),mergesort(karyawan *data,int low,int up,int sortmerge,int byk);
void setdata(),sambung(),edit(),hapus();
void tampil(karyawan *data,int n);
void garis();
void header();

int menutama, bykdata, menusearch, searchseq, searchbin;
int menusort, sortbub, sortslc;
int sortist, sortshell, sortquick, sortmerge, menutrans;
int carid, cargaji, b, j, i;
string menu, carnama, carposisi;
char namafile[30];

int main()
{
	do{
	system("cls");
	cout<<"\n\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl; Sleep(100);
	cout<<"\t    ~~~~~~~~~~~ kel.9 (002,009) ~~~~~~~~~~~"<<endl; Sleep(100);
	cout<<"\t       ~~ S E L A M A T   D A T A N G ~~"<<endl; Sleep(200);
	cout<<"\t    ~~~~~~~~ Program Data Karyawan ~~~~~~~~"<<endl; Sleep(100);
	cout<<"\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl; Sleep(100);
	cout<<"\n\t\t============================\n";
	cout<<"\t\t|   M E N U   U T A M A    |"<<endl;
	cout<<"\t\t----------------------------\n";
	cout<<"\t\t |  [1] Input Data        |"<<endl;
	cout<<"\t\t |  [2] Output Data       |"<<endl;
	cout<<"\t\t |  [3] Searching Data    |"<<endl;
	cout<<"\t\t |  [4] Sorting Data      |\n";
	cout<<"\t\t |  [5] Setting Data      |\n";
	cout<<"\t\t |  [6] Keluar            |\n";
	cout<<"\t\t ==========================\n\n";
	do{
		cout << "\tMasukkan Pilihan   = "; cin>> menutama;
	}while(menutama > 6);
		if(menutama==1){
			cin.ignore();
			input();
		}
		else if(menutama==2){
			cin.ignore();
			output();
		}
		else if(menutama==3){
			cin.ignore();
			cout << "\n >> Nama File         = "; cin.getline(namafile, 30);
			searching();
		}
		else if(menutama==4){
			cin.ignore();
			cout << "\n >> Nama File         = "; cin.getline(namafile, 30);
			sorting();
		}
		else if(menutama==5){
			cin.ignore();
			setdata();
		}
		else if(menutama==6){
			cout<<"\n Terimakasih ... \n"<<endl;
			exit(0);
		}
		cout<< "\nKembali Ke Menu Utama?\n";
		cout<< "\nY : Kembali\nN : Keluar\n Masukan Pilihan\t: "; cin>>menu;
	}while(menu=="y" || menu == "Y");

	return 0; 
}

void input(){
	karyawan *data;
	FILE *dt;
	system("cls");

	cout << "\t========================="<<endl;
	cout << "\t| INPUT DATA KARYAWAN   |" <<endl;
	cout << "\t========================="<<endl;
	cout << "\n >> Input Nama File = ";cin.getline(namafile, 30);
	dt = fopen(namafile, "a");
	if(dt == NULL){
		cout << " File tidak dapat diciptakan!" << endl;
	}
	else{
		cout << "\n Banyaknya Data    = "; cin>>bykdata;
		data = (karyawan*)calloc(bykdata, sizeof(karyawan));
		for(int i=0; i<bykdata; i++){
			cout << "\n";
			cout << " > Data ke-"<<i+1<<endl;
			cout << "\tID       = "; cin>>data[i].id;cin.ignore();
			cout << "\tNama     = "; cin.getline(data[i].nama, 100);
			cout << "\tPosisi   = "; cin.getline(data[i].posisi,100);
			cout << "\tGaji     = "; cin>>data[i].gaji;
			fflush(stdin);
			fwrite(&data[i], sizeof(karyawan), 1, dt);
		}
		cout << "\n";
	}
	fclose(dt);
}

void output(){
	karyawan data;
	FILE *dt;
	system("cls");
	
	cout << "\t=========================="<<endl;
	cout << "\t|  OUTPUT DATA KARYAWAN  |" <<endl;
	cout << "\t=========================="<<endl;
	cout << "\t>> Nama File = "; cin.getline(namafile, 30);
	cout << "\n";
	header();
	dt = fopen(namafile, "rb");
	if(dt == NULL){
		cout << " File tidak tersedia!" << endl;
	}
	else{
		while(fread(&data, sizeof(karyawan), 1, dt)==1){
			cout << left << " " << setw(20)<< data.id << setw(20)<< data.nama << setw(20) << data.posisi << setw(20)<< data.gaji << endl;
		}
		garis();
	}
	fclose(dt);
}

void tampil(karyawan *data, int n){
	header();
	for(int j=0;j<n;j++){
		cout << left << " " << setw(20)<< data[j].id << setw(20)<< data[j].nama << setw(20) << data[j].posisi << setw(20)<< data[j].gaji<< endl;
	}
	garis();
}

void searching(){
	string balik;
	do{
		system("cls");
		cout << "\t==========================="<<endl;
		cout << "\t|   CARI DATA KARYAWAN    |" <<endl;
		cout << "\t==========================="<<endl;
		cout << "\t[1] Sequential Search\n\t[2] Binary Search\n ";
		cout << "\t==========================="<<endl;
		do{
			cout << " Masukkan Pilihan\t= "; cin>>menusearch;
		}while(menusearch > 2);
		if(menusearch==1){
			sequential();
		}
		else if(menusearch==2){
			binary();
		}
		cout<< "\n Kembali Ke Menu Searching?\n";
		cout<< "\n Y : Ke Menu Searching\n N : Ke Menu Utama\n Masukan Pilihan\t: "; cin>>balik;
	}while(balik == "y" || balik == "Y");
}

void sequential(){
	karyawan data;
	FILE *dt;
	bool cek=0;
	dt = fopen(namafile, "rb");
	system("cls");
	if(dt == NULL){
		cout << " File tidak dapat dibuka!" << endl;
	}
	else{
		cout << "\t========================"<<endl;
		cout << "\t| PENCARIAN SEQUENTIAL |" <<endl;
		cout << "\t========================"<<endl;
		cout << "\t[1] ID \n\t[2] Nama\n\t[3] Posisi\n\t[4] Gaji" << endl;
		cout << "\t========================"<<endl;
		do{
			cout << " Masukkan Pilihan\t= "; cin>>searchseq;
		}while(searchseq > 4);
		cout << endl;
		if(searchseq==1){
			cout << " Masukkan ID Karyawan\t= "; cin>>carid;
			while(fread(&data, sizeof(karyawan),1,dt)==1){
				if(data.id==carid){
					cek=1;
					cout << "\n\tID        = " << data.id <<endl; 
					cout << "\tNama      = " << data.nama <<endl;
					cout << "\tPosisi    = " << data.posisi <<endl; 
					cout << "\tGaji      = " << data.gaji <<endl;
					cout << endl;
				}
			}
		}
		else if(searchseq==2){
			cout << " Masukkan Nama Karyawan\t= "; cin.ignore(); getline(cin, carnama);
			while(fread(&data, sizeof(karyawan),1,dt)==1){
				if(data.nama==carnama){
					cek=1;
					cout << "\n\tID        = " << data.id <<endl; 
					cout << "\tNama      = " << data.nama <<endl;
					cout << "\tPosisi    = " << data.posisi <<endl; 
					cout << "\tGaji      = " << data.gaji <<endl;
					cout << endl;
				}
			}
		}
		else if(searchseq==3){
			cout << " Masukkan Posisi Karyawan\t= "; cin>>carposisi;
			while(fread(&data, sizeof(karyawan),1,dt)==1){
				if(data.nama==carposisi){
					cek=1;
					cout << "\n\tID        = " << data.id <<endl; 
					cout << "\tNama      = " << data.nama <<endl;
					cout << "\tPosisi    = " << data.posisi <<endl; 
					cout << "\tGaji      = " << data.gaji <<endl;
					cout << endl;
				}
			}
		}
		else if(searchseq==4){
			cout << " Masukkan Gaji Karyawan\t= "; cin>>cargaji;
			while(fread(&data, sizeof(karyawan),1,dt)==1){
				if(data.gaji==cargaji){
					cek=1;
					cout << "\n\tID        = " << data.id <<endl; 
					cout << "\tNama      = " << data.nama <<endl;
					cout << "\tPosisi    = " << data.posisi <<endl; 
					cout << "\tGaji      = " << data.gaji <<endl;
					cout << endl;
				}
			}
		}
		if(cek==0){
			cout << " Data Unavailable" << endl;
		}
	}
	fclose(dt);
}

void binary(){
		karyawan *data;
		FILE *dt;
		dt = fopen(namafile, "rb");
		fseek(dt,0,SEEK_END);
		int n = ftell(dt)/sizeof(karyawan);
		data = (karyawan*)calloc(n+1, sizeof(karyawan));
		rewind(dt);

		system("cls");
		if(dt == NULL){
			cout << " File tidak dapat dibuka!" << endl;
		}
		else{
			for( i=0; i<n; i++){
				fread(&data[i], sizeof(karyawan),1,dt);
			}
			cout << "\t======================"<<endl;
			cout << "\t|  PENCARIAN BINARY  |" <<endl;
			cout << "\t======================"<<endl;
			cout << "\t[1] ID\n\t[2] Nama\n\t[3] Posisi\n\t[4] Gaji" << endl;
			cout << "\t======================"<<endl;
			do{
				cout << " Masukkan Pilihan\t= "; cin>>searchbin;
			}while(searchbin > 4);
			if(searchbin==1){
				cout << " Masukkan ID Karyawan\t= "; cin>>carid;		
				cek = false;
				b = 0;
				j = n-1;
				while((!cek) & (b <= j)){
					i = (b + j) / 2;
					for(i = 0; i < n; i++){
						if(carid == data[i].id){
							cek = true;
							cout<<endl;
							cout << "\n\tID        = " << data[i].id <<endl; 
							cout << "\tNama      = " << data[i].nama <<endl;
							cout << "\tPosisi    = " << data[i].posisi <<endl; 
							cout << "\tGaji      = " << data[i].gaji <<endl;
						}
						else{
							if(carid < data[i].id){
								j = i - 1; 
							}
							else{	b = i + 1; 	}
						}		
					}
				}
			}
			else if(searchbin==2){
				cout << " Masukkan Nama Karyawan\t= "; cin.ignore(); getline(cin, carnama);
				cek = false;
				b = 0;
				j = n-1;
				while((!cek) & (b <= j)){
					i = (b + j) / 2;
					for(i = 0; i < n; i++){
						if(carnama == data[i].nama){
							cek = true;
							cout<<endl;
							cout << "\n\tID        = " << data[i].id <<endl; 
							cout << "\tNama      = " << data[i].nama <<endl;
							cout << "\tPosisi    = " << data[i].posisi <<endl; 
							cout << "\tGaji      = " << data[i].gaji <<endl;
						}
						else{
							if(carnama < data[i].nama){
								j = i - 1; 
							}
							else{	b = i + 1; 	}
						}		
					}
				}
			}
			else if(searchbin==3){
				cout << " Masukkan Posisi Karyawan = "; cin>>carnama;
				cek = false;
				b = 0;
				j = n-1;
				while((!cek) & (b <= j)){
					i = (b + j) / 2;
					for(i = 0; i < n; i++){
						if(carposisi == data[i].posisi){
							cek = true;
							cout<<endl;
							cout << "\n\tID        = " << data[i].id <<endl; 
							cout << "\tNama      = " << data[i].nama <<endl;
							cout << "\tPosisi    = " << data[i].posisi <<endl; 
							cout << "\tGaji      = " << data[i].gaji <<endl;
						}
						else{
							if(carposisi < data[i].posisi){
								j = i - 1; 
							}
							else{	b = i + 1; 	}
						}		
					}
				}
			}
			else if(searchbin==4){
				cout << " Masukkan Gaji Karyawan\t= "; cin>>cargaji;
				cek = false;
				b = 0;
				j = n-1;
				while((!cek) & (b <= j)){
					i = (b + j) / 2;
					for(i = 0; i < n; i++){
						if(cargaji == data[i].gaji){
							cek = true;
							cout<<endl;
							cout << "\n\tID        = " << data[i].id <<endl; 
							cout << "\tNama      = " << data[i].nama <<endl;
							cout << "\tPosisi    = " << data[i].posisi <<endl; 
							cout << "\tGaji      = " << data[i].gaji <<endl;
						}
						else{
							if(cargaji < data[i].gaji){
								j = i - 1; 
							}
							else{	b = i + 1; 	}
						}		
					}
				}
			}
			if(!cek){
				cout<<"\n\t Data Unavailable\n\n";
			}
		}
		fclose(dt);
}

void sorting(){
	string back;
	do{
		system("cls");
		cout << "\t============================"<<endl;
		cout << "\t| PENGURUTAN DATA KARYAWAN |" <<endl;
		cout << "\t============================"<<endl;
		cout << "\t[1] Bubble Sort\n\t[2] Selection Sort\n\t[3] Insertion Sort\n\t[4] Shell Sort\n\t[5] Quick Sort\n\t[6] Merge Sort" << endl;
		cout << "\t============================"<<endl;
		do{
			cout << " Masukkan Pilihan\t= "; cin>>menusort;
		}while(menusort > 6);
		if(menusort==1){
			bubble();
		}
		else if(menusort==2){
			selection();
		}
		else if(menusort==3){
			insertion();
		}
		else if(menusort==4){
			shell();
		}
		else if(menusort==5){
			quick();
		}
		else if(menusort==6){
			sortingmerge();
		}
		cout<< "\n Kembali Ke Menu Sorting?\n";
		cout<< "\n Y : Ke Menu Sorting\n N : Ke Menu Utama\n Masukan Pilihan\t: "; cin>>back;
	}while(back == "y" || back == "Y");
}

void bubble(){
		karyawan *data, temp;
		FILE *dt;
		dt = fopen(namafile, "rb");
		fseek(dt,0,SEEK_END);
		int s = ftell(dt)/sizeof(karyawan);
		data = (karyawan*)calloc(s, sizeof(karyawan));
		rewind(dt);
		system("cls");
		if(dt == NULL){
			cout << "File tidak dapat dibuka!" << endl;
		}
		else{
			for(int i=0; i<s; i++){
				fread(&data[i], sizeof(karyawan),1,dt);
			}
			cout << "\t====================="<<endl;
			cout << "\t| PENGURUTAN BUBBLE |" <<endl;
			cout << "\t====================="<<endl;
			cout << "\t[1] ID\n\t[2] Nama\n\t[3] Posisi\n\t[4] Gaji" << endl;
			cout << "\t====================="<<endl;
			cout << " Masukkan Pilihan\t= "; cin>>sortbub;
			
			if(sortbub==1){
				cout << "\n PROSES BUBBLE SORT\n";
				for(int i=0;i<s-1;i++){
					for(int x=0;x<s;x++){
						cout << " ["<<data[x].id << "] ";
					}cout << endl;
					for(int j=0;j<s-i-1;j++){
						if(data[j].id>data[j+1].id){
							temp=data[j];
							data[j]=data[j+1];
							data[j+1]=temp;
						}
					}
				} 
				for(int x=0;x<s;x++){
					cout << " ["<<data[x].id << "] ";
				}cout << endl << endl; 
			}
			else if(sortbub==2){
				cout << "\n PROSES BUBBLE SORT\n";
				for(int i=0;i<s-1;i++){
					for(int x=0;x<s;x++){
						cout << " ["<<data[x].nama << "] ";
					}cout << endl;
					for(int j=0;j<s-i-1;j++){
						if(strcmp(data[j].nama,data[j+1].nama)>0){
							temp=data[j];
							data[j]=data[j+1];
							data[j+1]=temp;
						}
					}
				}  
				for(int x=0;x<s;x++){
					cout << " ["<<data[x].nama << "] ";
				}cout << endl << endl; 
			}
			else if(sortbub==3){
				cout << "\n PROSES BUBBLE SORT\n";
				for(int i=0;i<s-1;i++){
					for(int x=0;x<s;x++){
						cout << " ["<<data[x].posisi << "] ";
					}cout << endl;
					for(int j=0;j<s-i-1;j++){
						if(strcmp(data[j].posisi,data[j+1].posisi)>0){
							temp=data[j];
							data[j]=data[j+1];
							data[j+1]=temp;
						}
					}
				}  
				for(int x=0;x<s;x++){
					cout << " ["<<data[x].posisi << "] ";
				}cout << endl << endl; 
			}
			else if(sortbub==4){
				cout << "\n PROSES BUBBLE SORT\n";
				for(int i=0;i<s-1;i++){
					for(int x=0;x<s;x++){
						cout << " ["<<data[x]. gaji<< "] ";
					}cout << endl;
					for(int j=0;j<s-i-1;j++){
						if(data[j].gaji>data[j+1].gaji){
							temp=data[j];
							data[j]=data[j+1];
							data[j+1]=temp;
						}
					}
				}  
				for(int x=0;x<s;x++){
					cout << " ["<<data[x].gaji << "] ";
				}cout << endl << endl; 
			}
	}
	fclose(dt);	
	tampil(data, s);	
}

void selection(){
	system("cls");
	karyawan *data, temp;
	FILE *dt;
	dt = fopen(namafile, "rb");
	fseek(dt,0,SEEK_END);
	int s = ftell(dt)/sizeof(karyawan);
	data = (karyawan*)calloc(s, sizeof(karyawan));
	
	rewind(dt);
	if(dt == NULL){
		cout << " File tidak dapat dibuka!" << endl;
	}
	else{
		for(int i=0; i<s; i++){
			fread(&data[i], sizeof(karyawan),1,dt);
		}
			cout << "\t========================"<<endl;
			cout << "\t| PENGURUTAN SELECTION |" <<endl;
			cout << "\t========================"<<endl;
			cout << "\t[1] ID\n\t[2] Nama\n\t[3] Posisi\n\t[4] Gaji" << endl;
			cout << "\t========================"<<endl;
			cout << " Masukkan Pilihan\t= "; cin>>sortslc;
			if(sortslc==1){
				cout << "\n PROSES SELECTION\n";
				for (int i = 0; i < s; i++){
					for(int j = i+1; j < s; j++){
						if(data[i].id > data[j].id){
							temp=data[i];
							data[i]=data[j];
							data[j]=temp;
						}
					}
					for(int x=0;x<s;x++){
						cout << " ["<<data[x].id << "] ";
					}cout << endl;
				}
			}
			else if(sortslc==2){
				cout << "\n PROSES SELECTION\n";
				for (int i = 0; i < s; i++){
					for(int j = i+1; j < s; j++){
						if(strcmp(data[i].nama, data[j].nama)>0){
							temp=data[i];
							data[i]=data[j];
							data[j]=temp;
						}
					}
					for(int x=0;x<s;x++){
						cout << " ["<<data[x].nama << "] ";
					}cout << endl;
				}
			}
			else if(sortslc==3){
				cout << "\n PROSES SELECTION\n";
				for (int i = 0; i < s; i++){
					for(int j = i+1; j < s; j++){
						if(strcmp(data[i].posisi, data[j].posisi)>0){
							temp=data[i];
							data[i]=data[j];
							data[j]=temp;
						}
					}
					for(int x=0;x<s;x++){
						cout << " ["<<data[x].posisi << "] ";
					}cout << endl;
				}
			}
			else if(sortslc==4){
				cout << "\n PROSES SELECTION\n";
				for (int i = 0; i < s; i++){
					for(int j = i+1; j < s; j++){
						if(data[i].gaji > data[j].gaji){
							temp=data[i];
							data[i]=data[j];
							data[j]=temp;
						}
					}
					for(int x=0;x<s;x++){
						cout << " ["<<data[x].gaji << "] ";
					}cout << endl;
				}
			}
	}
	fclose(dt);
	tampil(data, s);	
}

void insertion(){
	karyawan *data, temp;
	FILE *dt;
	dt = fopen(namafile, "rb");
	fseek(dt,0,SEEK_END);
	int s = ftell(dt)/sizeof(karyawan);
	data = (karyawan*)calloc(s, sizeof(karyawan));
	rewind(dt);
	system("cls");
	if(dt == NULL){
		cout << "File tidak dapat dibuka!" << endl;
	}
	else{
		for(int i=0; i<s; i++){
			fread(&data[i], sizeof(karyawan),1,dt);
		}
			cout << "\t========================"<<endl;
			cout << "\t| PENGURUTAN INSERTION |" <<endl;
			cout << "\t========================"<<endl;
			cout << "\t[1] ID\n\t[2] Nama\n\t[3] Posisi\n\t[4] Gaji" << endl;
			cout << "\t========================"<<endl;
			cout << " Masukkan Pilihan\t= "; cin>>sortist;
			if(sortist==1){
				cout << " PROSES INSERTION : " << endl;
				for(int x=0;x<s;x++){
					cout << " ["<<data[x].id << "] ";
				}cout << endl;
				for(int i=1; i<s; i++){
					temp = data[i];
					j=i-1;
					while((temp.id < data[j].id) && (j>=0)){
						data[j+1]=data[j];
						j--;
						data[j+1]=temp;
					}
					for(int x=0 ; x<s ; x++){
						cout << " ["<<data[x].id << "] ";
					}cout << endl;
				}    
			}
			else if(sortist==2){
				cout << " PROSES INSERTION : " << endl;
				for(int x=0;x<s;x++){
					cout << " ["<<data[x].nama << "] ";
				}cout << endl;
				for(int i=1; i<s; i++){
					temp = data[i];
					j=i-1;
					while(strcmp(data[j].nama, temp.nama)>0 && (j>=0)){
						data[j+1]=data[j];
						j--;
						data[j+1]=temp;
					}
					for(int x=0 ; x<s ; x++){
						cout << " ["<<data[x].nama << "] ";
					}cout << endl;
				}  	
			}
			else if(sortist==3){
				cout << " PROSES INSERTION : " << endl;
				for(int x=0;x<s;x++){
					cout << " ["<<data[x].posisi<< "] ";
				}cout << endl;
				for(int i=1; i<s; i++){
					temp = data[i];
					j=i-1;
					while(strcmp(data[j].posisi, temp.posisi)>0 && (j>=0)){
						data[j+1]=data[j];
						j--;
						data[j+1]=temp;
					}
					for(int x=0 ; x<s ; x++){
						cout << " ["<<data[x].posisi << "] ";
					}cout << endl;
				}  	
			}
			else if(sortist==4){
				cout << " PROSES INSERTION : " << endl;
				for(int x=0;x<s;x++){
					cout <<" ["<< data[x].gaji<< "] ";
				}cout << endl;
				for(int i=1; i<s; i++){
					temp = data[i];
					j=i-1;
					while((temp.gaji < data[j].gaji) && (j>=0)){
						data[j+1]=data[j];
						j--;
						data[j+1]=temp;
					}
					for(int x=0 ; x<s ; x++){
						cout << " ["<<data[x].gaji << "] ";
					}cout << endl;
				}  	
			}
	}
	fclose(dt);
	tampil(data, s);
}

void shell(){
	karyawan *data, temp;
	FILE *dt;
	dt = fopen(namafile, "rb");
	fseek(dt,0,SEEK_END);
	int s = ftell(dt)/sizeof(karyawan);
	data = (karyawan*)calloc(s, sizeof(karyawan));
	rewind(dt);
	
	int length=s;
	int i=0,d;
	int flag;
	d=length;
	flag=i;
	system("cls");
	if(dt == NULL){
		cout << "File tidak dapat dibuka!" << endl;
	}
	else{
		for(int i=0; i<s; i++){
			fread(&data[i], sizeof(karyawan),1,dt);
		}
			cout << "\t===================="<<endl;
			cout << "\t| PENGURUTAN SHELL |" <<endl;
			cout << "\t===================="<<endl;
			cout << "\t[1] ID\n\t[2] Nama\n\t[3] Posisi\n\t[4] Gaji" << endl;
			cout << "\t===================="<<endl;
			cout << " Masukkan Pilihan\t= "; cin>>sortshell;
			if(sortshell==1){
				cout << " PROSES SHELL : " << endl;
				for(int x=0;x<s;x++){
					cout <<" ["<<data[x].id<< "] ";
				}cout << endl;
				while(flag||(d>1)){
					flag=0;
					d=(d+1)/2;
					for(int i=0;i<(length-d);i++){
						if(data[i+d].id < data[i].id){
							temp=data[i+d];
						 	data[i+d]=data[i];
						 	data[i]=temp;
						 	flag=1;
						}
					}
					for(int x=0 ; x<s ; x++){
						cout<<" ["<<data[x].id<<"] ";
					}cout<<endl;
				}
			}
			else if(sortshell==2){
				cout << " PROSES SHELL : " << endl;
				for(int x=0;x<s;x++){
					cout << " ["<<data[x].nama<< "] ";
				}cout << endl;
				while(flag||(d>1)){
					flag=0;
					d=(d+1)/2;
					for(int i=0;i<(length-d);i++){
						if(strcmp(data[i].nama, data[i+d].nama)>0){
							temp=data[i+d];
						 	data[i+d]=data[i];
						 	data[i]=temp;
						 	flag=1;
						}
					}
					for(int x=0 ; x<s ; x++){
						cout<<" ["<<data[x].nama<<"] ";
					}cout<<endl;
				}
			}
			else if(sortshell==3){
				cout << " PROSES SHELL : " << endl;
				for(int x=0;x<s;x++){
					cout << " ["<< data[x].posisi<< "] ";
				}cout << endl;
				while(flag||(d>1)){
					flag=0;
					d=(d+1)/2;
					for(int i=0;i<(length-d);i++){
						if(strcmp(data[i].posisi, data[i+d].posisi)>0){
							temp=data[i+d];
						 	data[i+d]=data[i];
						 	data[i]=temp;
						 	flag=1;
						}
					}
					for(int x=0 ; x<s ; x++){
						cout<<" ["<<data[x].posisi<<"] ";
					}cout<<endl;
				}
			}
			else if(sortshell==4){
				cout << " PROSES SHELL : " << endl;
				for(int x=0;x<s;x++){
					cout << " ["<< data[x].gaji<< "] ";
				}cout << endl;
				while(flag||(d>1)){
					flag=0;
					d=(d+1)/2;
					for(int i=0;i<(length-d);i++){
						if(data[i+d].gaji < data[i].gaji){
							temp=data[i+d];
						 	data[i+d]=data[i];
						 	data[i]=temp;
						 	flag=1;
						}
					}
					for(int x=0 ; x<s ; x++){
						cout<<" ["<<data[x].gaji<<"] ";
					}cout<<endl;
				}
			}
	}
	fclose(dt);
	tampil(data, s);
}

void quick(){
	karyawan *data;
	FILE *dt;
	dt = fopen(namafile, "rb");
	fseek(dt,0,SEEK_END);
	int s = ftell(dt)/sizeof(karyawan);
	data = (karyawan*)calloc(s, sizeof(karyawan));
	rewind(dt);
	
	system("cls");
	if(dt == NULL){
		cout << "File tidak dapat dibuka!" << endl;
	}
	else{
		for(int i = 0; i < s; i++){
			fread(&data[i], sizeof(karyawan),1,dt);
		}
		 system("cls");
			cout << "\t===================="<<endl;
			cout << "\t| PENGURUTAN QUICK |" <<endl;
			cout << "\t===================="<<endl;
			cout << "\t[1] ID\n\t[2] Nama\n\t[3] Posisi\n\t[4] Gaji" << endl;
			cout << "\t===================="<<endl;
			cout << " Masukkan Pilihan\t= "; cin>>sortquick;
			cout << "\n PROSES QUICK SORT\n";
			if(sortquick==1){
				for(int p = 0; p < s; p++){
					cout << " ["<< data[p].id  << "] ";
				}cout<<endl;
			}
			else if(sortquick==2){
				for(int p = 0; p < s; p++){
					cout << " ["<< data[p].nama << "] ";
				}cout<<endl;
			}
			else if(sortquick==3){
				for(int p = 0; p < s; p++){
					cout<< " ["<< data[p].posisi<< "] ";
				}cout<<endl;
			}
			else if(sortquick==4){
				for(int p = 0; p < s; p++){
					cout<< " ["<< data[p].gaji << "] ";
				}cout<<endl;
			}
			sortingquick(data, 0, s-1, sortquick, s);
	}
	fclose(dt);
	tampil(data, s);
}

void sortingquick(karyawan *data, int low, int high, int sortquick, int s){
	karyawan temp, pivot;
	bool cek=0;
    int i = low;
    int j = high;
    pivot = data[(i + j) / 2];
	
	    if(sortquick==1){
	    	while (i <= j){
	    		cek=0;
		        while (data[i].id < pivot.id)
		            i++;
		        while (data[j].id > pivot.id)
		            j--;
		        if (i <= j){
		        	cek=1;
		            temp = data[i];
		            data[i] = data[j];
		            data[j] = temp;
		            i++;
		            j--;
		        }
		    }
		    if(cek){
		    	for(int x=0;x<s;x++){
					cout << " ["<< data[x].id << "] ";
				}cout << endl;
		    }
		}
		else if(sortquick==2){
	    	while (i <= j){
	    		cek=0;
		        while (strcmp(data[i].nama, pivot.nama)<0)
		            i++;
		        while (strcmp(data[j].nama, pivot.nama)>0)
		            j--;
		        if (i <= j){
		        	cek=1;
		            temp = data[i];
		            data[i] = data[j];
		            data[j] = temp;
		            i++;
		            j--;
		        }
		    }
		    if(cek){
		    	for(int x=0;x<s;x++){
					cout << " ["<<data[x].nama << "] ";
				}cout << endl;
		    }
		}
		else if(sortquick==3){
	    	while (i <= j){
	    		cek=0;
		        while (strcmp(data[i].posisi, pivot.posisi)<0)
		            i++;
		        while (strcmp(data[j].posisi, pivot.posisi)>0)
		            j--;
		        if (i <= j){
		        	cek=1;
		            temp = data[i];
		            data[i] = data[j];
		            data[j] = temp;
		            i++;
		            j--;
		        }
		    }
		    if(cek){
		    	for(int x=0;x<s;x++){
					cout <<" ["<< data[x].posisi << "] ";
				}cout << endl;
		    }
		}
		else if(sortquick==4){
	    	while (i <= j){
	    		cek=0;
		        while (data[i].gaji < pivot.gaji)
		            i++;
		        while (data[j].gaji > pivot.gaji)
		            j--;
		        if (i <= j){
		        	cek=1;
		            temp = data[i];
		            data[i] = data[j];
		            data[j] = temp;
		            i++;
		            j--;
		        }
		    }
		    if(cek){
		    	for(int x=0;x<s;x++){
					cout <<" ["<< data[x].gaji << "] ";
				}cout << endl;
		    }
		}
		if(j > low){
			sortingquick(data, low, j, sortquick, s);
		}
		if(i < high){
			sortingquick(data, i, high, sortquick, s);
		}
}

void sortingmerge(){
	karyawan *data;
	FILE *dt;
	dt = fopen(namafile, "rb");
	fseek(dt,0,SEEK_END);
	int s = ftell(dt)/sizeof(karyawan);
	data = (karyawan*)calloc(s, sizeof(karyawan));
	rewind(dt);

	system("cls");
	if(dt == NULL){
		cout << "File tidak dapat dibuka!" << endl;
	}
	else{
		for(int i=0; i<s; i++){
			fread(&data[i], sizeof(karyawan),1,dt);
		}
		int i = 0;
		system("cls");
		cout << "\t===================="<<endl;
		cout << "\t| PENGURUTAN MERGE |" <<endl;
		cout << "\t===================="<<endl;
		cout << "\t[1] ID\n\t[2] Nama\n\t[3] Posisi\n\t[4] Gaji" << endl;
		cout << "\t===================="<<endl;
		cout << " Masukkan Pilihan\t= "; cin>>sortmerge;
		cout << "\n PROSES MERGE SORT" << endl;
		cout << endl;
		if(sortmerge==1){
			for(int p = 0; p < s; p++){
				cout << " [" << data[p].id << "]" << " ";
			}
		}
		else if(sortmerge==2){
			for(int p = 0; p < s; p++){
				cout << " [" << data[p].nama << "]" << " ";
			}
		}
		else if(sortmerge==3){
			for(int p = 0; p < s; p++){
				cout << " [" << data[p].posisi << "]" << " ";
			}
		}
		else if(sortmerge==4){
			for(int p = 0; p < s; p++){
				cout << " [" << data[p].gaji << "]" << " ";
			}
		}
		cout << endl;
		mergesort(data, 0, s-1, sortmerge, s);
		header();
		while(i < s){
			cout << left << " " << setw(20)<< data[i].id << setw(20)<< data[i].nama << setw(20) << data[i].posisi << setw(20)<< data[i].gaji << endl;
			i++;
		}
		garis();
	}
	fclose(dt);
}

void merge(karyawan *data, int low, int mid, int up, int sortmerge, int byk){
	int x = mid - low + 1, y = up - mid;
	karyawan left[x], right[y];
	for(int i = 0; i < x; i++){
		left[i] = data[low + i];
	}
	for(int j = 0; j < y; j++){
		right[j] = data[mid + 1 + j];
	}
	int a = 0, b = 0, c = low;
	if(sortmerge == 1){
		while(a < x && b < y){
			if(left[a].id <= right[b].id){
				data[c] = left[a];
				a++;
			}else{
				data[c] = right[b];
				b++;
			}
			c++;
		}
		while(a < x){
			data[c] = left[a];
			a++;
			c++;
		}
		while(b < y){
			data[c] = right[b];
			b++;
			c++;
		}
		for(int p = 0; p < byk; p++){
			cout << " [" << data[p].id << "]" << " ";
		}
		cout << endl;
	}else if(sortmerge == 2){
		while(a < x && b < y){
			if(strcmp(left[a].nama, right[b].nama) <= 0){
				data[c] = left[a];
				a++;
			}else{
				data[c] = right[b];
				b++;
			}
			c++;
		}
		while(a < x){
			data[c] = left[a];
			a++;
			c++;
		}
		while(b < y){
			data[c] = right[b];
			b++;
			c++;
		}
		for(int p = 0; p < byk; p++){
			cout << " [" << data[p].nama << "]" << " ";
		}
		cout << endl;
	}else if(sortmerge == 3){
		while(a < x && b < y){
			if(strcmp(left[a].posisi, right[b].posisi) <= 0){
				data[c] = left[a];
				a++;
			}else{
				data[c] = right[b];
				b++;
			}
			c++;
		}
		while(a < x){
			data[c] = left[a];
			a++;
			c++;
		}
		while(b < y){
			data[c] = right[b];
			b++;
			c++;
		}
		for(int p = 0; p < byk; p++){
			cout << " [" << data[p].posisi << "]" << " ";
		}
		cout << endl;
	}else if(sortmerge == 4){
		while(a < x && b < y){
			if(left[a].gaji <= right[b].gaji){
				data[c] = left[a];
				a++;
			}else{
				data[c] = right[b];
				b++;
			}
			c++;
		}
		while(a < x){
			data[c] = left[a];
			a++;
			c++;
		}
		while(b < y){
			data[c] = right[b];
			b++;
			c++;
		}
		for(int p = 0; p < byk; p++){
			cout << " [" << data[p].gaji << "]" << " ";
		}
		cout << endl;
	}
}

void mergesort(karyawan *data, int low, int up, int sortmerge, int byk)
{	
	if(low >= up){
		return;
	}
		int mid =(low+(up-1))/2;
		mergesort(data, low, mid, sortmerge, byk);
		mergesort(data, mid+1, up, sortmerge, byk);
		merge(data, low, mid, up, sortmerge, byk);
}

void setdata(){
	system("cls");
	cout << "\t=============================="<<endl;
	cout << "\t|       SETTING DATA         |" <<endl;
	cout << "\t=============================="<<endl;
	cout << "\t[1] Sambung File\n\t[2] Edit Nama File\n\t[3] Delete File" << endl;
	cout << "\t=============================="<<endl;
	cout << " Masukkan Pilihan\t= "; cin>>menutrans;
	if(menutrans==1){
		cin.ignore();
		sambung();
	}
	else if(menutrans==2){
		cin.ignore();
		edit();
	}
	else if(menutrans==3){
		cin.ignore();
		hapus();
	}
}

void sambung(){
	karyawan data;
	char namafile1[30], namafile2[30], namafile3[30];
	FILE *dt1, *dt2, *dt3;
	system("cls");
	cout << "\t======================"<<endl;
	cout << "\t|    SAMBUNG DATA    |" <<endl;
	cout << "\t======================"<<endl;
	cout << "\t Masukkan Nama File 1\t= "; cin.getline(namafile1, 30);
	dt1 = fopen(namafile1, "rb");
	if(dt1==NULL){
		cout << "File tidak dapat dibuka" << endl;
		system("pause");
		setdata();
	}
	else{
		header();
		while(fread(&data, sizeof(karyawan), 1, dt1)==1){
			cout << left << " " << setw(20)<< data.id << setw(20)<< data.nama << setw(20) << data.posisi << setw(20)<< data.gaji << endl;
		}	
		garis();
	}
	fclose(dt1);
	cin.ignore();

	cout << "\t Masukkan Nama File 2\t= "; cin.getline(namafile2, 30);
	dt2 = fopen(namafile2, "rb");
	if(dt2==NULL){
		cout << "File tidak dapat dibuka" << endl;
		system("pause");
	}
	else{
		header();
		while(fread(&data, sizeof(karyawan), 1, dt2)==1){
			cout << left << " " << setw(20)<< data.id << setw(20)<< data.nama << setw(20) << data.posisi << setw(20)<< data.gaji << endl;
		}
		garis();
	}
	fclose(dt2);

	cout << "\t Masukkan Nama File Hasil Merging Sambung = "; cin.getline(namafile3, 30);
	dt1 = fopen(namafile1, "rb");
	dt2 = fopen(namafile2, "rb");
	dt3 = fopen(namafile3, "wb");
	if(dt3==NULL){
		cout << "File tidak dapat diciptakan" << endl;
		system("pause");
		setdata();
	}
	else{
		while(fread(&data, sizeof(karyawan),1,dt1)==1){
			fwrite(&data, sizeof(karyawan),1,dt3);
		}
		while(fread(&data, sizeof(karyawan),1,dt2)==1){
			fwrite(&data, sizeof(karyawan),1,dt3);
		}
		cout << "\n Data Berhasil Di Sambung, silakan cek di tampilan menu utama !\n\n";
	}
	fclose(dt1); fclose(dt2); fclose(dt3);
}

void edit(){
	int kode;
	char namafile1[30],namafile2[30];
	system("cls");
	cout << "\t========================"<<endl;
	cout << "\t|    EDIT NAMA FILE    |" <<endl;
	cout << "\t========================"<<endl;
	cout << "\n\tNama File yang Akan Diganti = "; cin.getline(namafile1, 30);
	cout << "\n\tNama File Baru              = "; cin.getline(namafile2, 30);
	cout << "\n";
	
			kode=rename(namafile1,namafile2);
			if (kode==0)
				cout<<" n : Data Berhasil DIEDIT ! Silahkan Cek pada Menu Output"<<endl;
				else
				cout<<" << GAGAL Mengedit >>"<<endl;
}

void hapus(){
	int kode;
	system("cls");
	cout << "\t====================="<<endl;
	cout << "\t|    DELETE FILE    |" <<endl;
	cout << "\t====================="<<endl;
	cout << "\n\tNama File yang Akan Dihapus = "; cin.getline(namafile, 30);
	cout << "\n";
	
			kode=remove(namafile);
			if (kode==0)
				cout<<" n : Data Berhasil DIHAPUS ! Silahkan Cek pada Menu Output"<<endl;
				else
				cout<<" << GAGAL Menghapus >>"<<endl;	
}

void header(){
	garis();
	cout << left << setw(20) << " ID" << setw(20) << " NAMA" << setw(20) << " POSISI" << setw(20) << " GAJI" << endl;
	garis();
}

void garis(){
	cout<<" ";
	for (int i = 0; i < 100; i++)
	{
		cout << "=";
	}
	cout << endl;
}
