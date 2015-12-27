
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

string input_file_name, input_file_name_1, output_file_name_1, output_file_name_2, output_file_name_3, output_file_name_4, output_file_name_5, output_file_name_6;
int N_molecules=0;
int *N_atoms=NULL;
int *N_edges=NULL;
char *name_labels;
int *number_edges;
int *number_labels;
char *list_of_all_labels;
string *name_el;
int *true_lb;

int i=0, j=0, k=0, total_number_of_atoms=0;

void read_input_file(string input_file_name, string output_file_name_1, string output_file_name_2, string output_file_name_3, string output_file_name_4, string output_file_name_5, string output_file_name_6){
   
    
    ifstream input_file;
    string input[400000];
    
    input_file.open(input_file_name.c_str());
    if(input_file.is_open()==0)
    {
        cout<<"error: could not open input file!"<<endl;
        exit(1);}
    
    while (!input_file.eof()) {
        getline(input_file, input[i]);
        i++;}
    k=i;
    input_file.close();
    
    cout<<"number of strings="<<k<<endl;
    string end_of_molecule="$$$$";
    int *n_lines;
    

    //look for number of molecules in the database
   
    for (i=0; i<k; i++)
    {
        if (input[i].compare(end_of_molecule)==0)
        {N_molecules=N_molecules+1;
        }
    }
    
    cout<<"N_molecules = "<<N_molecules<<endl;
   
    
    n_lines = new int [N_molecules];
    N_atoms = new int[N_molecules];
    N_edges = new int[N_molecules];
    
    name_el = new string[N_molecules];
    true_lb = new int[N_molecules];
    
    
    j=0;
    for (i=0; i<k; i++)
    {
         n_lines[j]=n_lines[j]+1;
        if (input[i].compare(end_of_molecule)==0)
        {
            j=j+1;
            
     }
    }
    
    
    
    //look for number of atoms and number of edges in each molecule
    int line_counter=0;
    for (i=0; i<N_molecules; i++)
    {
    string str;
        
        
    str=input[3+line_counter];
    stringstream stream(str);
    stream >>N_atoms[i];
    stream >>N_edges[i];
    total_number_of_atoms=total_number_of_atoms+N_atoms[i];
        
      line_counter=line_counter+n_lines[i];
    }
    
    
    list_of_all_labels = new char[total_number_of_atoms];
    number_labels = new int [total_number_of_atoms];
    number_edges = new int [total_number_of_atoms];
    int max_el=0;
    max_el=N_atoms[0];
    for (i=0; i<N_molecules; i++)
    {
        if (N_atoms[i]>max_el) max_el=N_atoms[i];
    }
    cout<<max_el<<endl;
    
    
    int *m_wrong;
    int f=0;
    line_counter=0;
    for (i=0; i<N_molecules; i++){
        
        int sub_m[N_edges[i]][3];
        
        
        for (j=0; j<N_edges[i]; j++){
            string str;
            str=input[4+j+N_atoms[i]+line_counter];
            
            istringstream iss(str);
            for (int l=0; l<3; l++)
            {
                iss>>sub_m[j][l];
                iss.clear();
            }
         
            if (sub_m[j][0]>1000) {f=f+1;
                break;
            }
            
        }
        
        
        line_counter=line_counter+n_lines[i];

    }

    m_wrong = new int[f];
    int lenght_m_w=0;
    k=0;
    line_counter=0;
    for (i=0; i<N_molecules; i++){
        
        int sub_m[N_edges[i]][3];
        for (j=0; j<N_edges[i]; j++){
            string str;
            str=input[4+j+N_atoms[i]+line_counter];

            istringstream iss(str);
            for (int l=0; l<3; l++)
            {
                iss>>sub_m[j][l];
                iss.clear();
            }
            if (sub_m[j][0]>1000) {m_wrong[lenght_m_w]=i; lenght_m_w=lenght_m_w+1; break;}
        }
        
        
        
        line_counter=line_counter+n_lines[i];
    }

    
    //write true label values into file
    
    line_counter=0;
    int flag=0;
    ofstream output_file_6;
    output_file_6.open(output_file_name_6.c_str());
    
    if(output_file_6.is_open()==0)
    {
        cout<<"error: could not create output file!"<<endl;
        exit(1);
    }
    for (i=0; i<N_molecules; i++){
        
        flag=0;
        for (j=0; j<lenght_m_w; j++) { if (i==m_wrong[j]) {flag=1; line_counter=line_counter+n_lines[i]; break;}}
        if (flag==0){
        string str;
        str=input[line_counter+n_lines[i]-12];
            cout<<str<<endl;
            double val=0, threshold = 1;
            
            
            if (str.compare(">")>0) {
                char str1[10];
                strcpy(str1, str.c_str());
                str1[0]=' ';
                string str2(str1);
                istringstream iss(str2);
                iss>>val;
                iss.clear();
                cout<<val<<endl;}
            else {
            istringstream iss(str);
            iss>>val;
            iss.clear();
                cout<<val<<endl;}
            if (val>=threshold) output_file_6<<1<<endl;
            else
                output_file_6<<0<<endl;
            
        line_counter=line_counter+n_lines[i];
        }
    }
    output_file_6.close();
    
    
    // for each graph write number of edges and number of nodes into file
    
    int flag=0;
    ofstream output_file_1;
    output_file_1.open(output_file_name_1.c_str());
    if(output_file_1.is_open()==0)
    {
        cout<<"error: could not create output file!"<<endl;
        exit(1);
    }
    for (i=0; i<N_molecules; i++){
        flag=0;
        for (j=0; j<lenght_m_w; j++) { if (i==m_wrong[j]) {flag=1; break;}}
        if (flag==0)
        output_file_1<<N_atoms[i]<<'\t'<<N_edges[i]<<endl;
    }
    output_file_1.close();
    
    
    
    
  

    //write a file with list of all labels
    line_counter=0;
    k=0;
    cout<<"inside list of labels"<<endl;
    for (i=0; i<N_molecules; i++)
    {
        for(j=0; j<N_atoms[i]; j++)
        {
            
    string str;
    str=input[4+j+line_counter];
        
    istringstream iss(str);
    string sub[4];
    for (int l=0; l<4; l++)
    {
        iss>>sub[l];
        iss.clear();
    }
    
    const char *ch=sub[3].c_str();
    list_of_all_labels[k]=ch[0];
            k=k+1;
  
        }
        line_counter=line_counter+n_lines[i];
    }
   
    
    //relabeling nodes from chemical elements to numbers
   
    k=1;
    number_labels[0]=k;
    
    for (i=1; i<total_number_of_atoms; i++){
        for (j=0; j<i; j++){
                    //if (list_of_all_labels[i]==list_of_all_labels[i-1]){
                //number_labels[i]=number_labels[i-1];
                  //  }
                     if (list_of_all_labels[i]==list_of_all_labels[j]){
                        number_labels[i]=number_labels[j];
                         break;
                    }
                    else if (j==(i-1) ) {k=k+1;
                        number_labels[i]=k;
                    }
        }
    }

    ofstream output_file_2;
    output_file_2.open(output_file_name_2.c_str());
    if (output_file_2.is_open()==0){
    cout<<"error: could not create output file!"<<endl;
        exit(1);
    }
    line_counter=0;
    for (i=0; i<N_molecules; i++)
    {
        flag=0;
        for (k=0; k<lenght_m_w; k++) { if (i==m_wrong[k]) {flag=1;  line_counter=line_counter+N_atoms[i]; break;}}
        
        if (flag==0){
        for (j=0; j<N_atoms[i]; j++){
        
        output_file_2<<number_labels[line_counter]<<endl;
        line_counter=line_counter+1;
        }}
        output_file_2<<endl;
    }

    output_file_2.close();
  
    //find adjacency matrix
   
    ofstream output_file_3;
    ofstream output_file_4;
    ofstream output_file_5;
    output_file_3.open(output_file_name_3.c_str());
    output_file_4.open(output_file_name_4.c_str());
    output_file_5.open(output_file_name_5.c_str());
    
    if (output_file_3.is_open()==0){
        cout<<"error: could not create output file!"<<endl;
        exit(1);
    }
    
    
    if(output_file_4.is_open()==0){
        cout<<"error: could not create output file!"<<endl;
        exit(1);
    }
    
    if (output_file_5.is_open()==0){
        cout<<"error: could not create file!"<<endl;
        exit(1);
    }
   
    
    
   
    
    line_counter=0;
    for (i=0; i<N_molecules; i++){
        
        int sub_m[N_edges[i]][3];
        int am[N_atoms[i]][N_atoms[i]];
        int al[N_atoms[i]][N_atoms[i]];
        
        flag=0;
        for (k=0; k<lenght_m_w; k++) { if (i==m_wrong[k]) {flag=1;  line_counter=line_counter+n_lines[i]; break;}}
        
        if (flag==0){
        
        
        for (int v=0; v<N_atoms[i]; v++)
        { for (int w=0; w<N_atoms[i]; w++)
        { am[v][w]=0;
            al[v][w]=-1;
        }}
        
        
        for (j=0; j<N_edges[i]; j++){
    string str;
    str=input[4+j+N_atoms[i]+line_counter];
    
    istringstream iss(str);
    //string sub[3];
    for (int l=0; l<3; l++)
    {
        iss>>sub_m[j][l];
        //cout<<sub_m[j][l]<<' ';
        iss.clear();
    }
           // cout<<endl;
   
        }
        
        line_counter=line_counter+n_lines[i];
        
        for (j=0; j<N_edges[i]; j++){
            am[sub_m[j][0]-1][sub_m[j][1]-1]=1;
            am[sub_m[j][1]-1][sub_m[j][0]-1]=1;
        }
        
        
        //flag=0;
        //for (k=0; k<lenght_m_w; k++) { if (i==m_wrong[k]) {flag=1;  line_counter=line_counter+N_atoms[i]; break;}}
        
        //if (flag==0){
        
        
        
        
        
        
        //___________________________________________
        
        
        cout<<input[line_counter]<<endl;
        cout<<i<<endl;
        
       
        
        for (int v=0; v<N_atoms[i]; v++)
        {for (int w=0; w<N_atoms[i]; w++)
        { output_file_3<<am[v][w]<<" ";
        
        }output_file_3<<endl;
        }
        output_file_3<<endl;
        
        //___________________________________________
        
        
        
        int m=0;
        for (int v=0; v<N_atoms[i]; v++)
        {for (int w=0; w<N_atoms[i]; w++)
        {
            if (am[v][w]!=0){
                al[v][w]=w+1;
                m=m+1;
            }
           
        }
           
                output_file_5<<m<<endl;
            m=0;
        }
        //____________________________________________
        
      
        for (int v=0; v<N_atoms[i]; v++)
        {for (int w=0; w<N_atoms[i]; w++)
        {
            if (al[v][w]!=-1)
             output_file_4<<al[v][w]<<" ";
            
            
        } output_file_4<<endl;
        } output_file_4<<endl;
       
        }
    }
    
       /* cout<<i<<": "<<endl;
        for (j=0; j<N_edges[i]; j++){
         for (int l=0; l<3; l++)
         {
         cout<<sub_m[j][l]<<' ';
         
         }
         cout<<endl;
         }
        cout<<endl;
     */
        //cout<<input[line_counter]<<endl;
    

    output_file_3.close();
    output_file_4.close();
    output_file_5.close();
    

}


