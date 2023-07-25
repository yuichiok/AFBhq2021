for cut in 0 
do
  hadd -f -j 4 -k results/QCDcorrelations_cuts${cut}_HV_qv100GeV.root output/QCDcorrelations_cuts${cut}_HV_qv100GeV_*.root
  hadd -f -j 4 -k results/QCDcorrelations_cuts${cut}_HV_qv50GeV.root output/QCDcorrelations_cuts${cut}_HV_qv50GeV_*.root
  hadd -f -j 4 -k results/QCDcorrelations_cuts${cut}_HV_qv10GeV.root output/QCDcorrelations_cuts${cut}_HV_qv10GeV_*.root
  hadd -f -j 4 -k results/QCDcorrelations_cuts${cut}_qqSM.root output/QCDcorrelations_cuts${cut}_qqSM_*.root
done



