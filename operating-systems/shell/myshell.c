// Sean Droke
// Temple University -- CIS 3207
// Project 2

/*
PROGRAM DESCRIPTION: The following is an implementation of a command line shell program,
                     It is written in the C programming language and utilizes the following
                     libraries and files to function correctly.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <dirent.h>
#include <fcntl.h>

/*
FUNCTION INITIALIZATION:
*/

char *readline (FILE *fp, char **buffer);
int prompt();
int processPrompt(char *userInput);
int executeBackgroundBlock(char* command);
int executePipeBlock(char* command);
int executeIOBlock(char* command);
int executeNormalBlock(char* command);
char **parser(char *str);
int checker(char **arguments, char* command);

/*
CONSTANT/GLOBAL VARIABLE INITIALIZATION:
*/

#define START 0
#define STOP 1

int promptStatus;

char error_message[30] = "An error has occurred\n";


/*
--MAIN FUNCTION--

DESCRIPTION:
  - Main is invoked from the terminal and can be given a batchfile or called alone
  - Should the batchfile require processing it is opened, each line is read and sent to the processor,
    at completion the batchfile is closed and the program quits.
  - Else, a prompt is printed to screen consecutively until the user terminates the shell

PARAMETERS
  char *argc, *argv[] - Commands invoked at program execution to allow for batchfile input

RETURN
  0 : Completed Process
  1 : Error Incurred Processing Batch File
*/

int main(int argc, char* argv[]) {
  if(argv[1] != NULL){
    FILE *fp = argc > 1 ? fopen(argv[1], "r") : stdin;
    if(!fp){
      write(STDERR_FILENO, error_message, strlen(error_message));
      exit(1);
    }
    char *line = NULL;
    size_t idx = 0;
    while (readline(fp, &line)){
      processPrompt(line);
      free(line);
      line = NULL;
    }
    if(fp != stdin) fclose(fp);
  }
  else{
    promptStatus = START;
    while(promptStatus != STOP){
      prompt();
    }
  }
  return 0;
}

/*
--READ LINE FUNCTION--

DESCRIPTION:
  - Function to process each line from a batchfile, it is invoked with the file and reference to line
  - buffer/line is dynamically allocated at start to a default value 64
  - Exception error thrown if memory does not exist to accomplish the task
  - Characters then read in a stream, allocating memory accordingly as needed
  - Memory is then released by the function and the line of characters is returned

PARAMETERS
  FILE *fp - Batch File
  char **buffer - Reference to line

RETURN
  Line read from batch file for processing
*/

char *readline(FILE *fp, char **buffer){
  int ch;
  size_t buflen = 0, nchar = 64;

  *buffer = malloc(nchar);
  if(!*buffer){
    write(STDERR_FILENO, error_message, strlen(error_message));
    exit(1);
  }
  while ((ch = fgetc(fp)) != '\n' && ch != EOF){
    (*buffer)[buflen++] = ch;
    if(buflen + 1 >= nchar){
      char *tmp = realloc(*buffer, nchar * 2);
      if(!tmp){
        write(STDERR_FILENO, error_message, strlen(error_message));
        (*buffer)[buflen] = 0;
        return *buffer;
      }
      *buffer = tmp;
      nchar *= 2;
    }
  }
  (*buffer)[buflen] = 0;
  if(buflen == 0 && ch == EOF){
    free(*buffer);
    *buffer = NULL;
  }
  return *buffer;
}

/*
--PROMPT FUNCTION--

DESCRIPTION:
  - Prompt is called repeatedly and serves to read input from user and display a prompt/working directory
  - A cwd array is initialized to hold the complete current working directory in the users prompt
  - getcwd() internal function is used to obtain the cwd
  - Prompt printed, memory management takes place to store a full command from the user
  - User invokes a character stream that is read in and appended to a character array for processing
  - Input is then sent for processing and the memory is freed

PARAMETERS
  None

RETURN
  Error
  None otherwise
*/

