#include <stdio.h>
#include <stdlib.h>

void imprimir_ip(unsigned char ip[]){
	char i = 0;
	printf("%d",ip[i]);
	for(i=1; i<4 ;i++)
		printf(".%d",ip[i]);
}

char tipo_clase(unsigned char ip[]){
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

void tipo_ip(unsigned char ip[]){
	switch(tipo_clase(ip)){
		case 1:
			 if(ip[1]==0 && ip[2]==0 && ip[3]==0)
			 	printf("IP DE TIPO RED");
			 else if(ip[1]==255 && ip[2]==255 && ip[3]==255)
			 	printf("IP DE TIPO BROADCAST");
			 else
			 	printf("IP DE TIPO HOST");
		break;
		case 2:
			if(ip[2]==0 && ip[3]==0)
				printf("IP DE TIPO RED");
			else if(ip[2]==255 && ip[3]==255)
				printf("IP DE TIPO BROADCAST");
			else
				printf("IP DE TIPO HOST");
		break;
		case 3:
			if(ip[3]==0)
				printf("IP DE TIPO RED");
			else if(ip[3]==255)
				printf("IP DE TIPO BROADCAST");
			else 
				printf("IP DE TIPO HOST");
		break;
		default:
			break;
	}
}


int main(void){
	
	unsigned char i = 0, j = 0, k = 0, flag= 0, repeat = 0;
	do{
		fflush(stdin);
		unsigned char ip[4] = {};
		unsigned char masc[4] = {};
		unsigned short int aux[4] = {};
		printf("Validacion IP - Alejandro Zepeda\nEscribe una IP: ");
		scanf("%d.%d.%d.%d",&aux[0],&aux[1],&aux[2],&aux[3]);
		for(i = 0; i < 4; i++){
			if(aux[i]<=255){
				ip[i]=aux[i];
			}
			else{
				printf("Direccion IP invalida\n"); 
				flag = 1;
			}
		}
		if(flag == 0){
			switch(tipo_clase(ip)){
				case 1:
					printf("\nIP DE CLASE A\n"); tipo_ip(ip);
					masc[0] = 255; masc[1] = 0; masc[2] = 0; masc[3] = 0;
	    			printf("\nMASCARA: ");
					for(i = 0; i < 4; ++i)
						printf("%d.",masc[i]); i = 0; 
			    	printf("\nIP MADRE: ");
					for(i = 0; i < 4; ++i)
						printf("%d.",ip[i]&masc[i]);
			    	for(j = 0; j < 4; ++j)
			    		masc[j]=~masc[j];
			    	printf("\nIP BROADCAST: ");
			    	for(k = 0; k < 4; ++k)
			    		printf("%d.", ip[k]|masc[k]);
			    	for(j = 0; j < 4; ++j)
			    		masc[j]=~masc[j];
			       	printf("\nRANGO DE HOST: %u.%u.%u.%u a", ip[0]&masc[0],ip[1]&masc[1],ip[2]&masc[2],(ip[3]&masc[3])+1);
			    	for(i = 0; i<4; i++)
			    		masc[i]=~masc[i];
			    	printf(" %u.%u.%u.%u\n", ip[0]|masc[0],ip[1]|masc[1],ip[2]|masc[2],(ip[3]|masc[3])-1);
				break;
				case 2:
					printf("\nIP DE CLASE B\n"); tipo_ip(ip);
					masc[0] = 255; masc[1] = 255; masc[2] = 0; masc[3] = 0;
		            printf("\nMASCARA: ");
					for(i = 0; i < 4; ++i)
						printf("%d.",masc[i]);i = 0;   
					printf("\nIP MADRE: ");
		    		for(i = 0; i < 4; ++i)
		    			printf("%d.",ip[i]&masc[i]);
					for(j = 0; j < 4; ++j)
						masc[j]=~masc[j];
		    		printf("\nIP BROADCAST: ");
					for(k = 0; k < 4; ++k)
						printf("%d.", ip[k]|masc[k]);
					for(j = 0; j < 4; ++j){masc[j]=~masc[j];}
		       		printf("\nRANGO DE HOST: %u.%u.%u.%u a", ip[0]&masc[0],ip[1]&masc[1],ip[2]&masc[2],(ip[3]&masc[3])+1);
		    		for(i = 0; i<4; i++)
		    			masc[i]=~masc[i];
		    		printf(" %u.%u.%u.%u\n", ip[0]|masc[0],ip[1]|masc[1],ip[2]|masc[2],(ip[3]|masc[3])-1);
				break;
				case 3:
					printf("\nIP DE CLASE C\n"); tipo_ip(ip);
					masc[0] = 255; masc[1] = 255; masc[2] = 255; masc[3] = 0;
	                printf("\nMASCARA: ");
					for(i = 0; i < 4; ++i)
						printf("%d.",masc[i]); i = 0;
					printf("\nIP MADRE: ");
					for(i = 0; i < 4; ++i)
						printf("%d.",ip[i]&masc[i]);
					for(j = 0; j < 4; ++j)
						masc[j]=~masc[j];
	    			printf("\nIP BROADCAST: ");
	    			for(k = 0; k < 4; ++k)
	    				printf("%d.", ip[k]|masc[k]);
	    			for (j = 0; j < 4; ++j)
	    				masc[j]=~masc[j];
	       			printf("\nRANGO DE HOST: %u.%u.%u.%u a", ip[0]&masc[0],ip[1]&masc[1],ip[2]&masc[2],(ip[3]&masc[3])+1);
	    			for(i = 0; i<4; i++)
	    				masc[i]=~masc[i];
	    			printf(" %u.%u.%u.%u\n", ip[0]|masc[0],ip[1]|masc[1],ip[2]|masc[2],(ip[3]|masc[3])-1);
				break;
				case 4:
					printf("\nIP DE CLASE D");
					printf("\nUSO: MULTICAST\n");
				break;
				case 5:
					printf("\nIP DE CLASE E");
					printf("\nUSO: EXPERIMENTAL\n");
				break;
			}
		}
		printf("\nDesea ingresar otra IP? SI(1) NO(2)  "); 
		scanf("%d",&repeat);printf("\n");
	}while(repeat == 1);
	return 0;
}