#include "hospital_list.h"
#include <stdlib.h>

// Struct que repesenta o no da lista, contendo o ID, as posicoes antiga e atual e um ponteiro para o proximo elemento da lista
struct node{
	int ID;
	int old_position;
	int cur_position;
	struct node *next;
};

// Struct que representa a lista em si, contendo um ponteiro para a sentinela, um para o ultimo no e o tamanho da lista
struct list{
	struct node *sentry;
	struct node *last;
	int size;
};

/*------------------------------------------------------------------------------------------------------------
   create_node()
        Funcao que cria um no da lista com o id e as posicoes passados como parametro, retornando NULL caso o
	processo de criacao nao seja bem sucedido. O no criado sempre aponta para si mesmo inicialmente
        - Parametros
          int : id do elemento a ser criado
          int : posicao (antiga e atual) do elemento a ser criado
        - Retorno
          NODE* : endereco do no criado
*/
NODE *create_node(int id, int pos){
	NODE *node = (NODE*)malloc(sizeof(NODE));

	if(node != NULL){
		node->ID = id;
		node->old_position = pos;
		node->cur_position = pos;
		node->next = node;
	}

	return node;
}

/*------------------------------------------------------------------------------------------------------------
   delete_node()
        Funcao que deleta um no cujo endereco eh passado como parametro, liberando a memoria alocada e fazendo
	o ponteiro apontar para NULL
        - Parametros
          NODE** : endereco do no a ser deletado
        - Retorno
          int : 0 - falha; 1 - sucesso;
*/
int delete_node(NODE **node){
	if(node != NULL && (*node) != NULL){
		free(*node);
		(*node) = NULL;
		return 1;
	}
	return 0;
}

/*------------------------------------------------------------------------------------------------------------
   create_list()
        Funcao que cria uma lista que inicialmente possui apenas o no sentinela ou no cabeca apontando para si
	mesmo, retornando NULL quando houver erro na criacao
        - Parametros
          void
        - Retorno
          LIST* : lista criada
*/
LIST *create_list(void){
	LIST *list = (LIST*)malloc(sizeof(LIST));

	if(list != NULL){
		NODE *sentry = create_node(-1, -1);
		if(sentry != NULL){
			list->sentry = sentry;
			list->last = sentry;
			list->size = 0;
		}else{
			free(list);
			list = NULL;
		}
	}

	return list;
}

/*------------------------------------------------------------------------------------------------------------
   insert_end()
        Funcao que cria um novo no com o id passado e o insere no final da lista, salvando sua posicao de acordo
	com o tamanho atual da lista
        - Parametros
          LIST* : lista
	  int   : id do no a ser adicionado
        - Retorno
          int : 0 - falha; 1 - sucesso;
*/
int insert_end(LIST *list, int id){
	if(list != NULL){
		NODE *new_node = create_node(id, list->size + 1);
		if(new_node != NULL){
			list->last->next = new_node;
			new_node->next = list->sentry;
			list->last = new_node;
			list->size++;

			return 1;
		}
	}

	return 0;
}

/*------------------------------------------------------------------------------------------------------------
   remove_end()
        Funcao que remove um no do final da lista e o apaga utilizando a funcao delete_node()
        - Parametros
          LIST* : lista
        - Retorno
          int : 0 - falha; 1 - sucesso;
*/
int remove_end(LIST *list){
	if(list != NULL && list->size > 0){
		NODE *aux = list->sentry;
		// Procura o penultimo no da lista
		while(aux->next != list->last) aux = aux->next;
		// Faz com que o penultimo no passe a ser o ultimo e deleta o que antes era o ultimo
		aux->next = list->sentry;
		delete_node(&list->last);
		list->last = aux;
		list->size--;

		return 1;
	}

	return 0;
}

/*------------------------------------------------------------------------------------------------------------
   get_node()
        Funcao que percorre a lista a procura do no na posicao desejada e retorna esse no quando for encontrado,
	retornando NULL caso n tenha sido possivel encontra-lo ou busca-lo
        - Parametros
          LIST* : lista
	  int   : posicao desejada para busca
        - Retorno
          NODE* : no encontrado
*/
NODE *get_node(LIST *list, int position){
	NODE *aux = NULL;
	if(list != NULL){
		// A sentinela recebe o valor da busca para ser a condicao de parada
		list->sentry->cur_position = position;
		aux = list->sentry->next;
		// A variavel aux percorre a lista a procura da posicao
		while(aux->cur_position != position) aux = aux->next;
		// Se aux == list->sentry, a posicao desejada n foi encontrada
		if(aux == list->sentry) aux = NULL;
		// O valor da sentinela volta ao original
		list->sentry->cur_position = -1;
	}

	return aux;
}

/*------------------------------------------------------------------------------------------------------------
   is_special_node()
       Funcao que analisa o ID de um node e retorna se ele eh ou nao um no representando usuario especial
        - Parametros
          NODE* : no analisado
        - Retorno
          int : 1 - positivo; 0 - negativo ou no invalido;
*/
int is_special_user(NODE *node){
	if(node != NULL){
		if(node->ID >= 60) return 1;
	}
	return 0;
}

