target remote localhost:1234
symbol-file ~/dev/duck-os/build/DuckOS
set pagination off

hb dstd::strlen(const char*)
commands
silent
print "strlen called:"
printf "\tstring addr: %p\n", &str
printf "\tstring is: %s\n", str
x/4x str
continue
end
