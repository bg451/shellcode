
char shellcode[] = 

	"\xf7\xf0"            
	"\xcd\x80";             

int main(int argc, char **argv) {
	int *ret;
	ret = (int *)&ret + 2;
	(*ret) = (int) shellcode;
}