/*------------------------------------------------------------------------------------------------------------
   delete_list()
        Funcao que utiliza a funcao remove_end para deletar todos os nos da lista menos a sentinela, depois
	deleta a sentinela, libera a memoria alocada pela lista e faz com que o ponteiro aponte para NULL, o
	que indica lista nao criada
        - Parametros
          LIST** : endereco da lista a ser apagada
        - Retorno
          void
*/
void delete_list(LIST **list){
	if(list != NULL && (*list) != NULL){
		// Enquanto n houver so a sentinela(list->size == 0), remove do fim
		while((*list)->size > 0) remove_end(*list);
		delete_node( &((*list)->sentry) );
		free(*list);
		(*list) = NULL;
	}
}

/*------------------------------------------------------------------------------------------------------------
   print_list()
        Funcao que percorre a lista imprimindo as posicoes antiga e atual de cada no
        - Parametros
          LIST* : lista
        - Retorno
          void
*/
void print_list(LIST *list){
	if(list != NULL){
		int i;
		NODE *aux;

		/*
		A cada iteracao do for, a funcao get_node e chamada e seu resultado eh armazenado na variavel aux. A funcao eh chamada com a variavel
		i sendo passada com parametro, o que faz com que a cada iteracao do for a funcao get_node procure a proxima posicao da lista. Caso o
		fim da lista seja atingido, a posicao desejada nao sera encontrada e o retorno da funcao sera NULL, fazendo com que saia do loop
		*/
		for(i = 1; (aux = get_node(list, i)) != NULL; i++){
			printf("%d - %d\n", aux->old_position, aux->cur_position);
		}
	}
}

/*------------------------------------------------------------------------------------------------------------
   search_list()
        Funcao que percorre a lista a procura de um no com o ID desejado, retornando esse valor quando for encontrado
	e -1 quando nao for
        - Parametros
          LIST* : lista
	  int   : id a ser procurado
        - Retorno
          int : id encontrado ou indicador de erro
*/
int search_list(LIST *list, int id){
	NODE *aux = NULL;
	if(list != NULL){
		// Mecanismo de busca semelhante a get_node()
		list->sentry->ID = id;
		aux = list->sentry->next;
		while(aux->ID != id) aux = aux->next;
		list->sentry->ID = -1;
		if(aux != list->sentry) return aux->cur_position;
	}

	return -1;
}

/*------------------------------------------------------------------------------------------------------------
   get_list()
        Funcao que cria uma lista usando create_list() e le inteiros da stream de dados ate o fim do arquivo,
	inserindo nos no final da lista com ids iguais aos inteiros lidos. Caso haja erro na criacao, retorna NULL
        - Parametros
          FILE* : stream de dados a ser lida
        - Retorno
          LIST* : lista criada
*/
LIST *get_list(FILE *stream){
	LIST *list = create_list();

	if(list != NULL){
		int aux;

		while(fscanf(stream, "%d", &aux) != EOF){
			insert_end(list, aux);
		}
		// Precaucao
		if(list->last == NULL){
			remove_end(list);
		}

	}

	return list;
}

/*------------------------------------------------------------------------------------------------------------
   get_old_positions()
        Funcao que percorre uma lista alterando os valores da posicao antiga de cada no de acordo com a posicao
	em que eles sao encontrados na outra lista
        - Parametros
          LIST* : lista "velha"
          LIST* : lista "nova"
        - Retorno
          int : 0 - falha; 1 - sucesso
*/
int get_old_positions(LIST *old_list, LIST *new_list){
	if(old_list != NULL && new_list != NULL){
		int i;
		NODE *aux;

		// Mecanismo de busca semelhante a print_list()
		for(i = 1; (aux = get_node(new_list, i)) != NULL; i++){
			// Caso esse id nao esteja presente na lista antiga, recebera -1 na posicao antiga
			aux->old_position = search_list(old_list, aux->ID);
		}
		return 1;
	}

	return 0;
}

/*------------------------------------------------------------------------------------------------------------
   get_special_list()
        Funcao que cria um lista contendo apenas os usuarios especiais de uma dada lista usando create_list()
	e salva os valores de posicao antiga utilizando get_old_position(). Retorna NULL quando ha erro na criacao
        - Parametros
          LIST* : lista contendo todos os usuarios
        - Retorno
          LIST* : lista contendo os usuarios especiais
*/
LIST *get_special_list(LIST *full_list){
	LIST *special_list = create_list();

	if(special_list != NULL){
		int i;
		NODE *aux;

		// Mecanismo de busca semelhante a print_list()
		for(i = 1; (aux = get_node(full_list, i)) != NULL; i++){
			// Coloca os usuarios especiais no final da nova lista. Caso n haja usuarios especiais a nova lista contera apenas a sentinela
			if(is_special_user(aux)) insert_end(special_list, aux->ID);
		}

		get_old_positions(full_list, special_list);
	}

	return special_list;
}
