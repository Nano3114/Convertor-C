/**
De Rodrigo Herlein para todos:  03:55 PM
https://www.youtube.com/watch?v=8Ib7nwc33uA&list=LL&index=1

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define Dig_Entero 10
#define Dig_Fraccion 5

	void convertNumber(int*,int*,char*,int*,int*);
	void convertToBase(int*,int*,double*,char*);
	void convertFractionInBaseDiez(int*,int*,char*,int*);
	void convertFractionFromBaseDiez(int*,int*,double*,char*);

/*
    Invierte una cadena de caracteres
    ar puntero a cadena de caracteres
    puntero a entero tama�o de la cadena ar
    Retorna puntero a cadena invertida
*/
char* invCadena(char* ar, int* size){
    char* toReturn= malloc(sizeof(char)*(*size)); //Alocamos memoria en ejecucion , ya que , desconocemos el tama�o de la cadena.
    int s=(*size)-1;
    for (int i=0; i<*size;i++){ //Invertimos
        toReturn[i]=ar[s];
        s--;
    }
    toReturn[*size]='\0'; //A�adimos caracter nulo al final del arreglo
    return toReturn;
}

/*
    Retorna el valor del caracter en entero
    @param caracter
    @return valor entero
*/
int valorBase10(char n){
    int toReturn=(int)n;
    if (toReturn>=48 && toReturn<=57){ //sea un numero
        toReturn-=48;
    }
    else{
        if (toReturn>=65 && toReturn<=70){ //sea una letra entre A-F mayusculas
            toReturn-=55;
        } else{
            if (toReturn>=97 && toReturn<=102){ //sea una letra entre a-f minusculas
                toReturn-=87;
            }
        }
    }
    return toReturn;
}

/*
    Convierte un numero entero en su respectivo en otras bases
    n entero a convertir
    retorna caracter convertido
*/
char valorBaseDestino (int n){
    char toReturn;
    if (n>=0 && n<=9){ //Si es menor a 9 le corresponde un caracter numero
        toReturn=n+48;
    } else if (n>=10 && n<=15){ //Si es mayor a 10 le corresponde una caracter letra
        toReturn=n+55;
    }
    return toReturn;
}

/*
    Convierte una cadena de caracteres de una base a decimal
    srcBase puntero a entero base 2-16
    num puntero a cadena de caracteres correspondiente a la base
    show puntero a entero
    Retorna puntero puntero a entero convertido de base pasa por parametro a decimal
*/
int* baseADecimal(int* srcBase, char *num,int* show){
    int i=0;
    int numDecimal=0;
    int corte=strlen(num);
    int poder=corte-1;
    if (*show==1){
        printf("%s = ",num);
    }
    while (i<corte){ //Mientras haya caracteres en el arreglo de caracteres
        if (valorBase10(num[i])>=*srcBase){ //Si el numero no pertenece a la base hay un error
            printf("\nERROR_FAILURE");
            i=corte;
        }
        else{
            numDecimal+=valorBase10(num[i])*pow(*srcBase,poder); //Metodo de la multiplicacion
            if (*show==1){ //Si quiere que el usuario lo muestre
                printf("%d * %d^(%d) +",valorBase10(num[i]),*srcBase,poder);
            }
        }
        poder--;
        i++;
    }
    if (*show==1){
        printf("\n\n");
    }
    int *toReturn= malloc(sizeof(int)); //Es alocal manualmente la memoria del puntero porque sino se pierda al terminar la funcion
    *toReturn=numDecimal;
    return toReturn;
}

/*
    Convierte un numero en base decimal a uno en otra base
    dstbase puntero a entero base destino
    nuu puntero a entero numero a convertir
    show puntero a entero determina si se muestra
    Retorna un puntero a cadena de caracteres
*/
char* decimalABase(int* dstBase, int* num, int* show){
    int size=1;
    char *numBase= malloc(sizeof(char)*size); //Alocamos el tama�o minimo de memoria
    int resto=0;
    int i=0;
    while (*num!=0){ //mientras que se puede seguir dividiendo
        resto=*num%*dstBase;
        numBase[i]=valorBaseDestino(resto);
        if (*show==1){ //Si quiere mostrar el proceso
            printf("%d mod %d = %d , y Q = (%d-%d)/%d=%d\n",*num,*dstBase,resto,*num,resto,*dstBase,((*num-resto)/(*dstBase)));
        }
        if (i>=size-1){ //Si nos estamos quedando sin espacio aumentamos en uno el espacio
            numBase= realloc(numBase,sizeof(char)+1);
            size=size+1;
        }
        *num=(*num-resto)/(*dstBase);
        i++;
    }
    numBase[i]='\0'; //Agregamos el caracter para convertirlo en cadena
    numBase=invCadena(numBase,& i); //Invertimos la cadena
    if (*show==1){
        printf("\n");
    }
    return numBase;
}


