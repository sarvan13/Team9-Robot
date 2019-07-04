%Uncomment line below for first run
load('Day3Data.mat')

%Constants
d = 0.02565;
a = d/2;
L = 0.31;
s = 5.67 * 10^(-8);

p = 2700;
c = 902;

Ta = 20.8;
e = 0.0;
k = 197;
P = 10.3;
kc = 9.5;


UpTime = 60*10;
DownTime = UpTime;
switches = 8;
TotalTime = 1200;
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

dS1 = zeros(1,TotalTime/dt);
dS2 = zeros(1,TotalTime/dt);
dS3 = zeros(1,TotalTime/dt);
dS4 = zeros(1,TotalTime/dt);
dS5 = zeros(1,TotalTime/dt);
Pinovere = zeros(1,TotalTime/dt);

x = [0:dx:L+dx];
time = [0:dt:TotalTime];

dT = zeros(1,N);

%Create variable j for time
j=0;
count = 1;

powerON = 1;

while (j < TotalTime)

    powerIn = (P*dt)/(c*p*pi*a^2*dx);

    %Calculate change in first and last slice
    dT(1) = -k*dt*(T(1)-T(2))/(c*p*(dx)^2) + powerIn - ((2*pi*a*dx+pi*a^2)*kc*( T(abs(1)) - Ta) + (2*pi*a*dx+pi*a^2)*e*s*(( T(abs(1)) + 273)^4 - (Ta + 273)^4))*dt/(c*p*pi*a^2*dx);
    dT(N) = k*dt*(T(N-1)-T(N))/(c*p*(dx)^2) - ((2*pi*a*dx+pi*a^2)*kc*( T(N) - Ta) + (2*pi*a*dx+pi*a^2)*e*s*(( T(N) + 273)^4 - (Ta + 273)^4))*dt/(c*p*pi*a^2*dx);
   
    %Calculate change in temperature for the middle slices
    i = 2;
    while (i < N)
        dT(i) = (k*dt/(c*p))*(T(i-1)-2*(T(i))+T(i+1))/(dx^2) - (2*pi*a*dx*kc*( T(i) - Ta) + 2*pi*a*dx*e*s*(( T(i) + 273)^4 - (Ta + 273)^4))*dt/(c*p*pi*a^2*dx);
        i = i + 1;
    end
    
    
    Pins = k * pi * a^2 * (T(1:N-1) - T(2:N))/dx;
    dS1(count) = k * pi * a^2 * (T(c1-1) - T(c1))/dx;
    dS2(count) = k * pi * a^2 * (T(c2-1) - T(c2))/dx;
    dS3(count) = k * pi * a^2 * (T(c3-1) - T(c3))/dx;
    dS4(count) = k * pi * a^2 * (T(c4-1) - T(c4))/dx;
    dS5(count) = k * pi * a^2 * (T(c5-1) - T(c5))/dx;
    Pinovere(count) = k * pi * a^2 * (T(40) - T(41))/dx;

    %Add change in temperature to old temperature
    i = 1;
    while (i < N+1)
      T(i) = T(i) + dT(i);
      i = i + 1;
    end
    
    %Increment time
    j = j + dt;
    
    %Increment count for sensor indecies
    count = count + 1;
    
end

i = 1;
while i < N
    if Pins(i) < 10/exp(1)
        break
    end
    i = i + 1;
end
disp(i);

figure();
plot(time,dS1, 'b')
hold on
plot(time,dS2, 'r')
hold on
plot(time,dS3, 'g')
hold on
plot(time,dS4, 'm')
hold on
plot(time,dS5, 'k')
hold on
plot(time,Pinovere, '-.')
hold on
ylabel(['Power In (W)'])
xlabel('Time (s)')
legend('Sensor 1', 'Sensor 2', 'Sensor 3', 'Sensor 4', 'Sensor 5', 'Pin/e', 'Orientation', 'horizontal', 'Location', 'south')
