if grub-file --is-x86-multiboot $1; then
    echo multiboot is confirmed
else
    echo multiboot is not confirmed
fi
