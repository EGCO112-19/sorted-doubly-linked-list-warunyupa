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
      //ข้อมูลใหม่มีค่ามากกว่า ข้อมูลที่มีอยู่เดิม   
      while ( currentPtr != NULL && value > currentPtr->data ) {
         previousPtr = currentPtr; // walk to ...               
         currentPtr = currentPtr->nextPtr; // ... next node 
      } // end while                                         

      // insert new node at beginning of list --> ข้อมูลใหม่มีค่าน้อยกว่าข้อมูลเดิมทั้งหมด
      if ( previousPtr == NULL ) {
         newPtr->nextPtr = *sPtr;   //ให้ nextPtr ชี้กล่องแรกของข้อมูลเดิม 
         *sPtr = newPtr; //เปลี่ยนที่ชี้ให้กับ *sPtr มาชี้ที่กล่องใหม่ สีแดง
         currentPtr = newPtr; //สีเหลือง
      } // end if
      else { // insert new node between previousPtr and currentPtr
        /*สถานนะ pointer:
          currentPtr ชี้กล่องถัดไป ที่กำลังจะโดนแทรกข้างหน้า
          previousPtr ชี้กล่องแรกของข้อมูลเดิม
        */
         previousPtr->nextPtr = newPtr; //previousPtr ส่วนที่เป็น nextPtr เปลี่ยนมาชี้ newPtr สีเขียว
         newPtr->prevPtr = previousPtr; //สีเหลือง
         newPtr->nextPtr = currentPtr; //สีเขียว
         currentPtr = newPtr; //สีเหลือง
         
         
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
        *sPtr = ( *sPtr )->nextPtr; // de-thread the node
        free( tempPtr ); // free the de-threaded node
        (*sPtr)->prevPtr = NULL;
        return value;
   } // end if
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
         tempPtr = currentPtr; //ชี้กล่องถูกใจ
          if(currentPtr->nextPtr !=NULL){
            previousPtr->nextPtr = currentPtr->nextPtr; //ชี้กล่องถัดจากกล่องถูกใจ
            currentPtr->nextPtr->prevPtr = previousPtr;
            free( tempPtr );
          }
          else {//กรณีเหลือ 2 กล่องสุดท้าย<-->if(currentPtr->next == NULL)
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