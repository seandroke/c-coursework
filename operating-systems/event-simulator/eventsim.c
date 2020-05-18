// Sean Droke
// CIS 3207
//Project 1: Giorgio's Discrete Event Simulator

#include <stdio.h>
#include <stdlib.h>

//Global Variables
//Initialized using config.txt

int SEED;
int INIT_TIME;
int FIN_TIME;
int ARRIVE_MIN;
int ARRIVE_MAX;
float QUIT_PROB;
int CPU_MIN;
int CPU_MAX;
int DISK1_MIN;
int DISK1_MAX;
int DISK2_MIN;
int DISK2_MAX;

#define ARRIVAL 0
#define FINISH 1
#define DISK_ARRIVAL 2
#define DISK_FINISH 3
#define SIMULATION_END 4
#define IDLE 0
#define BUSY 1

#define START 0
#define STOP 1

#define COMPUTED 10

/* --Data Structures--
	Fifo Queue - Used for handling events sent to I/O
	Priority Queue - Handles events processed by the CPU
	Linked List - Used as the fundamental procedure in both queue
                queue structures and the basis for calculating
                statistics dynamically.
*/


/* --Structs--
	Event - General struct used for event scheduling, stores the time, job number, and the type
	Node - Used in the implementation of the queue linked list, stores an event (job) and a pointer to the next event
  Average - Struct used in calculating the average and maximum size for each queue dynamically via a linked list
  averageNode - Used in the linked list to store average and maximum queue size, represents a node
  utilization - Similar function to those above, used for a linkedlist that eventually computes throughput and utilization statistics
  throughput - Represents a node of the linked list for throughput and utilization statistics.
*/

typedef struct event{
    int time;
    int jobNumber;
    int type;
    int diskAssign;
}event;

typedef struct node{
    struct event job;
    struct node *next;
}node;

typedef struct average{
    int time;
    int size;
}average;

typedef struct averageNode{
    struct average item;
    struct averageNode *next;
}averageNode;

typedef struct utilization{
  int currentTime;
  int totalBusy;
}utilization;

typedef struct throughput{
  struct event job;
  int responseTime;
  struct throughput *next;
}throughput;

/* --Fifo Queue Function Initialization--
	fifoAppend - Append a value to the queue
	fifoRemoveFirst - Pop a value off the top of the queue
*/

void fifoAppend(node**,event,int*);
event fifoRemoveFirst(node**,int*);

/* --Priority Queue Function Initialization--
	priorityAppend - Append a value to the priority queue
	priorityRemoveFirst - Pop a value from the priority queue
*/

void priorityAppend(node**,event,int*);
event priorityRemoveFirst(node**,int*);

/* --General Function Initialization--
	eventGenerator - Each random event generated with this call
	Randomizer - Computes a random value
	processCPU - Process an event that utilizes the CPU
	processDISK - Process an event that utilizes the Disks
	logEvent - Event logged to external file
  finalCall - Prints some final statements to the log file
  beginningCall - Prints an initial starting statement to the log file
  computeAverage - logs data for average computation
  returnAverage - Return average results based on collected information
  averageGenerator - Generates necesarry information for the average linked list
  utilizingServer - Function used in the calculation of server utilization statistic
  processThroughput - Collects information used in calculating the throughput
  averageResponseTime - Returns the average response time of each queue
  maximumResponseTIme - Returns the maximum response time for each server
  throughputCalculation - Returns the throughput based on collected data
  returnMax - Returns the maximum size of each queue
*/

event eventGenerator(int, int, int, int);
int Randomizer(int, int);

void processCPU(event);
void processDISK(event*);
void logEvent(char*);
void finalCall();
void beginningCall();
void computeAverage(averageNode**, average);
int returnAverage(averageNode**);
average averageGenerator(int, int);
void utilizingServer(utilization*, int, int);
void processThroughput(throughput**, event);
int averageResponseTime(throughput**);
int maximumResponseTime(throughput**);
int throughputCalculation(throughput**);
int returnMax(averageNode**);


/* --General Variable Initialization--
	currentTime - Program "clock"
	randomTime - Temporary adjustable variable representing a random time
	node *CPU, *DISK_1, *DISK_2 - Structs to form the FIFO Queues
	node *eventQueue - Struct to form the Priority Queue
	event task - Initial task to be populated randomly
	cpuSize, disk1Size, disk2Size, eventSize, jobTotal - Summation variables to record size of each queue and the total number of jobs processed
	cpuState, disk1State, disk2State - Numeric values representing the current state of each resource for validation purposes
  utilization cpuTime, disk1Time, disk2Time - Logs information pertaining to when each server is utilized
  averageNode* CPUAVG, *DISK_1_AVG, *DISK_2_AVG, eventQueueAVG - Logs information pertaining to queue size and average/maximum size
  throughput* cpuThroughput, *disk1Throughput, *disk2Throughput - Logs information pertaining to throughput and response time
*/

