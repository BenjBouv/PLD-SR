#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/resource.h>

#define STACK_SIZE 16384

enum ctx_state {INIT, RUNNING, END}; 

typedef void (func_t) (void*);

struct ctx_s {
	int id;
	enum ctx_state state;
	int saved;
	long esp; 
	long ebp; 
	void* stack;
	func_t *f;
	void* args;
	struct ctx_s *next_ctx;
};

typedef struct ctx_s ctx_s;

static int id_counter;

static ctx_s *curr_ctx;
static ctx_s *first_ctx;

int create_ctx(int stack_size, func_t f, void *args);
int init_ctx(struct ctx_s *ctx, int stack_size, func_t f, void *args); 

void display_ctx();
void switch_to_ctx(struct ctx_s *ctx); 
void yield();
void destroy_all_ctx();

void f_ping(void *arg);
void f_pong(void *arg);
void f_paf(void *arg);

struct rlimit limite;

int main(int argc, char *argv[])
{
	/* Pour regarder les tailles de heap et stack dispo
	getrlimit(RLIMIT_STACK, &limite);
	printf("cur : %lu, max : %lu\n", limite.rlim_cur, limite.rlim_max);
	*/

	id_counter = 0;
	curr_ctx = NULL;
	first_ctx = NULL;
	/*
	 * Création des différents contextes
	 */
	create_ctx(STACK_SIZE, f_ping, NULL);
	create_ctx(STACK_SIZE, f_pong, NULL);
	create_ctx(STACK_SIZE, f_paf, NULL);
	/*
	 * Appel à l'ordonnanceur
	 */
	yield();
	destroy_all_ctx();
	exit(EXIT_SUCCESS);
}

int create_ctx(int stack_size, func_t f, void *args)
{
	static ctx_s* temp_ctx = NULL;
	curr_ctx = (ctx_s*) malloc(sizeof(ctx_s));
	curr_ctx->id = id_counter;
	curr_ctx->launched = 0;
	curr_ctx->saved = 0;
	curr_ctx->stack = malloc(stack_size);
	curr_ctx->f = f;
	curr_ctx->args = args;
	curr_ctx->next_ctx = NULL;
	
	if (id_counter == 1)
	{
		first_ctx = curr_ctx;
	}
	
	id_counter++;
	//printf("Contexte %d créé\n", curr_ctx->id);
	
	if (temp_ctx != NULL)
	{
		temp_ctx->next_ctx = curr_ctx;
	}
	temp_ctx = curr_ctx;
	curr_ctx = curr_ctx->next_ctx;
	
	
}

void display_ctx()
{
	curr_ctx = first_ctx;
	while (curr_ctx != NULL)
	{
		printf("Id : %d; ", curr_ctx->id);
		curr_ctx = curr_ctx->next_ctx;
	}
	printf("\n");
	
}

void yield() 
{

	//printf("Sauvegarde du contexte %d\n", curr_ctx->id);
	/* Saving stack pointers to the current context */
	asm ("movl %%ebp, %0" "\n\t" "movl %%esp, %1" "\n\t"
	: "=r"(curr_ctx->ebp), "=r"(curr_ctx->esp) /* output variables */
	: /* input variables */
	);
	
	//fflush(stdout);
	
	if (curr_ctx->next_ctx == NULL)
	{
		curr_ctx = first_ctx;
	}
	else
	{
		curr_ctx = curr_ctx->next_ctx;
	}
	
	if (!curr_ctx->launched)
	{
		curr_ctx->launched = 1;
		curr_ctx->f(curr_ctx->args);
	}
	
	/* Restore stack registers */
	asm ("movl %0, %%esp" "\n\t" "movl %1, %%ebp" "\n\t"
	:  /* output variables */
	: "r"(curr_ctx->esp), "r"(curr_ctx->ebp) /* input variables */
	: /*"%esp"/*, "%ebp" */
	);	
	
	
	
	//printf("Restitution du contexte %d\n", curr_ctx->id);
	
	return;
}

void destroy_all_ctx()
{
	ctx_s *temp_ctx;
	curr_ctx = first_ctx;
	while (curr_ctx != NULL)
	{
		//printf("Contexte %d à détruire\n", curr_ctx->id);
		temp_ctx = curr_ctx->next_ctx ;
		if (temp_ctx != NULL)
			printf("Prochain Contexte à détruire : %d\n", temp_ctx->id);
		//printf("Destruction du contexte %d ... ", curr_ctx->id);
		free(curr_ctx);
		//printf("... réussie !\n");
		curr_ctx = temp_ctx;
	} 
	
}

void f_ping(void *args)
{
	while(1) 
	{
		printf("A");
		yield();
		printf("B");
		yield();
		printf("C");
		yield();
	}
}

void f_pong(void *args)
{
	while(1) 
	{
		printf("1");
		yield();
		printf("2");
		yield();
	}

}

void f_paf(void *args)
{
	while(1) 
	{
		printf("y");
		yield();
		printf("z");
		yield();
	}
}
