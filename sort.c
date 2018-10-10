#include "types.h"
#include "user.h"
#include "fcntl.h"

int IntToString(char *s, int x)
{
    //  Set pointer to current position.
    char *p = s;

    //  Set t to absolute value of x.
    unsigned t = x;
    if (x < 0) t = -t;

    //  Write digits.
    do
    {
        *p++ = '0' + t % 10;
        t /= 10;
    } while (t);

    //  If x is negative, write sign.
    if (x < 0)
        *p++ = '-';

    //  Remember the return value, the number of characters written.
    int r = p-s;

    //  Since we wrote the characters in reverse order, reverse them.
    while (s < --p)
    {
        char t = *s;
        *s++ = *p;
        *p = t;
    }
    return r;
}

void insert(int a, int *list, int size){
	int* p = (list + size);
	if(size == 0)
		*p = a;
	
	else {
		while(*(p - 1) > a){
			*p = *(p - 1);
			p--;
		}
		*p = a;
	}
}

int main(){
	char buf[100];
	int list[5];
	int pid = getpid();
	int n = IntToString(buf, pid);
	write(1, "process id: ", 12);	
	write(1, buf, n);
	write(1, "\n", 1);
	int i;
	for(i = 0; i < 5; i++){
		read(1, buf, 100);
		insert(atoi(buf), list, i);
	}
	int fd = open("./result.txt", O_CREATE | O_RDWR);
	for(i = 0; i < 5; i++){
		int n = IntToString(buf, list[i]);
		write(fd, buf, n);
		write(fd, "\n", 1);
	}
	close(fd);
	exit();
}
