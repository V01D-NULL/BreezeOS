if grub-file --is-x86-multiboot kernel.elf ;
then
	echo "Mutliboot works"
else
	echo "Multiboot does NOT work"
fi
