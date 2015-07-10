cd /home/common/matlab/fieldtrip/data


%% find the interesting segments of data
cfg = [];                                           % empty configuration
cfg.dataset                 = 'Subject01.ds';       % name of CTF dataset
cfg.trialdef.eventtype      = 'backpanel trigger';
cfg.trialdef.prestim        = 1;
cfg.trialdef.poststim       = 2;
cfg.trialdef.eventvalue     = 3;                    % trigger value for fully incongruent (FIC)

%%
cfg = ft_definetrial(cfg);


%% preprocess the data
cfg.channel    = {'MEG', '-MLP31', '-MLO12'};        % read all MEG channels except MLP31 and MLO12
cfg.demean     = 'yes';
cfg.baselinewindow  = [-0.2 0];
cfg.lpfilter   = 'yes';                              % apply lowpass filter
cfg.lpfreq     = 35;                                 % lowpass at 35 Hz.
dataFIC_LP = ft_preprocessing(cfg);



%% find the interesting segments of data
cfg = [];                                           % empty configuration
cfg.dataset                 = 'Subject01.ds';       % name of CTF dataset
cfg.trialdef.eventtype      = 'backpanel trigger';
cfg.trialdef.prestim        = 1;
cfg.trialdef.poststim       = 2;
cfg.trialdef.eventvalue     = 9;                    % trigger value for fully congruent (FC)
cfg = ft_definetrial(cfg);

%% preprocess the data
cfg.channel    = {'MEG', '-MLP31', '-MLO12'};       % read all MEG channels except MLP31 and MLO12
cfg.demean     = 'yes';
cfg.baselinewindow  = [-0.2 0];
cfg.lpfilter   = 'yes';                              % apply lowpass filter
cfg.lpfreq     = 35;                                 % lowpass at 35 Hz.
dataFC_LP = ft_preprocessing(cfg);

%% find the interesting segments of data
cfg = [];                                           % empty configuration
cfg.dataset                 = 'Subject01.ds';       % name of CTF dataset
cfg.trialdef.eventtype      = 'backpanel trigger';
cfg.trialdef.prestim        = 1;
cfg.trialdef.poststim       = 2;
cfg.trialdef.eventvalue     = 5;                    % trigger value for initially congruent (IC)
cfg = ft_definetrial(cfg);

%% preprocess the data
cfg.channel    = {'MEG', '-MLP31', '-MLO12'};        % read all MEG channels except MLP31 and MLO12
cfg.demean     = 'yes';
cfg.baselinewindow  = [-0.2 0];
cfg.lpfilter   = 'yes';                              % apply lowpass filter
cfg.lpfreq     = 35;                                 % lowpass at 35 Hz.
dataIC_LP = ft_preprocessing(cfg);

%%
cfg = [];
avgFIC = ft_timelockanalysis(cfg, dataFIC_LP);
avgFC = ft_timelockanalysis(cfg, dataFC_LP);
avgIC = ft_timelockanalysis(cfg, dataIC_LP);

%%
cfg = [];
cfg.showlabels = 'yes';
cfg.fontsize = 6;
cfg.layout = 'CTF151.lay';
cfg.ylim = [-3e-13 3e-13];
ft_multiplotER(cfg, avgFIC);

%%
cfg = [];
cfg.showlabels = 'no';
cfg.fontsize = 6;
cfg.layout = 'CTF151.lay';
cfg.baseline = [-0.2 0];
cfg.xlim = [-0.2 1.0];
cfg.ylim = [-3e-13 3e-13];
ft_multiplotER(cfg, avgFC, avgIC, avgFIC);

%%
cfg.xlim = [-0.2 1.0];
cfg.ylim = [-1e-13 3e-13];
cfg.channel = 'MLC24';
clf;
ft_singleplotER(cfg,avgFC, avgIC, avgFIC);

%%
cfg = [];
cfg.xlim = [0.3 0.5];
cfg.colorbar = 'yes';
ft_topoplotER(cfg,avgFIC);

%%
cfg = [];
cfg.xlim = [-0.2 : 0.1 : 1.0];  % Define 12 time intervals
cfg.zlim = [-2e-13 2e-13];      % Set the 'color' limits.
clf;
ft_topoplotER(cfg,avgFIC);

%%
cfg                 = [];
cfg.feedback        = 'yes';
cfg.method          = 'template';
cfg.neighbours      = ft_prepare_neighbours(cfg, avgFIC);
cfg.planarmethod    = 'sincos';
avgFICplanar        = ft_megplanar(cfg, avgFIC);

%%
cfg                 = [];
cfg.feedback        = 'yes';
cfg.method          = 'template';
cfg.neighbours      = ft_prepare_neighbours(cfg, avgFIC);

%%
cfg = [];
avgFICplanarComb = ft_combineplanar(cfg,avgFICplanar);
