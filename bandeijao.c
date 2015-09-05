#include <stdio.h>
#include <stdlib.h>
#include "hospital_list.h"

int main(int argc, char *argv[]){

	LIST *full_list = NULL, *special_list = NULL;

	full_list = get_list(stdin);
	if(full_list == NULL) return 1;

	special_list = get_special_list(full_list);
	if(full_list == NULL) return 2;

	print_list(special_list);

	delete_list(&full_list);
	delete_list(&special_list);

	return 0;
}
