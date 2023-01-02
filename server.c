#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <ctype.h>


char * encrypt(char* str);
char* decrypt(char* str);
void error(const char *msg);
void file();

// arg c is total number of pareameters, argv contains original perameters
int main(int argc , char *argv[]){
    
    if(argc < 2){
        fprintf(stderr,"Port not specified, terminating ...\n");
        exit(1);
    }

    int socket_fd , new_socket_fd , port, n,flag;
    char buffer[256], *new_buffer;
    char choice , ans = 'y';
    
    printf("\033[0;35m[-]Enter \"y\" for chat or \"f\" for file transfer: \033[0m");
    scanf("%c" , &choice);
    if(choice == ans){
    
    
	    struct sockaddr_in server_addr , client_addr;
	    socklen_t clilen;

	    //initializing the socket
	    
	    socket_fd = socket(AF_INET,SOCK_STREAM,0);
	    if(socket_fd < 2)
	        error("Error opening socket");

	    bzero((char *)&server_addr, sizeof(server_addr));
	    port = atoi(argv[1]); // extracts port# from argv and converts it to int

	    server_addr.sin_family = AF_INET;
	    server_addr.sin_addr.s_addr = INADDR_ANY;
	    server_addr.sin_port = htons(port);
	    if(bind(socket_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0)
	        error("Binding failed !");

	    // listening for connections
	    
	    listen(socket_fd,5);
	    clilen = sizeof(client_addr);

	    // accepting connections
	        
	    new_socket_fd = accept(socket_fd , (struct socket_addr *)& client_addr , &clilen);
	    if(new_socket_fd < 0 )
	        error("Error Accepting the connection !");

	    printf("\033[5;34m");
	    printf("[*] Connection To Client Established \n[*]Communication is end to end encrypted\n"); printf("\033[0m");
	    printf("\033[0;35m[*] Enter \"help\" for help menu \n[*] Enter \"Bye\" to exit !\n\033[0m");

		

		   while(1){
			   
			   
			        bzero(buffer,256);

			        
			        n = read(new_socket_fd , buffer , 256);
			          new_buffer = decrypt(buffer); 
			        
			        printf("[Client]:>  %s",new_buffer);
			        bzero(buffer , 256);
			        printf("[you]:> ");
			        fgets(buffer , 256, stdin);
			        
			// ================================ if server admin enters bye , we exit ============================ //

			        if(strncmp("bye",buffer , 3) == 0 )
				 break;
				 

				
			        new_buffer = encrypt(buffer);
			        n = write(new_socket_fd ,new_buffer , strlen(new_buffer));


			    }
			
	}
	
	else {
              
              struct sockaddr_in server_addr , client_addr;
	    socklen_t clilen;

	    //initializing the socket
	    
	    socket_fd = socket(AF_INET,SOCK_STREAM,0);
	    if(socket_fd < 2)
	        error("Error opening socket");

	    bzero((char *)&server_addr, sizeof(server_addr));
	    port = atoi(argv[1]); // extracts port# from argv and converts it to int

	    server_addr.sin_family = AF_INET;
	    server_addr.sin_addr.s_addr = INADDR_ANY;
	    server_addr.sin_port = htons(port);
	    if(bind(socket_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0)
	        error("Binding failed !");

	    // listening for connections
	    
	    listen(socket_fd,5);
	    clilen = sizeof(client_addr);

	    // accepting connections
	        
	    new_socket_fd = accept(socket_fd , (struct socket_addr *)& client_addr , &clilen);
	    if(new_socket_fd < 0 )
	        error("Error Accepting the connection !");
              
              
              
              FILE *Fptr;
	    int ch = 0 , words; 
	    
	    Fptr = fopen("received.txt", "a");
	    read(new_socket_fd, &words, sizeof(int));
	    
	    // reading and writing the words
	    while(ch != words){
	    
	    	read(new_socket_fd, buffer,256);
	    	fprintf(Fptr, "%s ", buffer);
	    	ch++;
	    }
	    
	    printf("[*] File received \n" );
    }
		
	
// ====================================================================================================== //}
    // closing the socket once communication is terminated

    close(new_socket_fd);
    close(socket_fd);

    printf("\033[0;31m ====== !!! Connection Closed !!! ====== \033[0m");

    return 0;
}

char * encrypt(char* str) {
	
	for (int i = 0; i < strlen(str); i++) {
		str[i] = str[i] + 7;
	}
	return str;
}

char* decrypt(char* str) {

	for (int i = 0; i < strlen(str); i++) {
		str[i] = str[i] - 7;
	}
	return str;
}

void error(const char *msg){
       perror(msg); // built in function to evaluate error
       exit(1); // terminates the program
}

