find $1 | xargs file | grep -e "executable" -e "shared object" | grep ELF \
    | cut -f 1 -d : | xargs strip  --strip-unneeded 2> /dev/null || true

find $2 -type f -exec gzip -9 {} \;
for i in $(find $2 -type l ) ; do ln -s $(readlink $i).gz $i.gz ; rm $i ; done
