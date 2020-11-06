#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void imprime(unsigned char IP[], unsigned char MRSR[]);
void imprimeB(unsigned char IP[]);
void imprimeA(unsigned char IP[]);
int tipo_clase(unsigned char ip[]);
int validar_ip(unsigned int ip[]);

unsigned int ark; char val;
unsigned char IP[4], MR[4], MRSR[4], MaskP;
int i, option, repeat, noRedes, bitP, bitH, noHost, * ip;

int main(void){
	do{
		system("cls");
		ip = (int *)malloc(sizeof(int)*4);
		printf("Practica 2 - Alejandro Zepeda Flores\n");
		printf("Introduzca una direccion IP: "),
		scanf("%d.%d.%d.%d", &ip[0], &ip[1], &ip[2], &ip[3]);
		if(validar_ip(ip)){
			free(ip);
			printf("\n1-. Definir #SR\n2-. Definir #Host/SR\n3-. Mascara personalizada\n");
			printf("Opcion: "); scanf("%d", &option);
			switch(tipo_clase(IP)){
				case 1:
					printf("\nClase A\n");
					printf("Mascara de Red: 255.0.0.0\n");
					MR[1]=MR[2]=MR[3]=MRSR[1]=MRSR[2]=MRSR[3]=0;
					MR[0]=MRSR[0]=255;
					switch(option){
						case 1:
							i = 1;
							while(i!=0){
								printf("Cantidad de Subredes:");
								scanf("%d", &noRedes);
								if(noRedes<2 || noRedes>4194304)
									printf("Numero de redes invalido\n" );
								else
								  i = 0;
							}
							bitP = 1;
							while(pow(2,bitP)<noRedes)
								bitP++;
							printf("Bits Prestado: %d\n", bitP );
							printf("Bits de Host: %d\n", 24-bitP );
							noHost = pow(2,24-bitP);
							printf("No. de Host: %d\n", noHost-2 );
							imprimeA(IP);
						break;
						case 2:
							i = 1;
							while(i!=0){
								printf("Numero de Host");
								scanf("%d", &noHost);
								if(noHost<2 || noHost>8388608)
										printf("Numero de Host invalid\n" );
								else
									i=0;
							}
							bitH = 1;
							while(pow(2,bitH)<(noHost+2))
								bitH++;
							bitP = 24-bitH;
							noHost = pow(2,24-bitP);
							printf("Bits Prestado: %d\n", bitP );
							printf("Bits de Host: %d\n", bitH );
							noRedes = pow(2,bitP);
							printf("No. de Subredes: %d\n", noRedes );
							imprimeA(IP);	
						break;
						case 3:
							i = 1;
							while(i!=0){
								printf("Mascara personalizada\n");
								printf("%d.%d.%d.%d/", IP[0], IP[1], IP[2], IP[3]);
								scanf("%d", &MaskP);
								if(MaskP<8 || MaskP>30)
									printf("Mascara invalida\n" );
								else
									i = 0;
							}
							printf("La red es %d.%d.%d.%d/%d \n", IP[0], IP[1], IP[2], IP[3], MaskP);
							bitH = 32-MaskP;
							bitP = 24-bitH;
							printf("Bits Prestado: %d\n", bitP );
							printf("Bits de Host: %d\n", bitH );
							noRedes = pow(2,bitP);
							printf("No. de Subredes: %d\n", noRedes );
							noHost=pow(2,24-bitP);
							printf("No. de Host: %d\n", noHost-2 );
							imprimeA(IP);
						break;
					} 
				break;
				case 2:
					printf("\nClase B\n");// INICIO CLASE B
					printf("Mascara de Red: 255.255.0.0\n");
					MR[2]=MR[3]=MRSR[2]=MRSR[3]=0;
					MR[0]=MR[1]=MRSR[0]=MRSR[1]=255;
					switch(option){
						case 1:
							i = 1;
							while(i!=0){
								printf("Cantidad de subredes: ");
								scanf("%d", &noRedes);
								if(noRedes<2 || noRedes>16384)
									printf("Numero de redes invalido\n" );
								else  
									i = 0;
							}
							bitP = 1;
							while(pow(2,bitP)<noRedes)
								bitP++;
							printf("Bits Prestado: %d\n", bitP );
							printf("Bits de Host: %d\n", 16-bitP );
							noHost = pow(2,16-bitP);
							printf("No. de Host: %d\n", noHost-2 );
							imprimeB(IP);
						break;
						case 2:
							i = 1;
							while(i!=0){
								printf("Numero de Host: ");
								scanf("%d", &noHost);
								if(noHost<2 || noHost>32768)
									printf("Numero de Host invalido\n" );
								else  
									i = 0;
							}
							bitH = 1;
							while(pow(2,bitH)<(noHost+2))
								bitH++;
							bitP = 16-bitH;
							noHost = pow(2,16-bitP);
							printf("Bits Prestado: %d\n", bitP );
							printf("Bits de Host: %d\n", bitH );
							noRedes = pow(2,bitP);
							printf("No. de Subredes: %d\n", noRedes );
							imprimeB(IP);
						break;
						case 3:
							i = 1;
							while(i!=0){
								printf("Mascara personalizada\n");
								printf("%d.%d.%d.%d/", IP[0], IP[1], IP[2], IP[3]);
								scanf("%d", &MaskP);
								if(MaskP<16 || MaskP>30)
									printf("Mascara invalida\n" );
								else
									i = 0;
							}
							printf("La red es %d.%d.%d.%d/%d \n", IP[0], IP[1], IP[2], IP[3], MaskP);
							bitH = 32-MaskP;
							bitP = 16-bitH;
							printf("Bits Prestado: %d\n", bitP );
							printf("Bits de Host: %d\n", bitH );
							noRedes = pow(2,bitP);
							printf("No. de Subredes: %d\n", noRedes );
							noHost = pow(2,16-bitP);
							printf("No. de Host: %d\n", noHost-2 );
							imprimeB(IP);
						break;
					}
				break;
				case 3:
					printf("\nClase C\n");// INICIO CLASE C
					printf("Mascara de Red: 255.255.255.0\n");
					MR[0]=MR[1]=MR[2]=MRSR[0]=MRSR[1]=MRSR[2]=255; MR[3]=0;
					switch(option){
						case 1:
							i = 1;
							while(i != 0){
								printf("Cantidad de subredes: "); scanf("%d", &noRedes);
								if(noRedes<2 || noRedes>64)
									printf("Numero de subredes invalido\n");
								else  
									i = 0;
							}
							bitP = 1;
							while(pow(2,bitP)<noRedes)
								bitP++;
							printf("Bits Prestado: %d\n", bitP);
							printf("Bits de Host: %d\n", 8-bitP);
							noHost = pow(2,8-bitP);
							printf("No. de Host: %d\n", noHost-2);
							MRSR[3] = (255-noHost)+1;
							imprime(IP,MRSR);
						break;
						case 2:
							i = 1;
							while(i!=0){
								printf("Numero de Host: ");
								scanf("%d", &noHost);
								if(noHost<2 || noHost>124)
									printf("Numero de Host invalido\n");
								else  
									i = 0;
							}
							bitH = 1;
							while(pow(2,bitH)<(noHost+2))
								bitH++;
							bitP = 8-bitH;
							noHost = pow(2,8-bitP);
							printf("Bits Prestado: %d\n", bitP);
							printf("Bits de Host: %d\n", bitH);
							noRedes = pow(2,bitP);
							printf("No. de Subredes: %d\n", noRedes);
							MRSR[3] = (255-noHost)+1;
							imprime(IP,MRSR);
						break;
						case 3:
							i=1;
							while(i!=0){
								printf("Mascara personalizada\n");
								printf("%d.%d.%d.%d/", IP[0], IP[1], IP[2], IP[3]);
								scanf("%d", &MaskP);
								if(MaskP<24 || MaskP>30)
									printf("Mascara invalida\n" );
								else 
									i = 0;
							}
							printf("La red es %d.%d.%d.%d/%d \n", IP[0], IP[1], IP[2], IP[3], MaskP);
							bitH = 32-MaskP;
							bitP = 8-bitH;
							bitP = 8-bitH;
							printf("Bits Prestado: %d\n", bitP );
							printf("Bits de Host: %d\n", bitH );
							noRedes = pow(2,bitP);
							printf("No. de Subredes: %d\n", noRedes );
							noHost = pow(2,8-bitP);
							MRSR[3] = (255-noHost)+1;
							printf("No. de Host: %d\n", noHost-2 );
							imprime(IP,MRSR);
						break;
					}
				break;
				case 4:
					printf("\nIP de clase D\n");
				break;
				case 5:
					printf("\nIP de clase E\n");
				break;
			}
		}
		else
			printf("\nDireccion IP invalida\n");
		printf("\n\nDesea repetir el programa? SI(1)   NO(2)\n");
		printf("Opcion: "); scanf("%d",&repeat);
		system("cls");
	}while(repeat == 1);
	return 0;
}

