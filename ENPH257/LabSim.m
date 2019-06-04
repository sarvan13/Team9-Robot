%Uncomment line below for first run
%load('Day3Data.mat')

%Constants
d = 0.02565;
a = d/2;
L = 0.31;
Ta = 21;
s = 5.67 * 10^(-8);

p = 2700;
c = 902;

e = 0.08;
k = 200;
P = 10.2;
kc = 9.2;

UpTime = 60*10;
DownTime = UpTime;
switches = 8;
TotalTime = UpTime*switches;
sensorDiameter = 0.0048;

%Sensor Positions
pos3 = 0.15;
pos4 = 0.221 - sensorDiameter/2 ;
pos5 = 0.290 - sensorDiameter/2;
pos2 = pos3 - 0.065;
pos1 = pos2 - 0.065;


%Declare step sizes 
dt = 0.01;
dx = sensorDiameter;
N = round(L/dx) + 1;



c1 = round(pos1/dx);
c2 = round(pos2/dx);
c3 = round(pos3/dx);
c4 = round(pos4/dx);
c5 = round(pos5/dx);

%Create necessary arrays
T = ones(1, N)*20;

S1 = zeros(1,TotalTime/dt);
S2 = zeros(1,TotalTime/dt);
S3 = zeros(1,TotalTime/dt);
S4 = zeros(1,TotalTime/dt);
S5 = zeros(1,TotalTime/dt);

x = [0:dx:L];
time = [0:dt:TotalTime-dt];

dT = zeros(1,N);

%Create variable j for time
j=0;
count = 1;

powerON = 1;

while (j < TotalTime)

    if (j < UpTime)
        powerIn = (P*dt)/(c*p*pi*a^2*dx);
    elseif (j >= UpTime && j < 2*UpTime)
        powerIn = 0;
    elseif (j >= 2*UpTime && j < 3*UpTime)
        powerIn = (P*dt)/(c*p*pi*a^2*dx);
    elseif (j >= 3*UpTime && j < 4*UpTime)
        powerIn = 0;
    elseif (j >= 4*UpTime && j < 5*UpTime+30)
        powerIn = (P*dt)/(c*p*pi*a^2*dx);
    elseif (j >= 5*UpTime+30 && j < 6*UpTime)
        powerIn = 0;
    elseif (j >= 6*UpTime && j < 7*UpTime)
        powerIn = (P*dt)/(c*p*pi*a^2*dx);
    elseif (j >= 7*UpTime && j < 8*UpTime)
        powerIn = 0;
    end

    S1(count) = T(c1);
    S2(count) = T(c2);
    S3(count) = T(c3);
    S4(count) = T(c4);
    S5(count) = T(c5);
    
        
    %Calculate change in first and last slice
    dT(1) = -k*dt*(T(1)-T(2))/(c*p*(dx)^2) + powerIn - ((2*pi*a*dx+pi*a^2)*kc*( T(abs(1)) - Ta) + (2*pi*a*dx+pi*a^2)*e*s*(( T(abs(1)) + 273)^4 - (Ta + 273)^4))*dt/(c*p*pi*a^2*dx);
    dT(N) = k*dt*(T(N-1)-T(N))/(c*p*(dx)^2) - ((2*pi*a*dx+pi*a^2)*kc*( T(N) - Ta) + (2*pi*a*dx+pi*a^2)*e*s*(( T(N) + 273)^4 - (Ta + 273)^4))*dt/(c*p*pi*a^2*dx);
   
    %Calculate change in temperature for the middle slices
    i = 2;
    while (i < N)
        dT(i) = (k*dt/(c*p))*(T(i-1)-2*(T(i))+T(i+1))/(dx^2) - (2*pi*a*dx*kc*( T(i) - Ta) + 2*pi*a*dx*e*s*(( T(i) + 273)^4 - (Ta + 273)^4))*dt/(c*p*pi*a^2*dx);
        i = i + 1;
    end
    
    %Add change in temperature to old temperature
    i = 1;
    while (i < N+1)
      T(i) = T(i) + dT(i);
      i = i + 1;
    end
    
    %Increment time
    j = j +dt;
    
    %Increment count for sensor indecies
    count = count + 1;
    
end

%Correct for extra time added
 j = j - dt;
 
%Create steady state plot

plot(time,S1, 'b')
hold on
plot(time,S2, 'r')
hold on
plot(time,S3, 'g')
hold on
plot(time,S4, 'm')
hold on
plot(time,S5, 'k')
hold on
ylabel(['Temperature (' char(176) 'C)'])
xlabel('Time (s)')

hold on 
plot(TimeE,SE1, 'b.')
hold on
plot(TimeE,SE2, 'r.')
hold on
plot(TimeE,SE3, 'g.')
hold on
plot(TimeE,SE4, 'm.')
hold on
plot(TimeE,SE5, 'k.')
hold on

legend('Sim Sensor 1', 'Sim Sensor 2', 'Sim Sensor 3', 'Sim Sensor 4', 'Sim Sensor 5', 'Data Sensor 1', 'Data Sensor 2', 'Data Sensor 3', 'Data Sensor 4', 'Data Sensor 5')


            err = zeros(round(length(SE1)/500));
            S1err = zeros(round(length(SE1)/500));
            S2err = zeros(round(length(SE2)/500));
            S3err = zeros(round(length(SE3)/500));
            S4err = zeros(round(length(SE4)/500));
            S5err = zeros(round(length(SE5)/500));
            Timeerr = zeros(round(length(SE1)/500));
            
            count = 1;
            
            while (count < length(SE1))
                if(mod(count,500) == 0)
                    S1err(count/500) = SE1(count);
                    
                    Timeerr(count/500) = TimeE(count);
                    err(count/500) = 1;
                end
                
                count = count + 1;
            end
                    
            errorbar(Timeerr, S1err,err, 'k', 'LineStyle','none', 'HandleVisibility','off', 'Linewidth', 2);
ylim([15, 60])
xlim([0,5000])
   