int currentTime = 0, randTime = 0;
node* CPU = NULL, *DISK_1 = NULL, *DISK_2 = NULL;
node* eventQueue = NULL;
event task;
int cpuSize = 0, disk1Size = 0, disk2Size = 0, eventSize = 0, jobTotal = 1;
int cpuState = IDLE, disk1State = IDLE, disk2State = IDLE;
utilization cpuTime = {0,0}, disk1Time = {0,0}, disk2Time = {0,0};
averageNode* CPUAVG = NULL, *DISK_1_AVG = NULL, *DISK_2_AVG = NULL;
averageNode* eventQueueAVG = NULL;
throughput* cpuThroughput = NULL, *disk1Throughput = NULL, *disk2Throughput = NULL;

/* --Main Function--
	PARAMETERS: None
	FUNCTION: Values are collected from config file, seed is randomized. A current time counter will be updated as an internal clock.
            Appended to the priority queue will be 2 default events or that of the first job and the finished command.the program
            continues until the priority queue runs out (Never) or the final declared time is reached. Until that point, a switch
            statement executes the random events as they move through the priority queue.
	RETURN VALUE: None, main function serves as a program driver.
*/

int main(){

    FILE *FILE;
    FILE = fopen("config.txt", "rt");
    if(FILE==NULL){
      printf("\n**Error Opening Config File**\n");
    }
    else{
    (fscanf(FILE, "%*s %d", &SEED));
    (fscanf(FILE, "%*s %d", &INIT_TIME));
    (fscanf(FILE, "%*s %d", &FIN_TIME));
    (fscanf(FILE, "%*s %d", &ARRIVE_MIN));
    (fscanf(FILE, "%*s %d", &ARRIVE_MAX));
    (fscanf(FILE, "%*s %f", &QUIT_PROB));
    (fscanf(FILE, "%*s %d", &CPU_MIN));
    (fscanf(FILE, "%*s %d", &CPU_MAX));
    (fscanf(FILE, "%*s %d", &DISK1_MIN));
    (fscanf(FILE, "%*s %d", &DISK1_MAX));
    (fscanf(FILE, "%*s %d", &SEED));
    (fscanf(FILE, "%*s %d", &DISK2_MAX));
    fclose(FILE);
  }

    srand(SEED);
    currentTime = INIT_TIME;

    priorityAppend(&eventQueue,eventGenerator(INIT_TIME,1,ARRIVAL, 0),&eventSize);
    priorityAppend(&eventQueue,eventGenerator(FIN_TIME,0,SIMULATION_END, 0),&eventSize);
    computeAverage(&eventQueueAVG, averageGenerator(INIT_TIME, eventSize));

 /*//TESTING OF THE PRIORITY QUEUE; ALL EVENTS POP OFF

    randTime = Randomizer(ARRIVE_MIN,ARRIVE_MAX) + currentTime; jobTotal++;
    priorityAppend(&eventQueue,eventGenerator(randTime,jobTotal,ARRIVAL, 0),&eventSize);

    randTime = Randomizer(ARRIVE_MIN,ARRIVE_MAX) + currentTime; jobTotal++;
    priorityAppend(&eventQueue,eventGenerator(randTime,jobTotal,ARRIVAL, 0),&eventSize);

    randTime = Randomizer(ARRIVE_MIN,ARRIVE_MAX) + currentTime; jobTotal++;
    priorityAppend(&eventQueue,eventGenerator(randTime,jobTotal,ARRIVAL, 0),&eventSize);

    event task1 = priorityRemoveFirst(&eventQueue,&eventSize);
    printf("\n\n\n\n%d\n\n\n\n",task1.jobNumber);

    event task2 = priorityRemoveFirst(&eventQueue,&eventSize);
    printf("\n\n\n\n%d\n\n\n\n",task2.jobNumber);

    event task3 = priorityRemoveFirst(&eventQueue,&eventSize);
    printf("\n\n\n\n%d\n\n\n\n",task3.jobNumber);
*/

    beginningCall();
    while(eventSize != 0 && currentTime < FIN_TIME){
        task = priorityRemoveFirst(&eventQueue,&eventSize);
        currentTime = task.time;
        computeAverage(&eventQueueAVG, averageGenerator(currentTime, eventSize));
        switch(task.type){
            case ARRIVAL: processCPU(task); break;
            case FINISH: processCPU(task); break;
            case DISK_ARRIVAL: processDISK(&task); break;
            case DISK_FINISH: processDISK(&task); break;
            case SIMULATION_END: finalCall(); break;
        }
    }
    return 0;
}

