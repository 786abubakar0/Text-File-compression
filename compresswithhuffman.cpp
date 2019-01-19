#include <iostream>
#include <string.h>
#include <assert.h>
#include <fstream>
#include <math.h>
using namespace std;
/************************************linked list for storing subtree address**************************************************/
/*--------------------------linked list node-------------------------------------*/
struct llnode{
struct llnode* next=0;
struct sbnode* value=0;
} ;

class subtrees{
private:
   struct llnode* head=0;
    struct llnode* tail=0;
    int numofnodes=0;
public:

    void addathead(sbnode* v=0){//adding actually at tail
        llnode* p=new llnode;
        p->value=v;
        if(!head){
            p->next=0;
            head=p;
            tail=p;
        }
        else{
            tail->next=p;
            tail=p;

        }
        numofnodes++;
    }

    sbnode* accessvalue(int index)//index starting from 0
    {
        llnode* traverse=head;
        for(int i=0;i<index;i++)
        {
                traverse=traverse->next;
        }

        sbnode* value=traverse->value;
        return value;
    }

    int getnodes()
    {

        return numofnodes;
    }
};

/*--------------------------sorting frequency array and corresponding character array in descending order-------------------------------------*/

void bubbleSort(int* arr,int* ascii, int n)    //decreasing order
{
   int i, j;
   for (i = 0; i < n-1; i++)

       // Last i elements are already in place
       for (j = 0; j < n-i-1; j++)
           if (arr[j] > arr[j+1])
              {
                  int num1=arr[j];
                  int num2=ascii[j];
                  arr[j]=arr[j+1];
                  ascii[j]=ascii[j+1];
                  arr[j+1]=num1;
                  ascii[j+1]=num2;

              }
};

/************************************binary tree**************************************************/
struct sbnode{
sbnode* left=0;
sbnode* right=0;
int character=-1;
int freq=-1;
int sum=-1;
};

class bt{
private:
    sbnode* p1=0;
    sbnode* p2=0;
    sbnode* p3=0;
    subtrees obj;
    int tmp=256;
    int stindex=0;
    sbnode* head=0;

public:
    bt(int* freqarr,int* corrascii,int arraylength){

        int isend=0;
        while(isend!=arraylength-1)
        {
        int leftchar=corrascii[isend];
        int leftf=freqarr[isend];
        int rightchar=corrascii[isend+1];
        int rightf=freqarr[isend+1];
        int sum=leftf+rightf;

        if(leftchar>255)
        {
            p1=obj.accessvalue(stindex++);

        }
        else{
             p1=createsbnode(0,0,leftchar,leftf,-1);
        }
        if(rightchar>255)
        {
            p2=obj.accessvalue(stindex++);
        }
        else{
            p2=createsbnode(0,0,rightchar,rightf,-1);

        }
        p3=createsbnode(p1,p2,-1,-1,sum);
        obj.addathead(p3);
        freqarr[0]=sum;
        freqarr[1]=0;
        corrascii[0]=tmp++;
        corrascii[1]=0;
        bubbleSort(freqarr,corrascii,arraylength);
        isend++;
        }
        head=obj.accessvalue(stindex);

    }
    sbnode* gethead(){
    return head;
    }


    sbnode* createsbnode(sbnode* left=0,sbnode* right=0,int character=-1,int freq=-1,int sum=-1){
        sbnode* retnode=new sbnode;
        retnode->left=left;
        retnode->right=right;
        retnode->character=character;
        retnode->freq=freq;
        retnode->sum=sum;
        return retnode;
    }
};
/*-------------------------------array stack------------------------------------------*/
class arraystack
{

private:
    int counter=0;
    int array[8];
public:
    void push(int n)
    {
        array[counter++]=n;
    }
    int pop(){
    return array[--counter];
    }

    bool isfull(){
    return counter==8;}

    bool isempty()
    {

        return counter==0;
    }
    int getcounter(){
    return counter;
    }

};


/*--------------------------------encoding class---------------------------------------------------*/
class encoding{
private:
int** encode=new int*[256];
    int* numofelementarr=new int[256];//number of bits in each character
public:
    /*----------------------printing codes called by print-codes method---------------------------------*/

