#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#define true 1
#define false 0

//memsim <tracefile> <nFrames> <vms|lru|clk|opt> <debug|quiet>

// Page #, Valid Bit, Dirty Bit(kicked out), double lastUsed, int reference / cleaned(Read in), frame #[user can choose # of frames in args], last used (Clock.getime), use (reference bit for CLK)  

//************************************************
//// Page Table Layout
//// _____________________________________________
//// | Column 0 | Column 1 | Column 2 | Column 3 |
//// ---------------------------------------------
//// | Valid bit| Dirty bit| Frame #  | Last Used|
//// ---------------------------------------------
//// Rows = Page #
//************************************************
// PageEntry struct is equivalent to a row on a page table entry
typedef struct PageEntry
{
	int validBit;
	int dirtyBit;
	int frameNumber;
	double lastUsed; //changed to double
	int reference;

} PageEntry;


typedef struct listNode
{
	// Create a doubly linked list, but NOT a doubly circular linked list
	struct listNode* prev; 
	struct listNode* next;
	int pageNumber;
	// Next node will always be null while building
	// Need to think of a way to kill it.
		// SOLUTION:
		// If size of linked list != nFrames, create next
		// ELSE if size of linked list == nFrames, find the one with next==NULL
} listNode;

typedef struct setList
{
	// A set is a list of things, with a size, in no particular order.
	int listSizeMax;
	int numElements;
	struct listNode* headNode;

} setList;


typedef int bool; // int bools 0, 1

const int lineSize = 64;

const int numEntries = 1048576; // 1048576 = 2^20 = [ 2^32( Hex Address ) / 2^12( pageSize ) ] = numEntries for page table
const int pageSize = 4096; // 2^12, given

// Supported Algorithms
void lru( FILE* inputFile, int numFrames, bool verbose);
void vms( FILE* inputFile, int numFrames, bool verbose );
void clk( FILE* inputFile, int numFrames, bool verbose);
void opt( FILE* inputFile, int numFrames, bool verbose );

// Support Functions
void initializeFrameTable(int* frameTable, int numFrames);
void evictPage2( PageEntry* pageTable, int pageIndex, int* frameTable, int frameIndex, int* numWrites );
void evictPage(PageEntry* pageTable, int pageIndex, int* frameTable, int frameIndex, int* numWrites  );
void loadPage( PageEntry* pageTable, int pageIndex, int* frameTable, int frameIndex, char readWrite, int* numReads );
void printFinalOutput( int numFrames, int numEvents, int numReads, int numWrites );
int insertNode( struct setList* list, int incomingPageNumber );
struct listNode* evictNode( struct setList* list, int outgoingPageIndex );
struct listNode* evictNode( struct setList* list, int outgoingPageIndex );
int FindLastDirty( int* dirtyList, int numFrames ); //VMS
int findMaxDistance( int* frameTable, int numFrames, int* frameTable_DEBUG ); //OPT
int findNextEmptyFrame(int* frameTable, int* numFrames); //LRU
int findLeastRecentPageFrame(PageEntry* pageTable, int* frameTable, int numFrames); //LRU
double getTime(); //LRU
int findUnusedPage(PageEntry* pageTable, int* frameTable, int numFrames, int* clockHand); //CLK
int findPageFrame(int* frameTable, int numFrames, int pageNumber); //CLK
int getNextDistance( FILE* file, int* distArray, int numFrames, int pageNumber ); // for OPT


// -- (1)+TraceFile (2)+#ofFrames (3)+Algorithm[ vms | lru | clk | opt ] (4)+[ debug | quiet ]
int main ( int argc, char* argv[ ] ) 
{
	assert( argc == 5 );
        char* traceFile = argv[ 1 ]; //holds trace file name
        int numFrames = atoi(argv[ 2 ]);
        char* algorithm = argv[ 3 ]; //vms, lru, clk, or opt
	bool verbose; //debug print OR quiet
	if( strcmp( "debug", argv[ 4 ] ) == 0 )
                verbose = 1;
        else if( strcmp( "quiet", argv[ 4 ] ) == 0 )
                        verbose = 0;
        else
	{ 
                perror( "Incorrect print method. Exiting." );
        	exit( EXIT_FAILURE );
        }

	FILE* file  = fopen( traceFile, "r" );
	assert( file != NULL );

	if( strcmp( "vms", algorithm ) == 0 )
		vms(file, numFrames, verbose); // Replace with function call: vms
	else if ( strcmp( "lru", algorithm ) == 0 )
		lru(file, numFrames, verbose);
        else if ( strcmp( "clk", algorithm ) == 0 )
                clk(file, numFrames, verbose); 
        else if ( strcmp( "opt", algorithm ) == 0 )
		opt( file, numFrames, verbose );	
	else
		printf("Invalid algorithm name, use [ vms | lru | clk | opt ]\n");
	
	fclose( file );	
	return 0;
}


