#include "sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <time.h>

#define _DEBUG_
#define NPRINT 50
#define INROW 10

typedef void ( *pFUN )( int*, int );

int* CreateTab( int );
void InitTab( int*, int );
void PrintTab( int*, int );
void DeleteTab( int** );

int main( int argc, char* argv[] )
{
    if( argc != 2 )
    {
        printf( "Usage: %s <wielkosc tablicy>\n", argv[0] );
        return 1;
    }

    int nSize = atoi( argv[1] );

    int* pTab = CreateTab( nSize );
    if( !pTab )
    {
        perror( "ERROR: Nie przydzielono pamieci dla tablicy nieposortowanej!\n" );
        return 2;
    }
    InitTab( pTab, nSize );
#ifdef _DEBUG_
    printf( "Tablica wejsciowa:\n" );
    PrintTab( pTab, ( nSize > NPRINT ) ? NPRINT : nSize );
#endif
   
    const char* pTabNames[] = { "InsertionSort", "SelectionSort", "BubbleSort", "MixedSort", "HalfInsertSort", "HeapSort_rosnaco", "HeapSort_malejaco", "QuickSort" };
    
    pFUN pSortTab[] = { InsertionSort, SelectionSort, BubbleSort, MixedSort, HalfInsertSort, HeapSort_rosnaco, HeapSort_malejaco, QuickSort };
    int nFun = sizeof( pSortTab ) / sizeof( pFUN );

    int* pTabSort = CreateTab( nSize );
    if( !pTabSort )
    {
        perror( "ERROR: Nie przydzielono pamieci dla tablicy posortowanej!\n" );
        return 3;
    }

    for( int i = 0; i < nFun; i++ )
    {
        memcpy( pTabSort, pTab, nSize * sizeof( int ) );

#ifdef _DEBUG_
        printf( "Przed posortowaniem:\n" );
        PrintTab( pTabSort, ( nSize > NPRINT ) ? NPRINT : nSize );
#endif

        int start = clock();
        pSortTab[i]( pTabSort, nSize );
        printf( "%s\tczas sortowania: %d ms\n", pTabNames[i], clock() - start );

#ifdef _DEBUG_
        printf( "Po posortowaniu:\n" ); 
        PrintTab( pTabSort, ( nSize > NPRINT ) ? NPRINT : nSize );
#endif
    }
    
    DeleteTab( &pTabSort );
    DeleteTab( &pTab );
    return 0;
}

int* CreateTab( int nSize )
{
    int* pTab = (int*)malloc( nSize * sizeof( int ) );
    if( !pTab ) return NULL;
    memset( pTab, 0, nSize * sizeof( int ) );
    return pTab;
}

void InitTab( int* pTab, int nSize )
{
    srand( (unsigned int)time( NULL ) );
    for( int i = 0; i < nSize; i++ )
    {
        *pTab++ = rand() % nSize;
    }       
}

void PrintTab( int* pTab, int nSize )
{
    for( int i = 0; i < nSize; i++ )
    {
        printf( "%5d ", *pTab++ );
        if( !( ( i + 1 ) % INROW ) ) printf( "\n" );
    }
    printf( "\n" );
}

void DeleteTab( int** pTab )
{
    free( *pTab );
    *pTab = NULL;
}