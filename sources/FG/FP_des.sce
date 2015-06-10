clear;

scl = 5;
fin = 200;
nop = 64;
phase = 0;
dt = 500 * 10^-6;

tmp = 2^scl;
dt_fp = uint16(dt * tmp);
dt_fp_us = uint16(dt * 10^6 * tmp);

nop_fp = uint16(nop * tmp);

freq_fp = uint16(fin * tmp);

pinv_fp = uint16(fin * nop * uint32(dt_fp_us) / 10^6);
//pinv_fp = uint32(fin * nop * dt * tmp);
pinv_ufp = fin * nop * dt;

disp("MAX");
disp(2^16);

disp("FP")
disp(dt_fp);
disp(dt_fp_us);
disp(nop_fp);
disp(freq_fp);
disp(pinv_fp);

disp("OUT")
disp(dt_fp / tmp);
disp(dt_fp_us / tmp);
disp(nop_fp / tmp);
disp(freq_fp / tmp);
disp(double(pinv_fp) / tmp);

disp("UFP");
disp(pinv_ufp);