void evictPage2(PageEntry* pageTable, int pageIndex, int* frameTable, int frameIndex, int* numWrites  )
{	
	PageEntry evictedPage = pageTable[ pageIndex ]; // Keep track of the pages location in memory
	if( evictedPage.dirtyBit == 1 )
	{
		++*numWrites; // Write to disk presumed
		evictedPage.dirtyBit = 0; // Clean dirtybit after "write" is performed
	}
	evictedPage.validBit = 0;
	//printf( "Evicted: %d\n", frameTable[ frameIndex ] );
	pageTable[ pageIndex ] = evictedPage;
	frameTable[ frameIndex ] = -1; //-1 means empty; CANNOT assign NULL to type int
	return;
}

void evictPage(PageEntry* pageTable, int pageIndex, int* frameTable, int frameIndex, int* numWrites  )
{	
	//printf("  In Evict:\tframeIndex: %d\tframeTable[frameIndex]: %d\n", frameIndex, frameTable[frameIndex]);
	//////PageEntry evictedPage = pageTable[ pageIndex ]; // Keep track of the pages location in memory
	int evictedPage = frameTable[ frameIndex ];
	//printf("  In Evict:\tevictedPage.dirtyBit == %d\n", pageTable[ evictedPage ].dirtyBit);
	if( pageTable[ evictedPage ].dirtyBit == 1 )
	{
		//printf("Dirty bit was 1\n");
		*numWrites = *numWrites + 1; // Write to disk presumed
		pageTable[ evictedPage ].dirtyBit = 0; // Clean dirtybit after "write" is performed
	}
	pageTable[ evictedPage ].validBit = 0;
	//printf( "Evicted: %d\n", frameTable[ frameIndex ] );
	//pageTable[ pageIndex ] = frameTable[ evictedPage ];
	frameTable[ frameIndex ] = -1; //-1 means empty; CANNOT assign NULL to type int
	return;
}


// Need to load into FRAME Table 
void loadPage( PageEntry* pageTable, int pageIndex, int* frameTable, int frameIndex, char readWrite, int* numReads ) //made readWrite type char*
{
	if ( frameTable[ frameIndex ] != -1 )
	{
		//printf( "Page was not properly evicted.\n" );
		return;
	}
	
	++*numReads; //loading from disk
	//event indicates a write, make dirty bit high in the page table
	//if( strcmp( "W", readWrite ) == 0 ){
	if (readWrite == 87){
		//printf("dirty bit set high in load");	
		pageTable[ pageIndex ].dirtyBit = 1;
	}
	//printf( "Loaded: %d, frame: %d\n", pageIndex, frameIndex );
	pageTable[ pageIndex ].validBit = 1;
	frameTable[ frameIndex ] = pageIndex; // Represents the storage of a page
	return;
}

void initializeFrameTable(int* frameTable, int numFrames)
{
	int i = 0;

	for(i = 0; i < numFrames; ++i)
	{
		frameTable[i] = -1;
	}
}

int findLeastRecentPageFrame(PageEntry* pageTable, int* frameTable, int numFrames){
//assume at least frame0 is occupied to find least recently used.
//smallest value timestamp --> least recent page access

	int candidatePageIndex = frameTable[ 0 ]; //use first page for comparing least recently used
	int candidateFrameIndex = 0;
	int nextPageIndex = 0;
	double smallestTime = pageTable[ candidatePageIndex ].lastUsed;

	int i = 0;
	for(i = 0; i < numFrames; ++i)
	{
		nextPageIndex = frameTable[ i ]; //get the page # it contains 
		if(smallestTime > pageTable[ nextPageIndex ].lastUsed && (pageTable[ nextPageIndex ].lastUsed) != 0) 
		{	//found less recent page
			smallestTime = pageTable[ nextPageIndex ].lastUsed;
			candidatePageIndex = nextPageIndex;
			candidateFrameIndex = i;
			//printf("Less recent page: %d, time: %f\n", nextPageIndex, smallestTime);
		}
	}
	//printf("Candidate Page: %d, time: %f, in frame: %d\n", candidatePageIndex, smallestTime, candidateFrameIndex);
	return candidateFrameIndex;
}

