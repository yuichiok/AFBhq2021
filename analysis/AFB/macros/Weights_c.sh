for pol in 0 1 2 3
do
    for tipo in 0 1
    do
        root -l -q Weights_c.C\($pol,4,$tipo\)
	    root -l	-q Weights_c.C\($pol,5,$tipo\)
    done
    tipo=2
    root -l -q Weights_c.C\($pol,4,$tipo\)
    root -l -q Weights_c.C\($pol,5,$tipo\)
done

#for pol in 0 1 2 3
#do
#    for tipo in 0 1 2 #weights tagging, pq, weights charge
#    do
#	    for lastit in {1..5} #charge method (Kc, Vtx and different cheating options)
	    #do
        #    root -l -q Weights_c.C\($pol,4,$tipo,$lastit\)
        #    root -l -q Weights_c.C\($pol,5,$tipo,$lastit\)
    #done
#done

