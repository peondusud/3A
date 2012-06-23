%==========================================================================
% Ball and Beam control using lag compensation and PD
% To customize this code you need to:
% 1- Change the constants and variables of the Ball and Beam 
% 2- Change the zeros of lead compensation
% 3- Change the gains of PD controller
%==========================================================================


clc;
clear;
close all

% Ball and Beam constants
m = 0.15;   % mass of the ball
R = 0.015;  % radius of the ball
g = -9.8;   % gravitational acceleration
L = 1.0;    % length of the beam
d = 0.05;   % lever arm offset
J = 1e-6;   % ball?s moment of inertia
k = (m*g*d)/(L*(J/R^2+m));  

% Transfer Function
num = [-k];
den = [1 0 0];
disp('Open loop Transfer function without controller')
TF_BallBeam=tf(num,den)

t=0:0.1:10; % Time for step input

[numclp,denclp]=cloop(num,den,-1);
disp('Closed loop Transfer Function without controller')
tf(numclp,denclp)

% Open loop response without controller
step(0.25*num,den,t),grid on
title('Open loop response without controller')

% Closed loop response without controller
figure
step(0.25*numclp,denclp,t),grid on
title('Closed loop response without controller')

% State Spapce representation
H = -m*g/(J/(R^2)+m);
   
A=[0 1 0 0
   0 0 H 0
   0 0 0 1
   0 0 0 0];
B=[0;0;0;1];
C=[1 0 0 0];
D=[0];


disp('State Space representation:')
SYS_BB=ss(A,B,C,D)


% Checking Controlability and Observability
if det(ctrb(A,B))==0
    disp('          ----------> System is NOT Controllable <----------')
else
    disp('          ----------> System is Controllable <----------')
end
    

if det(obsv(A,C))==0
    disp('          ----------> System is NOT Observable   <----------')
else
    disp('          ----------> System is Observable   <----------')
end

% Drawing Root locus
figure
rlocus(num,den),grid on
title('Root Locus without controller')


% Design Criteria
Ts=1.5;       % Settling time<2 second
PO=0.04;    % Overshoot<4%
abs(roots([1+(((-log(PO))/pi)^2) 0 -(((-log(PO))/pi)^2)])); % Damping ratio
Damp=ans(1); 
Wn=4/(Ts*Damp);     % Natural frequency

disp('Desired Damping ratio is:'),Damp
disp('Desired Natural Frequency is:'),Wn

% Desired Characteristic Equation:
dend=[1 2*Wn*Damp Wn^2];
disp('Desired Characteristic Equation is:'),dend

% Desired Poles location
Dp=roots(dend);
disp('Desired Pole locations:'),Dp

% From root locus and the location of desired closed loop pole, it can be
% found that a lead compensator is needed to shift the current root locus to left.

% Designing Lead compensator to meet the desired Settling time and Overshoot
% ------------------------------------------------------------------------%
z1=0.000001;          % Assuming zero of the lead compensator

% Finding pole of the lead compensator
num=num/den(1);  
den=den/den(1);
ANS=inv([den(1) -dend(1) 0;den(2) -dend(2) num(1);den(3) -dend(3) num(1)*z1])*[dend(2)-den(2);dend(3)-den(3);0];

disp('Pole of the Lead compensator is:')
p1=ANS(1)
c=ANS(2);
disp('Gain of the Lead compensator is:')
K=ANS(3)

% TF of the Lead compensator G1(s)=K(s+z1)/(s+p1)
numlead=K*[1 z1];
denlead=[1 p1];
disp('Transfer function of the Lead compensator to improve Ts and PO%:')
tf(numlead,denlead)

% Ball&Beam motor Transfer function with Lead compensator
disp('Ball & Beam motor Transfer function with Lead compensator')
NUM=conv(numlead,num);
DEN=conv(denlead,den);
TF=tf(NUM,DEN)
% Root locus with Lag compensator 1
figure
rlocus(TF),grid on
title('Root locus with Lead compensator')

% Open loop responce of the system with Lead compensator
figure
step(0.25*TF,t),grid on
title('Open loop response with Lead compensator')

% Closed loop responce of the system with Lead compensator
[numc,denc]=cloop(NUM,DEN);
figure
step(0.25*numc,denc,t),grid on
title('Closed loop response with Lead compensator that improves Ts & PO%')


%--------------------------------PID control------------------------------%
% PID control gain, using trial and error
kp=20;
kd=30;

% PID transfer function
numPD=[kd kp];
denPD=[1]

% Open loop TF of Ball & beam with PD controller
num_BB_PD=conv(num,numPD);
den_BB_PD=conv(den,denPD);
disp('Open loop TF of Ball & beam with PD controller')
tf(num_BB_PD,den_BB_PD)

% Closed loop TF of Ball & beam with PD controller
[NumPD_CLP,DenPD_CLP]=cloop(num_BB_PD,den_BB_PD);
disp('Closed loop TF of Ball & beam with PD controller')
tf(NumPD_CLP,DenPD_CLP)
figure
step(0.25*NumPD_CLP,DenPD_CLP), grid on
title('Closed loop response of Ball & beam with PID Control')
%-------------------------End of PID control------------------------------%

% Bode plot, Determining gain and phase margin
figure
margin(numclp,denclp), grid on % Bode plot of closed loop TF without controller
figure
margin(numc,denc), grid on %Bode plot of closed loop TF with lead compensator
figure
margin(NumPD_CLP,DenPD_CLP), grid on % Bode plot of closed loop TF with PID controller