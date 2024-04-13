////////////////////////////////////
///                              ///
///        ALEX OLHOVSKIY        ///
///                              ///
////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

void makeTxtFile(char*name,int count,int maxWordSize,int minWordSize,int isNum){
    int i,j,n;
    char c=0;
    FILE*fd=fopen(name,"w");
    if(fd!=NULL){
        printf("Opened\n");
        for(i=0;i<count;i++){
            if(isNum==1){
                if(i%5==0){
                    n=1+rand()%minWordSize;
                    for(j=0;j<n;j++){
                        c=48+rand()%10;
                        fprintf(fd,"%c",c);
                    }
                }else{
                    n=minWordSize+rand()%(maxWordSize-minWordSize);

                    for(j=0;j<n;j++){
                        if(j==0){
                            c=65+rand()%26;
                        }else{
                            c=97+rand()%26;
                        }
                        fprintf(fd,"%c",c);
                    }
                }
            }else{
                n=minWordSize+rand()%(maxWordSize-minWordSize);
                for(j=0;j<n;j++){
                    if(j==0){
                        c=65+rand()%26;
                    }else{
                        c=97+rand()%26;
                    }

                    fprintf(fd,"%c",c);
                }
            }

            fprintf(fd," ");
        }
        fclose(fd);
    }else{
        printf("Cannot open!\n");
    }
}

void printFile(char*name){
    char buffer[256]={0};
    FILE*fd=fopen(name,"r");
    if(fd!=NULL){
        printf("\n");
        while(fscanf(fd,"%s",buffer)==1){
            printf("%s ",buffer);
        }
        fclose(fd);
    }else{
        printf("Cannot open!\n");
    }
}

void getLinkedFile(char*str,char*name){
    int i=0,n=0;
    while(str[i]){
        if(str[i]=='.'){
            name[i+n]='_';
            n++;
            name[i+n]='1';
            n++;
        }
        name[i+n]=str[i];
        i++;
    }
    name[i+n]='\0';
}


void putAsFragment(char*sourceFile,char*distFile){
    FILE* fdSource = fopen(sourceFile, "r");
    FILE* fdDist = fopen(distFile, "a+");
    char border[]="\n==============================================\n";
    char buffer[256]={0};
    if(fdSource!=NULL&&fdDist!=NULL){
        fputs(border,fdDist);
        while(fgets(buffer, 256, fdSource) != NULL){
            fputs(buffer,fdDist);
        }
        fputs(border,fdDist);
        fclose(fdSource);
        fclose(fdDist);
    }else{
        printf("Cannot open\n");
    }
}

void neighbourSwap(char*name,char*linkedFile){
    char c[2]={0},temp=0,space=0;

    FILE*fd=fopen(name,"a+");
    FILE*lfd=fopen(linkedFile,"a+");

    int i=0;
    if(fd!=NULL&&lfd!=NULL){
        printf("Opened!");
        while((temp=fgetc(fd))!=EOF){
            if(temp==' '){
                if(i==1){
                    space=temp;
                }
                else{
                    fputc(temp,lfd);
                }
            }else{
                c[i]=temp;
                i++;
                if(i>1){
                    fputc(c[1],lfd);
                    if(space==' '){
                        fputc(space,lfd);
                        space=0;
                    }
                    fputc(c[0],lfd);
                    i=0;
                }
            }
        }
        if(i==1){
            fputc(c[0],lfd);
        }
        fclose(fd);
        fclose(lfd);
    }else{
        printf("Cannot open!");
    }
    putAsFragment(linkedFile,name);
}


void removeTwinSpaces(char*name,char*linkedFile){
    FILE*fd=fopen(name,"a+");
    FILE*lfd=fopen(linkedFile,"a+");

    char buffer[256]={0};
    int i=0;
    if(fd!=NULL&&lfd!=NULL){
        printf("Opened!");
        while(fscanf(fd,"%s",buffer)==1){
            fprintf(lfd,"%s ",buffer);
        }
        fclose(fd);
        fclose(lfd);
    }else{
        printf("Cannot open!");
    }
    putAsFragment(linkedFile,name);
}


int getLinkedFile2(char*str,char*buffer,char*ex){
    int n=0,j=0,i=strlen(str)-1;
    while(i){
        if((str[i]<97)||(str[i]>122)){
            if(str[i]==46){
                while(j<i){
                    buffer[j]=str[j];
                    j++;
                }
                while(ex[n]){
                    buffer[j]=ex[n];
                    j++;
                    n++;
                }
                buffer[j]='\n';
                return 0;
            }else{
                while(str[j]){
                    buffer[j]=str[j];
                    j++;
                }
                while(ex[n]){
                    buffer[j]=ex[n];
                    j++;
                    n++;
                }
                buffer[j]='\n';
                return 0;
            }
        }
        i--;
    }
    return -1;
}


void changeExtension(char*name,char*linkedFile){
    FILE*fd=fopen(name,"a+");
    FILE*lfd=fopen(linkedFile,"a+");

    char buffer[256]={0};
    char new_buffer[256]={0};
    char ex[]=".html";
    int i=0;
    if(fd!=NULL&&lfd!=NULL){
        //printf("Opened!");
        while(fscanf(fd,"%s",buffer)==1){
            printf("%s ",buffer);
            if(getLinkedFile2(buffer,new_buffer,ex)==0){
                fprintf(lfd,"%s\n",new_buffer);
            }
        }
        fclose(fd);
        fclose(lfd);
    }else{
        printf("Cannot open!\n");
    }
    putAsFragment(linkedFile,name);
}



int main(void)
{
    setlocale(LC_ALL, "Rus");
    srand(time(NULL));

    //1
    makeTxtFile("task1.txt",100,10,5,0);
    char linkedFile[80]={0};
    getLinkedFile("task1.txt",linkedFile);
    printf("%s",linkedFile);
    neighbourSwap("task1.txt",linkedFile);
    printFile("task1.txt");
    printFile(linkedFile);

    //2
//    //makeTxtFile("task2.txt",20,10,5,0);
//    char linkedFile[80]={0};
//    getLinkedFile("task2.txt",linkedFile);
//    printf("%s",linkedFile);
//    removeTwinSpaces("task2.txt",linkedFile);
//    printFile("task2.txt");
//    printFile(linkedFile);

    //3
//    char linkedFile[80]={0};
//    getLinkedFile("task3.txt",linkedFile);
//    //printf("%s",linkedFile);
//    changeExtension("task3.txt",linkedFile);
//    //printFile("task3.txt");
//    printFile(linkedFile);
//

    return 0;
}
