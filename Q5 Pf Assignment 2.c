#include <stdio.h>
#include <string.h>

void encodemessage(char msg[]) {
    int len = strlen(msg);
    char temp;
    int i;

    
    for(i=0;i<len/2;i++){
        temp = msg[i];
        msg[i] = msg[len-i-1];
        msg[len-i-1] = temp;
    }

    
    for(i=0;i<len;i++){
        msg[i] = msg[i] ^ (1<<1);
        msg[i] = msg[i] ^ (1<<4);
    }

    printf("\nEncoded Message:\n");
    for(i=0;i<len;i++){
        printf("%02X",(unsigned char)msg[i]);
    }
    printf("\n");
}

void decodemessage(char hexmsg[]) {
    int hexlen = strlen(hexmsg);
    if(hexlen%2!=0){
        printf("Invalid hex message\n");
        return;
    }

    int len = hexlen/2;
    char bytes[200];
    char pair[3]={0};
    unsigned int val;
    int i;

    for(i=0;i<len;i++){
        pair[0]=hexmsg[i*2];
        pair[1]=hexmsg[i*2+1];
        if(sscanf(pair,"%2X",&val)!=1){
            printf("Invalid hex\n");
            return;
        }
        bytes[i]=(char)val;
    }

    
    for(i=0;i<len;i++){
        bytes[i] = bytes[i] ^ (1<<1);
        bytes[i] = bytes[i] ^ (1<<4);
    }

    
    for(i=0;i<len/2;i++){
        char temp = bytes[i];
        bytes[i]=bytes[len-i-1];
        bytes[len-i-1]=temp;
    }

    printf("Decoded Message: ");
    for(i=0;i<len;i++){
        putchar(bytes[i]);
    }
    printf("\n");
}

int main(){
    char msg[200];
    int ch;

    do{
        printf("\n1. Encode Message\n");
        printf("2. Decode Message\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        if(scanf("%d",&ch)!=1){
            printf("Invalid input\n");
            while(getchar()!='\n');
            continue;
        }

        getchar();

        if(ch==1){
            printf("Enter message: ");
            fgets(msg,sizeof(msg),stdin);
            msg[strcspn(msg,"\n")]='\0';
            encodemessage(msg);
        }
        else if(ch==2){
            printf("Enter encoded HEX: ");
            fgets(msg,sizeof(msg),stdin);
            msg[strcspn(msg,"\n")]='\0';
            decodemessage(msg);
        }
        else if(ch==3){
            printf("Exiting...\n");
        }
        else{
            printf("Invalid choice\n");
        }
    }while(ch!=3);

    return 0;
}
