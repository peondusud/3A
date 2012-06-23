m=38*10^-3;
R =0.0150;
d = 0.0300;
g = 9.8000;
L = 0.4300;
J=2/5*m*R^2;

Beam_ball=tf(m*g*d,[L(J/(R^2)+m) 0 0]);
bode(Beam_ball);
figure;
nichols(Beam_ball);