/* --FIFO Append Function--
	PARAMETERS:
    node** head - Double pointer to allow for retrieval of interior elements of the Event Queue
    event toAppend - The event to be appended to the queue
    int* total - Pointer to the retrieve the total size of the queue

	FUNCTION:
    1. Allocate space for placeholder list node that will contain the event to be Appended
    2. lastNode is assigned the head value
    3. Total is incremented as the value is Appended
    4. Should the head be empty, populate with the event to be appended.
    5. Loop through the list, until null achieved
    6. Append to the end of the list for first in first out execution
	RETURN VALUE: None, value appended to the queue.
*/

void fifoAppend(node** head, event toAppend, int* total){
    node* holder = (node*) malloc(sizeof(node));
    holder->job = toAppend;
    holder->next = NULL;

    node *lastNode = *head;
    (*total)++;
    if (*head == NULL){
        *head = holder;
        return;
    }
    while (lastNode->next != NULL)
        lastNode = lastNode->next;

    lastNode->next = holder;
    return;
}

/* --FIFO Removal--
	PARAMETERS:
    node** head - Double pointer to allow for retrieval of interior elements of the Event Queue
    int* total - Pointer to the retrieve the total size of the queue

	Event:
    1. Placeholder list node will be assigned to the head
    2. Head value is then assigned to the next element
    3. Job is assigned the placeholders job
    4. placeholder is freed of its memory
    5. Total is decremented and the new queue is returned
	RETURN VALUE: Job, such that this element can be processed next
*/

event fifoRemoveFirst(node** head, int* total){
    node *holder = *head;
    *head = (*head)->next;
    event job = holder->job;
    free(holder);
    (*total)--;
    return job;
}

/* --Priority Append Function--
	PARAMETERS:
    node** head - Double pointer to allow for retrieval of interior elements of the Event Queue
    event toAppend - The event to be appended to the queue
    int* total - Pointer to the retrieve the total size of the queue

	FUNCTION:
    1. Allocate space for placeholder variable which represents the event to be appended
    2. priorityNumber assigns the time of the new event as the priority for comparison
    3. Total is incremented as a value is about to be appended to the queue
    4. lastNode is assigned the head value
    5. Should head be unoccupied, replace the head value with the new event
    6. Should the priority of the event to be appended be less than the head value, event comes before and is linked to the head.
    7. Loop through the list, until null value reached or if priorityNumber reaches a higher item.
    8. Insert the event into its rightful position and link accordingly
	RETURN VALUE: None, value appended to the queue.
*/
void priorityAppend(node** head, event toAppend, int* total){
    node* holder = (node*) malloc(sizeof(node));
    holder->job = toAppend;
    holder->next = NULL;

    int priorityNumber = holder->job.time;
    (*total)++;
    node *lastNode = *head;
    if (*head == NULL){
        *head = holder;
        return;
    }else if(priorityNumber < lastNode->job.time){
        holder->next = lastNode;
        *head = holder;
        return;
    }
    while (lastNode->next != NULL && priorityNumber >= lastNode->next->job.time)
        lastNode = lastNode->next;
        holder->next = lastNode->next;
        lastNode->next = holder;
        return;
}

/* --Priority Queue Removal--
	PARAMETERS:
    node** head - Double pointer to allow for retrieval of interior elements of the Event Queue
    int* total - Pointer to the retrieve the total size of the queue

	Event:
    1. Placeholder list node will be assigned to the head
    2. Head value is then assigned to the next element
    3. Job is assigned the placeholders job
    4. placeholder is freed of its memory
    5. Total is decremented and the new queue is returned
	RETURN VALUE: Job, such that this element can be processed next
*/

event priorityRemoveFirst(node** head, int* total){
    node *holder = *head;
    *head = (*head)->next;
    event job = holder->job;
    free(holder);
    (*total)--;
    return job;
}

