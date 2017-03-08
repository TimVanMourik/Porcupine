%% Resource File

currentPath = fileparts(mfilename('fullpath'));
saveLocation = fullfile(currentPath, '../Resources/');


docNode = com.mathworks.xml.XMLUtils.createDocument('RCC');
docRoot = docNode.getDocumentElement();

%
currentNode = docNode.createElement('qresource');
currentNode.setAttribute('prefix', '/');

fileNode = docNode.createElement('file');
fileNode.setAttribute('alias', 'node_schema.xsd');
fileNode.appendChild(docNode.createTextNode('node.xsd'));
currentNode.appendChild(fileNode);

fileNode = docNode.createElement('file');
fileNode.setAttribute('alias', 'datatype_schema.xsd');
fileNode.appendChild(docNode.createTextNode('datatype.xsd'));
currentNode.appendChild(fileNode);

docRoot.appendChild(currentNode);

%
currentNode = docNode.createElement('qresource');
currentNode.setAttribute('prefix', '/Images');

fileNode = docNode.createElement('file');
fileNode.setAttribute('alias', 'RepeatingBrains.png');
fileNode.appendChild(docNode.createTextNode('Images/RepeatingBrains.png'));
currentNode.appendChild(fileNode);
docRoot.appendChild(currentNode);

%% Add NiPype nodes
prefix = 'Dictionaries/NiPype';
directory = fullfile('../Resources', prefix);
currentNode = docNode.createElement('qresource');
currentNode.setAttribute('prefix', prefix);

files = dir([directory '/*.node']);
files = {files(:).name};
for i = 1:length(files)
    fileNode = docNode.createElement('file');
    fileNode.setAttribute('alias', sprintf('node_%03d.xml', i - 1));
    
    [~, file, ~] = fileparts(files{i});
    fileNode.appendChild(docNode.createTextNode(strrep(fullfile(directory, [file, '.node']), '\', '/')));
    currentNode.appendChild(fileNode);
end
docRoot.appendChild(currentNode);

%% Add TvM nodes
prefix = 'Dictionaries/TvM';
directory = fullfile('../Resources', prefix);
currentNode = docNode.createElement('qresource');
currentNode.setAttribute('prefix', prefix);

files = dir([directory '/*.node']);
files = {files(:).name};
for i = 1:length(files)
    fileNode = docNode.createElement('file');
    fileNode.setAttribute('alias', sprintf('node_%03d.xml', i - 1));
    
    [~, file, ~] = fileparts(files{i});
    fileNode.appendChild(docNode.createTextNode(strrep(fullfile(directory, [file, '.node']), '\', '/')));
    currentNode.appendChild(fileNode);
end

%%
docRoot.appendChild(currentNode);

xmlFileName = fullfile(saveLocation, 'resources.qrc');
xmlwrite(xmlFileName, docNode);
type(xmlFileName);