void imprime(unsigned char IP[], unsigned char MRSR[]){
	printf("La mascara de SubRed es %d.%d.%d.%d \n", MRSR[0], MRSR[1], MRSR[2], MRSR [3]);
	printf("La red es %d.%d.%d.%d/%d \n", IP[0], IP[1], IP[2], IP[3], 24+bitP);
	for(i=0;i<pow(2,bitP);i++){
		printf("%d | %d.%d.%d.%d   | ", i, IP[0], IP[1], IP[2], IP[3]+(noHost*i) );
		printf(" %d.%d.%d.%d    ", IP[0], IP[1], IP[2], (IP[3]+(noHost*i))+1 );
		printf("hasta %d.%d.%d.%d   | ", IP[0], IP[1], IP[2], (IP[3]+(noHost*i) + (noHost-1))-1 );
		printf(" %d.%d.%d.%d  | ", IP[0], IP[1], IP[2], IP[3]+(noHost*i) + (noHost-1));
		printf("\n");
	}
}

void imprimeB(unsigned char IP[]){
	ark=((pow(2,16-bitP))-1);
	MRSR[2] = ( (~ark)>>8) &255;
	MRSR[3] =  (~ark) & 255;
	printf("La mascara de SubRed es %d.%d.%d.%d \n", MRSR[0], MRSR[1], MRSR[2], MRSR [3]);
	printf("La red es %d.%d.%d.%d/%d \n", IP[0], IP[1], IP[2], IP[3], 16+bitP);
	ark=0;
	for(i=0;i<pow(2,bitP);i++){
		printf("%d | %d.%d.%d.%d | ", i, IP[0], IP[1], IP[2], IP[3]);
		printf(" %d.%d.%d.%d  ", IP[0], IP[1], IP[2], IP[3] +1 );
		ark= (noHost*i)+(noHost-1);
		IP[3]=ark & 255;
		IP[2]=(ark>>8) & 255;
		printf("hasta  %d.%d.%d.%d  | ", IP[0], IP[1], IP[2], (IP[3])-1 );
		printf(" %d.%d.%d.%d | ", IP[0], IP[1], IP[2] , IP[3] );
		printf("\n");
		ark= (noHost*i)+(noHost-1)+1;
		IP[3]=(ark & 255);
		IP[2]=(ark>>8) & 255;
	}
}