/* --eventGenerator--
  PARAMETERS:
    int time - An arbitrary, randomized time value
    int jobNumber - The job number ID assigned to each individual event
    int type - The type of the job
  EVENT:
    1. New job is generated as an event
    2. Job is assigned the randomized Time, job number ID, and the type
  RETURN: The new job event is returned as a result
*/

event eventGenerator(int time, int jobNumber, int type, int diskAssign){
    event job;
    job.time = time;
    job.jobNumber = jobNumber;
    job.type = type;
    job.diskAssign = diskAssign;
    return job;
}

/* --averageGenerator--
  PARAMETERS:
    int time - An arbitrary, randomized time value
    int size - The size of the queue at the moment of time when called
  EVENT:
    1. average struct item generated
    2. Average is populated with the time and the size of the respective queue
  RETURN: The item that has just been generated
*/

average averageGenerator(int time, int size){
  average item;
  item.time = time;
  item.size = size;
  return item;
}

/* --Randomizer--
  PARAMETERS:
    int min - The minimum value to serve as the lower spectrum of a range
    int max - The maximum value to serve as the higher spectrum of a range
  FUNCTION: Calculate a random value within the range suggested by the parameters
  RETURN: Random number within the range
*/

int Randomizer(int min, int max){
    return (rand() % (max - min + 1)) + min;
}

/* --processCPU--
  PARAMETERS:
    event task - The event needing action from the CPU
  FUNCTION:
    1. A character string is initiliazed to hold the instruction information
    2. If task type is arrival, log file receives that the task has arrived at the CPU.
    3. In arrival phase, a new task is generated with ARRIVAL type and appended to the event queue
    4. The task being processed by the CPU is then initially appended to the CPU fifo server
    5. If the CPU is currently idle, the task is removed from the fifo queue, a random time equates the time it takes to complete at the CPU
       the event is then sent for processing again as a FINISHED type. CPU state is then considered busy while this is in process. If the CPU
       is busy when this process arrives at the queue it must wait for other events to complete.
    6. Else, the task is considered of the FINISHED job type. The log file receives that the event has completed at the CPU.
    7. When a job is FINISHED at the CPU the event either leaves the loop entirely based on a quit probability, or is sent to a disk for I/O operation.
    8. Background processes compute the average as the queue size changes, keep track of throughput statistics, and utilization timers.
  RETURN: None, void funciton
*/

void processCPU(event task){
    char str[80];
    if(task.type == ARRIVAL){
        sprintf(str, "At time %d, Job%d arrives at the CPU.",currentTime,task.jobNumber);
        processThroughput(&cpuThroughput, task);
        logEvent(str);
        randTime = Randomizer(ARRIVE_MIN,ARRIVE_MAX) + currentTime; jobTotal++;
        priorityAppend(&eventQueue,eventGenerator(randTime,jobTotal,ARRIVAL, 0),&eventSize);
        computeAverage(&eventQueueAVG, averageGenerator(randTime, eventSize));
        fifoAppend(&CPU,task,&cpuSize);
        computeAverage(&CPUAVG, averageGenerator(currentTime, cpuSize));
        if (cpuState == IDLE){
            task = fifoRemoveFirst(&CPU,&cpuSize);
            computeAverage(&CPUAVG, averageGenerator(currentTime, cpuSize));
            randTime = Randomizer(CPU_MIN,CPU_MAX) + currentTime;
            priorityAppend(&eventQueue,eventGenerator(randTime,task.jobNumber,FINISH, 0),&eventSize);
            computeAverage(&eventQueueAVG, averageGenerator(randTime, eventSize));
            cpuState = BUSY;
            utilizingServer(&cpuTime, currentTime, cpuState);
        }
    }else{
        sprintf(str, "At time %d, Job%d finishes at CPU.",currentTime,task.jobNumber);
        processThroughput(&cpuThroughput, task);
        logEvent(str);
        cpuState = IDLE;
        utilizingServer(&cpuTime, currentTime, cpuState);
        int quit = rand() <  QUIT_PROB * ((double)RAND_MAX + 1.0);
        if(quit){
            sprintf(str, "At time %d, Job%d exits.",currentTime,task.jobNumber);
            logEvent(str);
        }else{
            randTime = Randomizer(ARRIVE_MIN,ARRIVE_MAX) + currentTime;
            priorityAppend(&eventQueue,eventGenerator(currentTime,task.jobNumber,DISK_ARRIVAL, 0),&eventSize);
            computeAverage(&eventQueueAVG, averageGenerator(currentTime, eventSize));
        }
    }
}