void main(int argc, char* argv[])
{
    char* num=NULL;
    int srcBase=10;
    int dstBase=10;
    int show=0;
    int help=0;
    int i=1;
    while (help!=1 && i<argc){
        if (strcmp(argv[i],"-h")==0){
            help=1;
        } else{
            if (strcmp(argv[i],"-n")==0){
                i++;
                num=argv[i];
                i++;
            } else{
                if (strcmp(argv[i],"-s")==0){
                    i++;
                    if (2<=atoi(argv[i])<=16){
                    srcBase=atoi(argv[i]);
                    i++;
                    }
                    else{
                        i=argc;
                    }
                } else {
                    if (strcmp(argv[i],"-d")==0){
                        i++;
                        if (2<=atoi(argv[i])<=16){
                            dstBase=atoi(argv[i]);
                            i++;
                        }
                        else{
                            i=argc;
                        }
                    } else{
                         if (strcmp(argv[i],"-v")==0){ //Como hacer para mostrar proceso
                            show=1;
                            i++;
                        } else{
                            i++;
                        }
                    }
                }
            }
        }
    }
    if (help==1){
        printf("Introduzca -n (numero) -s (base del numero n) -d (base a convertir numero n) -h (esta ayuda) -v (mostrar proceso)");
    } else{
        if (num==NULL || dstBase<2 || dstBase>16 || srcBase<2 || srcBase>16 || strlen(num)>10){
            printf("\nERROR_FAILURE");
        } else{
				printf("voy a mostrar la conversion\n");
				convertNumber(&srcBase,&dstBase,num,&help,&show);
				/**
            //Transformacion a decimal
            printf("Numero introducido %s \n",num);
            int* test = baseADecimal(&srcBase,num,&show);

            //Transformacion desde decimal
            printf("\nEn base 10 es %d\n",*test);
            char* numConvertido = decimalABase(&dstBase,test,&show);
            printf("\nEn base %d convertido a base %d es %s",srcBase,dstBase,numConvertido);
				*/
            //Liberamos las memorias alocadas
				//free(test);
            //free(numConvertido);
        }
    }

}

	void convertNumber(int *srcBase,int* dstBase,char* num,int* help,int* show){
		char num_entero[10];
		char salida[6];
		char num_fraccion[6];
		int size=0,cantDigFraccion=0   ,valorEntero=0;

		while(size<Dig_Entero && *(num+size)!='.' && *(num+size)!='\0'){
			num_entero[size]=*(num+size);
			size++;
		}

		num_entero[size]='\0';

		if(*(num+size)=='\0'	|| *(num+size)=='.'){
			if(*(srcBase)==10){
				valorEntero=atoi(&(num_entero[0]));
            char* numConvertido = decimalABase(dstBase,&valorEntero,show);
            printf("\nEn base %d convertido a base %d es %s",*srcBase,*dstBase,numConvertido);
			}
			else{
				 //Transformacion a decimal
            printf("Numero introducido %s \n",num);
            int* test = baseADecimal(srcBase,&(num_entero[0]),show);
				printf("\nEn base %d convertido a base %d es %i",*srcBase,*dstBase,*test);
			}

			if(*(num+size)=='.'){
				size++;
				while(*(num+size)!='\0'){
					num_fraccion[cantDigFraccion]=*(num+size);
					size++;cantDigFraccion++;
				}
				num_fraccion[size]='\0';
				if(*(srcBase)==10){
					int valorEnteroDeFraccion=atoi(&(num_fraccion[0]));

					double valorDeFraccion=valorEnteroDeFraccion*pow(10,-1*cantDigFraccion);
					printf("\n le estoy pasando una fraccion que es %d :",valorDeFraccion);

					char* outcome=&(salida[0]);
					convertFractionFromBaseDiez(srcBase,dstBase,&valorDeFraccion,outcome);
					printf("\n De base %d convertido a base %d es .%s",*srcBase,*dstBase,outcome);
				}
				else{
					int* outcome=0;
					convertFractionInBaseDiez(srcBase,dstBase,&(num_fraccion[0]),outcome);
					printf("\n De base %d convertido a base %d es .%i",*srcBase,*dstBase,*outcome);

				}

			}
		}
		else
			printf("\nERROR_FAILURE");
	}

	void convertFractionInBaseDiez(int* srcBase,int* dstBase,char* fraction,int* outcome){
		int valor;
		if(*fraction!='\n'){
			valor=valorBase10(*fraction);//valor que respresenta *fraction en ese punto
			if(*(fraction+1)!='\0'){
				*(outcome)=(*(outcome)+valor)/(*(srcBase));
			}
			else{
				convertFractionInBaseDiez(srcBase,dstBase,(fraction+1),outcome);
				*(outcome)=(*(outcome)+*(fraction))/(*(srcBase));
			}
		}
	}

	void convertFractionFromBaseDiez(int* srcBase,int* dstBase,double* fraction,char* outcome){
		double valor;
		if(*fraction!='\0'){
			int i=0;
			while(i<4){
				*(fraction)=modf((*fraction)*(*dstBase),&valor);
				convertToBase(srcBase,dstBase,&valor,outcome);
				outcome++;
				i++;
			}

		}
	}

	void convertToBase(int* srcBase,int* dstBase,double* value,char* outcome){
		if(*(value)<=9)
			*(outcome)=*(value);
		else
			if(*(value)==10)
				*(outcome)='A';
			else
				if(*(value)==11)
					*(outcome)='B';
				else
					if(*(value)==12)
						*(outcome)='C';
					else
						if(*(value)==13)
							*(outcome)='D';
						else
							if(*(value)==14)
								*(outcome)='E';
							else
								if(*(value)==15)
									*(outcome)='F';
	}
