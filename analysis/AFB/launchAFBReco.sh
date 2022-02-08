

for pol in "eL_pR" "eR_pL"
do
    for method in 0 1 2 3
    do
	source test_AFBReco.sh 2f_hadronic_sample $pol $method
        source test_AFBReco.sh 2f_hadronic $pol $method

    done
    #source test_AFBReco.sh 2f_hadronic $pol 0   
done



