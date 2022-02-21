#include "process_schedule.h"



int main(int argc,char *argv[]){

	char select;

        initscr();

	init_pcb_table();

	bool end=false;

	

	while(!end){

		clear();

		refresh();

		

		printw("|----------MAIN    MENU--------------|\n");

		printw("|  a: Create a process               |\n");

		printw("|  b: Display processes queue        |\n");

		printw("|  1: First-Come-First-Served (FCFS) |\n");

		printw("|  2: Shortest Job First (SJF)       |\n");

		printw("|  3: Round Robin (RR)               |\n");

		printw("|  4: Priority Scheduling            |\n");

		printw("|  5:exit                            |\n");

		printw("|------------------------------------|\n");

		

		printw("select a function(1~8,a~d):");

               refresh();

                

		do{

			select=(char)getch();

                        refresh();

		}while(!((49<=select&&select<=56)||(97<=select&&select<=100)));

		

		clear();

        	refresh();

        

		switch(select){

		

		case 'a':

			create_process();

			break;

		case 'b':

			display_process_queue(pcb_ready);

			break;

		case '1':

			FCFS();

			break;

		case '2':

			SJF();

			break;

		case '3':

			RR();

			break;

		case '4':

			PF();

			break;

		case '5':

			printw("\n");

		        end=true;

		}

		printw("press any key to continue.\n");

		getch();

		refresh();

	}

	endwin();

	return 0;

}

 

void init_pcb_table()

{

	int i=0;

	pcb_free=&pcb_table[0];

	pcb_table[MAX_PROCESS-1].next=NULL;

	pcb_table[MAX_PROCESS-1].process_number=0;

	pcb_table[MAX_PROCESS-1].process_start_moment=0;

    pcb_table[MAX_PROCESS-1].process_need_time=0;

	pcb_table[MAX_PROCESS-1].process_priority=0;

	pcb_table[MAX_PROCESS-1].process_waiting_time=-1;

	pcb_table[MAX_PROCESS-1].process_turnarround_time=-1;

	strcpy(pcb_table[MAX_PROCESS-1].process_name,"");

	for(i=0;i<MAX_PROCESS-1;i++){

		pcb_table[i].next=&pcb_table[i+1];

		pcb_table[i].process_number=0;

		pcb_table[i].process_start_moment=0;

		pcb_table[i].process_need_time=0;

		pcb_table[i].process_priority=0;

		pcb_table[i].process_waiting_time=-1;

		pcb_table[i].process_turnarround_time=-1;

		strcpy(pcb_table[i].process_name,"");

	}

}

 



PCB *create_process()

{

	PCB *p=pcb_free;

	if(p==NULL)

		return NULL; //Maximum allowed number of processes reached

	else

	{

		pcb_free=pcb_free->next;

		clear();

		refresh();

		printw("please enter the following fields:\n");

		//printw("| name | start_moment | need_time | time_slice | priority |\n");

		

		printw("Process name: ");

		scanw("%s", p->process_name);

		

		printw("Arrival time: ");

		scanw("%d", &(p->process_start_moment));

		

		printw("CPU burst: ");

		scanw("%d%d%d", &(p->process_need_time));

		

		printw("Priority: ");

		scanw("%d", &(p->process_priority));

		

		p->process_number=(process_number+1)%100;

		process_number++;

		p->next=NULL;

		

		

		if(pcb_ready==NULL)

			pcb_ready=pcb_ready_rear=p;

		else

		{

		    pcb_ready_rear->next=p;

		    pcb_ready_rear=p;

		}

		return p;

	}

}

 



 

 void display_process_queue(PCB *queue)

{

	PCB *p=queue;

	int i=4;

    	move(1,1);

	printw("|----------|----------|----------|----------|----------|----------|-------------|\n");

	move(2,1);

	printw("| name     | number   | Arrival  | Burst    | Priority |  Waiting | Turnaround  |\n");

	move(3,1);

	printw("|----------|----------|----------|----------|----------|----------|-------------|\n");

	while(p!=NULL){

		move(i,1);

		printw("| ");

		printw("%s",p->process_name);

		move(i,12);

		printw("| ");

		printw("%d",p->process_number);

		move(i,23);

		printw("| ");

		printw("%d",p->process_start_moment);

		move(i,34);

		printw("| ");

		printw("%d",p->process_need_time);

		move(i,45);

		printw("| ");

		printw("%d",p->process_priority);

		move(i,56);

		

		printw("| ");

		printw("%d",p->process_waiting_time);

		move(i,67);

		

		printw("| ");

		printw("%d",p->process_turnarround_time);

		move(i,81);

		printw("|");

		p=p->next;

		i++;

	}

	move(i,1);

	printw("|----------|----------|----------|----------|----------|----------|-------------|\n");

	refresh();

}

 











