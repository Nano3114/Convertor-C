/**
De Rodrigo Herlein para todos:  03:55 PM
https://www.youtube.com/watch?v=8Ib7nwc33uA&list=LL&index=1

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define Dig_Entero 10
#define Dig_Fraccion 5
#define Comando_Numero "-n"

	int equals(char*,char[]);

	void convertNumber(int*,int*,char*,int*);
	void convertToBase(int*,int*,double*,char*);
	void convertFractionInBaseDiez(int*,int*,char*,float*,int*);
	void convertFractionFromBaseDiez(int*,int*,double*,char*,int*);
	void joinResult(char*  ,char* ,int* ,int* );
	int esEntero(char);
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



	/**
	*	Convierte la parte fraccionaria de una base cualquiera[2-16] a la base 10.
	*	srcBase es un puntero a un entero el cual es el valor de la base origen
	*	dstBase es un puntero a un entero el cual es el valor de la base destino
	*	*fraction es un puntero a un double ,que es la fraccion a convertir a base
	*  outcome es un puntero al primer lugar de un arreglo de characteres
	*/
	void convertFractionInBaseDiez(int* srcBase,int* dstBase,char* fraction,float* outcome,int* show ){
		int valor;
		float aux=*outcome;
		if(*fraction!='\n'){
			valor=valorBase10(*fraction);//valor que respresenta *fraction en ese punto
			if(*(fraction+1)=='\0'){
				*outcome=(aux+valor)/(*(srcBase));
				if(*show==1)
					printf("\n(( %f + %i)/%d) = %f",aux,valor,*srcBase,*outcome);
			}
			else{
				convertFractionInBaseDiez(srcBase,dstBase,(fraction+1),outcome,show);
				*(outcome)=((*outcome)+(valor))/(*srcBase);
				if(*show==1)
					printf("\n((%f + %i)/%d) = %f",aux,valor,*srcBase,*outcome);
			}
		}
	}

	/**
	*Convierte la parte fraccionaria en base 10 a otra base entre [2,16] mediante
	*srcBase es un puntero a un entero que es nro de la base.
	*fraction es un puntero a un double ,que es la fraccion a convertir a base
	*outcome es un puntero al primer lugar de un arreglo de characteres
	*/
	void convertFractionFromBaseDiez(int* srcBase,int* dstBase,double* fraction,char* outcome,int* show){
		double valor;
		double aux,fraccionAux;
		if(*show==1)
			printf("\nConvierto fraccion %s de base %d a base %d usando el metodo de multiplicacion :",fraction,*srcBase,*dstBase);
		if(*fraction!='\0'){
			int i=0;
			fraccionAux=*fraction;
			while(i<6){
				if(*show==1)
					printf("\n %f * %i = %d ==> d(i)",fraccionAux,*(dstBase),fraccionAux*(*dstBase));
				fraccionAux=modf(fraccionAux*(*dstBase),&valor);
				convertToBase(srcBase,dstBase,&valor,outcome);
				if(*show==1)
					printf(" = %c",*outcome );
				outcome++;
				i++;
			}

		}
	}
	int esEntero(char c){
		if((c=='0')||(c=='1')||(c=='2')||(c=='3')||(c=='4')||(c=='5')||(c=='6')||(c=='7')||(c=='8')||(c=='9'))
			return 1;
		else
			return 0;

	}
	/**
	*convierte un valor numerico en base 10 entre el rango de (2-16) a el mismo valor representado en otra base
	*src es un puntero a un entero que guarda el valor de la base 10
	*dstBase es un puntero a un entero que guarda el valor de la base a convertir
	*value es un puntero a un valor numerico(double) entre (2-16) en base 10
	*outcome es puntero de char donde se guardara la conversion de value.
	*/
	void convertToBase(int* srcBase,int* dstBase,double* value,char* outcome){
		if(*(value)<=9)
			*(outcome)=*(value)+'0';
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

	void joinResult(char* entrada ,char* salida,int* lim,int* isInt){
		int i=0;
		if((*isInt)==1){
			while((*lim)<Dig_Entero && esEntero(*(entrada+(*lim)))==1){
				*(salida+*(lim))=*(entrada+*(lim));
				printf("\n el valor que he metido al arreglo es %c en pos : %i",*(salida+(*lim)),*lim);
				*(lim)=*(lim)+1;


			}
		}
		else{
			i=2;
			while((i)<Dig_Fraccion && esEntero(*(entrada+i))==1){
				*(salida+i)=*(entrada+i);
				printf("\n el valor que he metido al arreglo es %c en pos : %i",*(salida+i),*lim);
				*(lim)=*(lim)+1;
				i++;
				printf("\nvoy a impriomir toodo %s",salida);
			}
		}

	}



	/**
	*/
	int equals(char* c,char c2[]){
		if(*(c)==c2[0] && *(c+1)==c2[1])
			return 1;
		else
			return 0;
	}

	/*
    Invierte una cadena de caracteres
    ar puntero a cadena de caracteres
    puntero a entero tama�o de la cadena ar
    Retorna puntero a cadena invertida

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
	*/
	/*
    Convierte un numero entero en su respectivo en otras bases
    n entero a convertir
    retorna caracter convertido
	*/

	char valorBaseDestino (int* n){
		char* toReturn;
		toReturn=malloc(sizeof(char));
		if (*n>=0 && *n<=9){ //Si es menor a 9 le corresponde un caracter numero
			*toReturn=*n+48;
		}
		else if (*n>=10 && *n<=15){ //Si es mayor a 10 le corresponde una caracter letra
			*toReturn=*n+55;
		}
		return *toReturn;
	}
	/*
    Convierte un numero en base decimal a uno en otra base
    dstbase puntero a entero base destino
    nuu puntero a entero numero a convertir
    show puntero a entero determina si se muestra
    Retorna un puntero a cadena de caracteres
*/
	void decimalABase(int* dstBase, int* num,char* res,int* posRes, int* show){
		/**
		int size=1;
		char *numBase= malloc(sizeof(char)*size); //Alocamos el tama�o minimo de memoria
		int resto=0;
		int i=0;
		while (*num!=0){
			resto=*num%*dstBase;
			//numBase[i]=valorBaseDestino(resto);
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
		return numBase;*/
		int* resto;
		int* i;int* j;
		char* c;
		i=malloc(sizeof(int));j=malloc(sizeof(int));
		resto=malloc(sizeof(int));
		c=malloc(sizeof(char));
		while((*num)!=0){//mientras que se puede seguir dividiendo
			*(resto)=(*num)%(*dstBase);
			*(res+(*posRes))=valorBaseDestino(resto);
			if ((*show)==1){ //Si quiere mostrar el proceso
            printf("%d mod %d = %d , y Q = (%d-%d)/%d=%d\n",*num,*dstBase,*resto,*num,*resto,*dstBase,(((*num)-(*resto))/(*dstBase)));
			}
			*(num)=((*num)-(*resto))/(*dstBase);
			*(posRes)=*(posRes)+1;
		}
		//invierto la cadena
		*i=0;*j=*posRes-1;
		while((*i)<(*j)){
			*c=*(res+(*i));
			*(res+(*i))=*(res+(*j));
			*(res+(*j))=*c;
			*i=*i+1;*j=*j-1;
		}
	}

	/**
	*Convierte el numero num a la base correspondiente
	*srcBase es un puntero a un valor entero que indica la base origen
	*dstBase es un puntero a un valor entero que indica la base destino.
	*num es un puntero al lugar en memoria del primer elemento del arreglo donde se guarda el numero a convertir
	*show es un puntero a un valor que indica si mostrar o no un breve resuemen de lo que se hace en la funcion
	*/
	void convertNumber(int *srcBase,int* dstBase,char* num,int* show){
		char num_entero[10];
		char salida[16];
		char num_fraccion[6];
		int* pos;int* valueInt;int* posRes;

		pos=malloc(sizeof(int));
		valueInt=malloc(sizeof(int));
		posRes=malloc(sizeof(int));

		*pos=0;
		*posRes=0;
		while((*pos)<Dig_Entero && *(num+(*pos))!='.' && *(num+(*pos))!='\0'){
			num_entero[*pos]=*(num+(*pos));
			*(pos)=*(pos)+1;
		}
		if((*pos)<Dig_Entero){//si laparte entera no supero el limite de parte entera(10) avanzo
			num_entero[*pos]='\0';
			if(*(num+(*pos))=='\0'	|| *(num+(*pos))=='.'){//independietemente que haya terminado en cualquiera de los dos debo convertir sio si la parte entera
				if((*srcBase)==10){
					*valueInt=atoi(&(num_entero[0]));
					decimalABase(dstBase,valueInt,&(salida[0]),posRes,show);
				}
				else{

				}
			}
			printf("\nEl valor %s en base %i =es=> %s en base %i",num,*srcBase,salida,*dstBase);
		}
		else{
			printf("\nERROR_FAILURE");
		}
		/**
		int size=0,cantDigFraccion=0   ,valorEntero=0 ,lim=0, isInt=1;
		while(size<Dig_Entero && *(num+size)!='.' && *(num+size)!='\0'){
			num_entero[size]=*(num+size);
			size++;
		}
		num_entero[size]='\0';
		*/
		/**
		if(*(num+size)=='\0'	|| *(num+size)=='.'){
			//Empiezo convirtiendo la parte entera independientemente de que halla o no parte fracionaria
			if(*(srcBase)==10){
				valorEntero=atoi(&(num_entero[0]));
            char* numConvertido = decimalABase(dstBase,&valorEntero,show);
				joinResult(numConvertido,&salida[lim],&lim,&isInt);
				isInt=0;
            //printf("\nEn base %d convertido a base %d es %s",*srcBase,*dstBase,numConvertido);
			}
			else{
            int* test = baseADecimal(srcBase,&(num_entero[0]),show);
            printf("\nVoy a meter el %i al arreglo al arreglo",*(test));
            char buffer2[10];
            itoa(*test,buffer2,10);
				joinResult(&buffer2[0],&(salida[lim]),&lim,&isInt);
				isInt=0;
			}

			printf("\n lo que voy en salida es %s             ",salida);

			if(*(num+size)=='.'){
				size++;
				while(*(num+size)!='\0'){
					num_fraccion[cantDigFraccion]=*(num+size);
					size++;cantDigFraccion++;
				}
				num_fraccion[cantDigFraccion]='\0';
				if(*(srcBase)==10){
					int valorEnteroDeFraccion=atoi(&(num_fraccion[0]));
					double valorDeFraccion=(double)valorEnteroDeFraccion;
					while(cantDigFraccion!=0){
						valorDeFraccion=valorDeFraccion/10;
						cantDigFraccion--;
					}
					char* outcome=&(salida[lim]);
					convertFractionFromBaseDiez(srcBase,dstBase,&valorDeFraccion,outcome,show);
					joinResult(outcome,&(salida[lim]),&lim,&isInt);
				}
				else{
					float outcome=0;
					if(*show==1)
						printf("\nConvierto la fraccion %s de base %i a base %i ,usando el metodo de division",num_fraccion,*srcBase,*dstBase);
					convertFractionInBaseDiez(srcBase,dstBase,&(num_fraccion[0]),&outcome,show);
					char buffer[Dig_Fraccion];
					snprintf(buffer,sizeof buffer,"%f",outcome);
					printf("\n voy a meter %s al salida",buffer);
					joinResult(&(buffer[0]),&(salida[lim]),&lim,&isInt);//copnvierto float a char*

				}

			}
			char arreglo[]={'1','2','3','4','5','6','7','8','9','1','2','3','4','5','6','7','8','9'};

			printf("\nEl valor %s en base %i =es=> %s en base %i",num,*srcBase,salida,*dstBase);
			for(int i=0;i<16;i++)
							printf(" %c",salida[i]);
		}
		else
			printf("\nERROR_FAILURE");
	*/
	}

	void main(int argc, char* argv[]){
		char* num;
		int* srcBase;int* dstBase;int* show;int* help;int* i;
		char cmd[5][2]={{'-','n'},{'-','s'},{'-','d'},{'-','v'},{'-','h'}};

		num=malloc(sizeof(int)*16);
		srcBase=malloc(sizeof(int));
		dstBase=malloc(sizeof(int));
		show=malloc(sizeof(int));
		help=malloc(sizeof(int));
		i=malloc(sizeof(int));

		*srcBase=10;
		*dstBase=10;
		*show=0;
		*help=0;
		*i=1;

		while((*help)!=1 && (*i) <argc){
				if(equals(argv[*i],cmd[4])==1)
					*(help)=1;
				else
					if(equals(argv[*i],cmd[0])==1){
						*(i)=*(i)+1;
						num=argv[*i];
						*(i)=*(i)+1;
					}
					else
						if(equals(argv[*i],cmd[1])==1){
							*(i)=*(i)+1;
							if(2<=atoi(argv[*i])<=16){
								*srcBase=atoi(argv[*i]);
								*(i)=*(i)+1;
							}
							else//independientemente de que sea cualquier cosa termino de revisar las bases ya se declararon en base 10 tanto origen como destino
								*i=argc;
						}
						else
							if(equals(argv[*i],cmd[2])==1){//es -d
								*(i)=*(i)+1;
								if(2<=atoi(argv[*i])<=16){
									*dstBase=atoi(argv[*i]);
									*(i)=*(i)+1;
								}
								else
									*i=argc;
							}
							else
								if(equals(argv[*i],cmd[3])==1){
									*(show)=1;
									*(i)=*(i)+1;
								}
								else
									*(i)=*(i)+1;
		}
		if (*(help)==1){
        printf("Introduzca -n (numero) -s (base del numero n) -d (base a convertir numero n) -h (esta ayuda) -v (mostrar proceso)");
		}
		else{
			if ((num)==NULL || *(dstBase)<2 || *(dstBase)>16 || *(srcBase)<2 || *(srcBase)>16 ){
            printf("\nERROR_FAILURE");
        } else{
				convertNumber(srcBase,dstBase,num,show);
        }
		}
	}
