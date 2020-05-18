//Sean Droke
//Monday April 15, 2019
//CIS 3207
//Project 4A

/*
    tableEntry Struct

    name -- Character string of the associated name of the file/directory
    start -- The first block allocated for this file or directory
    size -- The size of the file or the directory
         -- Directory calculated by total size of files within
    type -- Character of either F for file or D for directory
*/

typedef struct {
    char name[36];
    int start;
    int size;
    char type;
} tableEntry;

/*

*/

typedef union {
    char file[512];
    tableEntry directory[512/sizeof(tableEntry)];
} fullBlock;



/*
    FAT Struct

    HashTable main -- The primary data structure for managing the FAT system is
                      the hash table. The function of this is to effectively
                      allow for key value pairing between logical and virtual
                      address spaces.
*/

typedef struct {
    HashTable main[TotalBlocks];
} FAT;

/*
    HashTable Struct

    block -- Address of the block, will be an address for every block in system
    data -- Pointer to the data being mapped to the block
    occupied -- "Y" or "N" based on if the block is being used

*/

typedef struct {
    int block;
    int data;
    char occupied;
} HashTable;

/*
    DrectoryEntry Struct

    EntryName -- Name of the file or directory
    EntryExtension -- Extension if is a file
    EntryType -- 'F' for folder or 'd' for directory
    FirstBlock -- Location of the first block of the data sequence
    BlockOffset -- This blocks offset with respect to current sequence position
    FileSize -- Total file size for the data, reference variable
    CreationDate -- File creation date and time
    ModificationDate -- Modification date and time
*/

typedef struct {
    char EntryName[NameSize];
    char EntryExtension[ExtensionSize];
    char EntryType;
    int FirstBlock;
    int BlockOffset;
    int FileSize;
    char CreationDate[STDT];
    char ModificationDate[STDT];
} DirectoryEntry;

/*
    Block Struct

    DataStored -- The data stored within this block
    NextBlock -- Location of the next block within the FAT
*/

typedef struct {
    char DataStored[BlockSize];
    int NextBlock;
} Block;

/*
    DirectoryList Struct

    BinaryTree Listing -- Directory listing organized using a binary tree, each
                          node of the tree will be a DirectoryEntry struct.              
*/

typedef struct {
    BinaryTree Listing;
} DirectoryList;

/*
    BootSector Struct

    BlockSize -- Standard size of a block
    TotalBlocks -- Total number of blocks on the drive
    UsedBlocks -- Total number of used or occupied blocks on the drive
    DirectoryCount -- Total number of working directories on the drive
    NameSize -- Maximum size of a file or directory name
    ExtensionSize -- Maximum size of the extension for a file
    DriveLetter -- Identifier for the virtual drive
*/

typedef struct {
    int BlockSize;
    int TotalBlocks;
    int UsedBlocks;
    int DirectoryCount;
    int NameSize;
    int ExtensionSize;
    char DriveLetter;
} BootSector;




/*
    MAIN FUNCTION

    DESCRIPTION:
        - Main function serves to open a shell prompt, initialize the file system and begin a loop for user input
          related to virtual file system manipulation.

    PARAMETERS: None

    RETURN VALUE: None
*/


int main(){
    //char* address = InitializeFileSystem(); -- Result of mmap function
    //InitializeBootSector();
    //InitializeFat(address);
    //InitializeRootDirectory();

    // opens myshell.c to use in navigating the disk 
    // while shell passes commands to this program
        // case statements
            // Case -- CreateFile()
            // Case -- Delete File()
            // Case -- Open File()
            // Case -- Close File()
    //End of while loop is end of program

}



/*
    INITIALIZEFILESYSTEM FUNCTION

    DESCRIPTION:
        - This function serves to initialize the file system in the directory the program is called from
    
    PARAMETERS: None

    RETURN VALUE: File system is created as a result, address value returned
*/

void InitializeFileSystem(){
    //Open the file we intend to use as the virtual disk
        //If this fails then we exit
        //Else we continue
    //Assign a variable to be the result of the mmap() system call on our file
        //If this fails we must exit again
        //Else continue
    //Close the file we just created
    //Return the resultant value in the variable assigned to mmap()
}


/*
    INITIALIZEBOOTSECTOR FUNCTION

    DESCRIPTION:
        - This function serves to initialize the boot sector structure within the virtual file system.
    
    PARAMETERS: None

    RETURN: Created boot sector struct
*/

BootSector InitializeBootSector() {
    // Set default values for the boot sector struct
        //Default numerical values given in instructions
        //Occupied directories should be 0
    //Boot Sector will be used as a reference for the virtual disk
}



/*
    INITIALIZEFAT FUNCTION

    DESCRIPTION:
        - This function serves to initialize the FAT
    
    PARAMETERS: Address, returned from disk initiailization

    RETURN: Created FAT
*/

FAT InitializeFAT(address) {
    //Initialize the key/value pairing of the hash table
    //Use the address to traverse the disk and allocate the number of address spaces and blocks
        //While i < total number of blocks based on disk size
            //Initialize the FAT key and set the value to NULL
    //At End of While loop the full FAT should be created with the correct number of allocated blocks
}


/*
    INITIALIZEROOTDIRECTORY FUNCTION

    DESCRIPTION:
        - This function initializes the root directory within the file system
    
    PARAMETERS: None

    RETURN: Initialized root directory, and the directory list
*/

void InitializeRootDirectory() {
    //entry = CreateDirectoryEntry(root) -- Store a directory entry into a temp variable
    //Initialize a global root directory struct to point to this entry
    //InitializeDirectoryList();
}


