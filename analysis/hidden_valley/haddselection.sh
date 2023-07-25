for pol in "eL_pR" 
do
  for cut in 0
  do
 		#hadd -f -j 4 -k results/selection_cuts${cut}_4f_ZZ_hadronic_${pol}.root output/selection_cuts${cut}_4f_ZZ_hadronic_${pol}_*.root &
		#hadd -f -j 4 -k results/selection_cuts${cut}_2f_hadronic_sample_${pol}.root output/selection_cuts${cut}_2f_hadronic_sample_${pol}_*.root &
		#hadd -f -j 4 -k results/selection_cuts${cut}_2f_hadronic_${pol}.root output/selection_cuts${cut}_2f_hadronic_${pol}_*.root
		#hadd -f -j 4 -k results/selection_cuts${cut}_qqH_${pol}.root output/selection_cuts${cut}_qqH_${pol}_*.root &
		#hadd -f -j 4 -k results/selection_cuts${cut}_4f_WW_hadronic_${pol}.root output/selection_cuts${cut}_4f_WW_hadronic_${pol}_*.root &
		hadd -f -j 4 -k results/selection_cuts${cut}_HV_qv100GeV_${pol}.root output/selection_cuts${cut}_HV_qv100GeV_eL_pR*.root
		hadd -f -j 4 -k results/selection_cuts${cut}_HV_qv50GeV_${pol}.root output/selection_cuts${cut}_HV_qv50GeV_eL_pR*.root
		hadd -f -j 4 -k results/selection_cuts${cut}_HV_qv10GeV_${pol}.root output/selection_cuts${cut}_HV_qv10GeV_eL_pR*.root
		hadd -f -j 4 -k results/selection_cuts${cut}_qqSM_${pol}.root output/selection_cuts${cut}_qqSM_eLpR*.root &
		#hadd -f -j 4 -k results/selection_cuts${cut}_HV_qv50GeV_${pol}.root output/selection_cuts${cut}_HV_qv50GeV_eLpR*.root
		echo $cut
  done
done

for pol in "eL_pR"
do
  for cut in 0
  do
		#hadd -f -j 4 -k results/selectionPL_cuts${cut}_2f_hadronic_sample_${pol}.root output/selectionPL_cuts${cut}_2f_hadronic_sample_${pol}_*.root &
		#hadd -f -j 4 -k results/selectionPL_cuts${cut}_2f_hadronic_${pol}.root output/selectionPL_cuts${cut}_2f_hadronic_${pol}_*.root
		hadd -f -j 4 -k results/selectionPL_cuts${cut}_HV_qv100GeV_${pol}.root output/selectionPL_cuts${cut}_HV_qv100GeV_eL_pR*.root
		hadd -f -j 4 -k results/selectionPL_cuts${cut}_HV_qv50GeV_${pol}.root output/selectionPL_cuts${cut}_HV_qv50GeV_eL_pR*.root
		hadd -f -j 4 -k results/selectionPL_cuts${cut}_HV_qv10GeV_${pol}.root output/selectionPL_cuts${cut}_HV_qv10GeV_eL_pR*.root
		hadd -f -j 4 -k results/selectionPL_cuts${cut}_qqSM_${pol}.root output/selectionPL_cuts${cut}_qqSM_eL_pR*.root
		#hadd -f -j 4 -k results/selectionPL_cuts${cut}_HV_qv50GeV_${pol}.root output/selectionPL_cuts${cut}_HV_qv50GeV_eLpR*.root

  done
done
