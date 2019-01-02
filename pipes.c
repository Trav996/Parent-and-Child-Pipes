#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#define BUFFER_SIZE 25
char hello[BUFFER_SIZE]= "Hello, there";
int pipeParentToChild[2];
int pipechildToParent[2];

void child(void);
void parent(void);
#define WRITE 1
#define READ 0

int main()
{
    pipe(pipeParentToChild);
    pipe(pipechildToParent);

    if (fork()  == 0){
        child();
    }
    else {
        parent();
    }

}
void parent(){
    //Write MEssage TO Child
     char readMssg[BUFFER_SIZE];
    close(pipeParentToChild[READ]);
    write(pipeParentToChild[WRITE],hello,BUFFER_SIZE);
    //Get Reponse From Child
    close(pipechildToParent[WRITE]);
    read(pipechildToParent[READ],readMssg,BUFFER_SIZE);
    printf("%s\n",readMssg);
    //Sends Response To Child
    char response1[BUFFER_SIZE]=  "Are you available now?";
    close(pipeParentToChild[READ]);
    write(pipeParentToChild[WRITE],response1,BUFFER_SIZE+1);
    //Get Response From Child
    close(pipechildToParent[WRITE]);
    read(pipechildToParent[READ],readMssg,BUFFER_SIZE);
    printf("%s\n",readMssg);


}
void child(){
    char readMssg[BUFFER_SIZE];
    close(pipeParentToChild[WRITE]);
    read(pipeParentToChild[READ],readMssg,BUFFER_SIZE);
    printf("%s\n",readMssg);
    //Send Reponse To Parent
    char response1[BUFFER_SIZE] = "Hi, I'm child";
    close(pipechildToParent[READ]);
    write(pipechildToParent[WRITE],response1,BUFFER_SIZE);
    //Wait Reponse From parent And Read
    close(pipeParentToChild[WRITE]);
    read(pipeParentToChild[READ],readMssg,BUFFER_SIZE);
    printf("%s\n",readMssg);
    ///Reponse To Parent
    char response2[BUFFER_SIZE] = "Yes I'm";
    close(pipechildToParent[READ]);
    write(pipechildToParent[WRITE],response2,BUFFER_SIZE);

}