void printFinalOutput( int numFrames, int numEvents, int numReads, int numWrites )
{

	printf("total memory frames: %d\n", numFrames);
	printf("events in trace: %d\n", numEvents);
	printf("total disk reads: %d\n", numReads);
	printf("total disk writes: %d\n", numWrites);
}

void lru( FILE* inputFile, int numFrames, bool verbose )
{
	char line[ lineSize ];	//buffer for reading input from file
	// Trace Variables
	unsigned addr;
	char rw;
	int numEvents = 0, numReads = 0, numWrites = 0, numHits = 0, numMisses = 0;
	int nextFrame = -1; //indicates the next frame to hold a loaded page
	int pageNumber = 0;
	int candidatePageTimeStamp = 0; //holds the most recent accessed time for page to be evicted
	int candidatePageNumber = 0;
	
	//local tables
	PageEntry pageTable[ numEntries ];
	int frameTable[ numFrames ];
	initializeFrameTable(frameTable, numFrames);
	
	//gets the first event to compare for LRU
	fgets( line, lineSize, inputFile );
	sscanf(line, "%x %c", &addr, &rw);
	pageNumber = addr/pageSize; 
	pageTable[ pageNumber ].lastUsed = getTime(); 
	candidatePageTimeStamp = pageTable[ pageNumber ].lastUsed;
	candidatePageNumber = pageNumber;
	nextFrame = findNextEmptyFrame(frameTable, &numFrames);
	loadPage(pageTable, pageNumber, frameTable, nextFrame, rw ,&numWrites);	
	++numMisses;
	++numEvents;
	//printf("Page number %d lastused: %f\n", pageNumber, pageTable[ pageNumber ].lastUsed);
		
	//continue the rest of the trace file
	while( fgets( line, lineSize, inputFile ) != NULL )
	{    
		sscanf(line, "%x %c", &addr, &rw);
		//printf("%x, char: %c\n", addr, rw);
		//puts(line);
		pageNumber = addr/pageSize; 
		//printf("Addr:%d, pageSize:%d, pageNumber(Addr/Size):%d\n", addr, pageSize, pageNumber);
		
		if(pageTable[ pageNumber ].validBit == 1)
		{ //valid bit is 1, HIT in memory
			pageTable[ pageNumber ].lastUsed = getTime(); //save timestamp to the page last recently used
			++numHits;
		}
		else{
			++numMisses; //valid bit 0, MISS
			nextFrame = findNextEmptyFrame(frameTable, &numFrames);
			if(nextFrame != -1) //frame is not occupied
			{	//no eviction; load new page into frame	
				//printf("No Eviction!\n");
				loadPage(pageTable, pageNumber, frameTable, nextFrame, rw, &numReads);
				pageTable[ pageNumber ].lastUsed = getTime();
			} else {
			//need to evict a page for loading new page

				nextFrame = findLeastRecentPageFrame(pageTable, frameTable, numFrames);
				candidatePageNumber = frameTable[ nextFrame ] ;
				//printf("Need to evict page (%d), in frame %d\n", candidatePageNumber, nextFrame);
				//evict old page and load new page
				evictPage2(pageTable, candidatePageNumber, frameTable, nextFrame, &numWrites);
				loadPage(pageTable, pageNumber, frameTable, nextFrame, rw, &numReads);
				
				pageTable[ pageNumber ].lastUsed = getTime(); //update timestamp
			}
		}
		numEvents += 1;
	}
	//print results
	//printf("Hits: %d, Missess: %d\n", numHits, numMisses);
	printFinalOutput( numFrames, numEvents, numReads, numWrites);
		
}

