m=38*10^-3;
R=0.0150;
d=0.0300;
g=-9.8000;
L=0.4300;
J=2/5*m*R^2;

K = (m*g*d)/(L*(J/R^2+m)); 
num=[-K];
den=[1 0 0];
Beam_ball=tf(num,den);

%bode(Beam_ball);
%figure;
%nichols(Beam_ball);
rlocus(Beam_ball);

xi=0.69;
wn=5.8;
sgrid(xi, wn)
axis([-10 10 -6 6])
figure;

zo = 0.01;
po = 5;
contro=tf([1 zo],[1 po]);

rlocus(contro*Beam_ball)
axis([-10 10 -20 20])
figure;
step(0.43/2*Beam_ball)
figure;
kp = 10;
kd = 10;
contr=tf([kd kp],1);

step(0.43/2*feedback(contr*Beam_ball,1,-1));

xi=0.69;
wn=5.8;
sgrid(xi, wn)
axis([-5 5 -2 2])
