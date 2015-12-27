# convert
Set of tools which help to convert data from chemical table files into graph format.

Input file should be in .sd or .sdf format. Each molecule is considered to be a graph with nodes as atoms and edges as bonds between these atoms. Nodes are labeled, edges are not labeled.

Output files in .txt format are:
- sizes of the set (each line has two numbers, first number is for the number of atoms in molecule, second number - number of edges in considered molecule);
- lists of neigbours;
- adjacency matrices;
- lists of node labels;
- lists of edge degrees;
- lists of true labels (optional. Include in case if you know the classification criteria and threshold according to which you will classify your molecules).

In this example I include MATLAB file which cnverts output files into .mat format and is suitable for the classification with lib SVM.  
