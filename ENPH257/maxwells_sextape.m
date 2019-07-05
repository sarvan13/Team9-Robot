%Constants
d = 0.0254;
a = d/2;
L = 0.31;
Ta = 20;
s = 5.67 * 10^(-8);

p = 2700;
e = 0.08;
c = 902;

k = 190;
P = 11;
kc = 7;

e2 = 0.0;
k2 = 197;
P2 = 10.3;
kc2 = 9.5;

e3 = 0.85;
k3 = 210;
P3 = 11.3;
kc3 = 9.2;

%Declare step sizes 
dt = 0.005;
dx = 0.005; %This is the smallest step size that my computercould run without giving NaN values. 
N = L/dx + 1;

%Create necessary arrays
T = ones(1, N)*20;
T2 = ones(1,N)*20;
T3 = ones(1,N)*20;

x = [0:dx:L];

dT = zeros(1,N);
dT2 = zeros(1,N);
dT3 = zeros(1,N);

%Create variable j for time
j=0;

%Run for 10000 seconds and check dT of slices after to see if it is
%sufficient
while (j < 10000)
    %Calculate change in first and last slice
    dT(1) = -k*dt*(T(1)-T(2))/(c*p*(dx)^2) + (P*dt)/(c*p*pi*a^2*dx) -((2*pi*a*dx+pi*a^2)*kc*( T(abs(1)) - Ta) + (2*pi*a*dx+pi*a^2)*e*s*(( T(abs(1)) + 273)^4 - (Ta + 273)^4))*dt/(c*p*pi*a^2*dx);
    dT(N) = k*dt*(T(N-1)-T(N))/(c*p*(dx)^2) - ((2*pi*a*dx+pi*a^2)*kc*( T(N) - Ta) +(2*pi*a*dx+pi*a^2)*e*s*(( T(N) + 273)^4 - (Ta + 273)^4))*dt/(c*p*pi*a^2*dx);
   
    dT2(1) = -k2*dt*(T2(1)-T2(2))/(c*p*(dx)^2) + (P2*dt)/(c*p*pi*a^2*dx) -((2*pi*a*dx+pi*a^2)*kc2*( T2(abs(1)) - Ta) + (2*pi*a*dx+pi*a^2)*e2*s*(( T2(abs(1)) + 273)^4 - (Ta + 273)^4))*dt/(c*p*pi*a^2*dx);
    dT2(N) = k2*dt*(T2(N-1)-T2(N))/(c*p*(dx)^2) - ((2*pi*a*dx+pi*a^2)*kc2*( T2(N) - Ta) +(2*pi*a*dx+pi*a^2)*e2*s*(( T2(N) + 273)^4 - (Ta + 273)^4))*dt/(c*p*pi*a^2*dx);
    
    dT3(1) = -k3*dt*(T3(1)-T3(2))/(c*p*(dx)^2) + (P3*dt)/(c*p*pi*a^2*dx) -((2*pi*a*dx+pi*a^2)*kc3*( T3(abs(1)) - Ta) + (2*pi*a*dx+pi*a^2)*e3*s*(( T3(abs(1)) + 273)^4 - (Ta + 273)^4))*dt/(c*p*pi*a^2*dx);
    dT3(N) = k3*dt*(T3(N-1)-T3(N))/(c*p*(dx)^2) - ((2*pi*a*dx+pi*a^2)*kc3*( T3(N) - Ta) +(2*pi*a*dx+pi*a^2)*e3*s*(( T3(N) + 273)^4 - (Ta + 273)^4))*dt/(c*p*pi*a^2*dx);
    %Calculate change in temperature for the middle slices
    i = 2;
    while (i < N)
        dT(i) = (k*dt/(c*p))*(T(i-1)-2*(T(i))+T(i+1))/(dx^2) - (2*pi*a*dx*kc*( T(i) - Ta)+ 2*pi*a*dx*e*s*(( T(i) + 273)^4 - (Ta + 273)^4))*dt/(c*p*pi*a^2*dx);
        dT2(i) = (k2*dt/(c*p))*(T2(i-1)-2*(T2(i))+T2(i+1))/(dx^2) - (2*pi*a*dx*kc2*( T2(i) - Ta)+ 2*pi*a*dx*e2*s*(( T2(i) + 273)^4 - (Ta + 273)^4))*dt/(c*p*pi*a^2*dx);
        dT3(i) = (k3*dt/(c*p))*(T3(i-1)-2*(T3(i))+T3(i+1))/(dx^2) - (2*pi*a*dx*kc3*( T3(i) - Ta)+ 2*pi*a*dx*e3*s*(( T3(i) + 273)^4 - (Ta + 273)^4))*dt/(c*p*pi*a^2*dx);
        i = i + 1;
    end
    
    %Add change in temperature to old temperature
    i = 1;
    while (i < N+1)
      T(i) = T(i) + dT(i);
      T2(i) = T2(i) + dT2(i);
      T3(i) = T3(i) + dT3(i);
      i = i + 1;
    end
    
    %Increment time
    j = j +dt;
    
end

%Correct for extra time added
 j = j - dt;
 
 %Print changes in temperature to check if it is at steady state
 dT(1)
 dT(10)
 dT(N)
 
 %Print time
j

%Create steady state plot
hold on
plot(x,T, "b")
plot(x,T2, "r")
plot(x,T3, "k")
xlabel("Rod Position (cm)")
ylabel("Temperature (C)")
legend('Vertical Bare Rod', 'Horizontal Bare Rod' , 'Horizontal Black Rod', 'Location', 'northeast','Orientation', 'vertical')
hold off

X = [0.02 0.085 0.15 0.22 0.285];
blackie = [56.9716 51.499 47.9592 45.33832 44.228];
hory = [69.2937 64.0694 60.2652 57.6171 56.4191];
verty = [83.848 78.027 73.7647 70.7851 69.4339];

hold on 
plot(X, blackie, 'ko', 'HandleVisibility','off')
hold on
plot(X, hory, 'ro','HandleVisibility','off')
hold on
plot(X, verty, 'bo','HandleVisibility','off')
