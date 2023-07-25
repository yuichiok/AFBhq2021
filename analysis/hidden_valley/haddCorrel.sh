for pol in "eL_pR" "eR_pL"
do
  for cut in 0 
  do
      echo $cuts
      #hadd -f -j 4 -k results/QCDcorrelations_cuts${cut}_4f_ZZ_hadronic_${pol}.root output/QCDcorrelations_cuts${cut}_4f_ZZ_hadronic_${pol}_*.root &
      #hadd -f -j 4 -k results/QCDcorrelations_cuts${cut}_2f_hadronic_sample_${pol}.root output/QCDcorrelations_cuts${cut}_2f_hadronic_sample_${pol}_*.root 
      #hadd -f -j 4 -k results/QCDcorrelations_cuts${cut}_2f_hadronic_${pol}.root output/QCDcorrelations_cuts${cut}_2f_hadronic_${pol}_*.root
      #hadd -f -j 4 -k results/QCDcorrelations_cuts${cut}_qqH_${pol}.root output/QCDcorrelations_cuts${cut}_qqH_${pol}_*.root &
      #hadd -f -j 4 -k results/QCDcorrelations_cuts${cut}_4f_WW_hadronic_${pol}.root output/QCDcorrelations_cuts${cut}_4f_WW_hadronic_${pol}_*.root &
      #hadd -f -j 4 -k results/QCDcorrelations_cuts${cut}_HV_qv100GeV_${pol}.root output/QCDcorrelations_cuts${cut}_HV_qv100GeV_eL_pR_*.root
      #hadd -f -j 4 -k results/QCDcorrelations_cuts${cut}_HV_qv10GeV_${pol}.root output/QCDcorrelations_cuts${cut}_HV_qv10GeV_eL_pR_*.root &
      #hadd -f -j 4 -k results/QCDcorrelations_cuts${cut}_HV_qv50GeV_${pol}.root output/QCDcorrelations_cuts${cut}_HV_qv50GeV_eL_pR_*.root
  done
done

for pol in "eL_pR"
do
  for cut in 0 
  do
      hadd -f -j 4 -k results/QCDcorrelations_cuts${cut}_HV_qv100GeV_${pol}.root output/QCDcorrelations_cuts${cut}_HV_qv100GeV_eL_pR_*.root
      hadd -f -j 4 -k results/QCDcorrelations_cuts${cut}_HV_qv50GeV_${pol}.root output/QCDcorrelations_cuts${cut}_HV_qv50GeV_eL_pR_*.root
      hadd -f -j 4 -k results/QCDcorrelations_cuts${cut}_HV_qv10GeV_${pol}.root output/QCDcorrelations_cuts${cut}_HV_qv10GeV_eL_pR_*.root
      hadd -f -j 4 -k results/QCDcorrelations_cuts${cut}_qqSM_${pol}.root output/QCDcorrelations_cuts${cut}_qqSM_eL_pR_*.root
  done
done


