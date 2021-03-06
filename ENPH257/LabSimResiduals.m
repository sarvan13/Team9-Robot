%Uncomment line below for first run
load('Day3Data.mat')

%Constants
d = 0.02565;
a = d/2;
L = 0.31;
Ta = 20;
s = 5.67 * 10^(-8);

p = 2700;
e = 0.0;
c = 902;

k = 195;
P = 10.0;
kc = 9.0;

rmin = 10^10;

kgood = 0;
kcgood = 0;
Pgood = 0;

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

    while (P < 10.6)
        kc = 9.0;
        while (kc < 9.6)
            r = 0;

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



            while (j < TotalTime - 3)

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

                if (mod(count, 100) == 0)
                    r = r + abs(S1(count) - SE1(count/100)) + abs(S2(count) - SE2(count/100)) + abs(S3(count) - SE3(count/100)) + abs(S4(count) - SE4(count/100)) + abs(S5(count) - SE5(count/100));
                end

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

             r

             if (r < rmin)
                 rmin = r;
                 kcgood = kc;
                 kgood = k;
                 Pgood = P;

             end


            %Create steady state plot

            %{
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
            ylabel('Temperature')
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

            title('Horizontal rod (e = 0, P = 10.6, kc = 9.5)')
            legend('Sim S1', 'Sim S2', 'Sim S3', 'Sim S4', 'Sim S5', 'Data S1', 'Data S2', 'Data S3', 'Data S4', 'Data S5')
            %}

            kc = kc + 0.1;
        end
        P = P + 0.1;
    end