void clk( FILE* inputFile, int numFrames, bool verbose)
{
	char line[ lineSize ];	//buffer for reading input from file

	// Trace Variables
	unsigned addr;
	char rw;
	int numEvents = 0, numReads = 0,  numWrites = 0,  numHits = 0,  numMisses = 0;
	
	int nextFrame = 0; //indicates the next frame to hold a loaded page
	int pageNumber = 0;
	int candidatePageNumber = 0;
	int clockHand = 0;  //provides index to specific row in page table, start at arbtrary number
	
	//local tables
	PageEntry pageTable[ numEntries ];
	int frameTable[ numFrames ];
	initializeFrameTable( frameTable, numFrames); 

	while( fgets( line, lineSize, inputFile ) != NULL )
	{    
		sscanf(line, "%x %c", &addr, &rw);
		//printf("%x, char: %c\n", addr, rw);
		//puts(line);
		pageNumber = addr/pageSize;
		//printf("Addr:%d, pageSize:%d, pageNumber(Addr/Size):%d\n", addr, pageSize, pageNumber);
		
		if(pageTable[ pageNumber ].validBit == 1)
		{ 
			++numHits; //in memory, HIT
			pageTable[ pageNumber ].reference = 1; //update reference bit
		}
		else{
			++numMisses; //valid bit 0, MISS
			nextFrame = findNextEmptyFrame(frameTable, &numFrames);
			if(nextFrame != -1) 
			{	//frame is not occupied
				//no eviction; load new page into this empty frame	
				//printf("No Eviction!\n");
				loadPage(pageTable, pageNumber, frameTable, nextFrame, rw, &numReads);
				pageTable[ pageNumber ].reference = 1; //set reference bit high
			} else {
				//need to evict a page from Frame for loading new page
				candidatePageNumber = findUnusedPage(pageTable, frameTable, numFrames, &clockHand); //find a good candidate for replacing
				nextFrame = findPageFrame(frameTable, numFrames, candidatePageNumber); //find the frame it belongs to
				//printf("Need to evict page (%d), in frame %d, clockhand %d\n", candidatePageNumber, nextFrame, clockHand);
				//evict old page and load new page
				evictPage2(pageTable, candidatePageNumber, frameTable, nextFrame, &numWrites);
				loadPage(pageTable, pageNumber, frameTable, nextFrame, rw, &numReads);
				
				pageTable[ pageNumber ].reference = 1; //set reference bit
			}
		}
		
		numEvents += 1;
	}
	//printf("Hits: %d, Missess: %d\n", numHits, numMisses);
	//void printFinalOutput( int numFrames, int numEvents, int numReads, int numWrites )
	printFinalOutput( numFrames, numEvents, numReads, numWrites);
		
}