int prompt(){
  char cwd[PATH_MAX];
  if(getcwd(cwd, sizeof(cwd)) != NULL){
    printf("\nMyPrompt %s>", cwd);
    int length = 64;
    char *input = malloc(length * sizeof(char));
    int count = 0;
    char c;
    while((c = getchar()) != '\n'){
      if(count >= length){
        input = realloc(input, (length += 10) * sizeof(char));
      }
      input[count++] = c;
    }
    processPrompt(input);
  }
  else{
    printf("Error");
  }
  return 0;
}

/*
--PROCESS PROMPT FUNCTION--

DESCRIPTION:
  - A string is created from whatever is sent be it a command from prompt or line from batchfile
  - Using built in string functions, it can be determined where the process needs to be sent
  - & sends for background processing
  - | sends for piping
  - < or > indicate IO functionality
  - If none of the above, then process can be executed normally

PARAMETERS
  char *userInput - Either a user command or a command from batchfile

RETURN
  None, no error handling needed.
*/

int processPrompt(char *userInput){
  int i = 0;
  int j = 0;
  while(userInput[i]){
    i++;
    j++;
  }
  j++;
  char command[j];
  strncpy(command, userInput, j);
  command[j] = '\0';
  
  if(command[j-2] == '&'){
    executeBackgroundBlock(command);
  }
  else if(strstr(command, "|")){
    executePipeBlock(command);
  }
  else if(strstr(command, "<") || strstr(command, ">")){
    executeIOBlock(command);
  }
  else{
    executeNormalBlock(command);
  }
  return 0;
}

/*
--PARSER FUNCTION--

DESCRIPTION:
  - Used in processing to dilliniate between text and white space
  - Invoked with a string
  - Array of string arguments is generated, an argument placeholder is used as a temp variable
  - The string is tokenized by white space with the exception of the & value
  - Each argument is passed to the arguments array until NULL reached
  - Arguments array returned

PARAMETERS
  char *string - String requiring parsing

RETURN
  Array of argument strings
*/

char **parser(char *string) {
	char **arguments = malloc(1024 * sizeof(char*));
	char *argument;
  
  int i=0;
  int j = 0;
	argument = strtok(string, "  \t\n");
	while ((argument != NULL)) {
		arguments[i] = argument;
		argument = strtok(NULL, "  \t\n");
		i++;	
	}
  if(strstr(arguments[i-1], "&") != NULL){
    arguments[i-1] = NULL;
  }
  else{
    arguments[i] = NULL;
  }
	return arguments;
}

/*
--EXECUTE NORMAL BLOCK FUNCTION--

DESCRIPTION:
  - A normal block contains no special characters and is executing a simple command
  - The command string is parsed for a set of arguments, arguments are checked for any noted built ins
  - PID generated through a fork
  - If succesful, built in execvp() runs the command - will generate an error and exit should the command be wrong
  - In normal processing a wait() call is needed

PARAMETERS
  char *command - Command requiring processing of this type

RETURN
  0: Success
  Error and exit()
*/

int executeNormalBlock(char *command) {
	char **arguments = parser(command);
	
  if (checker(arguments, command) == 0) {
    return 0;
	}
	
  int pid = fork();
	if (pid == 0) {
		if (execvp(arguments[0], arguments) != 0) {
			write(STDERR_FILENO, error_message, strlen(error_message));
			exit(0); 
		}
	} 
  else {
		wait(NULL);
	}
	
  return 0;
}

/*
--EXECUTE BACKGROUND BLOCK FUNCTION--

DESCRIPTION:
  - A background block is similar to a normal block but completes the command in the background
  - The command string is parsed for a set of arguments, arguments are checked for any noted built ins
  - PID generated through a fork
  - If succesful, built in execvp() runs the command - will generate an error and exit should the command be wrong
  - In background processing no wait() call is needed

PARAMETERS
  char *command - Command requiring processing of this type

RETURN
  0: Success
  exit() if error
*/

int executeBackgroundBlock(char *command) {
	char **arguments = parser(command);

  if (checker(arguments, command) == 0) {
		return 0;
	}	

  int pid = fork();
  if (pid == 0) {
    if (execvp(arguments[0], arguments) != 0) { 
			write(STDERR_FILENO, error_message, strlen(error_message));
			exit(0);
		}
  } 
  
  return 0;
}

