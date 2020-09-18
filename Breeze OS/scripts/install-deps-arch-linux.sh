echo "NOTE: This script works ONLY on arch linux distros." ; echo ""
echo "Updating database"
sudo pacman -Sy --noconfirm 

echo "Installing mtools, xorriso, nasm, and qemu (x86)"
sudo pacman -S --noconfirm mtools xorriso nasm qemu gdb qemu-arch-extra