// Page Table, Frame Table, numFrames(optional, really, since sizeof()), , file
void opt( FILE* inputFile, int numFrames, bool verbose )
{
	int distTracker[ numFrames ]; // Tracks distance until next page occurence of same type for page value in the frame.

	//printf("Entering OPT!\n");
	// Trace Variables
	unsigned addr;
	char rw;

	struct PageEntry pageTable[ numEntries ];
	int initializer = 0;
	for( initializer = 0; initializer < numFrames; ++initializer)
		distTracker[ initializer ] = -1;
	
	int frameTable[ numFrames ]; // index is frameNumber, contains currently loaded page#, else NULL
 
	int numEvents = 0, numReads = 0, numWrites = 0, nHits = 0, nMisses = 0;
	char line[ lineSize ];

	//printf("Pre-While Loop (%d)\n", inputFile);
	while( fgets( line, lineSize, inputFile ) != NULL )
	{
		// Read next event   
		++numEvents; 
		//printf("%d\n", numEvents);
		sscanf(line, "%x %c", &addr, &rw);
		//printf("%x, char: %c\n", addr, rw);
		//puts(line);
		// After reading the next event,
		//  always decrement previous distances until next same-page event, for each page number in a frame.
		//  If distance becomes 0, update distance to next value.
		int t = 0;
		for( t = 0; t < numFrames; ++t )
		{
			if( distTracker[ t ] > 0 )
				--distTracker[ t ];
			else if( distTracker[ t ] == 0 )
				distTracker[ t ] = getNextDistance( inputFile, distTracker, numFrames, distTracker[ t ] ); // had &distTracker	
		}

	
		int pageNumber = addr/pageSize; // Calculate which page was just read
		//printf("Addr:%d, pageSize:%d, pageNumber(Addr/Size):%d\n", addr, pageSize, pageNumber);
	
		// Check the valid bit of the page: 0 = is not loaded, 1 is loaded in frames.
		if (pageTable[ pageNumber ].validBit == 0)
		{

			//printf("******************************\n");
			// Evict the old page
			int replaceIndex = findMaxDistance( distTracker, numFrames, frameTable );
			int debug_oldPageValue = frameTable[ replaceIndex ];
			//printf("Old:%d(%d)\n", frameTable[ replaceIndex ], distTracker[ replaceIndex ]);
			//printf("replace index: %\d\n", replaceIndex);
			evictPage( pageTable, pageNumber, frameTable, replaceIndex, &numWrites );
			
			// Load the new page
			loadPage( pageTable, pageNumber, frameTable, replaceIndex, rw, &numReads );
			// Calculate distance until next occurence for new page number (it will be decremented per new input)
			distTracker[ replaceIndex ] = getNextDistance( inputFile, distTracker, numFrames, pageNumber ) ; // had &distTracker
			//printf("New:%d(%d)\n", frameTable[ replaceIndex ], distTracker[ replaceIndex ]);

			//printf( "DEBUG: \tOld Page Number: %d\n\tIncoming Page Number:%d\n", debug_oldPageValue, pageNumber );
			//printf("********************************\n");
			++nMisses;
		} else{
			//valid is 1 
			++nHits;
		}

	}
	//printf("Hits: %d, Missess: %d\n", nHits, nMisses);
	//void printFinalOutput( int numFrames, int numEvents, int numReads, int numWrites )
	printFinalOutput( numFrames, numEvents, numReads, numWrites);

   
}


// Used by OPT to finds the distance between a page and its next reference
int getNextDistance( FILE* file, int* distArray, int numFrames, int pageNumber )
{
	int readDistance = 0; // return value
	char line[ lineSize ];
	int addr;
	char rw;
	while( fgets( line, lineSize, file ) != NULL )
	{
		//if( readDistance == 234 )
		//	exit(EXIT_FAILURE);
		//++readDistance;
		sscanf( line, "%x %c", &addr, &rw );
		++readDistance;
		int futurePageNumber = addr / pageSize;
		//printf("Read Distance: %d\t Desired Page: %d\t Current Page: %d(%d/%d)\n", readDistance, pageNumber, futurePageNumber, addr, pageSize );
		if( pageNumber == futurePageNumber )
			break;
		// It DOES start by reading the next line... so 1055->(81758 is read here)
		/////printf("futurePageNumber %d\n", futurePageNumber);
		////exit( EXIT_FAILURE );
	}
	int lineSize = 11;
	fseek( file, ( -1 * lineSize ) * readDistance, SEEK_CUR );
	//printf("Returning! (%d)\n", readDistance);
	return readDistance;
}

int findUnusedPage(PageEntry* pageTable, int* frameTable, int numFrames, int* clockHand) //CLK function
{
	PageEntry candidatePage;
	//printf("findUnusedPage, clock %d\n", *clockHand);
	PageEntry this;
	
	while(1)
	{
		if(*clockHand == numFrames)
		{
			//printf("Resetting clockhand: %d\n", *clockHand);
			*clockHand = 0;
			//printf("Clockhand reset %d\n", *clockHand);
		}
		candidatePage = pageTable[ frameTable [ *clockHand ] ];
		
		//printf("Candidate Page #: %d\n", *clockHand);
		if(candidatePage.reference == 0){
			//printf("page %d found for eviction\n", *clockHand);
			this = pageTable[ frameTable[ *clockHand] ];		
			//printf("valid bit %d, reference bit %d\n", this.validBit, this.reference);
			candidatePage.reference = 1;
			*clockHand = *clockHand;
			return frameTable[*clockHand];
		} else {
			if(candidatePage.reference == 1){
				//printf("setting %d back to 0, clockhand %d\n", *clockHand, *clockHand);
				pageTable[ frameTable[ *clockHand ]].reference = 0;
			}
		}
		++*clockHand;
	}
}