    void makingArr(int arr[],int n,int character)
{
    int i;
    int* arr2=new int[n];
    encode[character]=arr2;
    numofelementarr[character]=n;

    for (i = 0; i < n; ++i){
        // printf("%d ", arr[i]);
          arr2[i]=arr[i];
    }

   // printf("\n");
}
/*---------------------traversing binary tree for binary codes---------------------------------*/
  void makingCodes(struct sbnode* root, int arr[], int top)

{

    // Assign 0 to left edge and recur
    if (root->left!=0) {

        arr[top] = 0;
       makingCodes(root->left, arr, top + 1);
    }

    // Assign 1 to right edge and recur
    if (root->right!=0) {

        arr[top] = 1;
        makingCodes(root->right, arr, top + 1);
    }

    // If this is a leaf node, then
    // it contains one of the input
    // characters, print the character
    // and its code from arr[]
    if (root->character!=-1 &&root->freq!=-1) {

       // printf("%c:%d ", root->character,root->character);
        makingArr(arr, top,root->character);
    }
}

/*------------------encoding array------------------------------*/
int** getencodingarr()
{
    return encode;
}
/*--------------------number of bits in each character encoding----*/
int* getnumofelementarr(){
return numofelementarr;
}

void makingencodingfile(char* filename,int* freqarr){
    arraystack obj;
    fstream infile;
    fstream outfile;
    infile.open(filename,ios::in);
    outfile.open("compressed.txt",ios::out);

    char c;
    int** encodingarray=getencodingarr();
  int* numofelement=getnumofelementarr();

  outfile<<'A'<<endl;
      for(int i=2;i<256;i++)
    {
        if(i==2){
                 outfile<<0<<endl;

        }
        else{
        outfile<<freqarr[i]<<endl;}
    }


    while(infile>>noskipws>>c){
        int* element=encodingarray[c];
    for (int j=0;j<numofelement[c];j++)
    {
        char tosubmit;
        if(obj.isfull()){

                tosubmit=obj.pop()*pow(2,0) +obj.pop()*pow(2,1)+obj.pop()*pow(2,2)+obj.pop()*pow(2,3)+obj.pop()*pow(2,4)+obj.pop()*pow(2,5)+obj.pop()*pow(2,6)+obj.pop()*pow(2,7);
                outfile<<tosubmit;
        }
            obj.push(element[j]);

  }

}

    char tosubmit;
        if(obj.isfull()){
                tosubmit=obj.pop()*pow(2,0) +obj.pop()*pow(2,1)+obj.pop()*pow(2,2)+obj.pop()*pow(2,3)+obj.pop()*pow(2,4)+obj.pop()*pow(2,5)+obj.pop()*pow(2,6)+obj.pop()*pow(2,7);
                outfile<<tosubmit;
        }
int remain=0;
if(!obj.isempty()){
    remain=obj.getcounter();
    int* remainarr=new int[remain];
    int i=remain-1;
    while(!obj.isempty()){
        remainarr[i]=obj.pop();
        i--;
    }

    for(int i=0;i<remain;i++){
     outfile<<remainarr[i];
    }
}


outfile.clear();
outfile.seekg(0, ios::beg);
outfile<<remain<<endl;
void close();
void close();
}};
/*------------------------------making frequency table- each index navigates corresponding ascii character---------------------------------*/
int* freq(char* filename)
{

    int a;
    int* freqarr=new int[256];
    char c;
    fstream infile;
    infile.open(filename,ios::in);
    while(infile>>noskipws>>c){
            freqarr[c]+=1;
        }
    void close();

    return freqarr;
};

