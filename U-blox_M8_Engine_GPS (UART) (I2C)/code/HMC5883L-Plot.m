%% Init
clear, clc, close all

%% List Availables Serial-Ports
device = "usbmodem";

[status,cmdout] = system('ls /dev/tty.*');
devices = split(string(cmdout),'/dev/');

for i = 1 : length(devices)
    if (devices(i) ~= "")
        res = strfind(devices(i),device);
        if(~isempty(res))
            device = "/dev/" + devices(i);   % select device
            device = split(device,char(10)); % remove '\n'
            device = device(1);
        end
    end
end

%% Set-up Serial Port
if ~isempty(instrfind)
    fclose(instrfind);
    delete(instrfind);
end
% Register Serial port at /dev/cu.usbmodem14103
s = serial(device);
% Choose the BaudRate
s.BaudRate = 115200;

%% Start receiving from Serial Port
% Open Registed Serial Port
fopen(s);

% init vars and graphs
h = 10e-3;
MAX_N = 1*60 / h;
Y_axis = [];
X_axis = [];
Z_axis = [];
plot(X_axis,Y_axis,'b'), grid on, hold on
title('')
k = 1;

% Receive until ctrl+c
tic
while k < MAX_N
    % Receive new line
    newline = fscanf(s,'%c');
    newline = split(string(newline),char(13)); % remove string terminator
    newline = split(newline(1),' '); % split data
    
    % Go throw received data and search for Nox and Cox
    for i = 1:length(newline)
        if (newline(i) ~= "")
            if(lower(newline(i)) == "x:")
                for j = i : length(newline)
                    res = sscanf(newline(j),'%f');
                    if(~isempty(res))
                        X_axis(k) = res;
                        break;
                    end
                end
            elseif(lower(newline(i)) == "y:")
                for j = i : length(newline)
                    res = sscanf(newline(j),'%f');
                    if(~isempty(res))
                        Y_axis(k) = res;
                        break;
                    end
                end
            elseif(lower(newline(i)) == "z:")
                for j = i : length(newline)
                    res = sscanf(newline(j),'%f');
                    if(~isempty(res))
                        Z_axis(k) = res;
                        break;
                    end
                end
            end
        end
    end
    
    
    % Real Time Plot Animation
    if(~rem(k,1/h))
        plot(X_axis(k-99:k),Z_axis(k-99:k),'.b')
        drawnow
    end
    
    % increment k
    k = k + 1;
end
toc

% Start Counting Read Time
fclose(s);
clear s