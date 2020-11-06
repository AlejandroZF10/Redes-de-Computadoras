#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char bandera[6];

int nobits(unsigned char cadena[]){
	unsigned char  i = 0, j = 0, bits = 0;
	for(i=0; i<strlen(cadena) ;i++){
		for(j=128 ; j>0 ; j=j>>1){
			if(cadena[i]&j){
				bits += 1;
				printf("1");
			}
			else
				printf("0");
		}
		printf(" ");
	}
	return bits;
}

int getbits(unsigned char cadena){
	unsigned char  i = 0, j = 0, bits = 0;
	for(j=128 ; j>0 ; j=j>>1){
		if(cadena&j)
			printf("1");
		else
			printf("0");
	}
	printf(" ");
}

int capa_uno(unsigned char trama[]){
	unsigned char i = 0;
	unsigned char size = ((trama[0]>>4)*2);
	unsigned char enruta[][10] = {"Estatic","Dinamic"};
	unsigned char idioma[][10] = {"-","-","Spanish","English","Portuguese","French","German"};

	printf("\n*************** CAPA 1 ***************\n\n");
	printf("Size: %d bytes\n",size);
	printf("Language: %s\n",idioma[(trama[i]>>1)&7]);
	printf("Routing: %s\n",enruta[trama[i]&1]);
	printf("Message: ");
	for(i=1; i<(size+1) ;i++)
		printf("%c",trama[i]);

	return size+1;
}

int capa_dos(unsigned char trama[], unsigned char size){
	unsigned char i = 0;
	unsigned char grupos[][5] = {"-","2CM7","3CM5","5CM3"};

	printf("\n\n*************** CAPA 2 ***************\n\n");
	printf("Grupo origen: %s\n",grupos[(trama[size]>>6)&3]);
	printf("Alumno origen: %d\n",trama[size++]&0x3F);
	printf("Grupo destino: %s\n",grupos[(trama[size]>>6)&3]);
	printf("Alumno destino: %d",trama[size++]&0x3F);

	return size;
}

