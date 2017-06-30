/*****************************
 * 
 * Author : undefined
 * version : 1.0
 * tool name : ftsize
 * 
 *****************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<getopt.h>
#include<string.h>
#include<dirent.h>
#include<sys/stat.h>

#define AUTHOR "undefined"
#define TOOL_NAME "ftsize"
#define VERSION "1.0"
#define MSG "Tool Usage :=> When given an extension it will scan the [specified_path] and return the sum of all file sizes having the specified_extension"

#define PATH_SIZE 254

/*** function declarations **/

//function which we will use for debugging purpose.
//functions take an char* as msg to print when existing.
void die(char *msg);

//function we will be using to traverse the directories.
//takes extension=(c,cpp,etc) and traverse and return the collective size of the file with same extension.
void traverse_direct(char *ext, char *path, long *nb);

//function used to show details regarding size's(i.e B,KB,MK.etc)
//we pass bytes as an argument to the function , the function prints its equivalent Kb,Mb,etc forms.
void show_detail(long bytes);

/*** main function ***/

int main(int argc, char **argv){
	extern char *optarg;
	char c;
	char path[PATH_SIZE];
	long nb=0;	
	//default initailisation.
	//default path = "/" root directory.
	strcpy(path, "/");
	
	//if no argument specified exit.
	if(argc == 1){
		fprintf(stderr, "%s  <extension> [-h -v -p]\n", argv[0]);	
		exit(1);
	}

	//scan for options (-option)
	while((c=getopt(argc, argv, "hvp:"))!=-1){
		switch(c){
			case 'h':
				//help option.
				
				printf("%s\n\n\t\t%s  <extension> [-h -v -p]\n", MSG, argv[0]);
				exit(0);
			break;

			case 'v':
				//version detail option.

				printf("Author = %s\nTool Name = %s\nVersion Number = %s \n",AUTHOR,TOOL_NAME,VERSION);
				exit(0);
			break;

			case 'p':
				//path specify option.
				strcpy(path, optarg);//we copy the -p specified_path in to the path variable.
				traverse_direct(argv[1], path, &nb);
				show_detail(nb);		

			break;

			case '?':
				//when invailed option passed exit.
				exit(1);
			break;
		}
	
	}
	//not specific path specified so scan full system (i.e '/' root directory).
	if(argc==2){	
		traverse_direct(argv[1], path, &nb);
		show_detail(nb);		
	}
			
	return 0;
}

void die(char *msg){
	perror(msg);
	exit(1);
}

void show_detail(long bytes){
	double dbytes=bytes;
	printf("Bytes	  : %ld B's\n", bytes);
	//to prevent DevideByZero error, check if the bytes == 0.
	if(bytes==0)return;
	printf("KibiBytes : %lf KiB's\n", dbytes/1024.0);
	printf("MibiBytes : %lf Mib's\n", (dbytes/1024.0)/1024.0);
}

void traverse_direct(char *ext, char *path, long *nb){
	DIR *d=opendir(path);
	struct dirent *dir;
	struct stat st;
	
	int plen,len1,len2;//stores the path_len.
	char *pos;
	
	if(d==NULL)return ;
	
	while((dir=readdir(d))!=NULL){
		//if its '.' or '..' directories ignore them.
		if(strcmp(".",dir->d_name)==0 || strcmp("..",dir->d_name)==0)continue;
		
		//if its an directory recrusively call this func within it. 
		len1=strlen(path);
		len2=strlen(dir->d_name);
		plen=len1+len2;
		char tmp_path[plen];
	        
		if(path[len1-1]=='/')path[len1-1]='\0';	
		sprintf(tmp_path, "%s/%s",path,dir->d_name);
		
		if(dir->d_type == DT_DIR){
			//generate the new path and store it into tmp_path.
			traverse_direct(ext, tmp_path, nb);
		}else{
			//comparing the specified extension with files.
			pos=strrchr(dir->d_name, '.');
			if(pos!=NULL && strcmp(pos+1, ext)==0){
				lstat(tmp_path, &st);
				*nb = *nb + st.st_size;
				//printf("%ld => %s\n",st.st_size, tmp_path);
			}
		}
	}
	closedir(d);
}
