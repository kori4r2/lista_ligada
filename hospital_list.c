#include "hospital_list.h"
#include <stdlib.h>

struct node{
	int ID;
	int old_position;
	int cur_position;
	struct node *next;
};

struct list{
	struct node *sentry;
	struct node *last;
	int size;
};

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

void delete_node(NODE **node){
	if(node != NULL && (*node) != NULL){
		free(*node);
		(*node) = NULL;
	}
}

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

int remove_end(LIST *list){
	if(list != NULL && list->size > 0){
		NODE *aux = list->sentry;
		while(aux->next != list->last) aux = aux->next;
		aux->next = list->sentry;
		delete_node(&list->last);
		list->last = aux;
		list->size--;

		return 1;
	}

	return 0;
}

NODE *get_node(LIST *list, int position){
	NODE *aux = NULL;
	if(list != NULL){
		list->sentry->cur_position = position;
		aux = list->sentry->next;
		while(aux->cur_position != position) aux = aux->next;
		if(aux == list->sentry) aux = NULL;
		list->sentry->cur_position = -1;
	}

	return aux;
}

int is_special_user(NODE *node){
	if(node != NULL){
		if(node->ID >= 60) return 1;
	}
	return 0;
}

void delete_list(LIST **list){
	if(list != NULL && (*list) != NULL){
		while((*list)->size > 0) remove_end(*list);
		delete_node( &((*list)->sentry) );
		free(*list);
		(*list) = NULL;
	}
}

void print_list(LIST *list){
	if(list != NULL){
		int i;
		NODE *aux;

		for(i = 1; (aux = get_node(list, i)) != NULL; i++){
			printf("%d - %d\n", aux->old_position, aux->cur_position);
		}
	}
}

int search_list(LIST *list, int id){
	NODE *aux = NULL;
	if(list != NULL){
		list->sentry->ID = id;
		aux = list->sentry->next;
		while(aux->ID != id) aux = aux->next;
		list->sentry->ID = -1;
		if(aux != list->sentry) return aux->cur_position;
	}

	return -1;
}

LIST *get_list(FILE *stream){
	LIST *list = create_list();

	if(list != NULL){
		int aux;

		while(fscanf(stream, "%d", &aux) != EOF){
			insert_end(list, aux);
		}
		if(list->last == NULL){
			remove_end(list);
		}

	}

	return list;
}

int get_old_positions(LIST *old_list, LIST *new_list){
	if(old_list != NULL && new_list != NULL){
		int i;
		NODE *aux;
		
		for(i = 1; (aux = get_node(new_list, i)) != NULL; i++){
			aux->old_position = search_list(old_list, aux->ID);
		}
		return 1;
	}

	return 0;
}

LIST *get_special_list(LIST *full_list){
	LIST *special_list = create_list();

	if(special_list != NULL){
		int i;
		NODE *aux;

		for(i = 1; (aux = get_node(full_list, i)) != NULL; i++){
			if(is_special_user(aux)) insert_end(special_list, aux->ID);
		}

		get_old_positions(full_list, special_list);
	}

	return special_list;
}