//findFrame number given pageNumber
int findPageFrame(int* frameTable, int numFrames, int pageNumber)
{
	int i =0;
	//printf("findPageFrame: %d\n", pageNumber);
	
	
	for(i = 0; i<numFrames; ++i)
	{	//printf("Frame %d page %d\n", i, frameTable[i]);
		if(frameTable[i] == pageNumber)
		{
			//printf("found frame %d\n", i);
			return i;
		}
	}
	//printf("COULD NOT FIND FRAME, PAGE %d\n", pageNumber);
	return -1;
}

// Used by OPT to find the largest distance for replacement
int findMaxDistance( int* distArray, int numFrames, int* frameArray_DEBUG )
{
	int maxPosition = 0;
	int i = 0;
	for( i = 0; i < numFrames; ++i )
	{
		if( distArray[ i ] == -1 )
		{
			maxPosition = i;
			//printf("*************************\n");
			break;
		}
		//printf( "%d\n" ,frameTable[ i ]);
		else if( distArray[ i ] > distArray[ maxPosition ] )
			maxPosition = i;
	}

	//printf("**********************************\n");
	//for( i = 0; i < numFrames; ++i )
	//{
	//	printf("frame# %d] (%d)\t Distance: %d\n", i, frameArray_DEBUG[ i ], distArray [ i ] );
	//}
	//printf("**********************************\n");
	//printf("Returning Max Distance: %d, distance array position: %d\n", distArray[ maxPosition ], maxPosition );
	return maxPosition;
}


int findNextEmptyFrame(int* frameTable, int* numFrames)
{	//return -1 if no page was found
	int nextFrameAvailable =-1; //assume we don't find anything (return negative for error)
	
	int i =0;
	for(i = 0; i < *numFrames; ++i){
		if (frameTable[i] == -1) //frame (physical memory page frame) is not occupied
		{
			//printf("found empty frame: %d\n", i);
			return i; //return the next empty frame index	
		}
	}
	//all frames are occupied, return -1 for full
	//printf("no frame found %d\n", nextFrameAvailable);
	return nextFrameAvailable;
}