/* --processCPU--
  PARAMETERS:
    event* task - The event needing action from the CPU
  FUNCTION:
    1. A character string is initiliazed to hold the instruction information
    2. sendTo is initialized to zero, this will hold the disk ID that will process the task.
    2. If task type is DISK_ARRIVAL, a comparison is done to determine which disk is least busy
    3. If disk 1 is smallest the task is assigned disk 1 and the log file receives that the task has arrived
    4. Else if disk 2 is smallest the task is assigned disk 2 and the log file receives this information
    5. If both disks are the same size, the disk the task is sent to is computed randomly.
    6. Depending on this assignments, the conditions below process the arrival procedure
    7. Each disk appends its respective task to its queue and determines if it is at IDLE status.
       An IDLE status removes a job from the queue assigns it a random time spent at the disk,
       and appends it back to the event queue with a DISK_FINISH status. The disk is then sent to busy
    8. In the else case that status is not DISK_ARRIVAL or rather that of DISK_FINISH, an additional random
       time is assigned and the job is readded to the priority queue with a new ARRIVAL type for CPU processing.
       The log file will receive the disk information that the task ended will move back to IDLE status.
    9. Background processes compute the average as the queue size changes, keep track of throughput statistics, and utilization timers.
  RETURN: None, void function
*/

void processDISK(event* task){
    char str[80];
    int sendTo = 0;
    if (task->type == DISK_ARRIVAL){
        if(disk1Size < disk2Size){
            task->diskAssign = 1;
            sprintf(str, "At time %d, Job%d arrives at Disk 1.",currentTime,task->jobNumber);
            processThroughput(&disk1Throughput, *task);
            logEvent(str);
        }else if(disk1Size > disk2Size){
            task->diskAssign = 2;
            sprintf(str, "At time %d, Job%d arrives at Disk 2.",currentTime,task->jobNumber);
            processThroughput(&disk2Throughput, *task);
            logEvent(str);
        }else{
            sendTo = (rand() <  0.5 * ((double)RAND_MAX + 1.0)) + 1;
            task->diskAssign = sendTo;
            sprintf(str, "At time %d, Job%d arrives at Disk %d.",currentTime,task->jobNumber, sendTo);
            if(sendTo == 1){
              processThroughput(&disk1Throughput, *task);
            }
            if(sendTo == 2){
              processThroughput(&disk2Throughput, *task);
            }
            logEvent(str);
        }


        if(task->diskAssign == 1){
            fifoAppend(&DISK_1,*task,&disk1Size);
            computeAverage(&DISK_1_AVG, averageGenerator(currentTime, disk1Size));
            if(disk1State == IDLE){
                event job = fifoRemoveFirst(&DISK_1,&disk1Size);
                computeAverage(&DISK_1_AVG, averageGenerator(currentTime, disk1Size));
                randTime = Randomizer(DISK1_MIN,DISK1_MAX) + currentTime;
                priorityAppend(&eventQueue,eventGenerator(randTime,job.jobNumber,DISK_FINISH,1),&eventSize);
                computeAverage(&eventQueueAVG, averageGenerator(randTime, eventSize));
                disk1State = BUSY;
                utilizingServer(&disk1Time, currentTime, disk1State);

            }
        }else if(task->diskAssign == 2){
            fifoAppend(&DISK_2,*task,&disk2Size);
            computeAverage(&DISK_2_AVG, averageGenerator(currentTime, disk2Size));
            if(disk2State == IDLE){
                event job = fifoRemoveFirst(&DISK_2,&disk2Size);
                computeAverage(&DISK_2_AVG, averageGenerator(currentTime, disk2Size));
                randTime = Randomizer(DISK2_MIN,DISK2_MAX) + currentTime;
                priorityAppend(&eventQueue,eventGenerator(randTime,job.jobNumber,DISK_FINISH,2),&eventSize);
                computeAverage(&eventQueueAVG, averageGenerator(randTime, eventSize));
                disk2State = BUSY;
                utilizingServer(&disk2Time, currentTime, disk2State);

            }
        }
    }else{
        randTime = Randomizer(ARRIVE_MIN,ARRIVE_MAX) + currentTime;
        priorityAppend(&eventQueue,eventGenerator(currentTime,task->jobNumber,ARRIVAL,0),&eventSize);
        computeAverage(&eventQueueAVG, averageGenerator(currentTime, eventSize));
        if(task->diskAssign == 1){
            sprintf(str, "At time %d, Job%d finished I/O at Disk 1.",currentTime,task->jobNumber);
            processThroughput(&disk1Throughput, *task);
            logEvent(str);
            disk1State = IDLE;
            utilizingServer(&disk1Time, currentTime, disk1State);
        }else if (task->diskAssign == 2){
            sprintf(str, "At time %d, Job%d finished I/O at Disk 2.",currentTime,task->jobNumber);
            processThroughput(&disk2Throughput, *task);
            logEvent(str);
            disk2State = IDLE;
            utilizingServer(&disk2Time, currentTime, disk2State);
        }else{
          sprintf(str, "Error");
          logEvent(str);
        }
    }
}