int  comp_arrival(const void *l, const void * r) 

{ 

    PCB *a = (struct pcb *)l; 

    PCB * b = (struct pcb *)r; 

    return a->process_start_moment - b->process_start_moment;  



} 

 

 void FCFS()

{

	int n = process_number;

	

	qsort((void*)pcb_table, n,sizeof(pcb_table[0]) ,comp_arrival);

   	for(int i=0; i<n-1; i++){

   	pcb_table[i].next= &pcb_table[i+1];

   	

   	}

   	pcb_table[n-1].next= NULL;

	

	int wt[n], tat[n];

	int service_time[n];

	service_time[0] = 0;

	wt[0]=  pcb_table[0].process_waiting_time = 0;

	for (int i = 1; i < n ; i++)

	{

		service_time[i] = service_time[i-1] + pcb_table[i-1].process_need_time;  

		wt[i] = pcb_table[i].process_waiting_time = service_time[i] - pcb_table[i].process_start_moment;	

		if (wt[i] < 0)

			wt[i] = pcb_table[i].process_waiting_time = 0;

	}

	

	for (int i = 0; i < n ; i++)

		tat[i] = pcb_table[i].process_turnarround_time =pcb_table[i].process_need_time + wt[i]; 

	

	int total_wt = 0, total_tat = 0;

	for (int i = 0 ; i < n ; i++)

	{

		total_wt = total_wt + wt[i];

		total_tat = total_tat + tat[i];

		int compl_time = tat[i] + pcb_table[i].process_start_moment; 

	}



	display_process_queue(pcb_ready);

	printw("\n\nAverage waiting time = %f", (float)total_wt / (float)n);

	printw("\nAverage turn around time = %f\n",(float)total_tat / (float)n);

	

}



void SJF()

{



	

	int n= process_number;

	int mat[n][6];  

	int temp, val; 

	int total_wt = 0, total_tat = 0;

	

	//arrange by arrival time

       qsort((void*)pcb_table, n,sizeof(pcb_table[0]) ,comp_arrival);

   	for(int i=0; i<n-1; i++){

   	pcb_table[i].next= &pcb_table[i+1];

   	

   	}

   	pcb_table[n-1].next= NULL;

   	

	for(int i=0; i<n; i++) 

	{ 

		mat[i][0]= pcb_table[i].process_number; 

		mat[i][1]= pcb_table[i].process_start_moment;  

		mat[i][2]= pcb_table[i].process_need_time; 

	} 

	

	

	//completion Time

	mat[0][3] = mat[0][1] + mat[0][2]; 

	mat[0][5] = mat[0][3] - mat[0][1]; 

	mat[0][4] = mat[0][5] - mat[0][2]; 

	

	for(int i=1; i<n; i++) 

	{ 

		temp = mat[i-1][3]; 

		int low = mat[i][2]; 

		for(int j=i; j<n; j++) 

		{ 

			if(temp >= mat[j][1] && low >= mat[j][2]) 

			{ 

				low = mat[j][2]; 

				val = j; 

			} 

		} 

		mat[val][3] = temp + mat[val][2]; 

		mat[val][5] = mat[val][3] - mat[val][1]; 

		mat[val][4] = mat[val][5] - mat[val][2]; 

		for(int k=0; k<6; k++) 

		{ 

			swap(&mat[val][k], &mat[i][k]); 

		} 

	}

	



//Result

for (int i = 0; i < n; i++) 

{ 	

	pcb_table[mat[i][0]-1].process_waiting_time = mat[i][4];

	pcb_table[mat[i][0]-1].process_turnarround_time = mat[i][5];

	total_wt = total_wt + mat[i][4]; 

	total_tat = total_tat +mat[i][5] ; 

} 





//print results

	int i=4;

    	move(1,1);

	printw("|----------|----------|----------|----------|----------|----------|-------------|\n");

	move(2,1);

	printw("| name     | number   | Arrival  | Burst    | Priority |  Waiting | Turnaround  |\n");

	move(3,1);

	printw("|----------|----------|----------|----------|----------|----------|-------------|\n");

	int j=0;

	while(j<n){

		move(i,1);

		printw("| ");

		printw("%s",pcb_table[mat[j][0]-1].process_name);

		move(i,12);

		printw("| ");

		printw("%d",mat[j][0]);

		move(i,23);

		printw("| ");

		printw("%d",mat[j][1]);

		move(i,34);

		printw("| ");

		printw("%d",mat[j][2]);

		move(i,45);

		printw("| ");

		printw("%d",pcb_table[mat[j][0]-1].process_priority);

		move(i,56);

		

		printw("| ");

		printw("%d",mat[j][4]);

		move(i,67);

		

		printw("| ");

		printw("%d",mat[j][5] );

		move(i,81);

		printw("|");

		j++;

		i++;

	}

	move(i,1);

	printw("|----------|----------|----------|----------|----------|----------|-------------|\n");

	refresh();



printw("\nAVERAGE WAITING TIME : %f",(float)total_wt / (float)n); 

printw("\nAVERAGE TURN AROUND TIME : %f\n", (float)total_tat / (float)n); 



	

	

}







			

