%% Resource File

currentPath = fileparts(mfilename('fullpath'));
saveLocation = fullfile(currentPath, '../resources/');


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
currentNode.setAttribute('prefix', '/images');

fileNode = docNode.createElement('file');
fileNode.setAttribute('alias', 'RepeatingBrains.png');
fileNode.appendChild(docNode.createTextNode('images/RepeatingBrains.png'));
currentNode.appendChild(fileNode);
fileNode = docNode.createElement('file');
fileNode.setAttribute('alias', 'eye.png');
fileNode.appendChild(docNode.createTextNode('images/eye.png'));
currentNode.appendChild(fileNode);
fileNode = docNode.createElement('file');
fileNode.setAttribute('alias', 'eye-hidden.png');
fileNode.appendChild(docNode.createTextNode('images/eye-hidden.png'));
currentNode.appendChild(fileNode);
fileNode = docNode.createElement('file');
fileNode.setAttribute('alias', 'eye-hover.png');
fileNode.appendChild(docNode.createTextNode('images/eye-hover.png'));
currentNode.appendChild(fileNode);
fileNode = docNode.createElement('file');
fileNode.setAttribute('alias', 'eye-hidden-hover.png');
fileNode.appendChild(docNode.createTextNode('images/eye-hidden-hover.png'));
currentNode.appendChild(fileNode);

fileNode = docNode.createElement('file');
fileNode.setAttribute('alias', 'iterate.png');
fileNode.appendChild(docNode.createTextNode('images/iterate.png'));
currentNode.appendChild(fileNode);
fileNode = docNode.createElement('file');
fileNode.setAttribute('alias', 'iterate-off.png');
fileNode.appendChild(docNode.createTextNode('images/iterate-off.png'));
currentNode.appendChild(fileNode);
fileNode = docNode.createElement('file');
fileNode.setAttribute('alias', 'iterate-hover.png');
fileNode.appendChild(docNode.createTextNode('images/iterate-hover.png'));
currentNode.appendChild(fileNode);
fileNode = docNode.createElement('file');
fileNode.setAttribute('alias', 'iterate-off-hover.png');
fileNode.appendChild(docNode.createTextNode('images/iterate-off-hover.png'));
currentNode.appendChild(fileNode);
docRoot.appendChild(currentNode);

%
currentNode = docNode.createElement('qresource');
currentNode.setAttribute('prefix', '/qss');

fileNode = docNode.createElement('file');
fileNode.setAttribute('alias', 'visibility_button.qss');
fileNode.appendChild(docNode.createTextNode('qss/visibility_button.qss'));
currentNode.appendChild(fileNode);
fileNode = docNode.createElement('file');
fileNode.setAttribute('alias', 'iterator_button.qss');
fileNode.appendChild(docNode.createTextNode('qss/iterator_button.qss'));
currentNode.appendChild(fileNode);
docRoot.appendChild(currentNode);

%% Add NiPype nodes
prefix = 'dictionaries/NiPype';
directory = fullfile('../resources', prefix);
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
prefix = 'dictionaries/TvM';
directory = fullfile('../resources', prefix);
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














