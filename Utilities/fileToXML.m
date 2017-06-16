function fileNode = fileToXML(docNode, type, alias, url)

fileNode = docNode.createElement(type);
fileNode.setAttribute('alias', alias);
fileNode.appendChild(docNode.createTextNode(url));

end %end function