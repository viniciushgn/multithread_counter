/* Contador de palavras
 *
 * Este programa recebera uma serie de caracteres representando palavras em sua
 * entrada. Ao receber um caractere fim de linha ('\n'), deve imprimir na tela o
 * numero de palavras separadas que recebeu e, apos, encerrar.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#define MAX_NUM 100

//init variaveis----------------------------------------------------------------
int numero_elementos; //numero de elementos a ser processado
int numero_primos; //numero de primos achados entre os elementos
long long unsigned int lista[MAX_NUM]; //lista contendo elementos com primos
pthread_mutex_t trava; //mutex limitando escrita na memoria compartilhada para
//uma thread por vez
//------------------------------------------------------------------------------




//TESTE_PRIMO--------------------------WORKING----------------------------------
int isPrime(long long unsigned int number){
long long unsigned int i = 2;

if(number == 0 | number == 1){ //1 e 0 nao sao primos nem sao divisores validos
  return 0;
}

while ( i < number){ //testando todos os valores complexidade O(n)
  if(number%i == 0){
    return 0;
  }
  i++;
}
return 1;
}
//------------------------------------------------------------------------------



//--LER TECLADO E DEFINIR VARIAVEIS UNIVERSAIS----------------------------------
void readDeclareVector (void){

// Ler teclado---------------------
unsigned long long int triagem[MAX_NUM];
char lixo;
unsigned int i;
i = 0;
while(lixo != '\n'){
scanf("%llu", &triagem[i]);
lixo = getchar();
i++;
}
//--Definir variaveis---------------
(numero_elementos)=i;//numero de elementos a processar

for(unsigned int k = 0; k < i; k++)
{
  lista[k] = triagem[k];//lista de numeros recebidos
}

(numero_primos)=0;//inicializando variavel global do contador de primos
}
//------------------------------------------------------------------------------


//-----PROCESSAMENTO------------------------------------------------------------
void* proc(void* arg){

//para separar a tarefa entre threads, podemos dividir as tarefas a partir de
//multiplos percorrendo o vetor de elementos
//ex:.  proc 1 -> [>0,1,2,3,>4,5,6,7,>8,9]
//arg: endereco do identificador da thread (1,2,3 ou 4)
int *N = (int*)(arg);
int id = (*N);//identificador de thread


for(int g = 0; (id+g*4) < (numero_elementos); g++){
if (  isPrime(lista[id + g*4])  ){
pthread_mutex_lock(&trava);//trava mutex impede escrita simultânea entre threads
  (numero_primos)++;
pthread_mutex_unlock(&trava);
}
}

return NULL;
}
//------------------------------------------------------------------------------





int main(int argc, char **argv) {
  readDeclareVector();
//-------------------------------- CALCULANDO NUMERO DE THREADS-----------------
  int n_threads = 0;
  if((numero_elementos) >3){
    n_threads = 4;
  }
  else{
    n_threads = (numero_elementos);
  }
//--------------------------------- CRIANDO THREADS E DEFININDO IDS-------------

pthread_t threads[n_threads];
int thread_id[n_threads];
for (int i=0; i<n_threads; i++)
  {thread_id[i] = i;}
//---------------------------------DISPARANDO THREADS---------------------------
for (int i=0; i<n_threads; i++) {
  pthread_create(&(threads[i]), NULL, proc, (void*) (&thread_id[i]));
}
//-------------------------------- ESPERANDO THREADS----------------------------
for (int i=0; i<n_threads; i++) {
  pthread_join(threads[i], NULL);
}
//-------------------------------IMPRIMINDO VARIAVEL UNIVERSAL------------------
printf("%d\n",(numero_primos) );
  return 0;
}
