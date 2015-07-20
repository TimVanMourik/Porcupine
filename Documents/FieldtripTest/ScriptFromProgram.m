%% Simulate frequencies for a given number of trials
cfg = [];
cfg.numtrl = 100;
cfg.outputfile = 'data1.mat';
ft_freqsimulation(cfg);

%% Simulate frequencies for a given number of trials
cfg = [];
cfg.numtrl = 100;
cfg.outputfile = 'data2.mat';
ft_freqsimulation(cfg);

%% Analyse frequencies of your signal
cfg = [];
cfg.method = 'wavelet';
cfg.toi = 0:0.1:10;
cfg.channel = 1;
cfg.keeptrials = 'yes';
cfg.inputfile = 'data1.mat';
cfg.outputfile = 'freq1.mat';
ft_freqanalysis(cfg);

%% Analyse frequencies of your signal
cfg = [];
cfg.method = 'wavelet';
cfg.toi = 0:0.01:1;
cfg.channel = 1;
cfg.keeptrials = 'yes';
cfg.inputfile = 'data2.mat';
cfg.outputfile = 'freq2.mat';
ft_freqanalysis(cfg);

%% Does all sorts of operation on your data
cfg = [];
cfg.operation = 'multiply';
cfg.parameter = 'powspctrm';
cfg.scalar = 0.9;
cfg.inputfile = 'freq1.mat';
cfg.outputfile = 'cond1.mat';
ft_math(cfg);

%% Does all sorts of operation on your data
cfg = [];
cfg.operation = 'multiply';
cfg.parameter = 'powspctrm';
cfg.scalar = 0.9;
cfg.inputfile = 'freq2.mat';
cfg.outputfile = 'cond2.mat';
ft_math(cfg);

%% Find the interesting segments of data
cfg = [];
cfg.statistic = 'indepsamplesT';
cfg.method = 'analytic';
cfg.ivar = 1;
cfg.design = [1*ones(1,100) 2*ones(1,100)];
%manually removed:
% cfg.inputfile1 = 'freq1.mat';
% cfg.inputfile2 = 'freq2.mat';
%manually added:
cfg.inputfile = {'freq1.mat', 'freq2.mat'};
cfg.outputfile = 'stat.mat';
ft_freqstatistics(cfg);

%% Recreates a pipeline from providence
cfg = [];
cfg.inputfile = 'stat.mat';
%manually removed:
% ft_analysispipeline(cfg);
%manually added:
load('stat.mat');
ft_analysispipeline(cfg, stat);

