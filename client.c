#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <ctype.h>


char * encrypt(char* str);
char* decrypt(char* str);
void login();
void error(const char *msg);
void file();

int main(int argc, char  *argv[]){
    int socket_fd, n, port;
    struct sockaddr_in server_addr;
    struct hostent *server;
    char buffer[256],*new_buffer;
    char choice , ans = 'y';
    
    //  password check , if wrong then exit to prevent brute forcing
//    login();

	printf("\033[0;35m[-]Enter \'y\' for chat or \'f\' for file transfer : \033[0m");
	scanf("%c" , &choice);
	
	if(choice == ans){
   	

	        if(argc < 3)
	        fprintf(stderr,"usage %s hostname port\n",argv[0]);


	    port = atoi(argv[2]);
	    socket_fd = socket(AF_INET , SOCK_STREAM ,0);
	    

	    if(socket_fd < 0)
	        error("Error opening socket !");
	    
	    server = gethostbyname(argv[1]);
	    if(server == NULL)
	        fprintf(stderr,"NO such host !");
	    
	    

	    bzero((char *)&server_addr , sizeof(server_addr));
	    server_addr.sin_family = AF_INET;
	    bcopy((char *) server->h_addr , (char *) &server_addr.sin_addr.s_addr, server->h_length); // transfering from *server to server_addr
	    
	    server_addr.sin_port = htons(port);
	    if(connect(socket_fd , (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0)
	        error("Connection failed");

	        printf("\033[5;34m");
	        printf("[*]Connection To Server Established \n[*]Communication is end to end encrypted\n"); printf("\033[0m");
	        printf("\033[0;35m[*] Enter \"help\" for help menu \n[*] Enter \"Bye\" to exit !\n\033[0m");
	   
	   	

	      		while(1){
	 

		        bzero(buffer,256);
		        printf("[you]:> ");
		        fgets(buffer,sizeof(buffer),stdin);
		        
	// ========================= exiting if user enteres bye ========================== //

		        if(strncmp("bye",buffer , 3) == 0)
			 break;

	// ==================================================================================//
	
		        new_buffer = encrypt(buffer);
		        n = write(socket_fd, new_buffer, strlen(new_buffer));  
		        bzero(new_buffer,256);
		        n = read(socket_fd, buffer , 256);
		        new_buffer = decrypt(buffer);
		        printf("[Server]:>  %s", new_buffer);	
		    }
    }
      
    else{
    
     		if(argc < 3)
	        fprintf(stderr,"usage %s hostname port\n",argv[0]);


	    port = atoi(argv[2]);
	    socket_fd = socket(AF_INET , SOCK_STREAM ,0);
	    

	    if(socket_fd < 0)
	        error("Error opening socket !");
	    
	    server = gethostbyname(argv[1]);
	    if(server == NULL)
	        fprintf(stderr,"No such host !");
	    
	    

	    bzero((char *)&server_addr , sizeof(server_addr));
	    server_addr.sin_family = AF_INET;
	    bcopy((char *) server->h_addr , (char *) &server_addr.sin_addr.s_addr, server->h_length); // transfering from *server to server_addr
	    
	    server_addr.sin_port = htons(port);
	    if(connect(socket_fd , (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0)
	        error("Connection failed");
	        
	       char *file_name = malloc(100);
	        printf("\033[0;37m[-]Enter name of file with the extension (.txt / .exe ...): \033[0m");
	        scanf("%100s",file_name);
	    
       		FILE *FPtr;
       		int words = 0;
       		char ch, c;

		    FPtr = fopen(file_name,"r");
		    
		    // counting the number of words in the file
		    while((c = getc(FPtr))!= EOF){
		    
		        fscanf(FPtr,"%s",buffer);
		        if(isspace(c))
			    words++;
		    }

		    write(socket_fd,&words,sizeof(words));
		    rewind(FPtr);

		    // sending the file
		    while(ch != EOF){

		    fscanf(FPtr,"%s", buffer);
		    write(socket_fd,buffer,256);
		    ch = fgetc(FPtr);
		    }
		
		    printf("\033[0;34m[*] File has been sent !!\n\033[0m");
		
 		
 		
 		}

 	    
	

    printf("\033[0;31m ====== !!!  Connection Closed !!! ====== \033[0m"); 
   
    close(socket_fd);

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

void login(){
    char pass[12];
    printf("Enter the  password: ");
    fgets(pass, 12, stdin);

     int i = strncmp("password123", pass , 12);
     if (i != 0)
        exit(1);
}

void error(const char *msg){
    perror(msg);
    exit(1);
}

