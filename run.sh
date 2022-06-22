nasm -f elf32 kernel.asm -o bin/kasm.o
gcc -m32 -c kernel.c -o bin/kc.o
ld -m elf_i386 -T link.ld -o bin/kernel bin/kasm.o bin/kc.o
qemu-system-i386 -kernel bin/kernel