/*
--CHECKER FUNCTION--

DESCRIPTION:
  - Checker is responsible for taking in tokenized arguments and the full command to process some built in tasks
  - Each time the function is called it compares the argument string with a series of possibilities
  - Should argument array at 0 be null then it is empty and cannot proceed
  - Should cd be the command then the existing argument is passed to chdir() to change locations within the file system
  - Should clr be the command then execvp() processes a system clear
  - Should dir be the command, a pointer is initialiazed to hold the directory, the dirent struct holds a directory entry,
    a path is then generated using the arguments and as long as the directory can be opened a wile loop traverses the directory stream
    printing the names of the directory as it goes before subsequently closing.
  - environ will print relevant environment strings
  - echo allocates memory to a string that will be echo'd, arguments are appended to the string and execvp() echo's the arguments
  - help reveals the manual
  - pause calls for the system to wait until a newline is entered
  - quit will end the program

PARAMETERS
  char **arguments - Arguments tokenized
  char *command - Command requiring processing of this type

RETURN
  0: Success
  -1 or exit() if error
*/

int checker(char **arguments, char* command) {
	
  if (arguments[0] == NULL) {
    write(STDERR_FILENO, error_message, strlen(error_message));
		return -1;
	}
	
  if (strcmp(arguments[0], "cd") == 0) {
		if(chdir(arguments[1]) != 0) {
			write(STDERR_FILENO, error_message, strlen(error_message));
			return -1;
		}
		return 0;	
	} 
  
  else if (strcmp(arguments[0], "clr") == 0) {
    int pid = fork();
    if (pid == 0) {
      if(execvp("clear", (char *const[]){"clear", NULL}) != 0){
        write(STDERR_FILENO, error_message, strlen(error_message));
        return -1;
      }
    } 
    else {
      wait(NULL);
    }
		return 0;
	} 
  
  else if (strcmp(arguments[0], "dir") == 0) {
		DIR *dp;
		struct dirent *list;
		char path[PATH_MAX];
		strcpy(path, arguments[1]);
		if ((arguments[1] == NULL) || ((dp = opendir(path)) == NULL)) {
			write(STDERR_FILENO, error_message, strlen(error_message));
			return -1;
		} 
    else {
			while ((list = readdir(dp))) {
				printf("%s\n", list -> d_name);
			}
			closedir(dp);
		}
		return 0;
	} 
  
  else if (strcmp(arguments[0], "environ") == 0) {
		int counter = 7;
    char* variables[] = {"USER", "HOME", "PATH", "SHELL", "OSTYPE", "PWD", "GROUP"};
    int i = 0;
    for(i = 0; i < counter; i++){
      const char *x = getenv(variables[i]);
      if(x != NULL){
        printf("%s  -   %s\n", variables[i], x);
      }
      else{
        write(STDERR_FILENO, error_message, strlen(error_message));
			  return -1;
      }
    }	
		return 0;
	} 
  
  else if (strcmp(arguments[0], "echo") == 0) {
    int pid = fork();
    if (pid == 0) {
      if((execvp("echo", arguments)) != 0){
      write(STDERR_FILENO, error_message, strlen(error_message));
      return -1;
      }
    } 
    else {
      wait(NULL);
    }
		return 0;
	}
  
  else if (strcmp(arguments[0], "help") == 0) {
    char fileName[] = "readme";
    FILE *fptr;
    char c;
    fptr = fopen(fileName, "r");
    if(fptr == NULL){
      write(STDERR_FILENO, error_message, strlen(error_message));
      return -1;
    }
    c = fgetc(fptr);
    while(c != EOF){
      printf("%c", c);
      c = fgetc(fptr);
    }
    fclose(fptr);
    return 0;
	}
  
  else if (strcmp(arguments[0], "pause") == 0) {
		char c;
		printf("Shell is paused. Enter to continue.\n");
		while ((c = getchar()) != '\n') {
		}
		return 0;
	}

  else if (strcmp(arguments[0], "quit") == 0) {
    exit(1);
  }

	return -1;
}