/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/*************************decimal to binary************************/
int* tobinary(int num){
int* arr=new int[8];
for(int j=0;j<8;j++){
    arr[j]=0;
}
if(num==0){
    return arr;
}
int i=7;
while(num!=1){
    arr[i]=num%2;
    num=num/2;
    i--;
}
arr[i]=num;
return arr;
}
/*-------------------------decompressing-------------------------------*/
class decoding{
public:
    decoding(char* filename){
        fstream infile;
        fstream infile2;
        infile.open(filename,ios::in);
        infile2.open(filename,ios::in);
        char c;
        int remainedbitsnum=0;
        c=infile.get();
        remainedbitsnum=c-'0';
        int pos=remainedbitsnum*(-1);
        //infile2.clear();
        infile2.seekg(pos,ios::end);
        int* freqarr=new int[256];
        int i=0;
        freqarr[0]=0;
        freqarr[1]=0;
        c=infile.get();
        i=2;
        while(i<256){
            if(c!=10){
                while(c!=10){
                freqarr[i]=freqarr[i]*10+(c-'0');
                c=infile.get();
            }
            i++;
            }
            c=infile.get();

        }
  int* corascii=new int[256];
  //giving each index value=index for tracking sorting of frequency array
  for(int i=0;i<256;i++){
    corascii[i]=i;
  }
  //sorting ascii array and frequency array in ascending order
  bubbleSort(freqarr,corascii,256);
  int num=0;//no of distinct characters in file
  //no of non zero frequency
  for(int i=0;i<256;i++){
    if(freqarr[i]!=0){
        num++;
    }
  }

  int* frequencyarr=new int[num];   //array of frequency with non zero values only
  int* correspondingascii=new int[num]; //array of characters with non-zero frequency
  int tmp=255;
  //copying non zero freq and ascii in sorted order
  for(int i=num-1;i>=0;i--){
    frequencyarr[i]=freqarr[tmp];
    correspondingascii[i]=corascii[tmp--];
  }
  //constructor call of binary tree class for making binary tree
  bt obj(frequencyarr,correspondingascii,num);
  sbnode* head=obj.gethead();


    sbnode* traverse=head;
  arraystack stackobj;
fstream outfile;
char* decodedfile="decompressed.txt";
outfile.open(decodedfile,ios::out);
int isbreak=0;
l1:
  while(isbreak==0){

  if(infile.tellg()==infile2.tellg())
    {

        isbreak++;}
        int ascii=c;
       // if(c<0){

         //   c=256+c;
        //}


        if(ascii<0)
        {
            ascii=256+ascii;
        }
        //cout<<"infile:"<<infile.tellg()<<"-infile2:"<<infile2.tellg()<<"-c:"<<(char)ascii<<endl;

        int* binarray=tobinary(ascii);
        for(int i=7;i>=0;i--){
            stackobj.push(binarray[i]);
        }
        l2:
        while(traverse->left!=0 && traverse->right!=0){
            if(!stackobj.isempty()){

                int bit=stackobj.pop();
             //   cout<<"pop is "<<bit<<endl;

                if(bit==0){
                    traverse=traverse->left;
                }
                else if(bit==1){
                    traverse=traverse->right;
                }

            }

            else{
                c=infile.get();
                goto l1;
            }
        }
        outfile<<(char)traverse->character;
        //cout<<"char:"<<(char)traverse->character<<endl;
        //cout<<"c is "<<(char)c<<endl;
        traverse=head;
        goto l2;
  }
  /*------------------remaining bits-------------------------*/
 if(remainedbitsnum!=0)
 {

  infile.seekg(-1,ios::cur);
   int k=1;

  while(!infile.eof()){
    int bit;
    if(traverse->left==0 && traverse->right==0){
        outfile<<(char)traverse->character;
        traverse=head;
       // cout<<"k:"<<k<<endl;
    }
     bit=infile.get()-'0';
     //cout<<bit<<endl;
        if(bit==0){
                    traverse=traverse->left;
                }
        else if(bit==1){
                    traverse=traverse->right;

                }
  k++;
  }}


  infile.close();
  infile2.close();
 outfile.close();
 delete freqarr;
 delete corascii;
 delete correspondingascii;
 delete frequencyarr;
    }

};



/*---------------------------main------------------------------------*/



int main()
{
    char filename[100];  //file to be compressed
    cout<<"File to compress:";
    cin>>filename;
  int* freqarr=new int[256];
  for(int i=0;i<256;i++){
    freqarr[i]=0;
  }
  freqarr=freq(filename);//file read and returning frequency of each character on corresponding index
  int* unsortedfarr=new int[256];

  for(int i=0;i<256;i++)
  {
      unsortedfarr[i]=freqarr[i];
  }
  int* corascii=new int[256];
  //giving each index value=index for tracking sorting of frequency array
  for(int i=0;i<256;i++){
    corascii[i]=i;
  }
  //making null and start of head(ing) frequency zero because it is not important
  freqarr[0]=0;
  freqarr[1]=0;
  //sorting ascii array and frequency array in ascending order
  bubbleSort(freqarr,corascii,256);
  int num=0;//no of distinct characters in file
  //no of non zero frequency
  for(int i=0;i<256;i++){
    if(freqarr[i]!=0){
        num++;
    }
  }

  int* frequencyarr=new int[num];   //array of frequency with non zero values only
  int* correspondingascii=new int[num]; //array of characters with non-zero frequency
  int tmp=255;
  //copying non zero freq and ascii in sorted order
  for(int i=num-1;i>=0;i--){
    frequencyarr[i]=freqarr[tmp];
    correspondingascii[i]=corascii[tmp--];

  }
  //constructor call of binary tree class for making binary tree

  bt obj(frequencyarr,correspondingascii,num);

  sbnode* head=obj.gethead();

 encoding obj2;
  int arr[1000],top=0;
  obj2.makingCodes(head,arr,top);
  obj2.makingencodingfile(filename,unsortedfarr);


  //decomressing//////////////////////////////////////////////////////////////////////////
  char* encodedfile="compressed.txt";
    decoding obj3(encodedfile);

}
