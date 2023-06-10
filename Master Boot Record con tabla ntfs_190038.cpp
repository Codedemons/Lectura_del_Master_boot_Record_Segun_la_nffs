//https://www.ntfs.com/partition-table.htm

//Librerias
#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <math.h>

//Lectura de Sectores para  el master boots record 
using namespace std;
short ReadSect
       (const char *_dsk,    // disco para acceder
       char *&_buff,         // b�fer donde se almacenar� el sector
       unsigned int _nsect   // n�mero de sector, comenzando con 0
       )
{
	DWORD dwRead;   
	HANDLE hDisk=CreateFile(_dsk,GENERIC_READ,FILE_SHARE_VALID_FLAGS,0,OPEN_EXISTING,0,0);
	if(hDisk==INVALID_HANDLE_VALUE) // esto puede suceder si otro programa ya est� leyendo desde el disco
    {  //ejecutar como administrador
    	puts("Error Problemas de Privilegos Acceso denegado \n");
    	CloseHandle(hDisk);
    	return 1;
    }
  	SetFilePointer(hDisk,_nsect*512,0,FILE_BEGIN); // que sector leer

  	ReadFile(hDisk,_buff,512,&dwRead,0);  // leer sector
  	CloseHandle(hDisk);
  	return 0;
}


int main()
{
	char * drv="\\\\.\\C:"; 
	char *dsk="\\\\.\\PhysicalDrive0";
	int sector=0;
	//Variables
	unsigned  char VarUno=0;
	unsigned  char Vardos = 0;
  	unsigned VarTres= 0;
  	unsigned VarF= 0;
  	int indicador = 1;
	char *buff=new char[512];
	ReadSect(dsk,buff,sector);
	//Comprueba la firma del sistema operativo
	if((unsigned char)buff[510]==0x55 && (unsigned char)buff[511]==0xaa)

  	for(int cont = 446; cont < 510; cont++){
  		
		//indicador del numero de Particiones  		
		if(cont == 446 ){
			printf(" Tabla de Particion 1 \n");
		}
		if(cont == 462 ){
			printf(" Tabla de Particion 2 \n");
		}
		if(cont == 478 ){
			printf(" Tabla de Particion 3 \n");
		}
		if(cont == 494 ){
			printf(" Tabla de Particion 4 \n");
		}
  		if(indicador == 1){
  			printf("Indicador de Arraque: ");
  			printf("%02hhx ", (unsigned char)buff[cont]);  			  			
  			
		}else if(indicador == 2){
					printf("Cabeza de partida: ");
		  			printf("%02hhx ", (unsigned char)buff[cont]);
		  			
		}else if(indicador == 3){
					unsigned VarUno = 0, i = 0;
  					double p = 0;
					unsigned dato = buff[cont];
  	
    				for (int i = 128 >> 7; i < 64; i *= 2){
    					if(dato & i){
    						VarUno += pow(2, p);
						}
						p ++;
					}
					printf("Sector Inicio: ");
					printf ("%02hhx ", (unsigned)VarUno);
					
		}else if(indicador == 4){	
		 			unsigned i = 0, VarUno = 0, Vardos = 0;
					double p = 7;
					unsigned char dato = buff[cont-1];
					unsigned char datos = buff[cont];
									  	
					for (int i = 1 << 7; i > 0; i /= 2){
						if((dato & i) && (i > 5)){
							Vardos += pow(2, p);
						}
						p --;
					}
						Vardos /= 63;		
						p = 9;
											
					for (i = 1 << 1; i > 0; i /= 2){
						if(Vardos & i){
							VarUno += pow(2, p);
						}
						p --;
					}				
					unsigned int data = datos + VarUno;
					printf("Cilindro de Arranque: ");
					printf("%03hhx ", (unsigned int)data);
		  					
		}else if(indicador == 5){
					printf("Identificacion de Sistemas: ");
			 		printf("%02hhx ", (unsigned char)buff[cont]);
		 				 		
		}else if(indicador == 6){
					printf("Cabeza Final: ");
					printf("%02hhx ", (unsigned char)buff[cont]);
		  							
		}else if(indicador == 7){
					unsigned VarUno = 0, i = 0;
  					double p = 0;
					unsigned dato = buff[cont];
  	
    				for (int i = 128 >> 7; i < 64; i *= 2){
    					if(dato & i){
    						VarUno += pow(2, p);
						}
						p ++;
					}
					printf("Sector Final: ");
		  			printf("%02hhx ", (unsigned char)VarUno);
		  								
		}else if(indicador == 8){
					unsigned i = 0, VarUno = 0, Vardos = 0;
				  	double p = 7;
				  	unsigned char dato = buff[cont-1];
				  	unsigned char datos = buff[cont];
							  	
				    for (int i = 1 << 7; i > 0; i /= 2){
					   	if((dato & i) && (i > 5)){
					   		Vardos += pow(2, p);
						}
						p --;
					}
					Vardos /= 63;		
					p = 9;
											
				    for (i = 1 << 1; i > 0; i /= 2){
				    	if(Vardos & i){
					   		VarUno += pow(2, p);
						}
						p --;
					}				
					unsigned int data = datos + VarUno;
					printf("Cilindro Final: ");
					printf("%03hhx ", (unsigned int)data);
		  									
		}else if(indicador  >=9 && indicador <= 12 ){
					printf("Sector Relativo: ");
					printf("%02hhx ", (unsigned char)buff[cont]);
		  										
		}else if(indicador  >=13 && indicador <= 16  ){
					printf("Total de Sectores: ");
					printf("%02hhx ", (unsigned char)buff[cont]);
		  										
		}
			indicador++;
  			printf("\n");
		if(indicador == 17){
		 	printf("\n\n\n");
		  	indicador = 1;  	
			VarUno=0;
			Vardos = 0;
			VarTres= 0;
			VarF= 0;
		  }		  
  	}
	printf("\n");	
	getchar();
}