void vms( FILE* inputFile, int numFrames, bool verbose )
{
	struct PageEntry pageTable [ numEntries ];
	struct setList cleanList, dirtyList;
	cleanList.listSizeMax = numFrames;
	dirtyList.listSizeMax = numFrames;
	cleanList.headNode = malloc( sizeof( struct listNode ) );
	dirtyList.headNode = malloc( sizeof( struct listNode ) );	
	cleanList.numElements = 1;
	dirtyList.numElements = 1;

	unsigned addr;
	char rw;
	char line[ lineSize ];

	int numEvents = 0, numReads = 0, numWrites = 0, nHits = 0, nMisses = 0;

	while( fgets( line, lineSize, inputFile ) != NULL )
        {

		// Print everything in each list____DEBUG
		int k = 0;
		struct listNode* ptr = cleanList.headNode;
		printf("*********************************\n");
		printf("cleanList.numElements(%d)\n", cleanList.numElements);
		for(k = 0; k < cleanList.numElements; ++k)
		{
//			printf("k(%d)\tpage(%d)\n", k, ptr->pageNumber);
//
		}

		printf("********************************\n");


		printFinalOutput( numFrames, numEvents, numReads, numWrites );	
		++numEvents;
		sscanf(line, "%x %c", &addr, &rw);
		
		/* When you open a text file that is blank, type in "abcd" and DO NOT SAVE, then read that same file within the same process
 		* it is considered A HIT. The reason is because the read will read the DIRTY version in memory. But then why is it that you open
 		* another copy of the text file and it is blank? Not having "abcd" in it? It's because it is a SEPARATE PROCESS with its own
 		* allocated frames / pages etc. So the second process will read a clean version. Also remember that infinite reads may be performed
 		* but only one process may have write privileges (normal circumstances).*/

		printf("While Start\n");

		int pageNumber = addr / pageSize;
		// If valid, already in one of the two tables.
		if( pageTable[ pageNumber ].validBit == 1 )
		{
			printf("Valid bit found\n");
			++nHits;
			if( rw == 87 ) // 87 is "W" 
			{	
				// WRITE ONLY CARES ABOUT PULLING FROM CLEAN WHEN VALID
				// If pageNumber is in clean, extract and etc.
				// Else if it is not, do nothing.
				printf("---------------pre-findNode\n");
				int evictPageIndex = findNode( &cleanList, pageNumber );
				if( evictPageIndex != -9 ) // If != -9, then the pageNumber was returned
				{
					// Page value was found
					  // Evict it (returned) and move it to Dirty List
					struct listNode* evictedNode = evictNode( &cleanList, evictPageIndex );
					if( dirtyList.numElements < dirtyList.listSizeMax ) // Dirty List is not yet full
					{
						insertNode( &dirtyList, evictedNode->pageNumber ); // insert the node, creating a new ptr, into the dirty list
						pageTable[ pageNumber ].dirtyBit = 1;	// set that corresponding page value to high
						free( evictedNode );			// free the old reference ptr			
					}
					else // dirtyList is full, need to evict from the dirtyList into clean, causing a write to happen.
					{
					//******** For the EVICTED DIRTY NODE
						++numWrites; // Because we are kicking out the last page in the dirtyList to clean.
						// Evict the last page in the dirtyList, need to move it to clean
						struct listNode* dirtyEvictTemp = evictNode( &dirtyList, ( dirtyList.listSizeMax - 1 ) );
						
						// dirtyEvictTemp needs to be in clean list, check clean list availability
						if ( cleanList.numElements < cleanList.listSizeMax ) // Clean list is not yet full
						{
							insertNode( &cleanList, dirtyEvictTemp->pageNumber ); // Insert it, creating a new ptr, into the clean list
							pageTable[ dirtyEvictTemp->pageNumber ].dirtyBit = 0; 	     // set the dirtyBit low 
							free( dirtyEvictTemp );					// Free the old reference ptr.
						}
						else // Clean list is full, eviction needed
						{
							struct listNode* discardNode = evictNode( &cleanList, ( cleanList.listSizeMax - 1 ) ); // Find the last clean node
							pageTable[ discardNode->pageNumber ].validBit = 0; // Boot last clean node out of memory officialy
							free( discardNode ); // Free the memory of the useless kicked clean node.
							insertNode( &cleanList, dirtyEvictTemp->pageNumber ); // Insert it, creating a new ptr, into the clean list
							pageTable [ dirtyEvictTemp->pageNumber ].dirtyBit = 0; // set the dirty bit low
							free( dirtyEvictTemp ); // Free the old reference ptr
						}
						// NOW, insert the pageNumber into dirtylist, with the old dirtyNode kicked out and placed into clean
						insertNode( &dirtyList, evictedNode->pageNumber ); // The value that was plucked from clean into dirty with a "W"
						pageTable[ evictedNode->pageNumber ].dirtyBit = 1; // in dirty, so set to high
						free( evictedNode ); // Insert created a new node, delete the old reference.
					//**********
					}	
						
				} // else // evictPageIndex == -9 (not in clean list,
					// so it must be in dirty list since validBit == 1 )
				 	// { Do nothing, "W" in a hit on dirtyList will do nothing. }
			}
			// else // rw != 87, then rw=82, or "R"
			  // Do nothing, "R" in a hit will do nothing regardless of it being in clean or dirty.	
		}
		else if( pageTable[ pageNumber ].validBit == 0 ) // Not in either tables, need to evict.
		{
			if(numEvents == 4)
			{
				printf("Shits gonna happen\n");
			}
			printf("Valid bit not found\n");
			++nMisses; // because valid bit == 0, we missed.
			++numReads; // Because it was not in memory before, we must load it.
			if( rw == 87 ) // 87 is "W"
			{
				//  Loading a "W" Always goes to dirty, need to check dirtyList size or boot a dirty into clean. 
					// if evict a dirty, booting a clean, must clean evicted dirty.
				if( dirtyList.numElements < dirtyList.listSizeMax ) // Dirty list is not full
				{
					insertNode( &dirtyList,	pageNumber ); // Insert the page number into the dirtyList, creating a node.
					pageTable[ pageNumber ].dirtyBit = 1;
					pageTable[ pageNumber ].validBit = 1;
				}
				else // dirtyList is full
				{
					// Need to evict last page in dirty and insert to clean
					struct listNode* dirtyEvictTemp = evictNode( &dirtyList, ( dirtyList.listSizeMax - 1 ) );
					// Check if clean list is not full
					if( cleanList.numElements < cleanList.listSizeMax ) // cleanList is not full, no eviction
					{
						insertNode( &cleanList, dirtyEvictTemp->pageNumber );
						pageTable[ dirtyEvictTemp->pageNumber ].dirtyBit = 0;
						free( dirtyEvictTemp );
					}
					else // clean list is full, need to evict.
					{
						struct listNode* discardNode = evictNode( &cleanList, ( cleanList.listSizeMax - 1 ) ); // find the last clean node
						pageTable[ discardNode->pageNumber ].validBit = 0; // Boot last clean node out of memory officially
						free( discardNode );
						insertNode( &cleanList, dirtyEvictTemp->pageNumber );
						pageTable[ dirtyEvictTemp->pageNumber ].dirtyBit = 0;
						free( discardNode ); // Delete old reference.
					}
				}
				// Now that space is available in dirty, load pageNumber into dirty "W"
				insertNode( &dirtyList, pageNumber ); // Create and insert new
				pageTable[ pageNumber ].validBit = 1;
				pageTable[ pageNumber ].dirtyBit = 1; 
			}
			else if(rw == 82) // 82 is "R"
			{
				if( !( cleanList.numElements < cleanList.listSizeMax ) ) // Clean list is full, need to evict
				{
					struct listNode* discardNode = evictNode( &cleanList, ( cleanList.listSizeMax - 1 ) ); // find the last clean node
					pageTable[ discardNode->pageNumber ].validBit = 0;
					free( discardNode );
				}
				insertNode( &cleanList, pageNumber ); // Create new reference, load it to cleanList
                                pageTable[ pageNumber ].validBit = 1;
			}	
		}
	printf("End While(not reached)\n");
	}	
	return;
}