/*
--EXECUTE IO BLOCK FUNCTION--

DESCRIPTION:
  - When a command arrives for IO, it is parsed for tokenized arguments, and the command to be executed is given a variable
  - Parameters are then subsequently appended for the command
  - Simple calculation is done to determine the number of inputs and outputs done within the command
  - With the necesarry variables set to begin IO Processing a series of comparisons are completed
  - If inputs and outputs are both one, a pid is generated using a fork and two files are opened from the argument list as long
    as they exist, one will be for input and the other for output. execvp() processes the command and files are subsequently 
    closed, pid wait.
  - Alternatively there might be 2 outputs which really means there is one output but the instruction is then to create the
    file should it not already exist, hence properties applied to the open() function. Once more there is input, so the process
    behaves similar to above with a pid, opened files, and execution. At completion files are closed and pid wait.
  - Another option is for 2 outputs and no inputs. Again 2 outputs executes in a way that creates a file should it not exist.
    In this circumstance without input, the command may not be internally recognized by execvp() so calling checker will determine if
    any built in commands are needed. Else if execvp() passes, file is closed.
  - The final two scenarios involve singular input or output. In either scenario the file is opened with respective parameters,
    execvp() (also checker for output) executes and the files are then closed

PARAMETERS
  char *command - Command requiring processing of this type

RETURN
  0: Success
  exit() if error
*/

int executeIOBlock(char *command) {
	char** arguments = parser(command);
	
  char* primaryCommand = arguments[0];
	
  int i = 0;
  int lock = 0;
  while(lock == 0){
    if(arguments[i] == NULL){
      lock = 1;
    }
    else if(arguments[i][0] == '>' || arguments[i][0] == '<'){
      i++;
    }
    else{
      i++;
    }
  }
  
  char *parameters[i];
	
	int j =0;
	int inputs = 0;
	int outputs = 0;
  lock = 0;
  int z = 0;

	while (lock == 0) {
    if(arguments[j] == NULL){
      parameters[z] = NULL;
      lock = 1;
    }
    else if(arguments[j][0] == '<'){
      j++;
    }
    else if(arguments[j][0] == '>'){
      j++;
    }
    else{
      parameters[z] = arguments[j];
      j++;
      z++;
    } 
	}

	int count = 0;
	while (command[count] != '>') {
		count++;
	}	

	int k = 0;
  while (arguments[k] != NULL) {
		if (arguments[k][0] == '<') {
			inputs++;
		} 
    else if (arguments[k][0] == '>') {
      outputs++;
			if ((command[count+1]) && (arguments[k][1] == '>')) {
				outputs++;
			}
		}
		k++;
	}

	if ((inputs == outputs) == 1) {     
	  pid_t pid = fork();
		if (pid == 0) {
			int fd_in = open(arguments[j+1], O_RDONLY);
			int fd_out = open(arguments[j+3], O_WRONLY|O_CREAT|O_TRUNC,S_IRWXU|S_IRWXG|S_IRWXO);
			dup2(fd_in, 0);
			dup2(fd_out, 1);
			if (execvp(primaryCommand, parameters) != 0) {
				write(STDERR_FILENO, error_message, strlen(error_message));
				exit(0);
			}
			close(fd_in);
			close(fd_out);
		} 
    else {
			waitpid(pid, NULL, 0);
		}
		return 0;
	 } 
   
  else if ((outputs == 2) && (inputs == 1)) {
	  pid_t pid = fork();	
		if (pid == 0) {
			int fd_in = open(arguments[j+1], O_RDONLY);
			int fd_out = open(arguments[1+3], O_WRONLY|O_CREAT|O_APPEND,S_IRWXU|S_IRWXG|S_IRWXO);
			dup2(fd_in, 0);
			dup2(fd_out, 1);
			if (execvp(primaryCommand, parameters) != 0) {
        write(STDERR_FILENO, error_message, strlen(error_message));
				exit(0);
			}
			close(fd_in);
			close(fd_out);
		} 
    else {
			waitpid(pid, NULL, 0);
		}
	} 
  
  else if ((outputs == 2) && (inputs==0)) {
		pid_t pid = fork();
		if (pid == 0) {
			int fd = open(arguments[j+1], O_WRONLY|O_CREAT|O_APPEND,S_IRWXU|S_IRWXG|S_IRWXO);
			dup2(fd, 1);
			if (checker(arguments, command) == 0) {						
			} 
      else if (execvp(primaryCommand, parameters) != 0) {
        write(STDERR_FILENO, error_message, strlen(error_message));
				exit(0);
			}
			close(fd);
			exit(0);
		} 
    else {
			waitpid(pid, NULL, 0);
		}
	} 
  
  else if (inputs == 1) {
		pid_t pid= fork();
		if (pid == 0) {
			int fd = open(arguments[j-1], O_RDONLY);
			dup2(fd, 0);
			if (execvp(primaryCommand, parameters) != 0) {
        write(STDERR_FILENO, error_message, strlen(error_message));
				exit(0);
			}
			close(fd);
		} 
    else {
			waitpid(pid, NULL, 0);
		}		
  } 
  
  else if (outputs == 1) {
		pid_t pid = fork();
		if (pid == 0) {
			int fd = open(arguments[j-1], O_WRONLY|O_CREAT|O_TRUNC,S_IRWXU|S_IRWXG|S_IRWXO);
			dup2(fd, 1);
			if (checker(arguments, command) == 0) {			
			}
			if (execvp(primaryCommand, parameters) != 0) {
        write(STDERR_FILENO, error_message, strlen(error_message));
				exit(0);	
			}
			close(fd);
		} 
    else {
			waitpid(pid, NULL, 0);
		}
	}
	 
  return 0;
}

