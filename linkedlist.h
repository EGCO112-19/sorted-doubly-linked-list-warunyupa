// self-referential structure                       
struct Node {                                      
   int data; // each listNode contains a character 
   struct Node *nextPtr; // pointer to next node
   struct Node *prevPtr; // pointer to previous node
}; // end structure listNode  

typedef struct Node LLnode; // synonym for struct listNode
typedef LLnode *LLPtr; // synonym for ListNode* //pointer ของ LLnode
//หรือ typerdef  LLnode* LLPtr;

// prototypes


int deletes( LLPtr *sPtr, int value );
int isEmpty( LLPtr sPtr );
void insert( LLPtr *sPtr, int value );
void printList( LLPtr currentPtr );
void printListR( LLPtr currentPtr );
void instructions( void );





// display program instructions to user
void instructions( void )
{ 
   puts( "Enter your choice:\n"
      "   1 to insert an element into the list.\n"
      "   2 to delete an element from the list.\n"
      "   3 to end." );
} // end function instructions

// insert a new value into the list in sorted order
void insert( LLPtr *sPtr, int value )
{ 
   LLPtr newPtr; // pointer to new node
   LLPtr previousPtr; // pointer to previous node in list
   LLPtr currentPtr; // pointer to current node in list

  //สร้างกล่องข้อมูลใหม่
   newPtr =(LLPtr) malloc( sizeof( LLnode ) ); // create node
  //ใส่ค่าให้กล่องข้อมูลใหม่
   if ( newPtr != NULL ) { // is space available
      newPtr->data = value; // place value in node
      newPtr->nextPtr = NULL; // node does not link to another node
      newPtr->prevPtr = NULL;
      
      previousPtr = NULL; 
      currentPtr = *sPtr; //กำลังชี้กล่องแรกของข้อมูลเดิม
      // loop to find the correct location in the list 
      while ( currentPtr != NULL && value > currentPtr->data ) {
         previousPtr = currentPtr; // walk to ...               
         currentPtr = currentPtr->nextPtr; // ... next node 
      } // end while                                         

      // insert new node at beginning of list ->ตำแหน่งข้อมูลใหม่อยู่ตำแหน่งแรก
      if ( previousPtr == NULL ) {
         newPtr->nextPtr = *sPtr;   //ให้ nextPtr ชี้กล่องแรกของข้อมูลเดิม 
         *sPtr = newPtr; //เปลี่ยนที่ชี้ให้กับ *sPtr มาชี้ที่กล่องใหม่ 
         currentPtr = newPtr; //currentPtr->prevPtr = newPtr; ไม่ได้ Error-1 
      } // end if
      
      // 0 node
      else if(*sPtr == NULL){
        previousPtr = NULL;
        currentPtr = NULL;
        (*sPtr)->nextPtr = newPtr;
        newPtr->nextPtr = currentPtr;
      }//end else if

      //nornal insert
      else { // insert new node between previousPtr and currentPtr
         previousPtr->nextPtr = newPtr; //previousPtr-nextPtr เปลี่ยนมาชี้ newPtr
         newPtr->prevPtr = previousPtr; 
         newPtr->nextPtr = currentPtr; 
         currentPtr  = newPtr; 
      } // end else
   } // end if
   else { //เกิดขึ้นในกรณที่ พื้นที่เต็ม 
      printf( "%d not inserted. No memory available.\n", value );
   } // end else
} // end function insert

// delete a list element
int deletes( LLPtr *sPtr, int value )
{ 
   LLPtr previousPtr; // pointer to previous node in list
   LLPtr currentPtr; // pointer to current node in list
   LLPtr tempPtr; // temporary node pointer

   // delete first node
   if ( value == ( *sPtr )->data) {  //เช็คว่า ค่าที่เราเลือก ใช่ กล่องแรกไหม
        tempPtr = *sPtr; // hold onto node being removed
        *sPtr = ( *sPtr )->nextPtr;
        (*sPtr)->prevPtr = NULL;// de-thread the node
        free( tempPtr ); // free the de-threaded node
        return value;
   } // end if

  //delete last node Error-2
   else if(value == ( *sPtr )->data && (*sPtr)->nextPtr ==NULL){
     (*sPtr) = NULL;
     tempPtr = NULL;
     free(*sPtr);
   }// end else if
   
   //other node
   else { 
      previousPtr = *sPtr;
      currentPtr = ( *sPtr )->nextPtr;

      // loop to find the correct location in the list
      while ( currentPtr != NULL && currentPtr->data != value ) { 
         previousPtr = currentPtr; // walk to ...  
         currentPtr = currentPtr->nextPtr; // ... next node  
      } // end while

      // delete node at currentPtr
      if ( currentPtr != NULL ) { 
        //not last node and have other nodes
        if(currentPtr->nextPtr != NULL){
         tempPtr = currentPtr; //ชี้กล่องถูกใจ
         previousPtr->nextPtr = currentPtr->nextPtr; //ชี้กล่องถัดจากกล่องถูกใจ
         currentPtr->nextPtr->prevPtr = previousPtr;
         free( tempPtr );
        }
        //have last 2 nodes,delete last node
        else {
          tempPtr = currentPtr;
          previousPtr->nextPtr = NULL;
          free(tempPtr);
        }
         return value;
      } // end if

   }//end else
   return '\0';
} // end function delete

// return 1 if the list is empty, 0 otherwise
int isEmpty( LLPtr sPtr )
{ 
   return sPtr == NULL;
} // end function isEmpty

// print the list
void printList( LLPtr currentPtr )
{ 
   // if list is empty
   if ( isEmpty( currentPtr ) ) {
      puts( "List is empty.\n" );
   } // end if
   else { 
      puts( "The list is:" );

      // while not the end of the list
      while ( currentPtr != NULL ) { 
         printf( "%d --> ", currentPtr->data );
         currentPtr = currentPtr->nextPtr;   
      } // end while

      puts( "NULL\n" );
   } // end else
} // end function printList

// Reverse print list
void printListR( LLPtr currentPtr )
{ 
   // if list is empty
   if ( isEmpty( currentPtr ) ) {
      puts( "List is empty.\n" );
   } // end if
   else { 
      puts( "The list is:" );

      // while not the end of the list
      printf("NULL ");
      while(currentPtr->nextPtr !=NULL){
        currentPtr = currentPtr->nextPtr;
      }
      while (currentPtr!= NULL ) { 
         printf( "--> %d  ", currentPtr->data );
         currentPtr = currentPtr->prevPtr;   
      } // end while
      puts("\n");

   } // end else
} // end function printListR