void true_labels(string input_file_name, string output_file_name){
    cout<<"inside the function"<<endl;
    ifstream input_file;
    string *input1;
    input1 = new string[400000];
    cout<<"inside input file"<<endl;
    
    
    input_file.open(input_file_name.c_str());
    if (input_file.is_open()==0){
        cout<<"error: could not open input file!"<<endl;
        exit(1);
    }
    
    int b=0;
    while (!input_file.eof()){
        getline(input_file, input1[b]);
        b++;
    }
    cout<<"b = "<<b<<endl;
    
    
    for (i=0; i<b; i++)
    {
        string str;
        str=input1[i];
        
        istringstream iss1(str);
        
       // iss1>>name_el[i];
        iss1>>true_lb[i];
        iss1.clear();
        
        
        
    }
    
    cout<<"size of true_lb set:"<<b<<endl;;
    ofstream output_file;
    output_file.open(output_file_name.c_str());
    if (output_file.is_open()==0){
        cout<<"error: could not create a file!"<<endl;
        exit(1);
    }
    
    for (i=0; i<b; i++){
        output_file<<true_lb[i]<<endl;
    }
    output_file.close();


}



int main(int argc, const char * argv[]) {

    if(argc!=2){
        std::cout<<"error: wrong invocation!"<<endl;
        std::cout<<"try with:"<<endl;
        std::cout<<"motion <string input_file_name>"<<endl;
        return 0;
        
    }
    input_file_name=argv[1];
   // input_file_name_1=argv[2];
    
    read_input_file(input_file_name, "size_of_the_set.txt", "node_labels.txt", "adjacency_matrix.txt", "adjacency_labels.txt", "number_of_edges.txt", "true_labels.txt" );
    //true_labels(input_file_name_1, "true_labels.txt");
    return 0;
}
