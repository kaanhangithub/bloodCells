

#include<stdio.h>
#include<stdlib.h>
#define IMAGE_SIZE 10
#define MAX_LABEL 100

// this function prints the array
void printImgArray(int array[IMAGE_SIZE][IMAGE_SIZE])
{
  
    printf("------ Image Contents -------\n");
    int i, j;
	for (i=0; i<IMAGE_SIZE; i++)
    {
    for (j=0; j<IMAGE_SIZE; j++)
        printf("%02d, ",array[i][j]);
    printf("\n");
    }
    printf("-----------------------------\n");
}


// this is a helper method for cellCount.
// this function returns the unique numbers of labels inside the labels array.
int uniqueLabels(int labels[MAX_LABEL],int length){

int i, j, result = 0 ;
for(i=0; i<length; i++)
    for(j=i+1; j<length; j++)
        if(labels[i]==labels[j])
            //we know that label cant be zero so we can assign 0 to the duplicate ones.
            // by this way , we can locate unique labels.
            labels[j]=0;

for(i=0; i<length; i++) 
    // we are finding unique numbers of labels by counting non zero labels.
    if(labels[i]!=0)
        result++;
 
return result;    

}
/**
 * This function counts the number of distinct 
 * number (i.e. the number of cells)
 **/

int cellCount(int image[IMAGE_SIZE][IMAGE_SIZE]){
    // insert your code for task1.2 here
    // you may want to change the return value.
    int i, j, count = 0;
    int labels[MAX_LABEL];
    for (i=0; i<IMAGE_SIZE; i++)
      for (j=0; j<IMAGE_SIZE; j++) 
          if(image[i][j]!= 0)
              //we store all labels inside the labels array.
              // this array includes duplicate elements.
              labels[count++] = image[i][j];
          
    //we call uniqueLabels,because we have to get rid of the duplicate elements.
    int result = uniqueLabels(labels,count);
    return result;
}
//this function check if the current location is inside the border or not. helper for helperColor.
int insideBorder(int i,int j){
    if(i>=0 && j>=0 && i<IMAGE_SIZE && j<IMAGE_SIZE)
        return 1;
    else
        return 0;
}
//this is a helper function for color function.
void helperColor(int image[IMAGE_SIZE][IMAGE_SIZE],int label,int i,int j){

    // this two dimension array contains 8 different directions for current location.
    // North,North-East,East,South-East,South,South-West,West,North-West respectively.
    int directions[8][2] ={{-1,0},{-1,+1},{0,+1},{+1,+1},{+1,0},{+1,-1},{0,-1},{-1,-1}};

    if(image[i][j]==1 && insideBorder(i,j)){
        //if current location is inside the border and  1, we assign to the given label.
        image[i][j]=label;
        
        //we call all eight directions by recursive call.by this way we can find and label all the possible 1`s.
        int m;
        for (m=0; m<8; m++)
            helperColor(image,label,i+directions[m][0],j+directions[m][1]);    
        
    }  
}
/**
 * This function colors each blood cell with a unique color
 * (i.e. unique number)
 * Hint: scan the array element by element, and explore each element as much as possible, 
 * when come to an already labelled one, relabell the array to form larger cell
 **/
void color(int image[IMAGE_SIZE][IMAGE_SIZE]){
    // insert your code for task 1.1 here
    int i, j, label = 10;
    for (i=0; i<IMAGE_SIZE; i++)
        for (j=0; j<IMAGE_SIZE; j++)
            if( image[i][j] == 1)
                helperColor(image,label++,i,j);
}




/********************************************************************************/
//this function check if the current location is inside the border or not. helper for helperColor.
int insideBorderPtr(int i,int j){
    if(i>=0 && j>=0 && i<IMAGE_SIZE && j<IMAGE_SIZE)
        return 1;
    else
        return 0;
}
//this is a helper function for colorPtr function.
void helperColorPtr(int *image,int label,int i,int j){
    // this two dimension array contains 8 different directions for current location.
    // North,North-East,East,South-East,South,South-West,West,North-West respectively.
    int directions[8][2] ={{-1,0},{-1,+1},{0,+1},{+1,+1},{+1,0},{+1,-1},{0,-1},{-1,-1}};
    int *ptr = directions;

    if(*(image+i*IMAGE_SIZE+j)==1 && insideBorderPtr(i,j)){
        //if current location is inside the border and  1, we assign to the given label.
       *(image+i*IMAGE_SIZE+j)=label;
        
        //we call all eight directions by recursive call.by this way we can find and label all the possible 1`s.
        int m;
        for (m=0; m<8; m++)
            helperColorPtr(image,label,i+*(ptr+m*2+0),j+*(ptr+m*2+1));
             
    }  
}



