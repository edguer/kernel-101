mkdir bin

echo "Build NASM files..."

# NASM
nasm -f elf32 kernel.asm  -o bin/kasm.o
nasm -f elf32 idt.asm  -o bin/idtasm.o
nasm -f elf32 kb.asm  -o bin/kbasm.o
nasm -f elf32 ports.asm  -o bin/portsasm.o

echo "Build C files..."

# C
gcc -fno-stack-protector -m32 -c kernel.c -o bin/kc.o
gcc -fno-stack-protector -m32 -c idt.c -o bin/idtc.o
gcc -fno-stack-protector -m32 -c kb.c -o bin/kbc.o
gcc -fno-stack-protector -m32 -c video.c -o bin/videoc.o
gcc -fno-stack-protector -m32 -c queue.c -o bin/queuec.o
gcc -fno-stack-protector -m32 -c program1.c -o bin/program1.o

echo "Linking..."

# Linker
ld -m elf_i386 -T link.ld -o bin/kernel bin/kasm.o bin/idtasm.o bin/kbasm.o bin/portsasm.o bin/kc.o bin/idtc.o bin/kbc.o bin/videoc.o bin/program1.o bin/queuec.o

echo "Running..."
# Run QEMU
qemu-system-i386 -kernel bin/kernel