init-if-undefined $target_set = 0 
if $target_set == 0
    target remote localhost:20000
    file obj/kernel
    add-symbol-file obj/bootsector.out 0x7c00
    #source build/functions.gdb
    display/5i $pc 
    set $target_set = 1 
end
