#include <curses.h>

#include <stdlib.h>

#include <unistd.h>

#include <string.h>

#include <stdio.h> 



 

#define MAX_PROCESS 10

int process_number=0;

typedef struct pcb{

	struct pcb *next;

	char process_name[20];

	int process_number;

	int process_start_moment;

	int process_need_time;

	int process_time_slice;

	int process_priority;

	int process_waiting_time;

	int process_turnarround_time;

	

}PCB;

 

PCB pcb_table[MAX_PROCESS];

 

//PCB *pcb_run=NULL;

PCB *pcb_free=NULL;

PCB *pcb_ready=NULL;

PCB *pcb_ready_rear=NULL;



 

void init_pcb_table();

PCB *create_process();

void delete_process_by_name();

void display_process_queue(PCB *queue);

void swap(int *a, int *b) ;

 

void FCFS();

void SJF();

void RR();

void PF();