/* --logEvent--
  PARAMETER:
    char *line - A string printed above containing task information
  FUNCTION:
    The funciton appends the character string to the log file dynamically
  RETURN:
    None, void function
*/
void logEvent(char *line){
    FILE * fp;
    fp = fopen ("log.txt","a");
    fprintf (fp,"%s\n",line);
    fclose (fp);
}

/* --finalCall--
  PARAMETER:
    None
  FUNCTION:
    Appends simulation end statement to the log file as well as a statistical printout.
  RETURN:
    None, void function
*/

void finalCall(){
  char str[80];
  sprintf(str, "The Simulation Ended");
  logEvent(str);
  char str2[80];
  sprintf(str2,"\n\nThe average size of the CPU Queue is -- %d jobs\n", returnAverage(&CPUAVG));
  logEvent(str2);
  char str3[80];
  sprintf(str3,"The maximum size of the CPU Queue is -- %d jobs\n", returnMax(&CPUAVG));
  logEvent(str3);
  char str4[80];
  sprintf(str4,"The CPU Utilization is -- %f%%\n", (cpuTime.totalBusy/(float)(FIN_TIME - INIT_TIME)) * 100);
  logEvent(str4);
  char str5[80];
  sprintf(str5,"The average response time of the CPU Queue is -- %d\n", averageResponseTime(&cpuThroughput));
  logEvent(str5);
  char str6[80];
  sprintf(str6,"The maximum response time of the CPU Queue is -- %d\n", maximumResponseTime(&cpuThroughput));
  logEvent(str6);
  char str7[80];
  sprintf(str7,"The throughput of the CPU Queue is -- %d Jobs\n\n\n", throughputCalculation(&cpuThroughput));
  logEvent(str7);
  char str8[80];
  sprintf(str8,"The average size of the Disk 1 Queue is -- %d jobs\n", returnAverage(&DISK_1_AVG));
  logEvent(str8);
  char str9[80];
  sprintf(str9,"The maximum size of the Disk 1 Queue is -- %d jobs\n", returnMax(&DISK_1_AVG));
  logEvent(str9);
  char str10[80];
  sprintf(str10,"The Disk 1 Utilization is -- %f%%\n", (disk1Time.totalBusy/(float)(FIN_TIME - INIT_TIME)) * 100);
  logEvent(str10);
  char str11[80];
  sprintf(str11,"The average response time of the Disk 1 Queue is -- %d\n", averageResponseTime(&disk1Throughput));
  logEvent(str11);
  char str12[80];
  sprintf(str12,"The maximum response time of the Disk 1 Queue is -- %d\n", maximumResponseTime(&disk1Throughput));
  logEvent(str12);
  char str13[80];
  sprintf(str13,"The throughput of the Disk 1 Queue is -- %d Jobs\n\n\n", throughputCalculation(&disk1Throughput));
  logEvent(str13);
  char str14[80];
  sprintf(str14,"The average size of the Disk 2 Queue is -- %d jobs\n", returnAverage(&DISK_2_AVG));
  logEvent(str14);
  char str15[80];
  sprintf(str15,"The maximum size of the Disk 2 Queue is -- %d jobs\n", returnMax(&DISK_2_AVG));
  logEvent(str15);
  char str16[80];
  sprintf(str16,"The Disk 2 Utilization is -- %f%%\n", (disk2Time.totalBusy/(float)(FIN_TIME - INIT_TIME)) * 100);
  logEvent(str16);
  char str17[80];
  sprintf(str17,"The average response time of the Disk 2 Queue is -- %d\n", averageResponseTime(&disk2Throughput));
  logEvent(str17);
  char str18[80];
  sprintf(str18,"The maximum response time of the Disk 2 Queue is -- %d\n", maximumResponseTime(&disk2Throughput));
  logEvent(str18);
  char str19[80];
  sprintf(str19,"The throughput of the Disk 2 Queue is -- %d Jobs\n\n\n", throughputCalculation(&disk2Throughput));
  logEvent(str19);
  char str20[80];
  sprintf(str20,"The average size of the Event Queue is -- %d jobs\n", returnAverage(&eventQueueAVG));
  logEvent(str20);
  char str21[80];
  sprintf(str21,"The maximum size of the Event Queue is -- %d jobs\n", returnMax(&eventQueueAVG));
  logEvent(str21);
}