//the function and all the helper functions (if any) should use pointer notation, 
// instead of array index notation []. It is okey to use [] only when declaring extra arrays
void colorPtr(int* image){
    // insert your code for task 2.1 here
    int i, j, label = 10;
    for (i=0; i<IMAGE_SIZE; i++)
        for (j=0; j<IMAGE_SIZE; j++)
            if( *(image+i*IMAGE_SIZE+j) == 1)
                helperColorPtr(image,label++,i,j);

}
// this is a helper method for cellCountPtr.
// this function returns the unique numbers of labels inside the labels array.
int uniqueLabelsPtr(int *labels,int length){

int i, j, result = 0 ;
for(i=0; i<length; i++)
    for(j=i+1; j<length; j++)
        if(*(labels+i)==*(labels+j))
            //we know that label cant be zero so we can assign 0 to the duplicate ones.
            // by this way , we can locate unique labels.
            *(labels+j)=0;
            
for(i=0; i<length; i++) 
    // we are finding unique numbers of labels by counting non zero labels.
    if(*(labels+i)!=0)
        result++;
 
return result;    

}
//the function and all the helper functions (if any) should use pointer notation, 
// instead of array index notation []. It is okey to use [] only when declaring extra arrays
int cellCountPtr(int* image){
	int i, j, count = 0;
    int labels[MAX_LABEL];
    for (i=0; i<IMAGE_SIZE; i++)
      for (j=0; j<IMAGE_SIZE; j++) 
          if(*(image+i*IMAGE_SIZE+j)!= 0)
              //we store all labels inside the labels array.
              // this array includes duplicate elements.
              *(labels+count++) = *(image+i*IMAGE_SIZE+j);

    //we call uniqueLabels,because we have to get rid of the duplicate elements.
    int result = uniqueLabelsPtr(labels,count);
    return result;

}

/********************************************************************************/

/**
 * This function colors each cell with a unique color
 * (i.e., unique number).
 **/

int colorRecursively(int image[IMAGE_SIZE][IMAGE_SIZE]) {
    
    return 0;
 
}

 

#ifndef __testing
int main(){

    // DO not change anything in main(), it will confuse the
    // auto-checker.  
    puts("testing the code with color() function");
    int count = 0;
    int cellImg[IMAGE_SIZE][IMAGE_SIZE]={{0,0,1,1,0,0,1,0,0,1},\
		               {1,0,1,1,0,0,1,1,0,1},\
		               {1,0,0,1,1,0,1,1,0,1},\
		               {1,1,0,0,0,0,0,0,0,0},\
		               {1,0,0,1,1,1,0,0,1,0},\
		               {0,0,0,0,1,0,0,1,1,0},\
		               {0,0,1,0,0,1,0,1,0,0},\
		               {0,0,1,1,0,0,1,0,0,0},\
		               {0,0,1,0,0,0,0,0,1,1},
		               {0,1,1,0,0,0,1,1,1,1}};

    printImgArray(cellImg);
    color(cellImg);
    printImgArray(cellImg);
    count=cellCount(cellImg);
    printf("Total number of cells in the image: %d\n",count);
 

    puts("Testing the code with colorPtr");
    int cellImg_[IMAGE_SIZE][IMAGE_SIZE]={{0,0,1,1,0,0,1,0,0,1},\
		               {1,0,1,1,0,0,1,1,0,1},\
		               {1,0,0,1,1,0,1,1,0,1},\
		               {1,1,0,0,0,0,0,0,0,0},\
		               {1,0,0,1,1,1,0,0,1,0},\
		               {0,0,0,0,1,0,0,1,1,0},\
		               {0,0,1,0,0,1,0,1,0,0},\
		               {0,0,1,1,0,0,1,0,0,0},\
		               {0,0,1,0,0,0,0,0,1,1},
		               {0,1,1,0,0,0,1,1,1,1}};

    int* ptr = cellImg_;
    printImgArray(ptr);
    colorPtr(ptr);
    printImgArray(ptr);
    count=cellCountPtr(ptr);
    printf("Total number of cells in the image: %d\n",count); 
    
	puts("Testing the code with colorRecursively");
    int cellImg__[IMAGE_SIZE][IMAGE_SIZE]={{0,0,1,1,0,0,1,0,0,1},\
		               {1,0,1,1,0,0,1,1,0,1},\
		               {1,0,0,1,1,0,1,1,0,1},\
		               {1,1,0,0,0,0,0,0,0,0},\
		               {1,0,0,1,1,1,0,0,1,0},\
		               {0,0,0,0,1,0,0,1,1,0},\
		               {0,0,1,0,0,1,0,1,0,0},\
		               {0,0,1,1,0,0,1,0,0,0},\
		               {0,0,1,0,0,0,0,0,1,1},
		               {0,1,1,0,0,0,1,1,1,1}};
    printImgArray(cellImg__);
    colorRecursively(cellImg__);
    printImgArray(cellImg__);
    count=cellCount(cellImg__);
    printf("Total number of cells in the image: %d\n",count);
    return 0;
}
#endif