struct listNode* evictNode( struct setList* list, int outgoingPageIndex )
{
	printf("Evict Node Start\n");
	// Strictly evict
	// Assumed outgoingPageIndex is correct and found via search.
	struct listNode* ptr = list->headNode;
	int i = 0;
	printf("OutgoingPageIndex(%d)\n", outgoingPageIndex);
	for( i = 0; i < outgoingPageIndex - 1; ++i ) // Stops when it reaches the outgoingPageIndex
	{
		printf("i:%d\n", i);
		ptr = ptr->next;
	}			
	printf("Post-forloop\n");
	ptr->prev->next = NULL;
	ptr->prev = NULL;

	--list->numElements;
	printf("Evict Node Exit\n");
	return ptr;
}




 
int insertNode( struct setList* list, int incomingPageNumber )
{
	printf("Insert Node Start\n");
	// Insert the node and if size > maxSize, evict last node
	struct listNode* newNode = malloc( sizeof( struct listNode ) );
	struct listNode* tmp = list->headNode; // Store &address of old head
	tmp->prev = newNode;	// SEGFAULT	       // Make old head->prev set to new head
	list->headNode = newNode;	       // Make newNode new head
	list->headNode->next = tmp; 	       // Assign new head->next to old head
	++list->numElements;		       // Increment Number of Elements
	if( list->numElements >= list->listSizeMax )
		printf( "List has exceeded size, should not happen\n" );
	printf("Insert Node Exit\n");
	return list->numElements;
}

// Valid bit tells us a page exists in one of the two lists, however:
 // findNode will search for that page in a particular list.
 // If it is found, it will return the "list index", or how many nodes deep it is.
 // if it is not found, it will return -9
int findNode( struct setList* list, int pageNumber )
{
	printf("---+-----------------Find Node Start\n");
	struct listNode* ptr = list->headNode;
	int counter = 0;
	while ( ( ptr != NULL ) && ( counter < list->listSizeMax ) )
	{
		if( ptr->pageNumber == pageNumber )
			return counter;
		ptr = ptr->next;
		++counter;
	}
	return -9; // ptr->next is NULL or search exceeded max list Size
}




double getTime()
{
    struct timespec t;
    int result = clock_gettime(CLOCK_REALTIME, &t);
    assert(result == 0);
    return (double)t.tv_sec + (double)t.tv_nsec/ 1000000000L; //convert tv_nsec to seconds
}