/*
    CREATEDIRECTORYENTRY FUNCTION

    DESCRIPTION:
        - This function is used to create a directory entry for the file system
    
    PARAMETERS: Type of directory (i.e. root), name, extension... everything listed in struct.

    RETURN: New directory entry
*/

void CreateDirectoryEntry(PARAMETERS) {
    //If root is passed to the function we initialize all of the entries elements to that of the root directory
    //Else we build the directory entry using the parameters passed in
    //This can only happen if we confirm that the file size can fit based on information in the boot sector
    //If the entry requires more than the maximimum bytes to a block we must determine that here
    //AppendFAT(DirectoryEntry); -- Append item to the FAT
    //Recursively call back to this function with a new set of parameters for the next additional block
}



/*
    APPENDFAT FUNCTION

    DESCRIPTION:
        - This function will append an element to the FAT

    PARAMETERS: Pointer to the data we wish to append to the FAT

    RETURN: Item is appended to the FAT
*/

void appendFAT(DirectoryEntry){
    //Complete a search of the hash table to uncover a useable block
    //Assign that particular address to hold the entry passed in
    //Update the boot sector to reflect the number of used blocks
    //AppendDirectoryList(DirectoryEntry); -- Append item to the directory list tree
}



/*
    INITIALIZEDIRECTORYLIST FUNCTION

    DESCRIPTION:
        - This function serves to initialize the directory list that is saved in the file system
    
    PARAMETERS: None

    RETURN: Initialized directory listing
*/

DirectoryList InitializeDirectoryList() {
    //Create the foundation of the binary tree with a single NUll node as the root node
    //This is a global structure
}



/*
    APPENDDIRECTORYLIST FUNCTION

    DESCRIPTION:
        - This function appends a directory item to the direcotry list

    PARAMETERS: A Directory Entry

    RETURN: Item is appended to the directory list
*/

void AppendDirectoryList(DirectoryEntry){
    //Complete a Depth First Search to determine where the item belongs within the tree
    //Place the Directory Entry into the tree by pointer reference
    //Update the boot sector to reflect the number of directories
}



/*
    CREATEFILE FUNCTION

    DESCRIPTION:
        - This function will create a file into the disk

    PARAMETERS: None

    RETURN: File created
*/

void CreateFile(){
    //First we attempt to call on createdirectoryentry() to determine if space exists to allocate the new file
    //If so we can continue
    //We then prompt the user to enter name and extension of the file
    //Then the file is opened, it is marked with a creation and modification date
    //The file is open for editing
}



/*
    DELETEFILE FUNCTION

    DESCRIPTION:
        - This function will delete a file from the disk

    PARAMETERS: None

    RETURN: File is removed from the system
*/

void DeleteFile(){
    //First we prompt the user to enter the file name they wish to delete from the system
    //If this file exists we proceed with the deletion
    //DeleteDirectoryList(FileName); -- Delete from the FAT -- Will trigger deletion from the remaining systems
    //Function will return given the file is deleted
}



/*
    DELETEDIRECTORYLIST FUNCTION

    DESCRIPTION:
        - Removal from the Directory Listing

    PARAMETERS: FileName

    RETURN: Item removed from the directory list

*/

void DeleteDirectoryList(FileName){
    //Complete a depth first search to find the file by name
    //When found
        //deleteFAT(FoundEntry)
    //Remove the FoundEntry from the directory listing and replace the node with a NULL value
}



/*
    DELETEFAT FUNCTION

    DESCRIPTION:
        - Removal from the FAT

    PARAMETERS: FoundEntry from the Directory Listing

    RETURN: Item removed from the FAT
*/

void DeleteFAT(FoundEntry){
    //Using the informaton provided from FoundEntry find all associated blocks in the file table
    //Reset these blocks to being unoccupied and remove their reference to data
    //Subtract space from used blocks in the boot sector
    //Remove the data from the virtual disk
}

/*
    OPENFILE FUNCTION

    DESCRIPTION:
        - Open files from the disk

    PARAMETERS: None

    RETURN: Opened file
*/

void OpenFile(){
    //Prompt the user for which file they wish to open
    //If the file exists continue else ask again
    //DirectoryListBuild(FileName)
}



/*
    DIRECTORYLISTBUILD FUNCTION

    DESCRIPTION:
        - Open files based on file name

    PARAMETERS: FileName

    RETURN: Forward to function that can rebuild and open files

*/

void DirectoryListBuild(FileName){
    //Traverse the directory list tree for the FileName provided
    //If found continue otherwise ask again
    //FATBuild(FoundEvent) -- Send the found event to the FAT processor to rebuild the file
}


/*
    FATBUILD FUNCTION

    DESCRIPTION:
        - This function utilizes the FAT to rebuild files based on their being found in the directory list

    PARAMETERS: FoundEvent, what is found in the directory list

    RETURN: Built file
*/

FILE FATBuild(FoundEvent){
    //Complete a search to find all of the blocks that represent a particular file
    //Append all of these to a temporary file and prepare to return them
    //Compile the file and return to open
}



/*
    CLOSEFILE FUNCTION

    DESCRIPTION:
        - Function to close the file

    PARAMETERS: None

    RETURN: File is closed
*/

void CloseFile(){
    //Closing the file only requires ensuring that the data within the file can be saved to the disk
    //Request from the boot sector if this is possible
    //If needed call on appending to the FAT to create more blocks for the data
    //Change the modification date
    //Save the file to disk and relaunch the shell prompt
}