/*
--EXECUTE PIPE BLOCK FUNCTION--

DESCRIPTION:
  - When a command arrives for Piping, it is parsed for tokenized arguments
  - for the initial half of the pipe, a command is retrieved from the arguments, which should always be position 0
  - To determine the size of argument array, a while loop executes until the pipe symbol | is reached
  - A parameters array is then populated with parameters from the first half of the pipe
  - After this, an additional command is sourced using the same command.
  - It's primary command is sourced from the position in the array directly after the pipe | symbol.
  - It's parameters are also appended given their respective size and both halves are then ready for execution
  - 2 file descriptors are used in the pipe() function, the pid is determined from fork(), should it be 0, then 
    the first half is subsequently dup(), file descriptors closed, and the command and parameters checked and executed
  - Should the pid not be 0 then a fork of the pid is generated and the second half of the process undergoes the same sequence above
  - Finally one last call to close any open fd's and the function returns

PARAMETERS
  char *command - Command requiring processing of this type

RETURN
  0: Success
  exit() if error
*/

int executePipeBlock(char* command) {
	char** arguments = parser(command);
	
  char* primaryCommand1 = arguments[0];
	
	int i = 0;
	while (arguments[i][0] != '|') { 
		i++;
	}
	
  char* parameters1[i];
  
  int j = 0;
  while(arguments[j][0] != '|'){
    parameters1[j] = arguments[j];
    j++;
  }
  parameters1[j] = NULL;
  j++;

	int k = j;
  int paramSize2 = 0;
  while(arguments[k] != NULL){
    k++;
    paramSize2++;
  }

  char* primaryCommand2 = arguments[j];
  char* parameters2[paramSize2];

  int l = 0;
	while (arguments[j] != NULL) {
		parameters2[l] = arguments[j];
		j++;
		l++;
	}
	parameters2[l] = NULL;
	
	pid_t pid1, pid2;
  int fd[2];
	pipe(fd);
  pid1 = fork();
	if (pid1 == 0) {
		dup2(fd[1], 1);
		close(fd[0]);
		if (checker(parameters1, command) == 0) {			
		}	
		if (execvp(primaryCommand1, parameters1) != 0) {
      printf("error here");
      write(STDERR_FILENO, error_message, strlen(error_message));
			exit(0);
		} 
	} 
  else {
		pid2 = fork();
		if (pid2 == 0) {
			dup2(fd[0], 0);
			close(fd[1]);
			if (checker(parameters2, command) == 0) {
			}
			if (execvp(primaryCommand2, parameters2) != 0) {
        printf("error here too");
        write(STDERR_FILENO, error_message, strlen(error_message));
				exit(0);
			}
		}
    else if(pid2 < 0){
      write(STDERR_FILENO, error_message, strlen(error_message));
			exit(0);
    }
    else{
      close(fd[0]);
      close(fd[1]);

      waitpid(pid1, NULL, 0);
      waitpid(pid2, NULL, 0);
    } 
	}
	return 0;
}



