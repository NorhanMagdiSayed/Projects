

clear all;
close all;

%% Global Flags
% This needs to be defined to select the correct input recording device.
AUDIO_DEVICE_ID = 1;
% Read the raw data .wav file here
READ_FROM_FILE = true;

%% Initial reading/recording and data setup
if (READ_FROM_FILE)
    [audio_stereo, f_sample] = audioread('2026-01-30--14-13-04.wav');
else
    if isempty(AUDIO_DEVICE_ID)
        % Help finding the correct audio recording device id.
        audio_devices = audiodevinfo;
        record_devices = struct2table(audio_devices.input);
        record_devices(:, [3, 1])
        disp('Please select the appropiate input device and define the AUDIO_DEVICE_ID variable accordingly!');
        return;
    else
        % Create audio device handle
        f_sample = 48000;  % number of samples per second 
        resolution = 16;
        audio_interface = audiorecorder(f_sample, resolution, 2, AUDIO_DEVICE_ID);
        disp('Start recording');

        % Record audio data
        record_length_seconds = 90;
        recordblocking(audio_interface, record_length_seconds)
        disp('Finished recording');

        % Read in data
        audio_stereo = getaudiodata(audio_interface);
        filename = datestr(now, 'yyyy-mm-dd--HH-MM-SS.wav');
        audiowrite(filename, audio_stereo, f_sample);
    end
end

% Constants
c = 3e8; %(m/s) speed of light

% Radar parameters
pules_time = 20E-3; % (s) pulse time
samples_per_pulse = pules_time * f_sample; % number of samples per pulse

f_rf_start = 2260E6; % (Hz) LFM start frequency for example
f_rf_stop = 2590E6; % (Hz) LFM stop frequency for example
bandwidth = f_rf_stop - f_rf_start; % (Hz) transmti bandwidth
f = linspace(f_rf_start, f_rf_stop, samples_per_pulse/2); % instantaneous transmit frequency

% Range resolution
rr = c / (2 * bandwidth);
max_range = rr * samples_per_pulse / 2;

trigger_signal = audio_stereo(:, 1);
input_signal = audio_stereo(:, 2)*(10^(10));
clear audio_stereo;

%% Index matrix generation and input-vector slicing.
% TODO:
% Parse the data into fast and slowtime by triggering off rising edge of sync pulse
%
% INPUT:
% input_signal: Signal
% trigger_signal: trigger
%
% OUTPUT:
% pos_signal_mat, neg_signal_mat: Matrices with slow time in first and fasttime in second
% dimension
% n_samples: Number of samples in fasttime ( samples per chirp ) 
% pos_time, neg_time: times stamps of slow time in seconds

% Sync pulse 
%% sync is a square wave 0 >>>>> 5 , find the rising edges 
%% AC Coupling & jitter
thershold = mean(trigger_signal);
norm_trigger = trigger_signal > thershold ; %%% x is a either 1 or 0 [1 0 1 0 1 0 1] 
% find rising edges , looks for index 
% diff(i) = x(i+1) - x(i)    1 - 0 = 1 %% should we add a 1 
rising_edge_index = find(diff(norm_trigger) == 1)   ;     % y here is the rising edges - 1 
falling_edge_index = find(diff(norm_trigger) == -1)   ;     % y here is the rising edges    

% we want to differ 
minimum_length = min(length(rising_edge_index),length(falling_edge_index))-1;
rising_edge_index = rising_edge_index(1:minimum_length);
falling_edge_index = falling_edge_index(1:minimum_length);
subtract_index = abs(rising_edge_index - falling_edge_index) ;     
n_samples = min(subtract_index);

%rising edge + n_samples 
indexes_for_ramps = rising_edge_index + (0:n_samples-1) ; 
pos_signal_mat = input_signal(indexes_for_ramps); 

%Falling edge + n_samples 
indexes_for_ramps2 = falling_edge_index + (0:n_samples-1) ; 
neg_signal_mat = input_signal(indexes_for_ramps2); 




%%%%%PROBLEM HEERREEEE %%%%%%%
%[row,col]= size(input_signal);


% pos_signal_mat, neg_signal_mat: Matrices with slow time in first and fasttime in second
% dimension
% n_samples: Number of samples in fasttime ( samples per chirp ) 
% pos_time, neg_time: times stamps of slow time in seconds

% how to get pos_time and neg_time >>