void imprimeA(unsigned char IP[]){
	ark=((pow(2,24-bitP))-1);
	MRSR[1] = ( (~ark)>>16) &255;
	MRSR[2] = ( (~ark)>>8) &255;
	MRSR[3] =  (~ark) & 255;
	printf("La mascara de SubRed es %d.%d.%d.%d \n", MRSR[0], MRSR[1], MRSR[2], MRSR [3]);
	printf("La red es %d.%d.%d.%d/%d \n", IP[0], IP[1], IP[2], IP[3], 8+bitP);
	ark=0;
	for(i=0;i<pow(2,bitP);i++){
		printf("%d | %d.%d.%d.%d | ", i, IP[0], IP[1], IP[2], IP[3]);
		printf(" %d.%d.%d.%d  ", IP[0], IP[1], IP[2], IP[3] +1 );
		ark= (noHost*i)+(noHost-1);
		IP[3]=ark & 255;
		IP[2]=(ark>>8) & 255;
		IP[1]=(ark>>16) & 255;
		printf("hasta  %d.%d.%d.%d  | ", IP[0], IP[1], IP[2], (IP[3])-1 );
		printf(" %d.%d.%d.%d | ", IP[0], IP[1], IP[2] , IP[3] );
		printf("\n");
		ark = (noHost*i)+(noHost-1)+1;
		IP[3]=(ark & 255);
		IP[2]=(ark>>8) & 255;
		IP[1]=(ark>>16) & 255;
	}
}

int tipo_clase(unsigned char ip[]){
	if(ip[0]&128)
		if(ip[0]&64)
			if(ip[0]&32)
				if(ip[0]&16)
					return 5; //CLASE E
				else
					return 4; //CLASE D
			else
				return 3; //CLASE C
		else
			return 2; //CLASE B
	else
		return 1; //CLASE A
}

int validar_ip(unsigned int ip[]){
	int i = 0;

	for(i = 0; i < 4; i++){
		if(ip[i]<=255)
			IP[i] = ip[i];
		else
			return 0;
	}
	return 1;
}