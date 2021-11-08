#define EXIT_FAIL 1
#define EXIT_BAD_ARGS 2

typedef struct {
    struct in_addr server;
    unsigned int port;
    char filter_file[200];
} args_t;

args_t parse_args(int argc, char **argv);
char* get_hostname(char* buffer, int* offset);
void set_refused(char* buffer);
int match(char* hostname, char* filter_file);
int submatch(char* subdomain, char* filter_file);
int get_next_domain(char* domain, FILE* file);
void set_end(char* domain, int end);