int capa_tres(unsigned char trama[], unsigned char size){
	printf("\n\n*************** CAPA 3 ***************\n\n");
	switch((trama[size]>>7)&1){ //Control de flujo
		case 0: //Parar y esperar
			bandera[0] = 0;
			printf("Control de flujo: Parar y esperar\n");
			switch((trama[size]>>5)&3){
				case 0:
					bandera[3] = 0;
					printf("Control de error: Bit de Paridad\n");
					switch((trama[size]>>4)&1){
						case 0:	bandera[4] = 0; printf("Tipo de paridad: Paridad Par");	break;
						case 1:	bandera[4] = 1; printf("Tipo de paridad: Paridad Impar"); break;
					}
				break;
				case 1:
					bandera[3] = 1;
					printf("Control de error: CRC\n");
					switch((trama[size]>>4)&1){
						case 0:	bandera[5] = 0;	printf("Tipo de CRC: 8 bits"); size = size + 1;	break;
						case 1:	bandera[5] = 1;	printf("Tipo de CRC: 32 bits"); size = size + 4; break;
					}
				break;
				case 2:
					bandera[3] = 2;
					printf("Control de error: Checksum\n");
				break;
			}
		break;
		case 1: //Ventana deslizante
			bandera[0] = 1;
			printf("Control de flujo: Ventana deslizante\n");
			switch((trama[size]>>6)&1){
				case 0: //GoBack N
					bandera[1] = 0;
					printf("Tipo de control de flujo: GoBack N\n");
					switch((trama[size]>>5)&1){
						case 0: // 3 bits
							bandera[2] = 0;
							printf("Tipo de GoBack: 3 bits\n");
							switch((trama[size]>>0)&3){
								size = size + 1;
								case 0:
									bandera[3] = 0;
									printf("Control de error: Bit de Paridad\n");
									switch((trama[size]>>7)&1){
										case 0:	bandera[4] = 0;	printf("Tipo de paridad: Paridad Par");	break;
										case 1:	bandera[4] = 1;	printf("Tipo de paridad: Paridad Impar"); break;
									}
								break;
								case 1:
									bandera[3] = 1;
									printf("Control de error: CRC\n");
									switch((trama[size]>>7)&1){
										case 0:	bandera[5] = 0;	printf("Tipo de CRC: 8 bits"); size = size + 1;	break;
										case 1: bandera[5] = 1;	printf("Tipo de CRC: 32 bits");	size = size + 4; break;
									}
								break;
								case 2:
									bandera[3] = 2;
									printf("Control de error: Checksum\n");
								break;
							}
						break;
						case 1: // 7 bits
							bandera[2] = 1;
							printf("Tipo de GoBack: 7 bits\n");
							size = size + 1;
							switch((trama[size]>>4)&3){
								case 0:
									bandera[3] = 0;
									printf("Control de error: Bit de Paridad\n");
									switch((trama[size]>>3)&1){
										case 0:	bandera[4] = 0;	printf("Tipo de paridad: Paridad Par");	break;
										case 1:	bandera[4] = 1;	printf("Tipo de paridad: Paridad Impar"); break;
									}
								break;
								case 1:
									bandera[3] = 1;
									printf("Control de error: CRC\n");
									switch((trama[size]>>3)&1){
										case 0:	bandera[5] = 0;	printf("Tipo de CRC: 8 bits"); size = size + 1;	break;
										case 1:	bandera[5] = 1;	printf("Tipo de CRC: 32 bits");	size = size + 4; break;
									}
								break;
								case 2:
									bandera[3] = 2;
									printf("Control de error: Checksum\n");
								break;
							}
						break;
					}
				break;
				case 1: //Rechazo Selectivo
					bandera [1] = 0;
					printf("Tipo de control de flujo: Rechazo Selectivo\n");
					switch((trama[size]>>4)&3){
						case 0:
							bandera[3] = 0;
							printf("Control de error: Bit de Paridad\n");
							switch((trama[size]>>3)&1){
								case 0: bandera[4] = 0;	printf("Tipo de paridad: Paridad Par");	break;
								case 1: bandera[4] = 1; printf("Tipo de paridad: Paridad Impar");break;
							}
						break;
						case 1:
							bandera[3] = 1;
							printf("Control de error: CRC\n");
							switch((trama[size]>>3)&1){
								case 0:	bandera[5] = 0;	printf("Tipo de CRC: 8 bits");	size = size + 1; break;
								case 1:	bandera[5] = 1;	printf("Tipo de CRC: 32 bits");	size = size + 4; break;
							}
						break;
						case 2:
							bandera[3] = 2;
							printf("Control de error: Checksum");
						break;
					}
				break;
			}
		break;
	}
	return size;
}

int capa_cuatro(unsigned char trama[], unsigned char size){
	unsigned char i = 0, j = 0;
	unsigned char codigo[][10] = {"Unipolar","Polar","RZ","NRZ","RMI"};

	size = size + 1;
	printf("\n\n*************** CAPA 4 ***************\n\n");
	switch((trama[size]>>7)&1){
		case 0:
			printf("Medio de transmision: Alambrico\n");
			switch((trama[size]>>5)&3){
				case 1:
					printf("Tipo de medio de transmision: FO\n");
				break;
				case 2:
					printf("Tipo de medio de transmision: Coaxial\n");
				break;
				case 3:
					printf("Tipo de medio de transmision: UTP\n");
				break;
			}
		break;
		case 1:
			printf("Medio de transmision: inalambrico\n");
			switch((trama[size]>>5)&3){
				case 0:
					printf("Tipo de medio de transmision: Infrarrojo\n");
				break;
				case 2:
					printf("Tipo de medio de transmision: WiFi\n");
				break;
				case 3:
					printf("Tipo de medio de transmision: NFC\n");
				break;
			}
		break;
	}
	for(j=16 ; j>0 ; j=j>>1){
		if((trama[size]&31)&j)
			printf("Codigo de linea: %s\n",codigo[i++]);
		else
			i = i + 1;
	}
	
}

int main(void){
	unsigned char cadena[100];
	unsigned char i = 0, aux = 0, size = 0, repeat = 0;
	unsigned char trama[] = {0x7B,0x69,0x6C,0x20,0x79,0x20,0x61,0x20,0x64,0x74,0x20,0x76,0x65,0x6E,0x74,0xCF,0x9A,0xA0,0x00,0x21};

	size = capa_uno(trama);
	size = capa_dos(trama,size);
	size = capa_tres(trama,size);
	size = capa_cuatro(trama,size);
	return 0;
}