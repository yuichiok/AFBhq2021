for pol in 0 1 2 3
do
    for tipo in 0 1
    do
	root -l -q Weights_c.C\($pol,4,$tipo\)
	root -l	-q Weights_c.C\($pol,5,$tipo\)
    done
done

for pol in 0 1 2 3
do
    for tipo in 2
    do
	for lastit in {1..5}
	do
            root -l -q Weights_c.C\($pol,4,$tipo,$lastit\)
            root -l -q Weights_c.C\($pol,5,$tipo,$lastit\)
	done
    done
done

