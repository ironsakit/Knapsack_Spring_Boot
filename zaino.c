#include <stdio.h>
#include <stdlib.h>

int max(int a, int b){
  return (a > b)? a : b;
}

int main(int argc, char *argv[]){

  /* CONTROLLO ERRORE */
  if(argc < 3){
    printf("ERRORE 1: numero di parametri insufficiente...\n");
    exit(1);
  }

  int CAPACITY = atoi(argv[1]);
  int NUM_ITEM = atoi(argv[2]);

  int v[NUM_ITEM];  // Valori
  int w[NUM_ITEM];  // Pesi
  int item_selected[NUM_ITEM];

  for(int i = 0; i < NUM_ITEM; i++) v[i] = atoi(argv[3 + i]);
  for(int i = 0; i < NUM_ITEM; i++) w[i] = atoi(argv[3 + NUM_ITEM + i]);
  for(int i = 0; i < NUM_ITEM; i++) item_selected[i] = 0;
  
  int valore, peso;

  int DP[NUM_ITEM + 1][CAPACITY + 1];  // Creo la mia tabella dei valori

  for(int item = 0; item <= NUM_ITEM; item++){
    for(int capacita = 0; capacita <= CAPACITY; capacita++){
      
      /* CASO BASE */
      if(item == 0 || capacita == 0){
	DP[item][capacita] = 0;  // Filliamo di zeri la prima riga e prima colonna
      }else{
	
	if(w[item-1] > capacita){  // Se il peso dell'item è maggiore della capacità dello zaino allora prendo il valore sopra (alla riga precedente) 
	  DP[item][capacita] = DP[item - 1][capacita];
	}else{ // invece se l'item può entrare nello zaino, valuto se ha senso metterlo oppure no
	  valore = v[item - 1];
	  peso = w[item - 1];
	  // Calcolo il miglior valore scegliendo la scorsa combinazione oppure con il valore che ho + un item che posso mettere che riesce ad entrare
	  DP[item][capacita] = max(DP[item - 1][capacita], DP[item - 1][capacita - peso] + valore);
	}
 
      }
    }
  }
 
  printf("La migliore combinazione e' %d\n", DP[NUM_ITEM][CAPACITY]);

  int counter = 0;
  int capacita = CAPACITY;
  for(int item = NUM_ITEM; item > 0 && capacita > 0; item--){
    if(DP[item][capacita] != DP[item-1][capacita]){
      item_selected[counter] = item - 1;
      counter++;
      capacita-= w[item - 1];
    }
  }
  
  printf("\nData dagli elementi: \n");
  for(int item = 0; item < counter; item++){
    printf("%d -> valore: %d -> peso: %d\n", item_selected[item], v[item_selected[item]], w[item_selected[item]]);
  }

  return 0;
}