pos_time = rising_edge_index / f_sample ; 

neg_time = falling_edge_index / f_sample ; 










%% (Optional) DC-Bias removal
% TODO:
% Remove the DC-Bias as well as ramp-periodic voltage swings from the input signal, that do not carry radar-target related information
%
% To improve the plot and signal quality, one can remove the fasttime as
% well as the slowtime mean value of the signal

pos_signal_mat = pos_signal_mat - mean(pos_signal_mat,2) ; %Fast_time
pos_signal_mat = pos_signal_mat - mean(pos_signal_mat,1) ; %slow _time 

neg_signal_mat = neg_signal_mat - mean(neg_signal_mat,2) ; %Fast_time
neg_signal_mat = neg_signal_mat - mean(neg_signal_mat,1) ; %slow _time 


%% RTI plot without any optimisations
% TODO:
% Calculate the spectra of the input signal across the fast-time.
% Go on then and normalize the magnitude of the spectrum, such that its
% maximum value equals 0dB, so you have a proper reference for the 
% upcoming plot.
%
% OUTPUT: pos_spectrum, neg_spectrum with slowtime in first dimension and frequency in second
% This variable is to be used for fft-zero-padding operation.
zero_padding = 2^nextpow2(8 * n_samples) ; 
pos_spectrum = abs(fft(pos_signal_mat,zero_padding,2));   %%% across fast time only 
pos_spectrum = 20*log10(pos_spectrum(:,1:zero_padding/2)) ; 
pos_spectrum = pos_spectrum - max(max(pos_spectrum)) ; 

%% fast time means in one row across the samples 
neg_spectrum = abs(fft(neg_signal_mat,zero_padding,2));   %%% across fast time only 
neg_spectrum = 20*log10(neg_spectrum(:,1:zero_padding/2)) ; 
neg_spectrum = neg_spectrum - max(max(neg_spectrum)) ;







% Plot template functionality:
% display pos_spectrum, neg_spectrum vs. pos_time, neg_time
% pos_range = linspace(0,max_range,size(pos_signal_mat,2));
% TODO:
% Determine a good value range (max_val, min_val) for the spectral plot, so the targets are
% well derpicted. This is crucial for the quality of your plots
max_val = 0;
min_val = -80;

figure 
pos_range = linspace(0, max_range, zero_padding);
imagesc(pos_range, pos_time, pos_spectrum, [min_val, max_val]);
colorbar;
ylabel('time (s)');
xlabel('range (m)');
title('Positive RTI without clutter rejection');

figure 
neg_range = linspace(0, max_range, zero_padding);
imagesc(neg_range, neg_time, neg_spectrum, [min_val, max_val]);
colorbar;
ylabel('time (s)');
xlabel('range (m)');
title('Negative RTI without clutter rejection');

%% Additional add Moving Target Indicator (MTI) as clutter reduction
% MTI based RTI plots

% this is with clutter reduction, >>> Stationary objects which are seen constant through out rows 
%% pos_spectrum MTI attempt 


pos_spectrum_2 = fft(pos_signal_mat,zero_padding,2);   
pos_spectrum_2 = diff(pos_spectrum_2) ; 
pos_spectrum_2 = abs(pos_spectrum_2) ; 
pos_spectrum_2 = 20*log10(pos_spectrum_2(:,1:zero_padding/2)) ;
pos_spectrum_2 = pos_spectrum_2 - max(max(pos_spectrum_2)) ; 

neg_spectrum_2 = fft(neg_signal_mat,zero_padding,2);   
neg_spectrum_2 = diff(neg_spectrum_2) ; 
neg_spectrum_2 = abs(neg_spectrum_2) ; 
neg_spectrum_2 = 20*log10(neg_spectrum_2(:,1:zero_padding/2)) ;
neg_spectrum_2 = neg_spectrum_2 - max(max(neg_spectrum_2)) ; 



figure 
pos_range = linspace(0, max_range, zero_padding);
imagesc(pos_range, pos_time, pos_spectrum_2, [min_val, max_val]);
colorbar;
ylabel('time (s)');
xlabel('range (m)');
title('Positive RTI with clutter rejection');

figure 
neg_range = linspace(0, max_range, zero_padding);
imagesc(neg_range, neg_time, neg_spectrum_2, [min_val, max_val]);
colorbar;
ylabel('time (s)');
xlabel('range (m)');
title('Negative RTI with clutter rejection');