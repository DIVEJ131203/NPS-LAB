#include<string.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<fcntl.h>
#include<sys/stat.h>
int main(){
//	int s,r,recb,sntb,x;
//	struct sockaddr_in server;
//	char buff[200];
//
//	s=socket(AF_INET,SOCK_STREAM,0);
//	if(s==-1){
//		printf("\nSocket creation error.");
//		exit(0);
//	}
//	printf("\nSocket created.");
//
//	server.sin_family=AF_INET;
//	server.sin_port=htons(3388);
//	server.sin_addr.s_addr=inet_addr("127.0.0.1");
//
//	r=connect(s,(struct sockaddr*)&server,sizeof(server));
//	if(r==-1){
//		printf("\nConnection error.");
//		exit(0);
//	}
//	printf("\nSocket connected.");
//	while(1){
        char arr[10];
        printf("Enter\n1 for Even Parity\n2 for Odd Parity\n");
        scanf("%c",&arr[0]);
        printf("%c",arr[0]);
        printf("\nEnter the 7-bit data: ");
        scanf("%c",&arr[1]);
        for(int i=1;i<8;i++){
            scanf("%c",&arr[i]);
        }
        arr[9]='\0';
        printf("Array: ");
        for(int i=0;i<8;i++){
            printf("%c",arr[i]);
        }
        int count=0;
        for(int i=1;i<8;i++){
            if(arr[i]=='1'){
                count++;
            }
        }
        printf("%c",arr[8]);
        int x;
        if(count%2==0){
            printf("\nEven");
            x=0;
        }
        else{
            printf("\nOdd");
            x=1;
        }
        printf("%c",arr[8]);
        if (x==0 && arr[0]=='1'){
            arr[8]='0';
        }
        else if(x==1 && arr[0]=='2'){
            arr[8]='0';
        }
        else if(x==0 && arr[0]=='2'){
            arr[8]='1';
        }
        else if(x==1 && arr[0]=='1'){
            arr[8]='1';
        }
        puts(arr);
        printf("%c",arr[8]);
//        printf("\n\nArray: ");
//        for(int i=0;i<10;i++){
//            printf("%c ",arr[i]);
//        }

        return 0;
//	}
	//close(s);

}