/* --beginningCall--
  PARAMETER:
    None
  FUNCTION:
    Called at the beginning of the function to append a start simulation to the log file.
  RETURN:
    None, void function
*/

void beginningCall(){
  char str[80];
  sprintf(str, "The Simulation Started");
  logEvent(str);
}

/* --computeAverage--
  PARAMETERS:
    averageNode* queueAVG - The queue of each server queue's sizes after each relevant pop and push. Empty to start.
    averagetoAppend - A server queue size to be added to the data set.
  FUNCTION:
    1. Initializes a holder to retain the average to be appended.
    2. An averageNode struct *lastNode is assigned to the queue head
    3. If the average queue is empty the queue is swapped with the holder
    4. Otherwise, a while loop executes through the list until a null value is reached, the holder is appended to the end.
  RETURN:
    Included return statements to end the looping
*/


void computeAverage(averageNode** queueAVG, average toAppend){
  averageNode* holder = (averageNode*) malloc(sizeof(averageNode));
  holder->item = toAppend;
  holder->next = NULL;

  averageNode *lastNode = *queueAVG;
  if (*queueAVG == NULL){
      *queueAVG = holder;
      return;
  }
  while (lastNode->next != NULL)
      lastNode = lastNode->next;

  lastNode->next = holder;
  return;
}

/* --returnAverage--
  PARAMETERS:
    averageNode* queueAVG - The queue of each server queue's sizes after each relevant pop and push. Empty to start.
  FUNCTION:
    1. Initializes summation an elements integers for computing average
    2. An averageNode struct *lastNode is assigned to the queue head
    3. A while loop executes through the list until a null value is reached, in each increment,
       the queue size is added to summation, elements is incremented, lastNode moves to next node.
    4. Execution of loop eventually terminates when null value reached
  RETURN:
    The average number of events in each queue.
*/

int returnAverage(averageNode** queueAVG){
  int summation = 0;
  int elements = 0;
  averageNode *lastNode = *queueAVG;
  while (lastNode != NULL){
    summation += lastNode->item.size;
    elements++;
    lastNode = lastNode->next;
  }
  return (summation/(float)elements);
}

/* --returnMax--
  PARAMETERS:
    averageNode* queueAVG - The queue of each server queue's sizes after each relevant pop and push. Empty to start.
  FUNCTION:
    1. Initializes max integer to be a placeholder throughout the search loop
    2. An averageNode struct *lastNode is assigned to the queue head
    3. A while loop executes through the list until a null value is reached, in each increment,
       the queue size is compared with the current max value, max is replaced if size is greater.
       Else, the lastNode increments to the next element.
    4. Execution of loop eventually terminates when null value reached
  RETURN:
    The maximum number of events in each queue.
*/

int returnMax(averageNode** queueAVG){
  int max = 0;
  averageNode *lastNode = *queueAVG;
  while(lastNode != NULL){
    if(lastNode->item.size > max){
      max = lastNode->item.size;
    }
    else{
      lastNode=lastNode->next;
    }
  }
  return max;
}

/* --utilizingServer--
  PARAMETERS:
    utilization* queueAVG - The queue of each server queue's utilization information during processing.
    int currentTime - The time the utilization information is being logged.
    int serverState - The state of the server component at time of function call.
  FUNCTION:
    1. Determines if the server is IDLE. If so, the utilization queue is appended with the time since the server was busy,
       as well as an updated calculation of the total time that the server is busy in total.
  RETURN:
    None, void function
*/

void utilizingServer(utilization* server, int currentTime, int serverState) {
  if(serverState == IDLE) {
    server->currentTime = currentTime - server->currentTime;
    server->totalBusy = server->totalBusy + server->currentTime;
  }
  else {
    server->currentTime = currentTime;
  }
}

