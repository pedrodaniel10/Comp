for file in tests/*gr8; do
    name=$(echo "${file}" | cut -f 1 -d '.')
    simpleName=${name##*/}
    echo "Running test: " ${simpleName}
    target/gr8 --target asm ${file}
    cd tests
    yasm -felf32 ${simpleName}.asm
    ld -melf_i386 -o ${simpleName} ${simpleName}.o -L../target/root/usr/lib -lrts
    ./${simpleName} > ${simpleName}.out
    diff -w <( tr -d ' \n' <${simpleName}.out ) <( tr -d ' \n' <expected/${simpleName}.out)
    find . -maxdepth 1 ! -name '*.gr8' -type f -delete
    cd ..
done