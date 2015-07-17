%% [p, f, x] = fileparts(mfilename('fullpath'));
p = tempname; 
mkdir(p);
cd(p)
fprintf('temporary results are stored in %s\n', p);

%% do not use local variables, only data on disk


%% Simulate frequencies for a given number of trials
configuration.numtrl = 100;
configuration.outputfile = 'data1.mat';
ft_freqsimulation(configuration);

%% Simulate frequencies for a given number of trials
configuration.numtrl = 100;
configuration.outputfile = 'data2.mat';
ft_freqsimulation(configuration);

%% Analyse frequencies of your signal
configuration.method = 'wavelet';
configuration.toi = 0:0.01:1;
configuration.channel = 1;
configuration.keeptrials = 'yes';
configuration.inputfile = 'data1.mat';
configuration.outputfile = 'freq1.mat';
ft_freqanalysis(configuration);

%% Analyse frequencies of your signal
configuration.method = 'wavelet';
configuration.toi = 0:0.01:1;
configuration.channel = 1;
configuration.keeptrials = 'yes';
configuration.inputfile = 'data2.mat';
configuration.outputfile = 'cond2.mat';
ft_freqanalysis(configuration);

%% Does all sorts of operation on your data
configuration.operation = 'multiply';
configuration.parameter = 'powspctrm';
configuration.scalar = 0.9;
configuration.inputfile = 'freq1.mat';
configuration.outputfile = 'cond1.mat';
ft_math(configuration);

%% Does all sorts of operation on your data
configuration.operation = 'multiply';
configuration.parameter = 'powspctrm';
configuration.scalar = 0.9;
configuration.inputfile = 'cond2.mat';
configuration.outputfile = 'cond2.mat';
ft_math(configuration);

%% Find the interesting segments of data
configuration.statistic = 'indepsamplesT';
configuration.method = 'analytic';
configuration.ivar = 1;
configuration.design = [1*ones(1,100) 2*ones(1,100)];
configuration.inputfile1 = 'freq1.mat';
configuration.inputfile2 = 'cond2.mat';
configuration.outputfile = stat.mat;
ft_freqstatistics(configuration);

%% Recreates a pipeline from providence
configuration.inputfile = stat.mat;
ft_analysispipeline(configuration);

