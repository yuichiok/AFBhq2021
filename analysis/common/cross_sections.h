/*
250GeV, old
double cross_section[2][5] = {
  {1405.06,343.03,14866.4,127966,33106.23}, //left, zz, hz, ww, qq, qq+radreturncut
  {606.71,219.486,136.822,70416.7,10633.8}
};*/
//500GeV, new format
double cross_section[2][6] = {
  {31686.1,7166.63,680.3,114.7,7680.7,165*4.}, //left, qq, qq+radreturncut,  zz, hz, ww, ttbar (not applciable at 250GeV)
  {17581.9,2392.2,271.9,73.4,33.5,64.3*4.}
};

/*250GeV
cross_section[0][0]=1405.06;//zz eL
cross_section[1][0]=606.71;//zz eR 
cross_section[0][1]=343.03;//hz eL
cross_section[1][1]=219.486;//hz eR 
cross_section[0][2]=14866.4;//ww eL
cross_section[1][2]=136.822;//ww eR 
cross_section[0][3]=127966;//qq eL
cross_section[1][3]=70416.7;//qq eR 
cross_section[0][4]=127966;//qq eL + rad ret cut (50GeV)
cross_section[1][4]=70416.7;//qq eR + rad ret cut (50GeV)
*/
