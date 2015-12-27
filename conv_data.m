size_of_graph=load('size_of_the_set.txt');
N_atoms=size_of_graph(:,1);
N_edges=size_of_graph(:,2);

N_N_edges=load('number_of_edges.txt');

labels=load('node_labels.txt');

count=0;
for i=1:length(N_atoms)
    for j=1:N_atoms(i)
SUTH(1,i).nl.values(j,1)=labels(j+count);
    end;
    count = count + N_atoms(i);
end;

%datafile = tdfread('adjacency_matrix_MonoAmTest.txt');

matr=textread('adjacency_matrix.txt', '%u');
clc

count=1;

for i=1:length(N_atoms)
x=matr(count : count+N_atoms(i)*N_atoms(i)-1);
SUTH(1,i).am=vec2mat(x,N_atoms(i));
count = count + N_atoms(i)*N_atoms(i);
end;


matr1=textread('adjacency_labels.txt', '%u');
matr1
count=1;
count1=0
for i=1:length(N_atoms)
    for j=1:N_atoms(i)
SUTH(1,i).al{j,1}=matr1(count: count-1+ N_N_edges(j+count1));
count=count+N_N_edges(j+count1);
    end;
    count1=count1+j;
    %count = count + N_atoms(i);

end;

tr_l=load('true_labels.txt');
