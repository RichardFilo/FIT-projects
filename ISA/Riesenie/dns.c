#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h> 
#include <string.h>
#include "dns.h"

int main(int argc, char **argv)
{
    //parsovanie argumentov prikazovej riadky
    args_t args = parse_args(argc, argv);
    
    //deklaracia potrebnych premennych
    int sock_fd, offset;
    struct sockaddr_in server_addr, client_addr, dns_server_addr;
    socklen_t client_len = sizeof(client_addr);
    socklen_t dns_server_len = sizeof(dns_server_addr);
    char buffer[512] = {0};
    char* hostname;

    //nastavenie adresy nasej sluzby
    memset(&server_addr, 0, sizeof(server_addr)); 
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(args.port);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    //nastavenie adresy dns servera
    memset(&dns_server_addr, 0, sizeof(dns_server_addr));
    dns_server_addr.sin_family = AF_INET;
    dns_server_addr.sin_port = htons(53);
    dns_server_addr.sin_addr = args.server;
   
    //vytvorenie udp soketu
	if ( (sock_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("ERROR: socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 

    //napojenie sluzby na port
    if ( bind(sock_fd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0 ) 
    { 
        perror("ERROR: bind failed"); 
        exit(EXIT_FAILURE); 
    }
    
    while (1)
    {
        //prijem dns dotazu
        int bytesrx = recvfrom(sock_fd, buffer, 512, 0, (struct sockaddr *) &client_addr, &client_len); 
        if (bytesrx < 0) {
            perror("ERROR: recvfrom"); 
            exit(EXIT_FAILURE);
        }
        //ulozenie dotazovanej domeny
        hostname = get_hostname(buffer, &offset);

        //kotrola typu dotazu(ak dotaz nie je typu A) a ci dotaz nepatri k neziaducim domenam
        if((ntohs(*((uint16_t*)(buffer+offset))) != 1)|| match(hostname, args.filter_file)){
            //nastavenie dns packetu ako "response refused"
            set_refused(buffer);

            //zaslanie odpovede klientovi
            sendto(sock_fd, buffer, bytesrx, MSG_CONFIRM, (const struct sockaddr *) &client_addr, client_len); 
        }
        else{
            //zaslanie dotazu na nastaveny dns server
            sendto(sock_fd, buffer, bytesrx, MSG_CONFIRM, (const struct sockaddr *) &dns_server_addr, dns_server_len); 

            //prijatie odpovede z dns servera
            memset(buffer, 0, 512);
            bytesrx = recvfrom(sock_fd, buffer, 512, 0, (struct sockaddr *) &dns_server_addr, &dns_server_len);
            if (bytesrx < 0) {
                perror("ERROR: recvfrom"); 
                exit(EXIT_FAILURE);
            }

            //zaslanie odpovede klientovi
            sendto(sock_fd, buffer, bytesrx, MSG_CONFIRM, (const struct sockaddr *) &client_addr, client_len); 
        }

        free(hostname);
	break;
    }
    return 0; 
}

/**
 * @brief parsuje cmd argumenty a uklada ich do struktury (pomocou getopts)
 * @param argc pocet argumentov
 * @param argv pole argumentov
 * @return struktura s argumentami
 */
args_t parse_args(int argc, char **argv)
{
    int opt;
    args_t args = (args_t){.port=53, .filter_file={0}};
    int is_server = 0, verbose = 0;
    char *ptr;
    FILE* file;
    while((opt = getopt(argc, argv, "vhs:f:p:")) != -1)  
    {  
        switch(opt)  
        {
            case 'v':           // prepinac verbose
                verbose = 1;  
                break;  
            case 'h':           //prepinac s napovedou
                printf("dns -s server [-p port] -f filter_file\n");   
                exit(EXIT_SUCCESS);  
                break;  
            case 's':           //nastavenie servra
                if(inet_aton(optarg, &(args.server)) == 0) {      //ip adresa
                    struct hostent *hp = gethostbyname(optarg);     //domenove meno
                    if(hp == NULL){
                        fprintf(stderr, "ERROR: Bad format of dns server!\n");
                        exit(EXIT_BAD_ARGS);
                    }
                    args.server = *( struct in_addr*)( hp -> h_addr_list[0]);
                }
                is_server = 1;
                break;
            case 'p':           //nastavenie portu
                args.port = strtol(optarg, &ptr, 10);   //prevod na cislo
                if(*ptr!=0 || args.port > 65535){       //kontrola hodnoty
                    fprintf(stderr, "ERROR: Bad number of port!\n");
                    exit(EXIT_BAD_ARGS);
                }
                break;
            case 'f':           //nastavenie suboru z neziaducimi domenami
                if((file = fopen(optarg,"r")) == NULL){
                    fprintf(stderr, "ERROR: Cannot open the file \"%s\"!\n",optarg);
                    exit(EXIT_BAD_ARGS);
                }
                fclose(file);
                strcpy(args.filter_file, optarg);  
                break;   
            case '?':           //nezname prepinace
                fprintf(stderr, "ERROR: Unknown option or missing argument to option!\n");
                exit(EXIT_BAD_ARGS);
                break;   
        }  
    }
    if(!is_server){
        fprintf(stderr,"ERROR: Server is not defined!\ndns -s server [-p port] -f filter_file\n");
        exit(EXIT_BAD_ARGS);
    }
    if(!args.filter_file[0]){
        fprintf(stderr,"ERROR: Filter_file is not defined!\ndns -s server [-p port] -f filter_file\n");
        exit(EXIT_BAD_ARGS);
    }
    if(verbose){            //vypis pri prepinaci verbose
        printf("server: %s\n", inet_ntoa(args.server));
        printf("port: %d\n", args.port);
        printf("file: %s\n", args.filter_file);
    }
    return args;  
}

/**
 * @brief zistuje dotazovanu domenu v tvare "3www3fit5vutbr2cz0" a nastavuje posun
 * @param buffer dns packet
 * @param offset posun v bufferi
 * @return struktura s argumentami
 */
char* get_hostname(char* buffer, int* offset){
    *offset = 12; //koniec hlavicky
    do{
        *offset += buffer[*offset] + 1; //vypocet dlzky retazca
    }while(buffer[*offset] != 0);
    (*offset)++; 

    char* hostname = (char*)calloc(*offset - 12, 1); //alokacia pamate
    if(hostname == NULL){
        fprintf(stderr,"ERROR: Memory allocation!\n");
        return NULL;
    }
    memcpy(hostname, buffer+12, *offset - 12); //kopirovanie retazca s hostname-om
    return hostname;
}

/**
 * @brief nastavuje dns packet na response refused
 * @param buffer dns packet
 */
void set_refused(char* buffer){
    uint16_t mask1 = 0x800F; //maska |1|000 0000 0000 |1111|
    uint16_t mask2 = 0xFFF5; //maska |1|111 1111 1111 |0101|
    uint16_t flags;
    memcpy((void*)&flags,buffer+2, 2); //kopirovanie flagov
    flags = ntohs(flags); //prevod z sietoveho bytoveho poradia
    flags |= mask1;
    flags &= mask2; //upravy pomocou masiek
    flags = htons(flags); //prevod spat
    memcpy(buffer+2, (void*)&flags, 2); //nastavenie hodnoty v packete
}

/**
 * @brief zistuje ci je domena neziaduca
 * @param hostname dotazovana domena
 * @param filter_file subor s neziaducimi domenami
 * @return true ak domena spada pod neziaduce domeny
 */
int match(char* hostname, char* filter_file){
    char subdomain[200] = {0};
    char presubdomain[200] = {0};

    int i = strlen(hostname);  //presun ukazatela na koniec retazca
    while(i > 1){
        for(; isalnum(hostname[i-1]); i--); //vyber dalsej poddomeny
        int n=0;
        for(; n < hostname[i-1]; n++){
            subdomain[n] = hostname[i+n]; //skopirovanie dalsej poddomeny
        }
        subdomain[n] = '.';
        subdomain[n+1] = 0;
        strncat(subdomain, presubdomain, 200); //spojenie teraz najdenej poddomeny z predchadzajucou
        strcpy(presubdomain, subdomain);
        if(submatch(subdomain, filter_file)) // kontrola ci poddomena patry do zoznamu neziaducich domen
            return 1;
        i--;
    }
    return 0;
}

/**
 * @brief zistuje ci je poddomena neziaduca
 * @param subdomain dotazovana poddomena
 * @param filter_file subor s neziaducimi domenami
 * @return true ak poddomena spada pod neziaduce domeny
 */
int submatch(char* subdomain, char* filter_file){
    FILE* file = fopen(filter_file,"r"); //otvorenie suboru pre citanie
    if(file == NULL){
        fprintf(stderr, "ERROR: Cannot open the file \"%s\"!\n",optarg);
        exit(EXIT_FAILURE);
    }
    char domain[500]={0};
    while(get_next_domain(domain, file)){   //nacitanie dalsej domeny zo suboru
        if(strcmp(subdomain, domain) == 0){     //kontrola ci sa zhoduju 
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

/**
 * @brief vracia dalsie domenu zo suboru
 * @param domain miesto kde sa ulozi najdena domena
 * @param file subor s neziaducimi domenami
 * @return true ak sa domenu podari nacitat
 */
int get_next_domain(char* domain, FILE* file){
    while(1){
        if( fgets (domain, 500, file) != NULL ) { //nacitanie dalsieho riadka
            if(domain[0] == '#' || domain[0] == '\n' || (domain[0] == '\r' && domain[1] == '\n')) continue; //preskoc prazdne alebo zakomentovane riadky
            if(domain[strlen(domain)-2] == '\r'){
                set_end(domain, strlen(domain)-3);  //windows endlines
            }
            else{
                set_end(domain, strlen(domain)-2);  //other endlines
            }
            return 1;
        }
        return 0;
    }
}

/**
 * @brief nastavuje koniec retazca domeny
 * @param domain retazec domeny
 * @param end posun kde konci
 */
void set_end(char* domain, int end){
    if(domain[end] == '.'){     //ak nekonci bodkov tak ju tam prida
        domain[end+1] = 0;      //odstvanenie konca riadku
    }
    else{
        domain[end+1] = '.';     //pridanie bodky na koniec domeny
        domain[end+2] = 0;      //odstvanenie konca riadku
    }
}