void RR()

{



int n = process_number; //number of processes

int quantum=1;



printw("Quantum: ");

scanw("%d\n",&quantum);



int wt_time[n];  //waiting time

int tat_time[n]; //turnaround time

int completion_time[n]; //completion time

int total_wt = 0, total_tat = 0;



//CalcWaitingTime

int rem_time[n];



for(int i = 0; i < n; i++)

	rem_time[i] = pcb_table[i].process_need_time;  



int t = 0;

int arrival = 0;



while(1)

{

	

	int done = 1;

	for(int i = 0; i < n; i++)

	{

	if(rem_time[i] > 0)

	{

		done = 0;

		if(rem_time[i] > quantum &&  pcb_table[i].process_start_moment <= arrival) 

		{

		t += quantum;

		rem_time[i] -= quantum;

		arrival++;

		}

		else

		{

		if(pcb_table[i].process_start_moment <= arrival)  

		{

			arrival++;

			t += rem_time[i];

			rem_time[i] = 0;

			completion_time[i] = t; 

		}else{

		arrival++;

		}

		}

	}

	}



	if(done==1)

	break;

} 



//Find TurnAround Time

for(int i = 0; i < n; i++)

{

	tat_time[i] = pcb_table[i].process_turnarround_time =  completion_time[i] -  pcb_table[i].process_start_moment ; 

	wt_time[i] = pcb_table[i].process_waiting_time = tat_time[i] -   pcb_table[i].process_need_time;  

}





//Result

for (int i = 0; i < n; i++) 

{ 

	total_wt = total_wt + wt_time[i]; 

	total_tat = total_tat + tat_time[i]; 

} 



display_process_queue(pcb_ready);

printw("\nAVERAGE WAITING TIME : %f",(float)total_wt / (float)n); 

printw("\nAVERAGE TURN AROUND TIME : %f\n", (float)total_tat / (float)n); 



}

	

	

	

int  comp(const void *l, const void * r) 

{ 

    PCB *a = (struct pcb *)l; 

    PCB * b = (struct pcb *)r; 

    

if(a->process_start_moment == b->process_start_moment) 

{ 

	return a->process_priority - b->process_priority ; 

} 

else

{ 

	return a->process_start_moment - b->process_start_moment;  

} 

} 

		

void PF()

{



   int n = process_number; //number of processes

   qsort((void*)pcb_table, n,sizeof(pcb_table[0]) ,comp);

   for(int i=0; i<n-1; i++){

   pcb_table[i].next= &pcb_table[i+1];

   	

   }

   pcb_table[n-1].next= NULL;

   FCFS();

   

}

		



void swap(int *a, int *b) 

{ 

	int temp = *a; 

	*a = *b; 

	*b = temp; 

} 