/* --processThroughput--
  PARAMETERS:
    throughput** server - A queue assigned to each respective server for logging response time and throughput information
    event forCompare - An event used to determine which server is active and append current information
  FUNCTION:
    1. Holder is assigned the event that will be used in the comparison stages of the function
    2. lastNode accesses the head of the queue
    3. Should the throughput server be empty, holder replaces the head.
    4. Else, job types determine what the event is doing.
    5. If it is a CPU or DISK arrival, the queue is traversed and the holder is appended
    6. If it is a CPU or DISK finished, the queue is traversed. If the job number of a stored queue node
       is the same as that of the temporary holder, this is considered an open event that has not been completed nor
       added to the throughput calculation. The responseTime value of the job is then calculated and assigned.
       The node is given a type of COMPUTED to indicate it will be considered a completed event and used for statistics.
  RETURN:
    Return's made to close the function prematurely when task accomplished
*/

void processThroughput(throughput** server, event forCompare){
  throughput* holder = (throughput*) malloc(sizeof(throughput));
  holder->job = forCompare;
  holder->next = NULL;

  throughput *lastNode = *server;
  if (*server == NULL){
      *server = holder;
      return;
  }

  else {
    if(holder->job.type == ARRIVAL){
      while (lastNode->next != NULL)
          lastNode = lastNode->next;

      lastNode->next = holder;
      return;
    }
    if(holder->job.type == FINISH){
      while (lastNode != NULL){
        if(lastNode->job.type != COMPUTED && lastNode->job.jobNumber == holder->job.jobNumber){
          lastNode->responseTime = (holder->job.time) - (lastNode->job.time);
          lastNode->job.type = COMPUTED;
          return;
        }
        else{
          lastNode = lastNode->next;
        }
      }
    }
    if(holder->job.type == DISK_ARRIVAL){
      while (lastNode->next != NULL)
          lastNode = lastNode->next;

      lastNode->next = holder;
      return;
    }
    if(holder->job.type == DISK_FINISH){
      while (lastNode != NULL){
        if(lastNode->job.type != COMPUTED && lastNode->job.jobNumber == holder->job.jobNumber){
          lastNode->responseTime = (holder->job.time) - (lastNode->job.time);
          lastNode->job.type = COMPUTED;
          return;
        }
        else{
          lastNode = lastNode->next;
        }
      }
    }
    }
  }

  /* --averageResponseTime--
    PARAMETERS:
      throughput** server - A queue assigned to each respective server for logging response time and throughput information
    FUNCTION:
      1. Initializes summation and element integers for average computation
      2. lastNode is set to the head of the throughput queue
      3. Queue is traversed, should the job type be COMPUTED, the summation is increased with the response time,
         elements increases. Else continue the loop.
    RETURN:
      The average response time of each server
  */

  int averageResponseTime(throughput** server){
    int summation = 0;
    int elements = 0;
    throughput *lastNode = *server;
    while (lastNode != NULL){
      if(lastNode->job.type == COMPUTED){
        summation += lastNode->responseTime;
        elements++;
        lastNode=lastNode->next;
      }
      else{
        lastNode=lastNode->next;
      }
    }
    return (summation/elements);
  }

  /* --maximumResponseTime--
    PARAMETERS:
      throughput** server - A queue assigned to each respective server for logging response time and throughput information
    FUNCTION:
      1. Initializes max as a placeholder for the maximum value in the throughput server
      2. lastNode is set to the head of the throughput queue
      3. Queue is traversed, should the job type be COMPUTED and the response time be greater than what is stored in
         max currently, max becomes this response time and the loop cointinues. Else loop continues.
    RETURN:
      The maximum response time of each server
  */

  int maximumResponseTime(throughput** server){
    int max = 0;
    throughput *lastNode = *server;
    while (lastNode != NULL){
        if(lastNode->job.type == COMPUTED && lastNode->responseTime > max){
          max = lastNode->responseTime;
          lastNode=lastNode->next;
        }
      else{
        lastNode=lastNode->next;
      }
    }
    return max;
  }

  /* --throughputCalculation--
    PARAMETERS:
      throughput** server - A queue assigned to each respective server for logging response time and throughput information
    FUNCTION:
      1. Initializes count as a placeholder for the number of items completed by each server
      2. lastNode is set to the head of the throughput queue
      3. Queue is traversed, should the job type be COMPUTED, the job is considered completed and the count is incremented.
    RETURN:
      The throughput of each server
  */

  int throughputCalculation(throughput** server){
    int count = 0;
    throughput *lastNode = *server;
    while(lastNode != NULL){
      if(lastNode->job.type == COMPUTED){
        count++;
        lastNode=lastNode->next;
      }
      else{
        lastNode=lastNode->next;
      }
    }
    return count;
  }
